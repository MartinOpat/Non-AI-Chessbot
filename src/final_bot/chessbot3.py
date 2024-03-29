import chess
import chess.svg
import chess.pgn

import numpy as np
import time

from bisect import insort
from tables import *


def preprocess_openings(file_path):
    fen_to_best_move = {}
    with open(file_path, 'r') as file:
        for line in file:
            parts = line.strip().split(" | Score: ")
            moves_str, score_str = parts[0], parts[1]
            moves = moves_str.split()
            score = int(score_str)

            board = chess.Board()
            for move_san in moves:
                move = board.parse_san(move_san)
                
                # Generate FEN for the current position
                fen = board.fen()
                if fen not in fen_to_best_move:
                    fen_to_best_move[fen] = [(score, move)]
                else:
                    insort(fen_to_best_move[fen], (score, move), key=lambda x: x[0])
                board.push(move)

    return fen_to_best_move

class ChessBot3:
    def __init__(self, depth=2, time_limit=10):
        self.depth = depth
        self.time_limit = time_limit
        self.start_time = 0
        
        self.history_table = np.zeros((64, 64), dtype=np.int32)  # History scores for each possible move
        
        self.fen_to_best_move = preprocess_openings('better_filtered_openings.pgn')
        self.is_opening = True

    def update_history_score(self, move, depth):
        self.history_table[move.from_square][move.to_square] += depth ** 2

    def get_move_history_score(self, move):
        return self.history_table[move.from_square][move.to_square]
    
    def get_best_move(self, board):
        if self.is_opening:
            if board.fen() in self.fen_to_best_move:
                if board.turn == chess.WHITE:
                    best_move = self.fen_to_best_move[board.fen()][-1][1]  # Try randomly top 5 moves also
                else:
                    best_move = self.fen_to_best_move[board.fen()][0][1]
                return best_move
            self.is_opening = False

        # TODO: Make it smarter than just this
        if self.is_endgame(board):
            best_move = self.select_move(board, depth=self.depth+1, is_maximizing=board.turn == chess.WHITE)
        else:
            best_move = self.select_move(board, depth=self.depth, is_maximizing=board.turn == chess.WHITE)
        return best_move

    def select_move(self, board, depth=2, alpha=float('-inf'), beta=float('inf'), is_maximizing=True):
        legal_moves = list(board.legal_moves)
        legal_moves.sort(key=self.get_move_history_score, reverse=True)

        best_eval = float('-inf') if is_maximizing else float('inf')
        best_move = None
        for move in legal_moves:
            board.push(move)
            eval = self.__alpha_beta_minimax_helper(board, depth - 1, alpha, beta, not is_maximizing)
            board.pop()

            if is_maximizing and eval > best_eval:
                best_eval = eval
                best_move = move
            if not is_maximizing and eval < best_eval:
                best_eval = eval
                best_move = move

            if is_maximizing: alpha = max(alpha, eval)
            else: beta = min(beta, eval)
            if beta <= alpha:  
                    self.update_history_score(move, self.depth - depth)
                    break
        return best_move

    def __alpha_beta_minimax_helper(self, board, depth=3, alpha=float('-inf'), beta=float('inf'), is_maximizing=True):
        if depth == 0 or board.is_game_over():
            return self.evaluate_board(board, depth)
        
        legal_moves = list(board.legal_moves)
        legal_moves.sort(key=self.get_move_history_score, reverse=True)

        best_eval = float('-inf') if is_maximizing else float('inf')
        for move in legal_moves:
            board.push(move)
            eval = self.__alpha_beta_minimax_helper(board, depth - 1, alpha, beta, not is_maximizing)
            board.pop()

            best_eval = max(best_eval, eval) if is_maximizing else min(best_eval, eval)

            if is_maximizing: alpha = max(alpha, eval)
            else: beta = min(beta, eval)
            if beta <= alpha:
                self.update_history_score(move, self.depth - depth)
                break
        return best_eval

    def evaluate_board(self, board, depth): 
        global piece_values

        if board.is_checkmate():
            if board.turn == chess.WHITE:
                return -1e6 - depth
            else:
                return 1e6 + depth
        if board.is_stalemate() or board.is_insufficient_material() or board.is_fifty_moves() or board.is_repetition(3):
            return 0

        # Material values
        piece_square_tables = {
            chess.PAWN: PAWN_TABLE,
            chess.KNIGHT: KNIGHTS_TABLE,
            chess.BISHOP: BISHOPS_TABLE,
            chess.ROOK: ROOKS_TABLE,
            chess.QUEEN: QUEENS_TABLE,
            chess.KING: KINGS_TABLE_OPENING if not self.is_endgame(board) else KINGS_TABLE_ENDGAME,
        }

        boardvalue = 0
        for piece_type in piece_values.keys():
            for color in [chess.WHITE, chess.BLACK]:
                sign = 1 if color == chess.WHITE else -1
                pieces = board.pieces(piece_type, color)
                material_value = piece_values[piece_type] * len(pieces)
                positional_value = sum(piece_square_tables[piece_type][i] for i in pieces)
                if color == chess.WHITE:
                    positional_value = sum(piece_square_tables[piece_type][i] for i in pieces)
                else:  # Correctly mirror and apply positional values for black
                    positional_value = sum(piece_square_tables[piece_type][chess.square_mirror(i)] for i in pieces)
                boardvalue += sign * (material_value + positional_value)

        return boardvalue
    
    def is_endgame(self, board):
        has_queens = chess.QUEEN in board.piece_map().values()
        num_pieces = len(board.piece_map()) 
        return (not has_queens and num_pieces < 15) or num_pieces < 12
    
    # TODO: Endgames aren't working properly => Increase depth
    # TODO: It didn't take a free rook for some reason, it also didn't see that the rook was for hanging (there might be a small mistake somewhere)
    # TODO: Add previous calcs. memoization
    # TODO: After adding memoization, add iterative deepening
    # TODO: Missed mate in 1: 4Q3/8/8/1Q6/8/4K3/k4P2/8 w - - 3 73    


board = chess.Board()
board.set_fen("r6r/1p1bkpp1/pN2p2p/8/8/1PnBPP2/P5PP/R4RK1 b - - 1 18")

bot = ChessBot3(depth=4)
print(bot.get_best_move(board))