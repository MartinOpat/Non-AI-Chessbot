import chess
import chess.svg
import chess.pgn

from PyQt5.QtSvg import QSvgWidget
from PyQt5.QtWidgets import QApplication, QWidget, QLineEdit, QPushButton, QVBoxLayout

from wrapper import ChessBot


class MainWindow(QWidget):
    def __init__(self, board, move_made_callback=None):  # Accept a callback for move made
        super().__init__()
        # Existing initialization code...
        self.move_made_callback = move_made_callback

        # Set the main window geometry
        self.setGeometry(100, 100, 1100, 1250)  # Adjust total height to fit board and controls

        # Initialize chessboard SVG widget
        self.widgetSvg = QSvgWidget(parent=self)
        self.widgetSvg.setGeometry(10, 10, 1080, 1080)  # Chessboard position and size

        # Initialize input for player's moves and submit button
        self.moveInput = QLineEdit(self)
        self.submitButton = QPushButton('Submit Move', self)
        self.submitButton.clicked.connect(self.submit_move)  # Connect button to the slot

        # Set geometry for input and button below the chessboard
        self.moveInput.setGeometry(10, 1100, 1080, 40)  # Position input box
        self.submitButton.setGeometry(10, 1150, 1080, 40)  # Position submit button

        self.chessboard = board
        self.update_svg()

    def update_svg(self):
        # Update the SVG representation of the chessboard
        self.chessboardSvg = chess.svg.board(self.chessboard).encode("UTF-8")
        self.widgetSvg.load(self.chessboardSvg)

    def submit_move(self):
        raw_move = self.moveInput.text().strip()
        if raw_move:
            try:
                move = self.chessboard.parse_san(raw_move)
                if move in self.chessboard.legal_moves:
                    self.chessboard.push(move)
                    self.update_svg()
                    self.moveInput.clear()  # Clear input after move
                    if self.move_made_callback:  # Check if the callback is provided
                        self.move_made_callback()  # Call the callback
                else:
                    print("Illegal move, try again")
            except ValueError:
                print("Invalid move format, try again")
                self.moveInput.clear()  # Clear input if invalid


board = chess.Board("rnb1kb1r/5ppp/pq1p1p2/1p1P4/2pNP3/2N4P/PPP2PP1/R2QKB1R w KQkq - 0 11")
app = QApplication([])
QApplication.processEvents()

bot = ChessBot()
human_turn = board.turn == chess.BLACK  # True if white, False if black

def human_move_made():
    global human_turn  # Use global to modify the variable outside of the function
    human_turn = False  # Set to False as the human has made their move

mw = MainWindow(board, move_made_callback=human_move_made)  # Pass the callback to MainWindow
mw.show()
QApplication.processEvents()

while not board.is_game_over(claim_draw=False):
    QApplication.processEvents()  # Ensure GUI updates including move submission
    if human_turn:
        continue  # Skip to the next iteration of the loop, waiting for human move
    else:
        # Bot's turn
        move = bot.__call__(board.fen())
        board.push(move)
        mw.update_svg()
        human_turn = True  # Change back to human's turn


game = chess.pgn.Game()
game.headers["Event"] = "Human vs Bot"
game.headers["White"] = "Human" if board.turn == chess.BLACK else "Bot"
game.headers["Black"] = "Bot" if board.turn == chess.BLACK else "Human"
game.setup(board)
game = game.from_board(board)
exporter = chess.pgn.StringExporter(headers=True, variations=True, comments=True)
pgn_string = game.accept(exporter)
print(pgn_string)
