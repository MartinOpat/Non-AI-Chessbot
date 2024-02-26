# Non-AI-Chessbot
Made using https://github.com/Disservin/chess-library
C++ chess bot with a Python wrapper into pychess.

Executable can be compiled as `make clean exe`
Library file (.so) for use in python can be compiled as `make clean && make` 

## Bot implements:
* Custom-made opening book made from openings of Karpov, Kasparov, and Tal
* Negamax algorithm (alpha-beta pruning)
* iterative deepening
* transposition table
* Move orderings based on cut-off history and transposition table
* Quiescence search 
* Custom evaluation function 
* Piece-position tables