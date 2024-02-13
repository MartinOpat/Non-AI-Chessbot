# Remove all openings that end in a score difference
# greater than x (centipawns)

with open("openings_filtered.pgn", "r") as file:
    openings = file.readlines()
    filtered_openings = []
    for opening in openings:
        if "Score:" in opening:
            score = int(opening.split("Score:")[1].strip())
            if abs(score) < 35:
                filtered_openings.append(opening)
        else:
            filtered_openings.append(opening)

# Write the filtered_openings into a file
with open("better_filtered_openings.pgn", "w") as file:
    file.writelines(filtered_openings)