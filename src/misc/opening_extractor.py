import chess.pgn
import io

def extract_openings(pgn_text, move_limit=10):
    unique_openings = set()
    pgn = io.StringIO(pgn_text)
    while True:
        game = chess.pgn.read_game(pgn)
        if game is None:
            break
        board = game.board()
        moves = []
        for move in game.mainline_moves():
            if len(moves) >= move_limit * 2:  # Assuming move_limit moves per side
                break
            moves.append(board.san(move))
            board.push(move)
        opening_sequence = " ".join(moves)  # Convert list of moves to a single string
        unique_openings.add(opening_sequence)
    return unique_openings


file_name = input()
with open(f'databases/{file_name}.pgn', 'r', encoding='utf-8') as file:
    pgn_content = file.read()

with open(f'databases/openings_{file_name}.pgn', 'w', encoding='utf-8') as file:
    for opening in extract_openings(pgn_content):
        file.write(opening + '\n')