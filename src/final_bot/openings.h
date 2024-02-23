#ifndef OPENINGS_H
#define OPENINGS_H

#include <map>
#include <vector>
#include <string>
#include <fstream>

#include "chess-library/include/chess.hpp"



struct ScoreMovePair {
    int score;
    chess::Move move; // Assuming Move is a suitable type for your chess library

    ScoreMovePair(int score, chess::Move move) : score(score), move(move) {}
};

bool operator<(const ScoreMovePair& a, const ScoreMovePair& b) {
        return a.score < b.score;
}

bool operator>(const ScoreMovePair& a, const ScoreMovePair& b) {
    return a.score > b.score;
}

bool operator==(const ScoreMovePair& a, const ScoreMovePair& b) {
    return a.score == b.score && a.move == b.move;
}

bool operator!=(const ScoreMovePair& a, const ScoreMovePair& b) {
    return !(a == b);
}

std::map<std::string, std::vector<ScoreMovePair>> loadOpeningsFromFile(const std::string& file_path);

#endif // OPENINGS_H
