#include <tuple> 

#include "endgames.h"

using namespace chess;

int evaluateKXK(const Board& board, Color strongSide) {
    Square strongKing = Square(board.pieces(PieceType::KING, strongSide).lsb());
    Square weakKing = Square(board.pieces(PieceType::KING, ~strongSide).lsb());

    int score = pushToEdge(weakKing); // Encourage driving king to edge
    score += pushClose(strongKing, weakKing); // Encourage closing distance between kings

    Bitboard strongPieces = board.us(strongSide) ^ board.pieces(PieceType::KING, strongSide);
    while (strongPieces) {
        Square pieceSquare = Square(strongPieces.lsb());
        score -= Square::distance(pieceSquare, strongKing);
        strongPieces.clear(pieceSquare.index());
    }
    score -= evaluateKingSafety(board, ~strongSide);
    score += pushToEdge(weakKing);


    return strongSide == Color::WHITE ? score : -score;
}

int evaluateKBNK(const Board& board, Color strongSide) {
    Square strongKing = Square(board.pieces(PieceType::KING, strongSide).lsb());
    Square weakKing = Square(board.pieces(PieceType::KING, ~strongSide).lsb());
    Square bishop = Square(board.pieces(PieceType::BISHOP, strongSide).lsb());

    int score = pushClose(strongKing, weakKing);
    if (isSquareWhite(bishop)) {
        score += pushToCorner(weakKing, Color::WHITE); 
    } else {
        score += pushToCorner(weakKing, Color::BLACK); 
    }

    return strongSide == Color::WHITE ? score : -score;
}

int evaluateKPK(const Board& board, Color strongSide) {
    Square strongKing = Square(board.pieces(PieceType::KING, strongSide).lsb());
    Square weakKing = Square(board.pieces(PieceType::KING, ~strongSide).lsb());
    Square pawnSquare = Square(board.pieces(PieceType::PAWN, strongSide).lsb());

    // Normalize board for strongSide to be white and pawn direction upwards
    if (strongSide == Color::BLACK) {
        strongKing = flipSquare(strongKing);
        weakKing = flipSquare(weakKing);
        pawnSquare = flipSquare(pawnSquare);
    }

    // Check for stalemate and other draw conditions
    if (isDraw(board) || canPromote(board, strongSide, pawnSquare)) {
        return 0; // Draw
    }

    // Use your method to convert squares into your board's coordinate system if needed
    int score = Value::WIN + Value::PAWN_EG + pawnSquare.rank(); // Adjust for your engine's scoring

    return (strongSide == Color::WHITE) ? score : -score;
}

int evaluateKNNK(const Board& board, Color strongSide) {
    // Typically a draw, but you might score slight advantages for pushing the weak king to the edge
    Square weakKing = Square(board.pieces(PieceType::KING, ~strongSide).lsb());
    Square strongKing = Square(board.pieces(PieceType::KING, strongSide).lsb());

    int score = pushToCorner(weakKing, Color::WHITE);
    score += pushClose(strongKing, weakKing); 
    
    return (strongSide == Color::WHITE) ? score : -score;
}

int evaluateKRKP(const Board& board, Color strongSide) {
    Square strongKing = Square(board.pieces(PieceType::KING, strongSide).lsb());
    Square weakKing = Square(board.pieces(PieceType::KING, ~strongSide).lsb());
    Square rookSquare = Square(board.pieces(PieceType::ROOK, strongSide).lsb());
    Square pawnSquare = Square(board.pieces(PieceType::PAWN, ~strongSide).lsb());

    int score = Value::ROOK_EG - Square::distance(strongKing, pawnSquare);

    if (Square::distance(weakKing, pawnSquare) > 1 || Square::distance(weakKing, rookSquare) > 2) {
        score += 200;
    }

    // Adjusting for pawn promotion based on color
    Rank promotionRank = (strongSide == Color::WHITE) ? Rank(1) : Rank(6); // Assuming Rank(1) is the 8th rank for black and Rank(6) is the 2nd rank for white
    if (pawnSquare.rank() == promotionRank) {
        score -= 500;
    }

    return (strongSide == Color::WHITE) ? score : -score;
}

int evaluateKRKB(const Board& board, Color strongSide) {
    Square weakKing = Square(board.pieces(PieceType::KING, ~strongSide).lsb());
    // Push the king to the edge of the board for better chances of winning
    int score = pushToEdge(weakKing); // Implement based on your engine's metrics

    // This score can be adjusted based on further analysis or specific position checks
    return (strongSide == Color::WHITE) ? score : -score;
}

int evaluateKRKN(const Board& board, Color strongSide) {
    Square weakKing = Square(board.pieces(PieceType::KING, ~strongSide).lsb());
    Square weakKnight = Square(board.pieces(PieceType::KNIGHT, ~strongSide).lsb());
    // Generally winning, but distance from knight and king matters for practical chances
    int score = pushToEdge(weakKing) + pushAway(weakKing, weakKnight);

    return (strongSide == Color::WHITE) ? score : -score;
}

int evaluateKBBK(const Board& board, Color strongSide) {
    Square strongKing = Square(board.pieces(PieceType::KING, strongSide).lsb());
    Square weakKing = Square(board.pieces(PieceType::KING, ~strongSide).lsb());
    Bitboard bishops = board.pieces(PieceType::BISHOP, strongSide);

    int index = bishops.lsb();
    Square bishop1 = Square(index);
    bishops.clear(index);
    Square bishop2 = Square(bishops.lsb());

    int score = 0;
    score += pushToEdge(weakKing);
    score += pushClose(strongKing, weakKing);
    score += controlCornerWeakKing(bishop1, bishop2, weakKing);

    return (strongSide == Color::WHITE) ? score : -score;
}


// Atm the endgames are not limited to strictly to contain only the pieces mentioned. If it ain't working, look into this
EndgameType::Type detectEndgameType(const Board& board) {
    // Calculate total material for both sides
    Bitboard whiteTotal = board.us(Color::WHITE);
    Bitboard blackTotal = board.us(Color::BLACK);

    // Count pieces for both sides using the provided Bitboard class
    Bitboard whitePawns = board.pieces(PieceType::PAWN, Color::WHITE);
    Bitboard blackPawns = board.pieces(PieceType::PAWN, Color::BLACK);
    Bitboard whitePieces = board.us(Color::WHITE) ^ whitePawns; // All white pieces except pawns
    Bitboard blackPieces = board.us(Color::BLACK) ^ blackPawns; // All black pieces except pawns

    if (!whitePawns.empty() && blackPieces.empty() && whitePieces.count() == 1) {
        return EndgameType::KPK; // King and Pawn vs. King
    }
    if (!blackPawns.empty() && whitePieces.empty() && blackPieces.count() == 1) {
        return EndgameType::KPK; // King vs. King and Pawn
    }

    // Additional checks for other endgames
    Bitboard whiteBishops = board.pieces(PieceType::BISHOP, Color::WHITE);
    Bitboard blackBishops = board.pieces(PieceType::BISHOP, Color::BLACK);
    Bitboard whiteKnights = board.pieces(PieceType::KNIGHT, Color::WHITE);
    Bitboard blackKnights = board.pieces(PieceType::KNIGHT, Color::BLACK);
    Bitboard whiteRooks = board.pieces(PieceType::ROOK, Color::WHITE);
    Bitboard blackRooks = board.pieces(PieceType::ROOK, Color::BLACK);

    // KNNK - one king and two knights vs. one king
    if (whiteKnights.count() == 2 && blackPieces.count() == 1) {
        return EndgameType::KNNK;
    }
    if (blackKnights.count() == 2 && whitePieces.count() == 1) {
        return EndgameType::KNNK;
    }

    // KRKP - one king and one rook vs. one king and one pawn
    if (whiteRooks.count() == 1 && blackPawns.count() == 1 && blackPieces == blackPawns) {
        return EndgameType::KRKP;
    }
    if (blackRooks.count() == 1 && whitePawns.count() == 1 && whitePieces == whitePawns) {
        return EndgameType::KRKP;
    }

    // KRKB - one king and one rook vs. one king and one bishop
    if (whiteRooks.count() == 1 && blackBishops.count() == 1 && blackPieces == blackBishops) {
        return EndgameType::KRKB;
    }
    if (blackRooks.count() == 1 && whiteBishops.count() == 1 && whitePieces == whiteBishops) {
        return EndgameType::KRKB;
    }

    // KRKN - one king and one rook vs. one king and one knight
    if (whiteRooks.count() == 1 && blackKnights.count() == 1 && blackPieces == blackKnights) {
        return EndgameType::KRKN;
    } 
    if (blackRooks.count() == 1 && whiteKnights.count() == 1 && whitePieces == whiteKnights) {
        return EndgameType::KRKN;
    }

    // KBBK - one king and two bishops vs. one king
    if (whiteBishops.count() == 2 && blackPieces.empty()) {
        return EndgameType::KBBK;
    } 
    if (blackBishops.count() == 2 && whitePieces.empty()) {
        return EndgameType::KBBK;
    }

    // KBNK - one king and one bishop vs. one king
    if (whiteBishops.count() and whiteKnights.count() and blackTotal.count() == 1) {
        return EndgameType::KBNK;
    }
    if (blackBishops.count() and blackKnights.count() and whiteTotal.count() == 1) {
        return EndgameType::KBNK;
    }

    // Determine the endgame type based on pieces
    if (whiteTotal.count() == 1 && blackTotal.count() > 1) {
        return EndgameType::KXK; // White has only king, black has additional material
    }
    if (blackTotal.count() == 1 && whiteTotal.count() > 1) {
        return EndgameType::KXK; // Black has only king, white has additional material
    }

    // If none of the conditions match, return UNKNOWN
    return EndgameType::NONE;
}


// Entry point for evaluating endgames
int evaluateEndgames(const Board& board) {
    int score = 0;

    int whiteBalance = evaluateMaterial(board, Color::WHITE, true);
    int blackBalance = evaluateMaterial(board, Color::BLACK, true);
    Color strongSide = whiteBalance > blackBalance ? Color::WHITE : Color::BLACK;

    EndgameType::Type endgameType = detectEndgameType(board);
    switch (endgameType) {
        case EndgameType::KXK:
            // std::cout << "KXK" << std::endl;
            score = evaluateKXK(board, strongSide);
            break;
        case EndgameType::KBNK:
            // std::cout << "KBNK" << std::endl;
            score = evaluateKBNK(board, strongSide);
            break;
        case EndgameType::KPK:
            // std::cout << "KPK" << std::endl;
            score = evaluateKPK(board, strongSide);
            break;
        case EndgameType::KNNK:
            // std::cout << "KNNK" << std::endl;
            score = evaluateKNNK(board, strongSide);
            break;
        case EndgameType::KRKP:
            // std::cout << "KRKP" << std::endl;
            score = evaluateKRKP(board, strongSide);
            break;
        case EndgameType::KRKB:
            // std::cout << "KRKB" << std::endl;
            score = evaluateKRKB(board, strongSide);
            break;
        case EndgameType::KRKN:
            // std::cout << "KRKN" << std::endl;
            score = evaluateKRKN(board, strongSide);
            break;
        case EndgameType::KBBK:
            // std::cout << "KBBK" << std::endl;
            score = evaluateKBBK(board, strongSide);
            break;
        case EndgameType::NONE:
            score = 0; // No endgame detected
            break;
    }

    score += whiteBalance + blackBalance;
    return score;
}
