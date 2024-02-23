import chess
import chess.svg
import chess.pgn

from time import sleep
import time
import numpy as np

import sys
sys.setrecursionlimit(10**9)

from chessbot2 import ChessBot2
from chessbot3 import ChessBot3
from cppChessbot import ChessBot4

from PyQt5.QtSvg import QSvgWidget
from PyQt5.QtWidgets import QApplication, QWidget


class MainWindow(QWidget):
    def __init__(self, board):
        super().__init__()

        self.setGeometry(100, 100, 1100, 1100)

        self.widgetSvg = QSvgWidget(parent=self)
        self.widgetSvg.setGeometry(10, 10, 1080, 1080)

        self.chessboard = board

        self.update_svg()

    def update_svg(self):
        self.chessboardSvg = chess.svg.board(self.chessboard).encode("UTF-8")
        self.widgetSvg.load(self.chessboardSvg)




board = chess.Board()
app = QApplication([])
mw = MainWindow(board)
mw.show()
QApplication.processEvents()

# MAKE SURE DEPTH IS EVEN, OTHERWISE BAD THINGS HAPPEN
whiteBot = ChessBot3(depth=4)
blackBot = ChessBot4(depth=4)

white_time = 0
black_time = 0

# Example game loop
while not board.is_game_over():
    try:
        # white
        start_time = time.time()
        move = blackBot.get_best_move(board.fen())
        end_time = time.time()
        white_time += end_time - start_time
        board.push(chess.Move.from_uci(move))

        print("White's so far time:", white_time)
        mw.update_svg()
        QApplication.processEvents()

        # black
        start_time = time.time()
        move = whiteBot.get_best_move(board)
        end_time = time.time()
        black_time += end_time - start_time
        board.push(move)

        print("Black's so far time:", black_time)
        mw.update_svg()
        QApplication.processEvents()

    except Exception as e:
        print(e)
        break
    except KeyboardInterrupt:
        print("Game ended by lack of patience")
        break
        
game = chess.pgn.Game()
game.headers["Event"] = "Self Game"
game.headers["White"] = "White"
game.headers["Black"] = "Black"

# Use the board's move stack to set up the game's moves
game.setup(board)
game = game.from_board(board)

# Export the game to PGN format
exporter = chess.pgn.StringExporter(headers=True, variations=True, comments=True)
pgn_string = game.accept(exporter)

# Print the game in PGN format
print(pgn_string)

print("White's total time:", white_time)
print("Black's total time:", black_time)
