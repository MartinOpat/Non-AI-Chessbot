

def remove_metadata_from_pgn(file_content):
    """
    Remove metadata from PGN chess file content and keep only the game moves.
    """
    games = file_content.split("\n\n")  # Split into games based on double newline
    cleaned_games = []

    for game in games:
        # Each game is separated into metadata (lines with brackets) and moves (the rest)
        lines = game.split("\n")
        moves = [line for line in lines if not line.startswith("[") and line.strip() != ""]
        cleaned_game = "\n".join(moves).strip()
        if cleaned_game:  # Check if there is any move data left after stripping metadata
            cleaned_games.append(cleaned_game)

    return "\n\n".join(cleaned_games)  # Join games back with double newline


file_name = input()
with open(f'databases/{file_name}.pgn', 'r', encoding='ISO-8859-1') as file:
    pgn_content = file.read()

cleaned_pgn = remove_metadata_from_pgn(pgn_content)

# To save the cleaned content back to a file
with open(f'databases/cleaned_{file_name}.pgn', 'w', encoding='utf-8') as file:
    file.write(cleaned_pgn)
