#include "openings.h"

std::map<std::string, std::vector<ScoreMovePair>> loadOpeningsFromFile(const std::string& file_path) {
    std::map<std::string, std::vector<ScoreMovePair>> fenToBestMove;
    std::ifstream file(file_path);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return fenToBestMove; // Return empty map if file can't be opened
    }

    while (getline(file, line)) {
        auto delimiterPos = line.find(" | Score: ");
        std::string movesStr = line.substr(0, delimiterPos);
        int score = std::stoi(line.substr(delimiterPos + 10)); // "+ 10" to skip past " | Score: "

        chess::Board board; // Assuming Board is a suitable type for your chess library
        std::istringstream movesStream(movesStr);
        std::string moveSan;
        while (movesStream >> moveSan) {
            chess::Move move = chess::uci::parseSan(board, moveSan); // Assuming parseSan is a method to parse SAN move notation

            std::string fen = board.getFen(); // Assuming toFen generates a FEN string for the board state
            board.makeMove(move); // Assuming makeMove applies a move to the board

            ScoreMovePair pair(score, move);
            auto& movesList = fenToBestMove[fen];
            if (movesList.empty() || std::find_if(movesList.begin(), movesList.end(), [&pair](const ScoreMovePair& existingPair) {
                return existingPair.move == pair.move;}) == movesList.end()) {
                movesList.push_back(pair);
            }

        }

    }
    // Sorting each vector of moves by score after all moves are inserted
    for (auto& [fen, pairs] : fenToBestMove) {
        std::sort(pairs.begin(), pairs.end());
    }

    file.close();
    return fenToBestMove;
}