#ifndef ENDGAMES_H
#define ENDGAMES_H

#include "chess-library/include/chess.hpp"
#include "eval.h"
#include "utils.h"

int evaluateEndgames(const Board& board);

namespace EndgameType {
    enum Type {
        KXK,
        KBNK,
        KPK,
        KNNK,
        KRKP,
        KRKB,
        KRKN,
        KBBK,
        NONE
    };
}


EndgameType::Type detectEndgameType(const Board& board);


#endif // ENDGAMES_H
