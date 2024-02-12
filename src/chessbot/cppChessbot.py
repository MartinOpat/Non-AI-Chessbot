from ctypes import cdll, c_char_p, POINTER, c_void_p, c_int, c_char, cast

lib = cdll.LoadLibrary("./chessbot4.so")

# Define argument and return types for the imported functions
lib.new_chessbot.argtypes = [c_int]
lib.new_chessbot.restype = POINTER(c_void_p)  # Assuming ChessBot3* is treated as void*

lib.delete_chessbot.argtypes = [POINTER(c_void_p)]
lib.delete_chessbot.restype = None

lib.get_best_move.argtypes = [POINTER(c_void_p), c_char_p]
lib.get_best_move.restype = POINTER(c_char)  # Treat the return type as a pointer to char


lib.free_allocated_memory.argtypes = [c_char_p]
lib.free_allocated_memory.restype = None


class ChessBot4:
    def __init__(self, depth):
        self.obj = lib.new_chessbot(depth)
    
    def get_best_move(self, board_fen):
        result_ptr = lib.get_best_move(self.obj, board_fen.encode('utf-8'))
        move = cast(result_ptr, c_char_p).value.decode("utf-8")
        lib.free_allocated_memory(result_ptr)
        return move
    
    def __del__(self):
        lib.delete_chessbot(self.obj)


# bot = ChessBot4(4)
# print(bot.get_best_move("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"))