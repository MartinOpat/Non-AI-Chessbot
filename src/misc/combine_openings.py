

with open("databases/openings_cleaned_Karpov.pgn", "r", encoding="utf-8") as file:
    karpov = file.readlines()

with open("databases/openings_cleaned_Kasparov.pgn", "r", encoding="utf-8") as file:
    kasparov = file.readlines()

with open("databases/openings_cleaned_Tal.pgn", "r", encoding="utf-8") as file:
    tal = file.readlines()


openings = karpov + kasparov + tal

# Remove duplicate lines
openings = list(set(openings))

# Remove lines that are prefixes of other lines. Suffixes and other substrings are not removed.
openings.sort(key=len)
openings = [opening for i, opening in enumerate(openings) if not any(other.startswith(opening.rstrip('\n')) for other in openings[i+1:])]


# Write openings to a file
with open("databases/openings_all.pgn", "w", encoding="utf-8") as file:
    for opening in openings:
        file.write(opening)
