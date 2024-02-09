import chess
import chess.svg
import chess.pgn

import random
import math
from time import sleep
import numpy as np

import sys
sys.setrecursionlimit(10**9)

from IPython.display import clear_output, display

# Define piece values
piece_values = {chess.PAWN: 1, chess.KNIGHT: 3, chess.BISHOP: 3, chess.ROOK: 5, chess.QUEEN: 9, chess.KING: 0}

def get_eval_score(board):
    # Calculate material balance
    material_balance = sum(len(board.pieces(piece_type, chess.WHITE)) * value for piece_type, value in piece_values.items()) - \
                       sum(len(board.pieces(piece_type, chess.BLACK)) * value for piece_type, value in piece_values.items())
    return material_balance

def get_count_pieces_on_board(board):
    # Initialize a counter
    piece_count = 0

    # Iterate through all squares on the board
    for square in chess.SQUARES:
        # Check if there is a piece on the square
        if board.piece_at(square):
            # If yes, increment the counter
            piece_count += 1

    return piece_count


def get_count_total_material(board):
    return sum(len(board.pieces(piece_type, chess.WHITE)) * value for piece_type, value in piece_values.items()) + \
                       sum(len(board.pieces(piece_type, chess.BLACK)) * value for piece_type, value in piece_values.items())

class ChessBot:
    def __init__(self, temperature=1.0, is_white=True):
        self.temperature = temperature
        self.initial_temperature = temperature
        self.is_white = is_white

    def evaluate_board(self, board):
        # Simple evaluation function - you might want to develop a more sophisticated one
        if board.is_checkmate():
            return float("inf") if board.turn == chess.WHITE else float("-inf")
        if board.is_stalemate():
            return 0
        # Example: Just count the material balance for simplicity
        return get_eval_score(board)

    def minimax(self, board, depth, alpha, beta, maximizing_player):
        if depth == 0 or board.is_game_over():
            return self.evaluate_board(board)

        if maximizing_player:
            max_eval = float('-inf')
            for move in board.legal_moves:
                board.push(move)
                eval = self.minimax(board, depth - 1, alpha, beta, not maximizing_player)
                board.pop()
                max_eval = max(max_eval, eval)
                alpha = max(alpha, eval)
                if beta <= alpha:
                    break
            return max_eval
        else:
            min_eval = float('inf')
            for move in board.legal_moves:
                board.push(move)
                eval = self.minimax(board, depth - 1, alpha, beta, not maximizing_player)
                board.pop()
                min_eval = min(min_eval, eval)
                beta = min(beta, eval)
                if beta <= alpha:
                    break
            return min_eval

    def select_move(self, board):
        best_value = float('-inf') if self.is_white else float("inf")
        alpha = float('-inf')
        beta = float('inf')
        depth = 2 + (78 - get_count_total_material(board)) // 9  # 2078 = sum of initial balance of both players
        print(depth)

        moves = {}
        for move in board.legal_moves:
            board.push(move)
            move_value = self.minimax(board, depth, alpha, beta, not self.is_white)
            board.pop()

            # if (self.is_white and move_value > best_value) or (not self.is_white and move_value < best_value):
            #     best_value = move_value
            #     best_moves = [move]
            # elif move_value == best_value:
            #     best_moves.append(move)

            moves[move] = move_value
            best_value = max(best_value, move_value) if self.is_white else min(best_value, move_value)

        filtered_moves = {key: value for key, value in moves.items() if abs(value-best_value) <= self.temperature}
        moves = np.array(list(filtered_moves.keys()))
        move_scores = np.array(list(filtered_moves.values()))

        exp_scores = np.exp(-np.abs(move_scores - best_value))
        probabilities = exp_scores / np.sum(exp_scores)

        # Choose a move based on the calculated probabilities
        chosen_move = np.random.choice(moves, p=probabilities)

        # Adjust temperature for the next move
        self.temperature = max(0, self.temperature - 0.1)

        return chosen_move


  # TODO: Actually make it be able to mate, it misses a mate in 1 still
  # TODO: Queen still gets randomly taken
  # TODO: Make loosing castling possibility be a bad thing
  # TODO: Slows down too much too quickly

"""## Play against self"""

# Example usage
whiteBot = ChessBot(temperature=0)
blackBot = ChessBot(temperature=0, is_white=False)

board = chess.Board()
# Example game loop
while not board.is_game_over():
    try:
        # white
        move = whiteBot.select_move(board)
        board.push(move)

        clear_output(wait=True)
        display(board)
        sleep(1)

        # black
        move = blackBot.select_move(board)
        board.push(move)

        clear_output(wait=True)
        display(board)
        sleep(1)

    except:
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
exit(0)

# Print the game in PGN format
print(pgn_string)

"""## Play against human"""

import ipywidgets as widgets

# Assuming ChessBot is defined elsewhere and initialized as blackBot
# blackBot = ChessBot(temperature=1.0, is_white=False)
board = chess.Board()

# Function to handle the human move submission
def on_move_submitted(b):
    global board  # Refer to the global board variable

    # Process the human move
    move_str = move_input.value
    move = chess.Move.from_uci(move_str)
    if move in board.legal_moves:
        board.push(move)
        update_display()
        if not board.is_game_over():
            # Bot makes its move here
            bot_move = blackBot.select_move(board)
            board.push(bot_move)
            update_display()
    else:
        print("Illegal move. Please try again.")

    move_input.value = ''  # Clear the input field

# Function to update the display of the board and input widgets
def update_display():
    clear_output(wait=True)
    print("Current board:")
    display(board)
    if board.is_game_over():
        print("Game over:", board.result())
    else:
        display(move_input, submit_button)

# Create the widgets for move input and submission
move_input = widgets.Text(
    description='Your move:',
    placeholder='e2e4',
    disabled=False
)
submit_button = widgets.Button(
    description='Submit',
    button_style='',  # Options: 'success', 'info', 'warning', 'danger', ''
    tooltip='Submit your move',
)

# Bind the button click event to the move submission function
submit_button.on_click(on_move_submitted)

# Initial display
update_display()
