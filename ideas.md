**Ideas**:

- Endgame tables are too large -> Implement endgame mating heuristics

- Try checks and captures first

- Try best move from previous iteration first

- Do https://en.wikipedia.org/wiki/Killer_heuristic for endgames

- Implement a hash table of previous position (FEN might be a solid hash ?) => beware the possibility of sub-optimal "best" move if not all information considered (castling right, 3-fold repetition) => EPD might fix that
- (https://en.wikipedia.org/wiki/Transposition_table#Related_techniques ?)

- Aspiration windows (stockfish uses), but needs more research => Zero windows search (MTDF(f)), kinda seems like binary search on alpha & beta

- IDDFS can be used to improve alpha-beta prunning but idk how yet, needs research

- Negamax (NegaScout): First try the best move as determined by previous (shallower) iteration as the first one. Assume it is best, try to prove this by searching the rest of the tree using zero window search. If fails, continue regular alpha-beta prunning (https://en.wikipedia.org/wiki/Principal_variation_search)  ... This did not turn out to be much better than minimax, we can try it again, more robust and see if it can go deeper

- Try the TSP

- Look into how to actually make it faster so that we can go deeper

- Quiescence Search: Implement a quiescence search that continues the search in positions with    possible tactical sequences (captures and checks), to avoid evaluating unstable positions.

- Transposition Table: Use a hash table to store previously evaluated positions (identified by a Zobrist hash or similar) and their evaluation. This can save time if the same position is reached through different move orders.


# AI-ed suggestions:
!

Implementing advanced evaluation and search strategies in a C++ chess bot, building upon an existing alpha-beta pruning framework, involves several key components. Given that all basic chess functionalities and an alpha-beta pruning algorithm are already in place, we'll focus on enhancing the bot's decision-making capabilities through better move prioritization, evaluation enhancements, and search optimizations. This will involve diving into more sophisticated techniques for move generation, evaluation functions, and search heuristics.
1. Enhancing the Evaluation Function

Your evaluation function is crucial for determining the positional value of a board state. To make it more sophisticated, consider these aspects:

    Material Evaluation: Ensure your evaluation function accurately values each piece according to its role in the current phase of the game (opening, middlegame, endgame). This might involve dynamic weighting, where the importance of certain pieces changes based on the game's stage.

    Positional Features: Incorporate advanced positional features into your evaluation:
        Pawn Structure: Analyze doubled, isolated, and backward pawns, and identify passed pawns, rewarding or penalizing these conditions appropriately.
        King Safety: Include considerations for king safety, such as the presence of pawn shields, control of surrounding squares, and potential attacking paths against the king.
        Mobility and Piece Activity: Evaluate the mobility of pieces, rewarding positions where pieces control key squares, especially in the center, and penalize pieces that are blocked or inactive.
        Control of Key Squares: Include specific bonuses for control of central squares, outposts for knights, and open files for rooks.

Implementing these in C++ requires defining a set of functions or a comprehensive evaluation class that takes the current board state as input and outputs a numerical score. Use bitboards for efficient board representation and calculation of moves and positions.
2. Move Ordering

To enhance your alpha-beta pruning efficiency, implement move ordering:

    Captures and Promotions: Prioritize captures, especially those that are winning material (use the "Most Valuable Victim - Least Valuable Aggressor" principle), followed by promotions.
    Killer Moves: Implement a killer move heuristic, where you track moves that cause a beta-cutoff in other branches at the same depth. Store these moves and try them early in other branches.
    History Heuristic: Maintain a history score for moves that have previously caused cuts, and use this score to prioritize moves in future searches.

In C++, you might use a priority queue or sort your move list based on these criteria before feeding moves into the alpha-beta search.
3. Search Enhancements

Beyond standard alpha-beta pruning, consider these techniques:

    Iterative Deepening: Use iterative deepening to improve move ordering and time management, allowing you to stop the search gracefully when running out of time.
    Quiescence Search: Implement a quiescence search that continues the search in positions with possible tactical sequences (captures and checks), to avoid evaluating unstable positions.
    Transposition Table: Use a hash table to store previously evaluated positions (identified by a Zobrist hash or similar) and their evaluation. This can save time if the same position is reached through different move orders.

4. Practical Implementation Tips

    Efficient Data Management: Efficiently manage your chessboard representation, move generation, and undoing moves. Consider using a structure like a stack for moves to easily revert to previous states.
    Concurrency: Leverage parallel processing where possible. For example, you can split the root moves among different threads, each conducting its alpha-beta search.
    Testing and Tuning: Constantly test your engine against others and use these results to tune your evaluation parameters. Tools like cutechess-cli can automate running matches against other engines.