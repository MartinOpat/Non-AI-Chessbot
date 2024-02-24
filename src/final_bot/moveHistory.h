#ifndef MOVEHISTORY_H
#define MOVEHISTORY_H

#include "chess-library/include/chess.hpp"
#include "utils.h"

#include <set>
#include <algorithm>

using namespace chess;
using Score = int;

// Assuming chess::Move and ScoreMovePair are defined elsewhere as provided.
// Define a custom comparator for the set to sort ScoreMovePairs in descending order.
struct DescendingScoreComparator {
    bool operator()(const ScoreMovePair& a, const ScoreMovePair& b) const {
        return a.score > b.score; // Descending order by score.
    }
};

// A node in the move history tree.
struct MoveNode {
    ScoreMovePair data; // This node's move and score.
    std::set<MoveNode, DescendingScoreComparator> children; // Children of this node.

    // Constructor
    MoveNode(int score, Move move) : data(score, move) {}

    // Function to add a child node to this node.
    void addChild(const MoveNode& child) {
        children.insert(child);
    }
};

enum class NodeType {
    EXACT, LOWERBOUND, UPPERBOUND
};

struct TTEntry {
    int score;              // Evaluated score of the position
    int depth;              // Depth of the search from which the score was derived
    NodeType flag;               // Type of node (EXACT, LOWERBOUND, UPPERBOUND)
    Move bestMove;          // Best move for this position
};

#endif // MOVEHISTORY_H
