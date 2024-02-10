**Ideas**:

- Implement basic openings

- Try checks and captures first

- Try best move from previous iteration first

- Implement a hash table of previous position (FEN might be a solid hash ?) => beware the possibility of sub-optimal "best" move if not all information considered (castling right, 3-fold repetition) => EPD might fix that

- Aspiration windows (stockfish uses), but needs more research => Zero windows search (MTDF(f)), kinda seems like binary search on alpha & beta

- IDDFS can be used to improve alpha-beta prunning but idk how yet, needs research

- Negamax (NegaScout): First try the best move as determined by previous (shallower) iteration as the first one. Assume it is best, try to prove this by searching the rest of the tree using zero window search. If fails, continue regular alpha-beta prunning (https://en.wikipedia.org/wiki/Principal_variation_search)


