import chess
import chess.pgn

def is_opening_legal(opening):
    board = chess.Board()
    for move_san in opening.split():
        try:
            move = board.parse_san(move_san)
            if move not in board.legal_moves:
                return False
            board.push(move)
        except ValueError:
            # The move is not legal or not correctly formatted
            return False
    return True

def filter_illegal_openings(input_file_path, output_file_path):
    with open(input_file_path, 'r', encoding='utf-8') as input_file, \
         open(output_file_path, 'w', encoding='utf-8') as output_file:
        
        for line in input_file:
            opening = line.strip()
            if is_opening_legal(opening):
                output_file.write(opening + "\n")

# Example usage
input_file_path = 'databases/openings_all.pgn'  # Path to your file containing openings
output_file_path = 'databases/openings_legal.pgn'  # Path where you want to save the filtered openings

filter_illegal_openings(input_file_path, output_file_path)

print("Filtered openings have been saved.")

