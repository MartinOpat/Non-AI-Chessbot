import chess
import chess.engine
import chess.pgn
import concurrent.futures


BLUNDER_THRESHOLD = -20
STOCKFISH_PATH = 'stockfish/stockfish-ubuntu-x86-64-avx2'
NUM_THREADS = 16  # Number of threads to use for parallel analysis

def analyze_moves_of_game(moves):
    final_score = None  # Initialize final score
    with chess.engine.SimpleEngine.popen_uci(STOCKFISH_PATH) as engine:
        board = chess.Board()
        for move_san in moves:
            try:
                move = board.parse_san(move_san)
                acceptable, move_score = analyze_move(engine, board, move)
                if not acceptable:
                    return False, None
                board.push(move)
                final_score = move_score  # Update final score after each move
            except ValueError:
                return False, None
    return True, final_score  # Return final score if opening is acceptable

def analyze_move(engine, board, move, threshold=BLUNDER_THRESHOLD):
    info = engine.analyse(board, chess.engine.Limit(depth=16))
    score_before = info.get("score")
    
    board.push(move)
    info_after = engine.analyse(board, chess.engine.Limit(depth=16))
    board.pop()
    
    score_after = info_after.get("score")
    
    if not score_before or not score_after:
        return True, None  # Assume move is acceptable if score is not available
    
    score_diff = score_before.relative.score(mate_score=10000) - score_after.relative.score(mate_score=10000)
    acceptable = score_diff > threshold if board.turn == chess.WHITE else score_diff < threshold
    final_score = score_after.relative.score(mate_score=10000)
    return acceptable, final_score

def filter_openings_parallel(file_path, output_file_path):
    with open(file_path, 'r') as f:
        lines = f.readlines()
    
    total_lines = len(lines)
    print(f"Total lines to process: {total_lines}")

    def process_line(index_and_line):
        index, line = index_and_line
        if index and index % (total_lines // 100) == 0:  # Update for every 1%
            print(f"Processing... {index / total_lines * 100:.2f}% completed")
        is_acceptable, final_score = analyze_moves_of_game(line.strip().split())
        return is_acceptable, line, final_score

    # Split the work among threads
    with concurrent.futures.ThreadPoolExecutor(max_workers=NUM_THREADS) as executor:
        futures = [executor.submit(process_line, (index, line)) for index, line in enumerate(lines)]
        results = [future.result() for future in concurrent.futures.as_completed(futures)]

    # Write the filtered results and store scores
    with open(output_file_path, 'w') as out_f:
        for is_acceptable, line, score in results:
            if is_acceptable:
                out_f.write(f"{line.strip()} | Score: {score}\n")

# Example usage
input_pgn = 'databases/openings_legal.pgn'  # Path to your input PGN file with games
output_pgn = 'databases/openings_filtered.pgn'  # Path to save the filtered PGN file
filter_openings_parallel(input_pgn, output_pgn)

print(f"Filtered PGN games have been saved to {output_pgn}")

