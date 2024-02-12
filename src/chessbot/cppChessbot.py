from ctypes import cdll, c_int, POINTER, c_string

lib = cdll.LoadLibrary("./chessbot3.so")

class Chessbot4:
    def __init__(self, depth=4):
        self.obj  = lib.new_chessbot(depth)

    def get_best_move(self, board):
        return lib.get_best_move(self.obj, board.fen())  # Due to the conversion 3-fold repetition might be an issue
    