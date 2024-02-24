import chess
import random
from abc import ABC, abstractmethod

from ctypes import *

lib = cdll.LoadLibrary("./chessbot4.so")

# Define the correct argument and return types for the C++ functions
lib.createBot.argtypes = None
lib.createBot.restype = c_void_p  # Correct: Bot* is returned as a void pointer

lib.deleteBot.argtypes = [c_void_p]  # Correct: Directly pass the void pointer
lib.deleteBot.restype = None

# This is where we expect the returned type to be a pointer to the characters
lib.getBestMove.argtypes = [c_void_p, c_char_p]  # Bot instance and FEN string
lib.getBestMove.restype = POINTER(c_char)  # POINTER(c_char) if memory management is manual

lib.freeMemory.argtypes = [POINTER(c_char)]  # Correctly match the pointer type for freeing
lib.freeMemory.restype = None

class ChessBotClass(ABC):
    @abstractmethod
    def __call__(self, board_fen: str) -> chess.Move:
        pass


# keep the bot named ChessBot when submitting
class ChessBot(ChessBotClass):
    def __init__(self):
        self.obj = lib.createBot()

    def __call__(self, boardFen):
        resultPtr = lib.getBestMove(self.obj, boardFen.encode('utf-8'))
        # Ensure the result pointer is valid
        if not resultPtr:
            raise Exception("Failed to get best move from the engine.")
        # Convert the result to a Python string
        move = cast(resultPtr, c_char_p).value.decode("utf-8")
        # Free the memory allocated by the C++ function
        lib.freeMemory(resultPtr)
        # Convert and return the move
        return chess.Move.from_uci(move)
    
    def __del__(self):
        if self.obj:
            lib.deleteBot(self.obj)
