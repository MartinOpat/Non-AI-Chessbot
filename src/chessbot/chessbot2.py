import chess
import chess.svg
import chess.pgn

class ChessBot2:
    def __init__(self, depth=2):
        self.depth = depth

    def get_best_move(self, board):
        # Make it smarter than just this
        if self.is_endgame(board):
            best_move = self.select_move(board, depth=self.depth+1, is_maximizing=board.turn == chess.WHITE)
        else:
            best_move = self.select_move(board, depth=self.depth, is_maximizing=board.turn == chess.WHITE)
        return best_move

    def make_move(self, board):
        best_move = self.get_best_move(board)
        board.push(best_move)

    def select_move(self, board, depth=2, alpha=float('-inf'), beta=float('inf'), is_maximizing=True):
        if is_maximizing:
            max_eval = float('-inf')
            best_move = None
            for move in board.legal_moves:
                board.push(move)
                eval = self.__alpha_beta_minimax_helper(board, depth - 1, alpha, beta, False)
                board.pop()
                if eval > max_eval:
                    max_eval = eval
                    best_move = move
                alpha = max(alpha, eval)
                if beta <= alpha:  # TODO: should this be the condition for both case ?
                    break
            return best_move
        else:
            min_eval = float('inf')
            for move in board.legal_moves:
                board.push(move)
                eval = self.__alpha_beta_minimax_helper(board, depth - 1, alpha, beta, True)
                board.pop()
                if eval < min_eval:
                    min_eval = eval
                    best_move = move
                beta = min(beta, eval)
                if beta <= alpha:
                    break
            return best_move

    def __alpha_beta_minimax_helper(self, board, depth=3, alpha=float('-inf'), beta=float('inf'), is_maximizing=True):
        if depth == 0 or board.is_game_over():
            return self.evaluate_board(board, depth)

        if is_maximizing:
            max_eval = float('-inf')
            for move in board.legal_moves:
                board.push(move)
                eval = self.__alpha_beta_minimax_helper(board, depth - 1, alpha, beta, False)
                board.pop()
                max_eval = max(max_eval, eval)
                alpha = max(alpha, eval)
                if beta <= alpha:  # TODO: should this be the condition for both case ?
                    break
            return max_eval
        else:
            min_eval = float('inf')
            for move in board.legal_moves:
                board.push(move)
                eval = self.__alpha_beta_minimax_helper(board, depth - 1, alpha, beta, True)
                board.pop()
                min_eval = min(min_eval, eval)
                beta = min(beta, eval)
                if beta <= alpha:
                    break
            return min_eval

    def evaluate_board(self, board, depth): 
        global piece_values

        if board.is_checkmate():
            if board.turn == chess.WHITE:
                return -1e6 - depth
            else:
                return 1e6 + depth
        if board.is_stalemate() or board.is_insufficient_material() or board.is_fifty_moves() or board.is_repetition(3):
            0
        
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
    # TODO: It very suspiciously lost a knight as white