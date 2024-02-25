#pragma once
#ifndef CONSTS_H
#define CONSTS_H

#include <vector>
#include <map>
#include <limits>

#include "chess-library/include/chess.hpp"

const char startFen[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

enum Value : int {
    ZERO = 0,
    DRAW = 0,
    WIN = 10000,
    MATE = 32000,
    INFINITY = INT32_MAX,
    NEG_INFINITY = INT32_MIN,
    PAWN_MG = 100,
    KNIGHT_MG = 320,
    BISHOP_MG = 330,
    ROOK_MG = 500,
    QUEEN_MG = 900,
    PAWN_EG = 200,
    KNIGHT_EG = 340,
    BISHOP_EG = 360,
    ROOK_EG = 520,
    QUEEN_EG = 920
};

const std::vector<std::vector<int>> PAWN_TABLE = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {5, 10, 10, -20, -20, 10, 10, 5},
    {5, -5, -10, 0, 0, -10, -5, 5},
    {0, 0, 0, 20, 20, 0, 0, 0},
    {5, 5, 10, 25, 25, 10, 5, 5},
    {10, 10, 20, 30, 30, 20, 10, 10},
    {50, 50, 50, 50, 50, 50, 50, 50},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

const std::vector<std::vector<int>> KNIGHTS_TABLE = {
    {-50, -40, -30, -30, -30, -30, -40, -50},
    {-40, -20, 0, 5, 5, 0, -20, -40},
    {-30, 5, 10, 15, 15, 10, 5, -30},
    {-30, 0, 15, 20, 20, 15, 0, -30},
    {-30, 5, 15, 20, 20, 15, 5, -30},
    {-30, 0, 10, 15, 15, 10, 0, -30},
    {-40, -20, 0, 0, 0, 0, -20, -40},
    {-50, -40, -30, -30, -30, -30, -40, -50}
};

const std::vector<std::vector<int>> BISHOPS_TABLE = {
    {-20, -10, -10, -10, -10, -10, -10, -20},
    {-10, 5, 0, 0, 0, 0, 5, -10},
    {-10, 10, 10, 10, 10, 10, 10, -10},
    {-10, 0, 10, 10, 10, 10, 0, -10},
    {-10, 5, 5, 10, 10, 5, 5, -10},
    {-10, 0, 5, 10, 10, 5, 0, -10},
    {-10, 0, 0, 0, 0, 0, 0, -10},
    {-20, -10, -10, -10, -10, -10, -10, -20}
};

const std::vector<std::vector<int>> ROOKS_TABLE = {
    {0, 0, 0, 5, 5, 0, 0, 0},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {5, 10, 10, 10, 10, 10, 10, 5},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

const std::vector<std::vector<int>> QUEENS_TABLE = {
    {-20, -10, -10, -5, -5, -10, -10, -20},
    {-10, 0, 0, 0, 0, 0, 0, -10},
    {-10, 0, 5, 5, 5, 5, 0, -10},
    {-5, 0, 5, 5, 5, 5, 0, -5},
    {0, 0, 5, 5, 5, 5, 0, -5},
    {-10, 5, 5, 5, 5, 5, 0, -10},
    {-10, 0, 5, 0, 0, 0, 0, -10},
    {-20, -10, -10, -5, -5, -10, -10, -20}
};

const std::vector<std::vector<int>> KINGS_TABLE_OPENING = {
    {20, 30, 10, 0, 0, 10, 30, 20},
    {20, 20, 0, 0, 0, 0, 20, 20},
    {-10, -20, -20, -20, -20, -20, -20, -10},
    {-20, -30, -30, -40, -40, -30, -30, -20},
    {-30, -40, -40, -50, -50, -40, -40, -30},
    {-30, -40, -40, -50, -50, -40, -40, -30},
    {-30, -40, -40, -50, -50, -40, -40, -30},
    {-30, -40, -40, -50, -50, -40, -40, -30}
};

const std::vector<std::vector<int>> KINGS_TABLE_ENDGAME = {
    {-50, -40, -30, -20, -20, -30, -40, -50},
    {-30, -20, -10, 0, 0, -10, -20, -30},
    {-30, -10, 20, 30, 30, 20, -10, -30},
    {-30, -10, 30, 40, 40, 30, -10, -30},
    {-30, -10, 30, 40, 40, 30, -10, -30},
    {-30, -10, 20, 30, 30, 20, -10, -30},
    {-30, -30, 0, 0, 0, 0, -30, -30},
    {-50, -30, -30, -30, -30, -30, -30, -50}
};

const std::string OPENINGS_BOOK_STRING = R"(Nf3 d5 d4 Nf6 c4 dxc4 e3 e6 Bxc4 c5 O-O a6 dxc5 Qxd1 Rxd1 Bxc5 a3 | Score: -24
d4 d5 Nf3 Nf6 c4 dxc4 e3 e6 Bxc4 c5 O-O a6 dxc5 Bxc5 Qxd8+ Kxd8 a3 | Score: -30
d4 Nf6 Nf3 g6 c4 Bg7 Nc3 O-O Bg5 c5 d5 d6 Nd2 h6 Bh4 a6 e4 b5 Be2 b4 | Score: 17
d4 Nf6 c4 g6 Nc3 Bg7 e4 d6 f3 O-O Bg5 c5 d5 a6 a4 h6 Be3 e6 Qd2 exd5 | Score: 30
d4 f5 g3 Nf6 Bg2 g6 Nh3 Bg7 Nf4 d6 d5 c6 c4 Bd7 Nc3 Na6 h4 Rg8 h5 g5 | Score: 21
e4 c6 d4 d5 e5 Bf5 Nd2 h6 Nb3 e6 c3 Nd7 Be3 Ne7 f4 h5 Nf3 h4 Be2 Bg4 | Score: 32
d4 d6 Nf3 g6 g3 Bf5 Nh4 Bd7 e4 Bg7 c3 Qc8 Qb3 a5 a4 Be6 Qc2 d5 e5 c5 | Score: 25
Nf3 Nf6 g3 b5 c3 Bb7 a4 a6 e3 Nc6 d4 e6 b4 Be7 Nbd2 Na7 Bd3 O-O e4 d6 | Score: 34
d4 Nf6 c4 c5 d5 b5 cxb5 a6 b6 d6 Nc3 Qxb6 e4 g6 Nf3 Bg7 a4 O-O a5 Qc7 | Score: 30
c4 g6 Nc3 Bg7 g3 Nc6 Bg2 d6 Nf3 e5 d3 f5 O-O Nf6 Rb1 h6 b4 O-O b5 Ne7 | Score: 28
d4 d5 c4 c6 Nf3 Nf6 e3 a6 Nc3 b5 b3 Bg4 Be2 e6 Bb2 Bd6 O-O O-O h3 Bh5 | Score: 29
d4 e6 c4 b6 Nc3 Bb7 a3 f5 d5 Nf6 g3 Na6 Bg2 Bd6 b4 O-O Nh3 c5 Nb5 Be5 | Score: -7
d4 d5 c4 c6 Nf3 Nf6 Nc3 e6 Bg5 h6 Bh4 dxc4 e4 g5 Bg3 b5 Be2 Bb7 h4 g4 | Score: 25
d4 Nf6 c4 g6 Nc3 Bg7 e4 d6 f3 O-O Bg5 a6 Qd2 c5 d5 b5 cxb5 Nbd7 a4 Qa5 | Score: 20
d4 Nf6 c4 e6 Nf3 d5 Nc3 dxc4 e3 a6 a4 c5 Bxc4 Nc6 O-O Be7 Qe2 cxd4 Rd1 | Score: -20
Nf3 Nf6 c4 b6 g3 c5 Bg2 Bb7 O-O g6 b3 Bg7 Bb2 O-O e3 e6 d4 Qe7 Nc3 Na6 | Score: 25
Nf3 d5 d4 c6 c4 Nf6 Nc3 e6 e3 Nbd7 Bd3 dxc4 Bxc4 b5 Bd3 a6 e4 c5 d5 c4 | Score: 15
Nf3 Nf6 d4 g6 c4 Bg7 g3 O-O Bg2 d6 Nc3 Nc6 O-O e5 d5 Ne7 e4 Ne8 Ne1 f5 | Score: 25
Nf3 Nf6 c4 c5 Nc3 e6 g3 b6 Bg2 Bb7 O-O Be7 b3 O-O Bb2 d6 e3 Nbd7 d4 a6 | Score: 32
e4 g6 d4 Bg7 Nf3 d6 Bc4 e6 Bb3 Ne7 c3 b6 Be3 Bb7 Nbd2 Nd7 h3 h6 Qe2 a5 | Score: 28
d4 d6 Nf3 Nf6 g3 g6 Bg2 Bg7 c4 O-O Nc3 Nc6 O-O e5 d5 Ne7 e4 Nd7 Ne1 f5 | Score: 30
d4 Nf6 Nf3 g6 c4 Bg7 g3 O-O Bg2 d6 O-O Nc6 Nc3 e5 d5 Ne7 e4 Nd7 Ne1 f5 | Score: 17
d4 d6 Nf3 g6 g3 Bg7 Bg2 Nd7 O-O e5 e4 Ngf6 Nc3 O-O Re1 c6 a4 Qc7 h3 b6 | Score: 25
Nf3 d5 c4 c6 e3 Nf6 Nc3 e6 d4 Nbd7 Bd3 dxc4 Bxc4 b5 Bd3 a6 e4 c5 d5 c4 | Score: 25
c4 g6 Nc3 Bg7 d4 Nf6 e4 d6 Nf3 O-O h3 e5 d5 Na6 Be3 Nh5 Nh2 Qe8 Be2 f5 | Score: 24
Nf3 Nf6 c4 e6 g3 d5 Bg2 Be7 O-O O-O d4 c6 b3 b6 Bb2 Bb7 Nc3 Nbd7 e3 c5 | Score: 34
Nf3 c5 c4 Nf6 g3 b6 Bg2 Bb7 O-O e6 Nc3 Be7 b3 O-O Bb2 d6 e3 Nbd7 d4 a6 | Score: 32
d4 Nf6 c4 c5 d5 e6 Nc3 exd5 cxd5 d6 e4 g6 Nf3 Bg7 h3 O-O Bd3 b5 O-O b4 | Score: 19
Nf3 g6 d4 Nf6 c4 Bg7 g3 O-O Bg2 d6 O-O c6 Nc3 Qa5 h3 Be6 Qd3 Qa6 b3 d5 | Score: 29
Nf3 Nf6 c4 e6 Nc3 Bb4 Qc2 c5 a3 Ba5 g3 O-O Bg2 Nc6 O-O d6 d3 h6 Rb1 e5 | Score: 15
d4 Nf6 c4 c5 d5 d6 Nc3 g6 e4 Bg7 Nf3 O-O h3 e6 Bd3 exd5 cxd5 b5 O-O b4 | Score: 15
d4 d5 c4 c6 Nf3 Nf6 cxd5 cxd5 Nc3 Nc6 Bf4 a6 e3 Bg4 Be2 e6 O-O Bd6 Bxd6 | Score: -14
d4 d5 c4 c6 Nc3 Nf6 e3 a6 Bd3 b5 b3 Bg4 Nge2 e6 Qc2 Nbd7 O-O Rc8 Bd2 c5 | Score: 10
d4 Nf6 c4 e6 Nc3 Bb4 e3 c5 Bd3 Nc6 Nf3 Bxc3+ bxc3 d6 e4 e5 h3 h6 Be3 b6 | Score: 27
Nf3 c5 g3 g6 Bg2 Bg7 c4 Nc6 Nc3 d6 a3 Nh6 d3 O-O Bd2 Nf5 Rb1 a5 O-O Bd7 | Score: 26
e4 c6 d4 d5 e5 Bf5 Nf3 e6 Be2 Ne7 O-O Nd7 Nbd2 h6 c3 a6 Ne1 c5 Ndf3 Nc6 | Score: 24
Nf3 Nf6 c4 e6 g3 d5 Bg2 Be7 O-O O-O d4 c6 Qc2 b6 Nbd2 Bb7 e4 Na6 e5 Nd7 | Score: 19
d4 g6 Nf3 f5 g3 Bg7 Bg2 Nf6 O-O O-O c4 d6 d5 c5 Nc3 Na6 Ne1 Rb8 Nc2 Nc7 | Score: 32
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O b5 Bb3 Bb7 Re1 Bc5 c3 Bb6 a4 O-O d3 h6 | Score: 34
c4 c5 Nf3 Nf6 Nc3 e6 g3 b6 e4 Bb7 d3 d6 Bg2 Be7 O-O O-O Re1 Nc6 d4 cxd4 | Score: 34
c4 g6 d4 Bg7 Nc3 Nf6 e4 d6 Be2 O-O Bg5 Nbd7 Qc1 c5 d5 b5 cxb5 a6 a4 Qa5 | Score: 28
d4 f5 g3 Nf6 Bg2 g6 Nf3 Bg7 O-O O-O c4 d6 Nc3 Qe8 d5 a5 Rb1 Na6 Ne1 Bd7 | Score: 21
d4 Nf6 c4 g6 Nc3 Bg7 e4 d6 Nf3 O-O Be2 e5 O-O Nc6 d5 Ne7 Nd2 a5 Rb1 Nd7 | Score: 31
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 b5 Bb3 O-O h3 Bb7 d3 d6 c3 Na5 | Score: 23
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 b5 Bb3 O-O d3 d6 c3 Na5 Bc2 c5 | Score: 18
d4 Nf6 c4 g6 Nf3 Bg7 g3 O-O Bg2 c6 O-O d5 b3 Bf5 Bb2 a5 Nc3 Ne4 e3 Nxc3 | Score: 25
e4 c6 d4 d5 e5 Bf5 Nc3 a6 h4 h5 Bd3 Bxd3 Qxd3 e6 Bg5 Qc7 Nf3 c5 O-O Nc6 | Score: 28
d4 Nf6 c4 c5 d5 b5 cxb5 a6 b6 d6 Nc3 Qxb6 e4 g6 Nf3 Bg7 Nd2 O-O Nc4 Qc7 | Score: 31
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 b5 Bb3 O-O c3 d6 d4 Bg4 d5 Na5 | Score: 28
Nf3 c5 c4 Nc6 Nc3 e5 g3 g6 Bg2 Bg7 O-O Nge7 a3 d6 d3 O-O Rb1 a5 Ne1 Be6 | Score: 18
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 b5 Bb3 d6 c3 O-O d4 Bg4 d5 Na5 | Score: 18
Nf3 d5 d4 Nf6 c4 c6 Nc3 e6 e3 Nbd7 Qc2 Bd6 b3 O-O Be2 b6 O-O Bb7 Bb2 c5 | Score: 33
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O b5 Bb3 Bb7 Re1 Bc5 c3 d6 d4 Bb6 Bg5 h6 | Score: 34
d4 Nf6 c4 g6 Nc3 Bg7 e4 d6 f3 O-O Be3 Nc6 Qd2 a6 Nge2 Re8 Nc1 e5 d5 Nd4 | Score: 30
d4 Nf6 c4 c5 d5 b5 cxb5 a6 b6 Qxb6 Nc3 d6 e4 Nbd7 f4 g6 Nf3 Bg7 Nd2 O-O | Score: 11
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Be3 e5 Nb3 Be6 f3 Nbd7 g4 b5 g5 b4 | Score: 19
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 b5 Bb3 O-O d4 d6 c3 Bg4 d5 Na5 | Score: 30
Nf3 Nf6 c4 e6 g3 a6 Bg2 b5 b3 c5 O-O Bb7 e3 Be7 Nc3 Qa5 Bb2 O-O Qe2 Nc6 | Score: 17
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 b5 Bb3 O-O a4 b4 c3 d6 a5 bxc3 | Score: 26
d4 Nf6 c4 e6 Nf3 c5 d5 exd5 cxd5 d6 Nc3 g6 g3 Bg7 Bg2 O-O O-O Re8 h3 a6 | Score: 30
d4 Nf6 c4 g6 Nc3 d5 Nf3 Bg7 Qb3 dxc4 Qxc4 O-O e4 Na6 Bf4 c5 d5 e6 d6 e5 | Score: 24
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 b5 Bb3 O-O h3 Bb7 d3 d6 a3 Na5 | Score: 34
Nf3 Nf6 c4 e6 g3 a6 Bg2 b5 b3 Bb7 Nc3 b4 Na4 d6 O-O Nbd7 d4 Be7 Nb2 O-O | Score: 15
d4 Nf6 c4 g6 g3 Bg7 Bg2 O-O Nc3 d6 Nf3 Nc6 O-O Bf5 d5 Na5 Nd2 c6 e4 Bg4 | Score: 23
d4 d5 c4 c6 Nc3 Nf6 e3 e6 Nf3 Nbd7 Qc2 Bd6 Bd3 O-O O-O h6 Rd1 Qe7 h3 b6 | Score: 30
d4 Nf6 c4 g6 Nc3 Bg7 e4 d6 f3 O-O Nge2 c5 d5 e6 Ng3 exd5 cxd5 h5 Be2 a6 | Score: 25
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 b5 Bb3 O-O a4 Bb7 d3 h6 c3 Re8 | Score: 17
c4 Nf6 Nc3 e6 Nf3 Bb4 Qc2 c5 a3 Ba5 g3 Nc6 Bg2 O-O O-O Qe7 d3 d6 Rb1 h6 | Score: 25
Nf3 Nf6 c4 g6 Nc3 Bg7 e4 d6 d4 O-O Be2 e5 Be3 Ng4 Bg5 f6 Bc1 Nc6 O-O f5 | Score: 27
d4 Nf6 c4 e6 Nc3 Bb4 e3 c5 Ne2 b6 a3 Ba5 Rb1 Na6 Bd2 O-O d5 d6 Nf4 Bxc3 | Score: 19
c4 Nf6 Nc3 e6 Nf3 Bb4 Qc2 c5 g3 Nc6 Bg2 O-O O-O Qe7 d3 h6 e4 d6 Nh4 Rb8 | Score: 20
d4 d5 c4 c6 Nf3 Nf6 e3 a6 Nc3 b5 b3 Bf5 Be2 e6 O-O Nbd7 Bd2 Be7 Nh4 Bg6 | Score: 34
d4 f5 g3 Nf6 Bg2 g6 Nf3 Bg7 c4 O-O O-O d6 Nc3 Qe8 Qb3 c6 d5 Na6 Be3 Ng4 | Score: 13
Nf3 Nf6 c4 c5 Nc3 e6 g3 b6 Bg2 Bb7 O-O Be7 b3 O-O Bb2 d6 e3 Nbd7 Qe2 a6 | Score: 22
Nf3 g6 e4 Bg7 d4 d6 c4 Nf6 Nc3 O-O Be2 e5 O-O Nc6 Be3 Ng4 Bg5 f6 Bc1 f5 | Score: 31
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 b5 Bb3 d6 c3 O-O d3 Na5 Bc2 c5 | Score: 20
c4 g6 Nc3 Bg7 d4 Nf6 e4 d6 Nf3 O-O h3 e5 d5 Na6 Be3 Nh5 Nh2 Qe8 Be2 Nf4 | Score: 29
d4 g6 e4 Bg7 Nc3 c5 d5 d6 Be2 Na6 Nf3 Nc7 O-O Nf6 Nd2 O-O a4 a6 Re1 Bd7 | Score: 23
c4 e6 Nc3 d5 d4 Be7 Nf3 Nf6 Bg5 O-O e3 Nbd7 Qc2 c6 Rd1 b6 Bd3 h6 Bh4 Bb7 | Score: 22
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 b5 Bb3 O-O a4 Bb7 d3 d6 Nc3 Na5 | Score: 23
d4 d5 c4 c6 Nf3 Nf6 e3 e6 Bd3 dxc4 Bxc4 c5 O-O a6 a4 Nc6 Qe2 Qc7 Nc3 Bd6 | Score: 31
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 b5 Bb3 d6 c3 Bg4 h3 Bh5 d4 Bxf3 | Score: 31
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 b5 Bb3 d6 c3 O-O d4 Bg4 Be3 Bh5 | Score: 26
d4 d5 c4 c6 Nf3 Nf6 Nc3 e6 e3 Nbd7 Qc2 Bd6 Be2 O-O O-O Re8 Rd1 Qe7 a3 b6 | Score: 32
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 b5 Bb3 O-O a4 b4 d3 d6 Nbd2 Rb8 | Score: 33
d4 Nf6 c4 c5 d5 e6 Nc3 exd5 cxd5 d6 Nf3 g6 Bg5 h6 Bh4 g5 Bg3 Nh5 e3 Nxg3 | Score: 8
e4 c5 Nf3 e6 d4 cxd4 Nxd4 a6 Bd3 Nf6 O-O d6 c4 Qc7 Qe2 g6 f4 Bg7 Kh1 O-O | Score: 24
d4 d5 c4 c6 Nc3 Nf6 e3 e6 Nf3 Nbd7 Qc2 Bd6 b3 O-O Be2 Re8 O-O Qe7 Rd1 b6 | Score: 10
d4 f5 Bg5 h6 Bh4 g5 e3 Nf6 Bg3 d6 h4 Rg8 hxg5 hxg5 Nc3 e6 f3 Qe7 Qd2 Nc6 | Score: 34
d4 d5 c4 c6 Nf3 Nf6 e3 Bf5 Nc3 e6 Nh4 Be4 f3 Bg6 Qb3 Qc7 g3 Be7 Kf2 Nbd7 | Score: 28
e4 c6 d4 d5 e5 Bf5 Nf3 e6 a3 Nd7 Be2 c5 c4 dxc4 Bxc4 a6 O-O Rc8 Bd3 Bxd3 | Score: 34
d4 d5 c4 e6 Nc3 c6 e3 f5 f4 Nf6 Nf3 Be7 Be2 O-O O-O b6 Qc2 Bb7 cxd5 cxd5 | Score: 20
Nf3 Nf6 c4 c5 g3 b6 Bg2 Bb7 O-O g6 Nc3 Bg7 d4 Ne4 Nxe4 Bxe4 d5 O-O a4 e6 | Score: 9
d4 Nf6 c4 e6 Nf3 d5 Nc3 c6 e3 Nbd7 Qc2 Bd6 b3 O-O Be2 b6 O-O Bb7 Bb2 Rc8 | Score: 30
d4 d5 c4 c6 Nc3 Nf6 e3 e6 Nf3 a6 b3 Bb4 Bd2 Nbd7 Bd3 O-O O-O Bd6 e4 dxc4 | Score: 15
e4 e5 Nf3 Nc6 Bb5 Nf6 d3 d6 c3 g6 O-O Bg7 Nbd2 O-O Re1 Re8 d4 Bd7 d5 Ne7 | Score: 28
e4 c5 Nf3 e6 d4 cxd4 Nxd4 a6 Nc3 Qc7 Bd3 Nf6 O-O d6 Qe2 Nbd7 f4 b5 a4 b4 | Score: 24
d4 Nf6 c4 g6 Nc3 Bg7 e4 d6 f3 O-O Be3 Nc6 Nge2 a6 Nc1 e5 d5 Nd4 Nb3 Nxb3 | Score: 34
d4 c6 c4 d5 Nf3 Nf6 e3 e6 Bd3 Be7 O-O O-O Nc3 Nbd7 b3 Re8 Bb2 b6 e4 dxe4 | Score: 28
d4 Nf6 c4 c5 d5 g6 Nc3 Bg7 g3 O-O Bg2 d6 Nf3 e6 O-O exd5 cxd5 Re8 Nd2 a6 | Score: 23
d4 Nf6 Nf3 c5 d5 e6 c4 exd5 cxd5 d6 Nc3 g6 Bg5 h6 Bh4 g5 Bg3 Nh5 e3 Nxg3 | Score: 19
d4 d5 c4 c6 Nc3 Nf6 Nf3 e6 e3 Nbd7 Bd3 dxc4 Bxc4 b5 Bd3 Bb7 O-O a6 e4 c5 | Score: 14
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Bg2 c6 O-O d5 Ne5 O-O Bc3 Bb7 | Score: 25
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 b5 Bb3 d6 a4 Bg4 c3 O-O h3 Bxf3 | Score: 33
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nc6 Nc3 a6 g3 Qc7 Bg2 Nf6 O-O h6 Nb3 Be7 a4 d6 | Score: 25
d4 Nf6 c4 e6 g3 c5 d5 exd5 cxd5 d6 Nc3 g6 Bg2 Bg7 Nf3 O-O O-O Re8 Nd2 a6 | Score: 30
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 b5 Bb3 d6 c3 O-O h3 Nb8 d3 Nbd7 | Score: 32
d4 Nf6 c4 g6 Nf3 Bg7 g3 d5 cxd5 Nxd5 Bg2 Nb6 O-O Nc6 e3 e5 Nc3 Bg4 d5 e4 | Score: 23
c4 e6 d4 d5 Nf3 Nf6 e3 Be7 Bd3 O-O b3 b6 O-O Bb7 Bb2 Nbd7 Nc3 a6 Rc1 Bd6 | Score: 31
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 b5 Bb3 O-O c3 d6 h3 Nb8 d3 Nbd7 | Score: 31
d4 Nf6 c4 g6 Nc3 Bg7 e4 d6 Nf3 O-O Be2 e5 Be3 exd4 Nxd4 Re8 f3 c6 Qd2 d5 | Score: 17
d4 Nf6 Nf3 e6 c4 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Bg2 O-O Ne5 c6 Bc3 d5 Nd2 Bb7 | Score: 32
e4 e5 Nf3 Nc6 Bc4 Bc5 c3 Nf6 d3 O-O O-O d6 Nbd2 a6 Bb3 h6 h3 Ba7 Re1 Re8 | Score: 18
e4 e5 Nf3 Nc6 Bc4 Bc5 c3 Nf6 d3 d6 O-O O-O Nbd2 a6 Bb3 Ba7 h3 h6 Re1 Re8 | Score: 22
d4 Nf6 c4 e6 Nf3 b6 Nc3 Bb4 e3 Bxc3+ bxc3 c5 Bd3 Nc6 e4 d6 O-O e5 d5 Na5 | Score: 25
d4 Nf6 c4 e6 g3 c5 d5 exd5 cxd5 d6 Nc3 g6 Bg2 Bg7 Nf3 O-O O-O Re8 h3 Ne4 | Score: 28
d4 Nf6 c4 e6 Nf3 d5 Nc3 c6 e3 Nbd7 Bd3 dxc4 Bxc4 b5 Bd3 Bb7 e4 b4 Na4 c5 | Score: 23
d4 d5 c4 c6 Nf3 Nf6 Nc3 e6 e3 Nbd7 Bd3 dxc4 Bxc4 b5 Bd3 Bb7 e4 b4 Na4 c5 | Score: 32
e4 e5 Nf3 Nc6 Bc4 Bc5 c3 Nf6 d3 d6 Nbd2 a6 O-O O-O Bb3 Ba7 h3 Be6 Bc2 d5 | Score: 15
d4 Nf6 c4 e6 g3 c5 d5 exd5 cxd5 d6 Nc3 g6 Bg2 Bg7 Nf3 O-O O-O a6 a4 Nbd7 | Score: 27
d4 Nf6 c4 e6 Nf3 b6 g3 Bb7 Bg2 Be7 Nc3 O-O O-O Ne4 Bd2 f5 d5 Bf6 Rc1 Na6 | Score: 23
d4 Nf6 Nf3 e6 c4 c5 e3 d5 Nc3 Nc6 a3 a6 dxc5 Bxc5 b4 Bd6 Bb2 O-O Rc1 Ne5 | Score: 17
d4 d5 c4 c6 Nf3 Nf6 e3 Bf5 Nc3 e6 Nh4 Bg6 Be2 Nbd7 g3 Bd6 O-O O-O b3 Ne4 | Score: 17
d4 Nf6 c4 g6 Nc3 Bg7 e4 d6 Be2 O-O Bg5 c5 d5 h6 Be3 e6 Qd2 exd5 cxd5 Re8 | Score: 27
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 e6 Be2 a6 f4 Qc7 O-O Be7 a4 O-O Kh1 b6 | Score: 14
d4 Nf6 c4 g6 Nc3 Bg7 e4 d6 f4 O-O Nf3 c5 d5 b5 cxb5 a6 bxa6 Qa5 Nd2 Bxa6 | Score: 8
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Bc5 c3 Ba7 d4 O-O Bg5 h6 Bh4 b5 dxe5 g5 | Score: 21
Nf3 Nf6 c4 g6 g3 Bg7 Bg2 O-O O-O d6 d4 c6 Nc3 Qa5 e4 e5 h3 Nbd7 Re1 exd4 | Score: 33
c4 Nf6 d4 e6 Nc3 c5 d5 exd5 cxd5 d6 Nf3 g6 g3 Bg7 Bg2 O-O O-O Re8 Nd2 a6 | Score: 28
d4 Nf6 c4 c5 d5 e6 Nc3 exd5 cxd5 d6 e4 g6 f4 Bg7 Nf3 O-O Be2 Re8 e5 dxe5 | Score: 29
d4 Nf6 c4 e6 Nf3 d5 Nc3 Be7 Bf4 O-O e3 c5 dxc5 Bxc5 a3 Nc6 Rc1 a6 b4 Bd6 | Score: 30
c4 c5 Nf3 g6 d4 Bg7 d5 Nf6 Nc3 d6 e4 O-O Bf4 Nh5 Bg5 h6 Bd2 e5 dxe6 Bxe6 | Score: 32
d4 d5 c4 c6 Nf3 Nf6 Nc3 e6 e3 Nbd7 Bd3 dxc4 Bxc4 b5 Bd3 Bb7 a3 b4 Ne4 a5 | Score: 28
Nf3 d6 d4 f5 g3 Nf6 Bg2 g6 O-O Bg7 c4 O-O Nc3 e6 Qc2 Nc6 Rd1 Qe7 e4 fxe4 | Score: 34
d4 Nf6 c4 c5 d5 d6 Nc3 g6 e4 Bg7 Bd3 O-O Nge2 e6 O-O exd5 cxd5 b6 Bg5 h6 | Score: 34
d4 Nf6 c4 e6 Nf3 c5 d5 exd5 cxd5 g6 Nc3 Bg7 Nd2 O-O Nc4 b6 e3 d6 Be2 Ba6 | Score: 16
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Be2 e6 O-O Be7 f4 O-O Kh1 Qc7 a4 Nc6 | Score: 32
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 f4 Qc7 a4 g6 Bd3 Bg7 Nf3 Bg4 Be3 Nc6 | Score: 22
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Bg2 c6 O-O d5 Bc3 O-O Ne5 Nfd7 | Score: 34
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O b5 Bb3 Bb7 d3 Be7 Re1 O-O Nbd2 d6 c3 Na5 | Score: 27
d4 Nf6 c4 e6 g3 d5 Bg2 dxc4 Nf3 a6 O-O Nc6 Nc3 Rb8 e4 Be7 d5 Nb4 Ne5 exd5 | Score: 32
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nf6 Nc3 d6 Be2 Be7 O-O O-O Be3 Nc6 Nb3 a6 a4 b6 | Score: 12
d4 Nf6 c4 e6 Nf3 c5 d5 d6 Nc3 exd5 cxd5 g6 e4 Bg7 h3 O-O Bd3 b5 Bxb5 Nxe4 | Score: 25
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nf6 Nc3 d6 Be2 a6 f4 Qc7 O-O Be7 Kh1 O-O a4 Nc6 | Score: 31
e4 e5 Nf3 Nc6 Bc4 Bc5 c3 Nf6 d3 d6 Bb3 a6 O-O Ba7 Re1 h6 Nbd2 O-O Nf1 Re8 | Score: 13
Nf3 d5 d4 Nf6 c4 c6 e3 e6 Bd3 dxc4 Bxc4 c5 O-O Nc6 Qe2 a6 dxc5 Bxc5 a3 b5 | Score: 32
e4 c5 Nf3 d6 Bb5+ Nd7 O-O Nf6 Re1 a6 Bf1 b6 d4 cxd4 Nxd4 Bb7 f3 e6 a4 Be7 | Score: 34
e4 e6 d4 d5 Nc3 Nf6 e5 Nfd7 f4 c5 Nf3 Nc6 Be3 a6 h4 Qb6 Na4 Qa5+ Nc3 cxd4 | Score: 23
d4 d5 c4 c6 Nf3 Nf6 Nc3 dxc4 a4 Bf5 e3 e6 Bxc4 Bb4 O-O Nbd7 Nh4 Bg6 h3 a5 | Score: 25
Nf3 Nf6 c4 c5 Nc3 e6 g3 b6 Bg2 Bb7 O-O a6 b3 d6 Bb2 Be7 d4 cxd4 Nxd4 Bxg2 | Score: 28
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 b5 Bb3 d6 c3 O-O d4 Bg4 Be3 exd4 | Score: 33
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 b5 Bb3 d6 a4 Bb7 d3 O-O Nbd2 Na5 | Score: 29
Nf3 d5 c4 c6 d4 Nf6 e3 g6 Nc3 Bg7 Be2 O-O O-O Bg4 b3 Nbd7 Bb2 Re8 Rc1 Ne4 | Score: 17
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 a4 Nc6 Be2 e6 Be3 Be7 f4 O-O O-O Qc7 | Score: 29
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nf6 Nc3 d6 f4 a6 Be2 Be7 O-O O-O Be3 Nc6 a4 Re8 | Score: 32
d4 Nf6 c4 d6 Nc3 e5 Nf3 Nbd7 Bg5 Be7 e3 O-O Qc2 c6 Bd3 h6 h4 b5 dxe5 Nxe5 | Score: 33
d4 Nf6 Nf3 e6 c4 c5 e3 d5 Nc3 dxc4 Bxc4 a6 a4 Be7 O-O O-O Qe2 Nc6 Rd1 Qc7 | Score: 7
d4 Nf6 c4 e6 Nf3 d5 Nc3 dxc4 e3 a6 a4 c5 Bxc4 Nc6 O-O Be7 d5 Na5 Ba2 exd5 | Score: 21
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb7 Bg2 Bb4+ Bd2 a5 O-O O-O Bg5 Be7 Nc3 Ne4 | Score: 22
d4 Nf6 c4 d6 Nf3 g6 g3 Bg7 Bg2 O-O O-O c6 Nc3 Bf5 Nh4 Bd7 e4 e5 dxe5 dxe5 | Score: 22
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nc6 Nc3 d6 Be2 Be7 O-O Nf6 Be3 a6 f4 Bd7 Qe1 b5 | Score: 30
c4 Nf6 Nf3 e6 g3 d5 Bg2 Be7 O-O O-O d4 c6 b3 b6 Bb2 Nbd7 Nbd2 Bb7 e3 dxc4 | Score: 26
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb7 Bg2 Bb4+ Bd2 a5 O-O O-O Nc3 d6 Qc2 Bxc3 | Score: 34
Nf3 c5 c4 Nc6 Nc3 Nf6 g3 g6 Bg2 Bg7 O-O O-O d3 a6 a3 Rb8 Rb1 b5 cxb5 axb5 | Score: 9
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 d3 b5 Bb3 Be7 a4 Rb8 axb5 axb5 O-O O-O c3 d5 | Score: 4
Nf3 Nf6 c4 g6 g3 Bg7 Bg2 O-O d4 d5 cxd5 Nxd5 O-O Nb6 Nc3 Nc6 d5 Na5 e4 c6 | Score: 24
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nc6 Nc3 Nf6 Bc4 Qb6 Nb3 e6 Be3 Qc7 f4 a6 Bd3 b5 | Score: 17
d4 d5 c4 c6 Nc3 Nf6 e3 e6 Nf3 Nbd7 Qc2 Bd6 b3 O-O Be2 a6 O-O e5 cxd5 cxd5 | Score: 32
e4 c6 d4 d5 e5 Bf5 Nd2 e6 Nb3 Nd7 Nf3 a6 Be2 Rc8 O-O c5 dxc5 Nxc5 c4 dxc4 | Score: 7
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Be2 e5 Nb3 Be6 f4 Qc7 a4 Nc6 f5 Bxb3 | Score: 11
c4 b6 d4 Bb7 Nc3 e6 a3 f5 d5 Nf6 g3 Na6 Bg2 Nc5 Nh3 Bd6 Be3 Be5 Bxc5 bxc5 | Score: 24
Nf3 Nf6 c4 e6 Nc3 d5 d4 Nbd7 Qc2 c6 e3 Bd6 g4 h6 Bd2 a6 e4 dxe4 Nxe4 Nxe4 | Score: 15
d4 Nf6 c4 e6 Nf3 c5 Nc3 cxd4 Nxd4 a6 e3 b6 Be2 Bb7 O-O Be7 b3 O-O Bb2 Nc6 | Score: 30
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nc6 Nc3 Qc7 Be3 Nf6 a3 a6 Be2 Be7 O-O O-O f4 d6 | Score: 14
d4 Nf6 c4 e6 Nf3 b6 g3 Bb7 Bg2 Be7 Nc3 Ne4 Bd2 Bf6 O-O O-O Rc1 d6 d5 Nxd2 | Score: 16
d4 Nf6 c4 e6 Nf3 b6 Nc3 Bb7 a3 d5 cxd5 Nxd5 e3 g6 Bb5+ c6 Bd3 Bg7 e4 Nxc3 | Score: 23
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 e6 Be2 Be7 O-O O-O f4 Nc6 Be3 e5 Nb3 a5 | Score: 32
Nf3 d5 c4 dxc4 e3 Nf6 Bxc4 e6 d4 c5 O-O a6 a4 Nc6 Nc3 Be7 Qe2 cxd4 Rd1 e5 | Score: 10
c4 Nf6 Nc3 g6 d4 Bg7 e4 d6 Be2 O-O Bg5 c5 d5 h6 Bf4 e6 dxe6 Bxe6 Bxd6 Re8 | Score: 23
Nf3 d5 d4 Nf6 c4 dxc4 e3 e6 Bxc4 c5 O-O a6 a4 Qc7 Qe2 Nc6 Nc3 Bd6 Bd2 O-O | Score: 18
c4 c6 Nf3 d5 e3 Nf6 Nc3 e6 b3 Nbd7 Qc2 Bd6 Bb2 a6 d4 O-O Be2 e5 cxd5 cxd5 | Score: 30
d4 d5 c4 dxc4 Nf3 e6 e3 a6 Bxc4 c5 O-O Nf6 Bd3 Nbd7 Re1 b6 e4 cxd4 e5 Nd5 | Score: 34
d4 Nf6 c4 e6 Nf3 b6 a3 Bb7 Nc3 d5 Qc2 dxc4 e4 c5 d5 exd5 exd5 Bd6 Bg5 O-O | Score: 0
d4 d5 c4 dxc4 Nf3 a6 e3 Nf6 Bxc4 e6 O-O c5 Bd3 cxd4 exd4 Be7 Nc3 b5 a4 b4 | Score: 21
c4 e6 Nf3 d5 g3 Nf6 Bg2 Be7 O-O O-O d4 dxc4 Qc2 a6 a4 Bd7 Qxc4 Bc6 Bg5 h6 | Score: 26
d4 Nf6 c4 e6 g3 d5 Bg2 Be7 Nf3 O-O O-O dxc4 Qc2 a6 a4 Bd7 Qxc4 Bc6 Bg5 h6 | Score: 32
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 e6 Nc3 Qc7 Be3 Nf6 Bd3 a6 O-O b5 Nb3 Be7 f4 d6 | Score: 24
d4 Nf6 c4 e6 Nc3 Bb4 e3 O-O Bd3 c5 Nf3 Nc6 d5 Ne7 e4 d6 Bd2 exd5 exd5 Bf5 | Score: 26
Nf3 Nf6 c4 g6 Nc3 Bg7 e4 d6 d4 O-O Be2 e5 O-O Nc6 d5 Ne7 Nd2 c6 dxc6 bxc6 | Score: 13
Nf3 d5 d4 Nf6 c4 e6 g3 Be7 Bg2 O-O O-O dxc4 Qc2 a6 a4 Bd7 Qxc4 Bc6 Bg5 a5 | Score: 19
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Be2 e5 Nb3 Be7 O-O O-O Kh1 Nc6 f4 a5 | Score: 25
d4 Nf6 c4 e6 Nf3 b6 g3 Bb4+ Bd2 Be7 Nc3 Bb7 Bg2 c6 e4 d5 cxd5 cxd5 e5 Ne4 | Score: 25
d4 Nf6 c4 e6 Nc3 Bb4 e3 O-O Bd3 c5 Nf3 d5 O-O dxc4 Bxc4 Nc6 a3 Ba5 Ba2 a6 | Score: 28
d4 Nf6 Nf3 g6 g3 Bg7 Bg2 O-O c4 d5 O-O dxc4 Na3 c3 bxc3 c5 e3 Nc6 Qe2 Bf5 | Score: 19
d4 Nf6 c4 e6 g3 d5 Bg2 Be7 Nf3 O-O O-O dxc4 Qc2 a6 a4 Bd7 Qxc4 Bc6 Bg5 a5 | Score: 27
d4 Nf6 c4 e6 g3 d5 Bg2 Be7 Nf3 O-O O-O dxc4 Qc2 a6 a4 Bd7 Rd1 Bc6 Nc3 Bb4 | Score: 33
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nf6 Nc3 d6 g3 Be7 Bg2 a6 O-O Qc7 a4 Nc6 Be3 O-O | Score: 30
d4 d5 c4 e6 Nc3 c5 e3 Nf6 Nf3 Nc6 a3 Bd6 dxc5 Bxc5 b4 Bd6 Bb2 O-O Qc2 Ne5 | Score: 16
d4 e6 c4 Nf6 Nf3 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Bg2 c6 O-O d5 Ne5 O-O Bc3 Nfd7 | Score: 27
d4 Nf6 c4 e6 Nf3 d5 Nc3 Be7 Bf4 O-O e3 Nbd7 a3 Nh5 Be5 c6 h3 Nxe5 dxe5 g6 | Score: 26
d4 Nf6 c4 g6 Nc3 Bg7 e4 d6 Nf3 O-O Be2 e5 O-O Na6 Be3 c6 dxe5 dxe5 h3 Qe7 | Score: 30
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 e6 f4 a6 Qf3 Qb6 a3 Nc6 Nb3 Qc7 Bd3 Be7 | Score: 29
d4 g6 c4 Bg7 Nc3 d6 Nf3 Nf6 Bg5 O-O e3 c6 Be2 a6 O-O b5 b4 bxc4 Bxc4 Nbd7 | Score: 14
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 f4 Qc7 a4 g6 Bd3 Bg7 Nf3 Nc6 O-O Bg4 | Score: 31
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 f3 e6 Be3 b5 g4 Nfd7 Qd2 Nb6 a4 bxa4 | Score: 32
Nf3 d5 d4 Nf6 c4 dxc4 e3 Bg4 Bxc4 e6 Nc3 a6 h3 Bh5 O-O Nc6 Be2 Bd6 b3 O-O | Score: 30
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 a4 g6 Be2 Bg7 Be3 O-O O-O Nc6 f4 Bd7 | Score: 10
d4 Nf6 Nf3 d5 c4 e6 Nc3 c6 e3 Nbd7 Qc2 Bd6 Bd3 O-O O-O dxc4 Bxc4 a6 a4 c5 | Score: 20
d4 Nf6 c4 g6 Nc3 Bg7 e4 d6 f3 O-O Be3 e5 Nge2 c6 Qd2 Nbd7 O-O-O a6 Kb1 b5 | Score: 31
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Be2 e6 a4 Nc6 Be3 Be7 O-O O-O f4 Qc7 | Score: 24
c4 c5 Nf3 Nf6 Nc3 e6 g3 b6 Bg2 Bb7 O-O Be7 d4 cxd4 Qxd4 d6 e4 O-O b3 Nbd7 | Score: 33
Nf3 Nf6 c4 c5 Nc3 e6 g3 d5 cxd5 exd5 d4 Nc6 Bg2 Be7 O-O O-O Be3 c4 Ne5 h6 | Score: 30
Nf3 Nf6 c4 c5 g3 b6 Bg2 Bb7 O-O e6 d4 cxd4 Qxd4 d6 Nc3 Be7 Rd1 a6 b3 Nbd7 | Score: 33
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 d3 b5 Bb3 O-O Nc3 d6 a3 Rb8 Nd5 Nxd5 | Score: 27
c4 c5 Nf3 Nf6 Nc3 e6 g3 b6 Bg2 Bb7 O-O d6 d4 cxd4 Qxd4 a6 Rd1 Be7 b3 Nbd7 | Score: 14
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Be3 Ng4 Bg5 h6 Bh4 g5 Bg3 Bg7 Be2 h5 | Score: 20
Nf3 d5 d4 Nf6 c4 e6 Nc3 dxc4 e3 a6 a4 c5 Bxc4 Nc6 O-O Be7 Qe2 cxd4 Rd1 e5 | Score: 32
d4 Nf6 Nf3 d5 c4 e6 Nc3 c6 e3 Nbd7 Qc2 Bd6 b3 O-O Be2 a6 O-O e5 cxd5 cxd5 | Score: 33
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nf6 Nc3 d6 Be2 a6 O-O Be7 f4 Qc7 a4 Nc6 Be3 O-O | Score: 27
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nf6 Nc3 d6 Be2 Be7 O-O O-O f4 a6 Kh1 Qc7 a4 Re8 | Score: 31
d4 d5 c4 dxc4 Nf3 Nf6 e3 e6 Bxc4 c5 O-O a6 a4 Nc6 Qe2 Be7 Rd1 Qc7 Nc3 O-O | Score: 9
Nf3 Nf6 c4 e6 Nc3 d5 d4 Be7 Bg5 h6 Bh4 O-O Qc2 b6 cxd5 exd5 e3 Bb7 Bd3 c5 | Score: 27
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nf6 Nc3 d6 Be2 Be7 O-O a6 a4 O-O f4 Qc7 Qe1 Nc6 | Score: 22
d4 d6 Nf3 g6 g3 Bg7 Bg2 Nd7 O-O e5 e4 Ngf6 Nc3 O-O a4 a6 dxe5 dxe5 b3 Re8 | Score: 34
e4 c6 d4 d5 Nd2 g6 c3 Bg7 e5 f6 f4 Nh6 Ngf3 O-O Be2 fxe5 fxe5 c5 Nb3 cxd4 | Score: 29
e4 c5 Nf3 d6 d4 Nf6 Nc3 cxd4 Nxd4 a6 a4 e6 Be2 Be7 O-O O-O f4 Nc6 Be3 Qc7 | Score: 24
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 f4 Qc7 a4 g6 Nf3 Bg4 Bd3 Nc6 h3 Bxf3 | Score: 22
d4 d5 c4 c6 Nf3 Nf6 Nc3 e6 g3 Nbd7 Bg2 dxc4 a4 Be7 O-O O-O e4 e5 dxe5 Ng4 | Score: 18
d4 Nf6 c4 e6 Nc3 Bb4 e3 b6 Bd3 Bb7 Nf3 O-O O-O Bxc3 bxc3 c5 Nd2 d6 e4 Nc6 | Score: 31
e4 c5 Nf3 Nc6 Nc3 e5 Bc4 Be7 d3 d6 Nd2 Bg5 h4 Bh6 Qh5 g6 Qd1 Nf6 Nf1 Bxc1 | Score: 27
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Bg2 c6 O-O d5 Qc2 Nbd7 Rd1 O-O | Score: 11
Nf3 Nf6 c4 b6 g3 Bb7 Bg2 e6 O-O Be7 Nc3 O-O d4 Ne4 Bd2 Bf6 Rc1 d6 d5 Nxd2 | Score: 21
d4 Nf6 c4 e6 Nf3 d5 Nc3 Nbd7 Bg5 c6 e3 Qa5 Nd2 Bb4 Qc2 O-O Be2 c5 Nb3 Qc7 | Score: 17
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 c5 dxc5 Bxc5 Nf3 Qc7 Bg5 a6 e3 Be7 Be2 b6 Rd1 d6 | Score: 23
d4 Nf6 c4 g6 Nf3 Bg7 g3 O-O Bg2 d6 O-O Nbd7 Nc3 e5 Qc2 c6 Rd1 Qe7 b3 exd4 | Score: 29
e4 c5 Nf3 e6 Nc3 d6 d4 cxd4 Nxd4 a6 Bd3 Nf6 O-O Be7 f4 O-O Be3 b5 e5 dxe5 | Score: 21
d4 d5 c4 c6 Nc3 Nf6 e3 e6 Nf3 Nbd7 Qc2 Bd6 Bd3 O-O O-O dxc4 Bxc4 a6 a4 c5 | Score: 22
c4 c5 Nf3 Nf6 Nc3 Nc6 e3 e6 d4 d5 dxc5 Bxc5 a3 a6 b4 Ba7 Bb2 O-O Be2 dxc4 | Score: 14
d4 Nf6 Nf3 e6 Bg5 c5 e3 d5 Nbd2 h6 Bh4 Nbd7 c3 Be7 Bd3 b6 O-O Bb7 Qe2 Ne4 | Score: 7
Nf3 Nf6 c4 b6 g3 Bb7 Bg2 e6 O-O Be7 d4 O-O Nc3 Ne4 Qc2 Nxc3 Qxc3 d6 b3 f5 | Score: 32
c4 Nf6 Nc3 e6 Nf3 c5 g3 b6 Bg2 Bb7 O-O a6 b3 d6 Bb2 Be7 d4 cxd4 Nxd4 Bxg2 | Score: 28
d4 e6 e4 c5 d5 exd5 exd5 d6 Nc3 Nf6 Be2 Be7 Nf3 O-O O-O Na6 h3 Nc7 Nh2 a6 | Score: 21
d4 Nf6 Nf3 e6 c4 b6 g3 Bb7 Bg2 Be7 O-O O-O b3 c5 Bb2 cxd4 Qxd4 Nc6 Qf4 d5 | Score: 31
e4 e6 d4 d5 Nc3 Nf6 Bg5 Bb4 e5 h6 Be3 Ne4 Qg4 Kf8 a3 Bxc3+ bxc3 c5 Bd3 h5 | Score: 34
e4 c6 d4 d5 e5 Bf5 c4 e6 Nc3 dxc4 Bxc4 Ne7 Nge2 Nd7 O-O Nb6 Bb3 Qd7 a4 a5 | Score: 17
d4 Nf6 c4 e6 g3 c5 d5 exd5 cxd5 b5 Bg2 d6 b4 Na6 bxc5 Nxc5 Nf3 g6 O-O Bg7 | Score: 33
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 e6 Be2 Be7 O-O O-O Be3 a6 a4 Nc6 f4 Bd7 | Score: 22
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Be2 e6 a4 Nc6 O-O Be7 Be3 O-O f4 Qc7 | Score: 34
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Be2 e6 f4 Be7 O-O O-O a4 Nc6 Be3 Qc7 | Score: 24
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 e6 Nc3 Qc7 g3 a6 Bg2 Nf6 O-O Be7 b3 O-O Bb2 d6 | Score: 33
e4 e6 d4 d5 e5 c5 c3 Nc6 Nf3 Bd7 Be2 Rc8 O-O a6 a3 cxd4 cxd4 Nge7 Nc3 Nf5 | Score: 16
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 b5 Bb3 O-O d4 d6 c3 Bg4 Be3 exd4 | Score: 32
c4 c6 Nf3 d5 e3 Nf6 Nc3 a6 b3 e6 Bb2 Bd6 d4 Nbd7 Be2 O-O Qc2 e5 cxd5 cxd5 | Score: 29
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Be3 e6 a4 Nc6 Be2 Be7 O-O O-O f4 Bd7 | Score: 24
d4 Nf6 c4 e6 Nf3 b6 a3 Ba6 Qc2 Bb7 Nc3 c5 e4 cxd4 Nxd4 Bc5 Nb3 Nc6 Bg5 h6 | Score: 18
Nf3 Nf6 c4 c5 g3 b6 Bg2 Bb7 O-O g6 b3 d5 cxd5 Bg7 Bb2 O-O d4 Nxd5 Qd2 Nc7 | Score: 13
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nc6 Nc3 a6 f4 Qc7 Be3 b5 Nb3 Nf6 Bd3 d6 O-O Be7 | Score: 20
d4 Nf6 c4 c5 d5 e6 Nc3 exd5 cxd5 d6 e4 g6 Bb5+ Nbd7 f4 Bg7 Nf3 O-O O-O a6 | Score: 14
d4 Nf6 c4 c5 d5 e6 Nc3 exd5 cxd5 d6 e4 g6 h3 Bg7 Nf3 O-O Bd3 b5 Bxb5 Nxe4 | Score: 24
d4 Nf6 c4 e6 g3 d5 Nf3 Be7 Bg2 O-O O-O dxc4 Qa4 a6 Qxc4 b5 Qc2 Bb7 Bd2 Be4 | Score: 13
Nf3 Nf6 c4 g6 g3 Bg7 Bg2 O-O O-O d5 cxd5 Nxd5 d4 Nb6 Nc3 Nc6 e3 Re8 d5 Na5 | Score: 34
d4 Nf6 c4 g6 g3 c6 Bg2 d5 cxd5 cxd5 Nf3 Bg7 Ne5 O-O Nc3 e6 O-O Nfd7 f4 Nc6 | Score: 31
c4 g6 e4 Bg7 d4 d6 Nc3 Nf6 f3 O-O Bg5 a6 Qd2 Nbd7 Nge2 c5 Bh6 Bxh6 Qxh6 b5 | Score: 23
e4 c6 Nc3 d5 Nf3 Bg4 h3 Bxf3 Qxf3 e6 d3 Nd7 Be2 g6 O-O Bg7 Qg3 Qb6 Kh1 Ne7 | Score: 11
e4 c5 Nf3 d6 d4 cxd4 Qxd4 Bd7 c4 Nc6 Qd2 Nf6 Nc3 g6 b3 Bg7 Bb2 O-O Be2 Qa5 | Score: 29
d4 Nf6 c4 e6 g3 d5 Bg2 Be7 Nf3 O-O O-O dxc4 Qc2 a6 Qxc4 b5 Qc2 Bb7 Bd2 Be4 | Score: 27
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 g6 Nc3 Bg7 Be3 Nf6 Bc4 O-O Bb3 d6 h3 a5 a4 Nxd4 | Score: 15
Nf3 Nf6 g3 b5 Bg2 Bb7 O-O e6 d3 d6 e4 c5 a4 a6 axb5 axb5 Rxa8 Bxa8 Na3 Bc6 | Score: 16
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 e6 Nb5 d6 c4 Nf6 N1c3 a6 Na3 Be7 Be2 O-O O-O b6 | Score: 28
d4 d5 Nf3 Nf6 c4 e6 cxd5 exd5 Nc3 c6 Qc2 Na6 a3 Nc7 Bg5 g6 e3 Bf5 Bd3 Bxd3 | Score: 8
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 Nc6 Bg5 Bd7 Qd2 Rc8 Nb3 a6 Be2 e6 O-O h6 | Score: 17
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Be2 e5 Nb3 Be6 O-O Nbd7 a4 Be7 f4 Qc7 | Score: 28
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 Qc7 Nc3 e6 Be2 a6 O-O Nf6 Be3 Be7 f4 d6 Qe1 O-O | Score: 32
d4 d5 c4 e6 Nc3 Be7 Nf3 Nf6 Bf4 O-O e3 c5 dxc5 Bxc5 Qc2 Nc6 Rd1 Qa5 a3 Be7 | Score: 26
e4 c5 Nf3 e6 d4 cxd4 Nxd4 a6 Bd3 Nf6 O-O d6 c4 Be7 Nc3 O-O Qe2 Re8 Rd1 Qc7 | Score: 32
d4 Nf6 c4 g6 Nf3 Bg7 g3 c6 Bg2 d5 cxd5 cxd5 Nc3 O-O Ne5 e6 O-O Nfd7 f4 Nc6 | Score: 31
d4 Nf6 c4 g6 Nf3 Bg7 g3 c6 Nc3 d5 cxd5 cxd5 Bg2 O-O Ne5 e6 O-O Nfd7 f4 Nc6 | Score: 34
d4 Nf6 c4 e6 Nf3 b6 g3 Bb7 Bg2 Be7 O-O O-O Nc3 Ne4 Qc2 Nxc3 Qxc3 c5 b3 Bf6 | Score: 34
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Be2 e6 O-O Be7 f4 O-O Kh1 Qc7 Bf3 Nc6 | Score: 12
d4 c6 c4 Nf6 Nc3 d5 Nf3 g6 cxd5 cxd5 Bf4 Nc6 e3 Bg7 Be2 O-O O-O Nh5 Be5 f6 | Score: 31
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nc6 Nc3 d6 Be2 Nf6 O-O Be7 Be3 O-O f4 Qc7 Nb3 b6 | Score: 25
Nf3 Nf6 g3 b6 Bg2 Bb7 O-O e6 c4 Be7 Nc3 O-O d4 Ne4 Qc2 Nxc3 Qxc3 c5 Rd1 d6 | Score: 21
d4 Nf6 c4 e6 Nc3 Bb4 e3 O-O Bd3 d5 Nf3 b6 O-O Bb7 a3 Bd6 b4 dxc4 Bxc4 Nbd7 | Score: 19
d4 d5 c4 e6 Nc3 Nf6 cxd5 exd5 Bg5 Be7 e3 h6 Bh4 O-O Bd3 b6 Nf3 Bb7 O-O Ne4 | Score: 23
d4 Nf6 c4 e6 Nc3 Bb4 e3 c5 Bd3 Nc6 a3 Bxc3+ bxc3 d6 Ne2 e5 e4 O-O O-O exd4 | Score: 21
d4 d5 c4 c6 Nf3 Nf6 Nc3 e6 e3 Nbd7 Qc2 Bd6 Bd3 O-O O-O dxc4 Bxc4 a6 Rd1 b5 | Score: 10
d4 d5 c4 c6 Nf3 Nf6 e3 Bg4 h3 Bxf3 Qxf3 e6 Nc3 Nbd7 Bd2 Bb4 a3 Ba5 Rd1 O-O | Score: 21
d4 Nf6 c4 e6 Nf3 d5 Nc3 c6 e3 Nbd7 Qc2 Bd6 Bd3 O-O O-O dxc4 Bxc4 a6 Rd1 b5 | Score: 21
d4 Nf6 Nf3 d5 c4 e6 g3 Be7 Bg2 O-O O-O dxc4 Qc2 a6 a4 Bd7 Qxc4 Bc6 Bg5 Bd5 | Score: 25
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Bg2 c6 O-O d5 Bc3 Nbd7 Nbd2 O-O | Score: 22
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 Qa4 Bb7 Bg2 c5 dxc5 bxc5 O-O Be7 Nc3 O-O Rd1 d6 | Score: 29
d4 Nf6 c4 g6 g3 Bg7 Bg2 d5 cxd5 Nxd5 Nf3 O-O O-O Nb6 Nc3 Nc6 e3 Re8 Re1 a5 | Score: 19
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Be2 e6 O-O Be7 f4 Qc7 Kh1 O-O Qe1 Nc6 | Score: 30
Nf3 Nf6 d4 e6 e3 b6 Bd3 Bb7 O-O Be7 c4 O-O Nc3 d5 cxd5 exd5 b3 Ne4 Bb2 Nd7 | Score: 33
e4 c5 Nf3 d6 Bb5+ Nd7 d4 Nf6 Nc3 cxd4 Qxd4 e5 Qd3 h6 Be3 a6 Bc4 b5 Bd5 Rb8 | Score: 20
Nf3 Nf6 c4 e6 g3 a6 Bg2 b5 b3 c5 Nc3 Qb6 O-O Bb7 Rb1 Be7 d4 cxd4 Qxd4 Qxd4 | Score: 27
d4 Nf6 c4 e6 g3 d5 Bg2 Be7 Nf3 O-O O-O dxc4 Qc2 a6 Qxc4 b5 Qc2 Bb7 Bf4 Nc6 | Score: 12
d4 Nf6 c4 g6 Nf3 Bg7 g3 c6 Bg2 d5 cxd5 cxd5 Ne5 O-O Nc3 e6 O-O Nfd7 f4 Nc6 | Score: 26
d4 Nf6 Nf3 g6 c4 Bg7 g3 O-O Bg2 d5 O-O dxc4 Na3 Na6 Nxc4 c5 b3 Bf5 Bb2 Be4 | Score: 30
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nc6 Nb5 Nf6 N1c3 d6 Bf4 e5 Bg5 a6 Na3 b5 Nd5 Be7 | Score: 23
Nf3 Nf6 c4 g6 g3 Bg7 Bg2 O-O d4 c6 Nc3 d5 cxd5 cxd5 Ne5 e6 O-O Nfd7 f4 Nc6 | Score: 22
Nf3 Nf6 c4 e6 g3 b6 Bg2 Bb7 O-O Be7 d4 O-O Nc3 Ne4 Qc2 Nxc3 Qxc3 c5 Rd1 d6 | Score: 31
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nf6 Nc3 d6 g4 h6 h4 Nc6 Rg1 d5 Bb5 Bd7 exd5 Nxd5 | Score: 21
d4 d6 e4 Nf6 Nc3 g6 Nf3 Bg7 Be2 O-O O-O Bg4 Be3 Nc6 Qd2 e5 d5 Ne7 Rad1 Bd7 | Score: 31
Nf3 Nf6 c4 b6 g3 c5 Bg2 Bb7 O-O e6 Nc3 Be7 Re1 d5 cxd5 Nxd5 e4 Nb4 d4 cxd4 | Score: 12
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 b5 Bb3 O-O d3 Bb7 Nbd2 h6 Nf1 Re8 | Score: 31
d4 Nf6 c4 g6 g3 Bg7 Bg2 O-O Nf3 c5 d5 e6 Nc3 d6 O-O exd5 cxd5 Nbd7 Nd2 Re8 | Score: 26
d4 Nf6 Nf3 e6 c4 b6 g3 Ba6 Nbd2 c5 Bg2 Nc6 dxc5 Bxc5 O-O O-O a3 Be7 b4 Bb7 | Score: 21
e4 e5 Nf3 Nf6 Nxe5 d6 Nf3 Nxe4 d4 d5 Bd3 Be7 O-O Nc6 Re1 Bf5 a3 O-O c4 Bf6 | Score: 13
e4 c5 Nf3 e6 d4 cxd4 Nxd4 a6 Nc3 b5 Bd3 Qb6 Nb3 Qc7 f4 d6 O-O Nd7 Kh1 Ngf6 | Score: 17
e4 e5 Nf3 Nf6 Nxe5 d6 Nf3 Nxe4 d4 d5 Bd3 Be7 O-O Nc6 c4 Nb4 Be2 O-O a3 Nc6 | Score: 29
d4 d5 c4 e6 Nf3 Nf6 Nc3 Be7 Bg5 O-O e3 h6 Bh4 Ne4 Bxe7 Qxe7 Rc1 c6 Be2 Nd7 | Score: 23
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 Nbd2 Bb7 Bg2 Be7 O-O O-O b3 c5 dxc5 Bxc5 Bb2 d5 | Score: 26
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Be2 e6 f4 Be7 O-O Qc7 Bf3 Nc6 Be3 Bd7 | Score: 17
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 e6 Nc3 Qc7 Be3 a6 Bd3 Nf6 O-O Ne5 h3 Bc5 Kh1 d6 | Score: 24
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Bg2 c6 Bc3 d5 Nbd2 O-O O-O Nbd7 | Score: 34
Nf3 c5 c4 Nf6 Nc3 e6 e3 Nc6 d4 d5 a3 a6 dxc5 Bxc5 b4 Bd6 Bb2 O-O cxd5 exd5 | Score: 22
Nf3 Nf6 c4 e6 g3 b6 Bg2 Bb7 O-O c5 d4 cxd4 Qxd4 d6 Nc3 a6 Rd1 Nbd7 Bg5 Be7 | Score: 28
e4 c5 Nf3 e6 d4 cxd4 Nxd4 a6 Nc3 Qc7 Bd3 Nc6 Be3 Nf6 O-O Ne5 h3 Bc5 Kh1 d6 | Score: 21
d4 Nf6 c4 e6 Nc3 d5 Bg5 Nbd7 e3 Be7 Nf3 O-O Qc2 a6 cxd5 exd5 Bd3 h6 Bf4 c5 | Score: 32
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nc6 Nc3 Qc7 Be3 a6 Bd3 Nf6 O-O Ne5 h3 Bc5 Kh1 d6 | Score: 18
d4 Nf6 Nf3 e6 Bg5 h6 Bh4 b6 e3 Bb7 Nbd2 c5 c3 Be7 Bd3 cxd4 cxd4 Nc6 a3 O-O | Score: 28
Nf3 Nf6 c4 e6 d4 b6 g3 Bb7 Bg2 Be7 O-O O-O Nc3 Ne4 Qc2 Nxc3 Qxc3 d6 b3 Nd7 | Score: 30
c4 e6 Nf3 d5 d4 Nf6 Nc3 c6 e3 Nbd7 Bd3 dxc4 Bxc4 b5 Bd3 Bb7 O-O b4 Ne4 Be7 | Score: 30
d4 Nf6 c4 e6 Nf3 b6 g3 Bb7 Bg2 Be7 O-O O-O Nc3 Ne4 Qc2 Nxc3 Qxc3 f5 b3 Bf6 | Score: 23
d4 Nf6 c4 e6 Nf3 d5 g3 Be7 Bg2 O-O O-O dxc4 Qc2 a6 Qxc4 b5 Qc2 Bb7 Bd2 Be4 | Score: 11
e4 c5 Nf3 e6 d4 cxd4 Nxd4 a6 Nc3 Qc7 g3 Nf6 Bg2 Be7 O-O O-O Qe2 d6 Be3 Nc6 | Score: 30
Nf3 Nf6 c4 b6 g3 Bb7 Bg2 g6 d4 Bg7 O-O O-O Nc3 Ne4 Nxe4 Bxe4 Be3 c5 Qd2 d6 | Score: 22
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 g6 Nc3 Bg7 Nb3 Nf6 Be2 O-O O-O a5 a4 d6 Bg5 Be6 | Score: 25
d4 Nf6 c4 e6 Nf3 b6 a3 d5 Nc3 Be7 cxd5 exd5 g3 O-O Bg2 c5 O-O Bb7 Qc2 Nbd7 | Score: 27
c4 Nf6 Nf3 b6 g3 c5 Bg2 Bb7 O-O g6 d4 cxd4 Qxd4 Bg7 Nc3 d6 Rd1 Nbd7 Be3 a6 | Score: 31
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Nxe4 d4 b5 Bb3 d5 dxe5 Be6 Nbd2 Nc5 c3 d4 | Score: 28
d4 Nf6 c4 g6 g3 c6 Bg2 d5 cxd5 cxd5 Nf3 Bg7 Nc3 O-O Ne5 e6 O-O Nfd7 f4 Nc6 | Score: 28
d4 Nf6 Nf3 g6 c4 Bg7 g3 O-O Bg2 c6 Nc3 d5 cxd5 cxd5 Ne5 e6 O-O Nfd7 f4 Nc6 | Score: 23
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 Nc6 Bg5 e6 Qd2 a6 O-O-O h6 Be3 Bd7 f4 b5 | Score: 25
d4 d5 Nf3 Nf6 c4 c6 Nc3 dxc4 a4 Bf5 e3 e6 Bxc4 Bb4 O-O Nbd7 Nh4 Bg6 h3 Bh5 | Score: 34
d4 Nf6 c4 g6 Nf3 Bg7 g3 d5 cxd5 Nxd5 Bg2 O-O O-O Nb6 Nc3 Nc6 e3 Re8 d5 Na5 | Score: 23
d4 d5 c4 c6 Nf3 Nf6 e3 Bf5 Nc3 e6 Nh4 Be4 f3 Bg6 Qb3 Qb6 Nxg6 hxg6 g3 Nbd7 | Score: 24
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Bg2 c6 Bc3 d5 Nbd2 Nbd7 O-O O-O | Score: 24
d4 Nf6 c4 e6 Nf3 d5 Nc3 Be7 Bf4 O-O e3 b6 Bd3 Bb7 O-O c5 Qe2 Nc6 dxc5 bxc5 | Score: 26
Nf3 Nf6 c4 e6 g3 b6 Bg2 Bb7 O-O Be7 Nc3 O-O d4 Ne4 Qc2 Nxc3 Qxc3 c5 Rd1 d6 | Score: 30
d4 d5 c4 c6 Nf3 Nf6 e3 Bf5 Nc3 e6 Nh4 Be4 f3 Bg6 Qb3 Qc7 Bd2 Be7 Nxg6 hxg6 | Score: 30
d4 d5 c4 e6 Nf3 Nf6 g3 Be7 Bg2 O-O O-O dxc4 Qc2 a6 Qxc4 b5 Qc2 Bb7 Bd2 Be4 | Score: 16
d4 d5 c4 c6 Nc3 dxc4 Nf3 Nf6 a4 Bf5 e3 e6 Bxc4 Bb4 O-O Nbd7 Nh4 Bg6 g3 O-O | Score: 22
d4 Nf6 c4 e6 g3 d5 Nf3 Be7 Bg2 O-O O-O dxc4 Qc2 a6 Qxc4 b5 Qc2 Bb7 Bd2 Be4 | Score: 21
d4 Nf6 c4 e6 Nc3 d5 cxd5 exd5 Bg5 c6 Qc2 Na6 e3 Nc7 Bd3 Ne6 Bh4 g6 Nf3 Be7 | Score: 29
d4 Nf6 c4 e6 Nc3 Bb4 e3 O-O Nf3 b6 Bd3 Bb7 O-O d5 a3 Bd6 b4 dxc4 Bxc4 Nbd7 | Score: 24
d4 Nf6 c4 e6 Nc3 Bb4 Nf3 Ne4 Qc2 f5 g3 Nc6 Bg2 O-O O-O Bxc3 bxc3 Na5 c5 d6 | Score: 34
d4 Nf6 c4 e6 Nf3 Bb4+ Bd2 c5 Bxb4 cxb4 Qd3 d6 e4 O-O Nbd2 a5 g3 b6 Bg2 Bb7 | Score: 33
Nf3 Nf6 c4 g6 g3 Bg7 Bg2 d5 cxd5 Nxd5 d4 Nb6 Nc3 Nc6 e3 O-O O-O Re8 d5 Na5 | Score: 22
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 Nbd2 d5 Bg2 Be7 O-O O-O Ne5 Bb7 cxd5 exd5 b3 a5 | Score: 33
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Bg5 e6 f4 Qc7 Bd3 Nbd7 Qe2 Be7 Nf3 h6 | Score: 0
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nf6 Nc3 Nc6 Ndb5 d6 Bf4 e5 Bg5 a6 Na3 b5 Nd5 Be7 | Score: 34
e4 d6 d4 g6 Nf3 Bg7 Be2 Nf6 Nc3 O-O O-O c5 d5 Na6 Re1 Nc7 Bf4 b5 Nxb5 Nxe4 | Score: 21
Nf3 d5 d4 Nf6 c4 e6 Nc3 c6 cxd5 exd5 Qc2 Na6 a3 Nc7 Bg5 g6 e3 Bf5 Bd3 Bxd3 | Score: 21
d4 Nf6 c4 c5 Nf3 e6 g3 cxd4 Nxd4 d5 Bg2 e5 Nf3 d4 O-O Nc6 e3 Be7 exd4 exd4 | Score: 28
d4 d5 c4 e6 Nc3 c6 Nf3 dxc4 a4 Bb4 e3 b5 Bd2 a5 axb5 Bxc3 Bxc3 cxb5 b3 Bb7 | Score: 32
Nf3 d5 d4 Nf6 c4 e6 g3 Be7 Bg2 O-O O-O dxc4 Qc2 a6 a4 Bd7 Qxc4 Bc6 Bg5 Bd5 | Score: 30
d4 Nf6 c4 g6 Nc3 d5 Nf3 Bg7 Qb3 dxc4 Qxc4 O-O e4 a6 e5 b5 Qb3 Nfd7 e6 fxe6 | Score: 17
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 d5 cxd5 Qxd5 Nf3 Qf5 Qb3 Nc6 Bd2 O-O h3 a5 g4 Qg6 | Score: 18
d4 d5 c4 dxc4 Nf3 Nf6 e3 e6 Bxc4 c5 O-O a6 a4 Nc6 Nc3 Be7 Qe2 cxd4 Rd1 O-O | Score: 29
Nf3 Nf6 c4 b6 g3 c5 Bg2 Bb7 O-O g6 Nc3 Bg7 d4 cxd4 Qxd4 d6 b3 Nbd7 Bb2 O-O | Score: 20
d4 d5 c4 e6 Nc3 Be7 Nf3 Nf6 Bf4 O-O e3 c5 dxc5 Bxc5 a3 Nc6 Qc2 Qa5 Rd1 Be7 | Score: 28
d4 Nf6 Nf3 g6 c4 Bg7 g3 c6 Bg2 d5 cxd5 cxd5 Nc3 O-O Ne5 e6 O-O Nfd7 f4 Nc6 | Score: 32
e4 c6 d4 d5 Nc3 dxe4 Nxe4 Bf5 Ng3 Bg6 h4 h6 Nh3 Nd7 Nf4 Bh7 Bc4 e5 Qe2 Qe7 | Score: 34
e4 c5 Nf3 e6 d4 cxd4 Nxd4 a6 c4 Nf6 Nc3 Bb4 Bd2 O-O e5 Ne8 Nc2 Be7 Bd3 Nc6 | Score: 26
d4 d5 c4 c6 Nf3 Nf6 e3 Bg4 h3 Bxf3 Qxf3 e6 Nc3 Nbd7 Bd3 g6 O-O Bg7 Rd1 O-O | Score: 30
d4 Nf6 c4 e6 Nf3 Bb4+ Bd2 c5 Bxb4 cxb4 g3 b6 Bg2 Bb7 O-O O-O Qb3 a5 a3 Na6 | Score: 20
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 d5 cxd5 exd5 Bg5 h6 Bh4 c5 dxc5 Nc6 e3 g5 Bg3 Ne4 | Score: 32
Nf3 Nf6 d4 e6 c4 b6 g3 Bb7 Bg2 Be7 O-O O-O Nc3 Ne4 Qc2 Nxc3 Qxc3 c5 b3 Bf6 | Score: 31
Nf3 Nf6 c4 b6 g3 e6 Bg2 Bb7 O-O Be7 Nc3 O-O d4 Ne4 Bd2 d6 Rc1 Nxd2 Qxd2 c5 | Score: 16
Nf3 Nf6 c4 e6 g3 d5 d4 Be7 Bg2 O-O O-O dxc4 Qc2 a6 Qxc4 b5 Qc2 Bb7 Bf4 Nd5 | Score: 29
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 b5 cxb5 Bxb5 Bg2 Bb4+ Bd2 a5 O-O O-O Re1 Bc6 | Score: 30
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb7 Bg2 Bb4+ Bd2 a5 O-O O-O Nc3 d5 cxd5 Bxc3 | Score: 33
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 d6 c3 Bd7 d4 Nge7 Bb3 h6 Nh4 Na5 Bc2 c5 dxc5 dxc5 | Score: 26
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Nxe4 d4 b5 Bb3 d5 dxe5 Be6 Qe2 Be7 c3 O-O | Score: 15
Nf3 c5 c4 Nc6 Nc3 Nd4 e3 Nxf3+ Qxf3 g6 b3 Bg7 Bb2 d6 g3 Nh6 Bg2 Rb8 Qe2 a6 | Score: 23
d4 d5 c4 c6 Nc3 Nf6 e3 g6 Nf3 Bg7 Bd3 O-O O-O Bg4 h3 Bxf3 Qxf3 e6 Rd1 Nbd7 | Score: 26
e4 Nf6 e5 Nd5 d4 d6 Nf3 Bg4 Be2 e6 O-O Be7 c4 Nb6 exd6 cxd6 Nc3 O-O Be3 d5 | Score: 23
d4 Nf6 c4 e6 g3 d5 Nf3 Be7 Bg2 O-O O-O dxc4 Qc2 a6 a4 Bd7 Qxc4 Bc6 Bg5 Bd5 | Score: 28
e4 c5 c3 Nf6 e5 Nd5 Nf3 Nc6 Bc4 Nb6 Bb3 d5 exd6 exd6 d4 Bg4 h3 Bh5 Be3 Be7 | Score: 20
d4 Nf6 c4 e6 Nf3 b6 a3 Bb7 Nc3 d5 Qc2 dxc4 e4 c5 d5 exd5 exd5 Bd6 Bxc4 O-O | Score: 28
d4 Nf6 c4 e6 Nf3 b6 a3 Bb7 Nc3 d5 cxd5 exd5 Qa4+ c6 g3 Bd6 Bg2 O-O O-O Re8 | Score: 25
d4 Nf6 Nf3 g6 c4 Bg7 g3 d5 cxd5 Nxd5 Bg2 Nb6 O-O Nc6 e3 O-O Nc3 Re8 Re1 a5 | Score: 28
d4 Nf6 c4 e6 Nf3 d5 Bg5 h6 Bxf6 Qxf6 Nc3 c6 e3 Nd7 Bd3 Bd6 O-O Qe7 Nd2 O-O | Score: 22
e4 d6 d4 Nf6 Nc3 e5 Nf3 Nbd7 Bc4 Be7 O-O O-O Re1 c6 a4 b6 d5 cxd5 Nxd5 Bb7 | Score: 25
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 f4 Qc7 Bd3 g6 Nf3 Bg7 O-O Nbd7 Kh1 b5 | Score: 20
d4 Nf6 Nf3 e6 c4 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Bg2 c6 Bc3 d5 Nbd2 Nbd7 O-O O-O | Score: 26
Nf3 f5 g3 Nf6 Bg2 g6 O-O Bg7 d3 d6 Nc3 e5 e4 fxe4 dxe4 O-O Be3 Nc6 Qd2 Kh8 | Score: 20
d4 d5 c4 c6 Nc3 Nf6 e3 e6 Nf3 Nbd7 Qc2 Bd6 Bd3 O-O O-O dxc4 Bxc4 a6 Rd1 b5 | Score: 24
d4 Nf6 c4 e6 Nc3 Bb4 e3 O-O Bd3 c5 Nf3 d5 O-O dxc4 Bxc4 a6 a3 Ba5 Bd3 Nbd7 | Score: 32
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 O-O a3 Bxc3+ Qxc3 b6 Bg5 Bb7 e3 d6 f3 Nbd7 Bd3 c5 | Score: 19
Nf3 Nf6 g3 b6 Bg2 Bb7 c4 e6 O-O Be7 Nc3 O-O d4 Ne4 Nxe4 Bxe4 Ne1 d5 Qa4 c5 | Score: 23
Nf3 Nf6 c4 b6 g3 Bb7 Bg2 e6 O-O Be7 d4 O-O Nc3 Ne4 Qc2 Nxc3 Qxc3 c5 Rd1 d6 | Score: 25
d4 Nf6 c4 e6 g3 d5 Bg2 Be7 Nf3 O-O O-O dxc4 Qc2 a6 Qxc4 b5 Qc2 Bb7 Bd2 Ra7 | Score: 32
d4 Nf6 c4 g6 Nf3 Bg7 g3 O-O Bg2 d5 O-O c6 cxd5 cxd5 Nc3 e6 Ne5 Nfd7 f4 Nc6 | Score: 19
d4 d5 c4 c6 cxd5 cxd5 Nc3 Nf6 Bf4 Nc6 e3 Bg4 Nf3 e6 Bb5 Nd7 h3 Bh5 O-O Be7 | Score: 21
Nf3 Nf6 c4 e6 Nc3 d5 d4 Be7 Bf4 O-O e3 c5 dxc5 Bxc5 Qc2 Nc6 Rd1 Qa5 a3 Be7 | Score: 29
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Bg2 c6 O-O d5 Bc3 O-O Nbd2 Nbd7 | Score: 23
Nf3 Nf6 g3 b5 Bg2 Bb7 O-O e6 d3 Be7 e4 d6 a4 a6 axb5 axb5 Rxa8 Bxa8 Na3 b4 | Score: 18
Nf3 Nf6 c4 e6 g3 d5 d4 Be7 Bg2 O-O O-O dxc4 Qc2 a6 Qxc4 b5 Qc2 Bb7 Bf4 Nc6 | Score: 14
d4 Nf6 c4 e6 g3 d5 Bg2 Be7 Nf3 O-O O-O dxc4 Qc2 a6 a4 Bd7 Qxc4 Bc6 Bg5 Bd5 | Score: 29
Nf3 Nf6 c4 b6 g3 Bb7 Bg2 e6 O-O c5 Nc3 Be7 Re1 Ne4 Nxe4 Bxe4 d3 Bb7 e4 Nc6 | Score: 30
d4 d5 c4 c6 Nc3 e6 e3 Nf6 Nf3 Nbd7 Qc2 Bd6 Bd3 O-O O-O dxc4 Bxc4 a6 Rd1 b5 | Score: 24
e4 c6 d4 d5 e5 Bf5 Nf3 e6 Be2 Ne7 O-O c5 c4 Nbc6 dxc5 d4 Bd3 Bxd3 Qxd3 Ng6 | Score: 29
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O b5 Bb3 Bb7 d3 Be7 c4 bxc4 Bxc4 O-O Nc3 d6 | Score: 25
c4 Nf6 Nc3 e6 Nf3 d5 d4 Be7 Bg5 O-O e3 Nbd7 Rc1 c6 Bd3 dxc4 Bxc4 c5 O-O h6 | Score: 30
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 d5 cxd5 exd5 Bg5 h6 Bh4 c5 dxc5 g5 Bg3 Ne4 e3 Qa5 | Score: 18
e4 e5 Nf3 Nc6 Bb5 g6 c3 a6 Bc4 d6 d4 Bg7 Bg5 Qd7 dxe5 dxe5 Qe2 Nf6 Na3 O-O | Score: 17
d4 Nf6 c4 e6 Nf3 b6 g3 Bb7 Bg2 Be7 O-O O-O Nc3 Ne4 Qc2 Nxc3 Qxc3 c5 Rd1 d6 | Score: 24
d4 Nf6 c4 e6 Nf3 Bb4+ Bd2 a5 Nc3 b6 e3 Bb7 Bd3 O-O O-O d5 cxd5 exd5 a3 Bd6 | Score: 23
d4 Nf6 Nf3 g6 c4 Bg7 Nc3 d5 Qb3 dxc4 Qxc4 O-O e4 a6 Be2 b5 Qb3 c5 dxc5 Bb7 | Score: 19
d4 d5 c4 dxc4 Nf3 e6 e3 a6 Bxc4 c5 O-O Nf6 Bd3 b6 dxc5 Bxc5 a3 Bb7 Qe2 O-O | Score: 21
Nf3 Nf6 c4 b6 g3 Bb7 Bg2 e6 O-O Be7 Nc3 O-O Re1 d5 cxd5 exd5 d4 c5 Be3 Na6 | Score: 20
d4 Nf6 c4 g6 Nc3 d5 Nf3 Bg7 Qb3 dxc4 Qxc4 O-O e4 Na6 Be2 c5 d5 e6 Bg5 exd5 | Score: 17
d4 Nf6 c4 d6 Nf3 Bg4 Nbd2 Nbd7 h3 Bh5 Qb3 Rb8 e4 e5 Qe3 a5 Bd3 Be7 O-O O-O | Score: 14
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Be2 e5 Nb3 Be7 O-O O-O Kh1 b6 Bg5 Bb7 | Score: 12
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 Qc7 Nc3 e6 Be3 a6 Bd3 Nf6 O-O Ne5 h3 Bc5 Kh1 d6 | Score: 20
d4 d5 c4 c6 Nf3 Nf6 e3 Bf5 Bd3 Bxd3 Qxd3 e6 O-O Nbd7 Nc3 Bb4 Bd2 a5 a3 Be7 | Score: 25
d4 Nf6 c4 e6 Nc3 Bb4 e3 c5 Nf3 O-O Bd3 d5 O-O dxc4 Bxc4 Nbd7 Qe2 a6 a3 Ba5 | Score: 27
d4 d6 e4 g6 Nf3 Bg7 h3 Nf6 Nc3 O-O Be3 c6 a4 Nbd7 Qd2 e5 dxe5 dxe5 Rd1 Qe7 | Score: 20
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Nxe4 d4 b5 Bb3 d5 dxe5 Be6 Be3 Be7 c3 Qd7 | Score: 30
Nf3 c5 c4 Nf6 Nc3 e6 g3 b6 Bg2 Bb7 O-O Be7 Re1 d5 cxd5 Nxd5 e4 Nb4 d4 cxd4 | Score: 17
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 f4 e6 a4 Nc6 Be3 e5 Nf3 exf4 Bxf4 Be7 | Score: 30
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Bg2 c6 Bc3 O-O O-O d5 Nbd2 Nbd7 | Score: 21
d4 d5 c4 c6 Nf3 Nf6 e3 Bg4 h3 Bxf3 Qxf3 e6 Nc3 Nbd7 Bd3 Bb4 Bd2 O-O a3 Ba5 | Score: 30
Nf3 Nf6 c4 c5 g3 b6 Bg2 Bb7 O-O g6 Nc3 Bg7 d4 cxd4 Qxd4 d6 b3 Nbd7 Bb2 O-O | Score: 19
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Be2 e5 Nb3 Be7 O-O Be6 a4 Nbd7 f4 Qc7 | Score: 33
c4 e6 Nc3 d5 d4 c5 cxd5 exd5 Nf3 Nc6 g3 Nf6 Bg2 Be7 O-O O-O b3 Ne4 Bb2 Bf6 | Score: 25
d4 d5 c4 c6 Nf3 Nf6 Nc3 a6 Ne5 Nbd7 Bf4 e6 e3 Nxe5 Bxe5 Be7 c5 O-O Bd3 Nd7 | Score: 14
d4 Nf6 c4 e6 Nf3 Bb4+ Nbd2 b6 e3 Bb7 Bd3 O-O O-O d5 a3 Be7 b4 c5 bxc5 bxc5 | Score: 23
d4 Nf6 Nf3 e6 Bg5 h6 Bh4 b6 e3 Bb7 Nbd2 Be7 c3 c5 h3 O-O Bd3 cxd4 cxd4 Nc6 | Score: 21
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 f4 Qc7 Be2 e6 Bf3 Nc6 Be3 Be7 O-O O-O | Score: 17
Nf3 c5 c4 Nf6 Nc3 b6 e4 Nc6 d4 cxd4 Nxd4 Bb7 Bf4 d6 Nf3 g6 Qd2 Bg7 Be2 Rc8 | Score: 30
d4 Nf6 c4 e6 Nf3 Bb4+ Bd2 c5 Bxb4 cxb4 Qb3 a5 a3 Na6 Nbd2 d6 g3 b6 Bg2 Bb7 | Score: 25
c4 g6 e4 Bg7 d4 d6 Nc3 Nf6 f3 O-O Be3 Nbd7 Bd3 c5 Nge2 cxd4 Nxd4 e6 O-O d5 | Score: 33
e4 c5 Nf3 d6 Nc3 Nc6 d4 cxd4 Nxd4 g6 Nd5 e6 Nc3 Nf6 Be2 a6 O-O Bg7 Bg5 Qc7 | Score: 27
d4 Nf6 c4 e6 Nf3 d5 Nc3 c6 e3 Nbd7 Be2 Be7 O-O O-O Qc2 b6 e4 dxe4 Nxe4 Qc7 | Score: 19
d4 d5 c4 dxc4 e4 Nf6 e5 Nd5 Bxc4 Nb6 Bd3 Nc6 Be3 Be6 Ne2 Nb4 Be4 Bd5 f3 e6 | Score: 27
d4 Nf6 Nf3 d5 c4 dxc4 e3 e6 Bxc4 c5 O-O a6 a4 Nc6 Nc3 Be7 Qe2 cxd4 Rd1 O-O | Score: 32
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 d5 Bg2 dxc4 Ne5 Bb4+ Kf1 c6 bxc4 O-O Bb2 Qc7 | Score: 27
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb7 Bg2 d5 O-O Nbd7 Nc3 Bb4 Qc2 O-O cxd5 exd5 | Score: 31
d4 d5 c4 c6 Nf3 Nf6 e3 Bg4 h3 Bxf3 Qxf3 e6 Bd3 Nbd7 O-O Bd6 Nc3 O-O Rd1 Re8 | Score: 17
e4 e5 Nf3 Nf6 Nxe5 d6 Nf3 Nxe4 d3 Nf6 d4 Be7 Bd3 Bg4 O-O O-O h3 Bh5 Re1 Nc6 | Score: 33
d4 Nf6 c4 e6 Nf3 b6 a3 Bb7 Nc3 d5 cxd5 exd5 Qa4+ c6 g3 Be7 Bg2 O-O O-O Nbd7 | Score: 30
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Bg2 c6 O-O d5 Ne5 Nfd7 Nxd7 Nxd7 | Score: 18
d4 d5 c4 e6 Nc3 Be7 Bf4 Nf6 e3 O-O Rc1 Nbd7 cxd5 exd5 Nf3 c6 h3 Re8 Bd3 Nf8 | Score: 32
d4 Nf6 c4 e6 g3 Bb4+ Bd2 Be7 Bg2 d5 Nf3 O-O O-O c6 Qb3 b6 Nc3 Ba6 cxd5 cxd5 | Score: 26
d4 d5 c4 dxc4 Nf3 e6 e3 c5 Bxc4 a6 O-O Nf6 a4 Nc6 Qe2 cxd4 Rd1 Be7 exd4 O-O | Score: 34
d4 d5 c4 e6 Nf3 Nf6 g3 Be7 Bg2 O-O O-O dxc4 Qc2 a6 Qxc4 b5 Qc2 Bb7 Bg5 Nbd7 | Score: 24
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nc6 Nc3 a6 Be2 Qc7 f4 b5 Nxc6 Qxc6 Bf3 Bb7 e5 Qc7 | Score: 10
d4 Nf6 c4 e6 Nf3 b6 g3 Bb7 Bg2 Be7 O-O O-O Nc3 Ne4 Bd2 f5 Qc2 Bf6 Rad1 Nxc3 | Score: 27
e4 c5 Nf3 e6 d4 cxd4 Nxd4 a6 Nc3 Qc7 Be3 Bb4 Bd2 Nf6 Bd3 d6 O-O Bc5 Nb3 Ba7 | Score: 12
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 O-O a3 Bxc3+ Qxc3 d6 Nf3 Nbd7 g3 b6 Bg2 Bb7 O-O a5 | Score: 26
d4 Nf6 c4 e6 Nc3 Bb4 Nf3 b6 e3 Ne4 Qc2 Bb7 Bd3 Bxc3+ bxc3 f5 O-O O-O Ne1 c5 | Score: 26
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nf6 Nc3 d6 g3 a6 Bg2 Qc7 O-O Be7 f4 Nc6 Nxc6 bxc6 | Score: 22
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Bg5 e6 f4 Nbd7 Qf3 Qc7 O-O-O b5 e5 Bb7 | Score: 7
c4 c5 Nf3 Nf6 Nc3 e6 g3 b6 Bg2 Bb7 O-O Be7 d4 cxd4 Qxd4 d6 Bg5 a6 Rfd1 Nbd7 | Score: 23
d4 Nf6 c4 e6 g3 d5 Nf3 Be7 Bg2 O-O O-O dxc4 Qc2 a6 a4 Bd7 Qxc4 Bc6 Bg5 Nbd7 | Score: 24
d4 Nf6 c4 g6 Nc3 Bg7 e4 d6 f3 O-O Be3 e5 Nge2 c6 Qd2 Nbd7 O-O-O a6 Bh6 Bxh6 | Score: 16
Nf3 Nf6 c4 g6 g3 Bg7 Bg2 O-O d4 c6 Nc3 d5 cxd5 cxd5 Ne5 e6 Bg5 Qb6 Qd2 Nfd7 | Score: 16
d4 d5 c4 c6 Nf3 Nf6 Nc3 dxc4 a4 Bf5 e3 e6 Bxc4 Bb4 O-O O-O Nh4 Nbd7 Qb3 Qb6 | Score: 33
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 d5 cxd5 exd5 Bg2 Bb4+ Bd2 Be7 Nc3 Bb7 O-O O-O | Score: 27
e4 c6 d4 d5 Nc3 dxe4 Nxe4 Bf5 Ng3 Bg6 N1e2 Nf6 h4 h6 Nf4 Bh7 c3 e6 Bd3 Bxd3 | Score: 13
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 e6 Nb5 d6 c4 Nf6 N1c3 a6 Na3 Be7 Be2 O-O O-O Qa5 | Score: 24
Nf3 Nf6 c4 e6 Nc3 d5 d4 Be7 Bg5 h6 Bh4 O-O e3 Ne4 Bxe7 Qxe7 Rc1 c6 Bd3 Nxc3 | Score: 16
d4 Nf6 c4 e6 Nc3 Bb4 e3 c5 a3 Bxc3+ bxc3 O-O Bd3 d5 cxd5 exd5 Ne2 b6 f3 Re8 | Score: 29
c4 Nf6 Nf3 e6 Nc3 c5 g3 Nc6 Bg2 d5 cxd5 Nxd5 O-O Be7 d4 O-O e4 Ndb4 a3 cxd4 | Score: 30
c4 Nf6 d4 e6 Nf3 d5 Nc3 c5 e3 Nc6 a3 Bd6 dxc5 Bxc5 b4 Bd6 Bb2 O-O cxd5 exd5 | Score: 31
c4 e6 g3 Nf6 Bg2 d5 Nf3 Be7 O-O O-O d4 dxc4 Qc2 a6 Qxc4 b5 Qc2 Bb7 Bg5 Nbd7 | Score: 24
d4 e6 c4 Nf6 Nc3 Bb4 Qc2 O-O a3 Bxc3+ Qxc3 d6 Nf3 Nbd7 g3 b6 Bg2 Bb7 O-O c5 | Score: 30
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O b5 Bb3 Bc5 a4 Bb7 Nc3 O-O d3 Na5 axb5 Nxb3 | Score: 11
Nf3 d5 d4 Nf6 c4 dxc4 e3 e6 Bxc4 a6 a4 c5 O-O Nc6 Qe2 cxd4 Rd1 Be7 exd4 O-O | Score: 23
d4 Nf6 Nf3 e6 c4 b6 g3 Bb7 Bg2 Be7 Nc3 Ne4 Bd2 Bf6 O-O O-O Rc1 c5 Nxe4 Bxe4 | Score: 24
d4 Nf6 c4 e6 Nc3 Bb4 e3 c5 Ne2 cxd4 exd4 d5 c5 Ne4 Bd2 Nxd2 Qxd2 b6 a3 Bxc3 | Score: 20
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 Nc6 Bg5 e6 Qd2 a6 O-O-O Bd7 f4 Be7 Nf3 b5 | Score: 27
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 Nf6 Nc3 g6 Bc4 Qa5 O-O Bg7 Nb3 Qc7 Bg5 O-O f4 b5 | Score: 29
d4 d5 c4 c6 Nf3 Nf6 Nc3 e6 e3 Nbd7 Qc2 Bd6 Bd3 O-O O-O dxc4 Bxc4 b5 Be2 Bb7 | Score: 32
d4 Nf6 Nf3 e6 c4 b6 g3 Be7 Bg2 Bb7 O-O O-O Nc3 Ne4 Bd2 d5 cxd5 exd5 Ne5 Nd7 | Score: 29
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 e6 Nc3 a6 Be2 d6 O-O Nf6 Be3 Be7 f4 O-O Qe1 Nxd4 | Score: 20
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 g3 e6 Bg2 Be7 O-O O-O b3 Nc6 Nxc6 bxc6 | Score: 31
d4 Nf6 c4 g6 Nf3 Bg7 g3 d5 Bg2 dxc4 Na3 c3 bxc3 O-O O-O c5 Qb3 Be6 Qxb7 Bd5 | Score: 21
d4 d5 c4 c6 Nf3 Nf6 e3 e6 Nbd2 c5 cxd5 Nxd5 dxc5 Bxc5 a3 Be7 Qc2 Nc6 b4 Bd7 | Score: 24
d4 d5 c4 dxc4 e3 Nf6 Bxc4 e6 Nf3 c5 O-O a6 a4 Nc6 Qe2 cxd4 Rd1 Be7 exd4 O-O | Score: 27
d4 Nf6 Nf3 e6 Bg5 h6 Bh4 b6 e3 Bb7 Nbd2 c5 c3 Be7 Bd3 cxd4 cxd4 O-O O-O Nc6 | Score: 22
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Bg2 O-O O-O d5 cxd5 Nxd5 Nc3 Nd7 | Score: 25
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nf6 Nc3 d6 Be2 Nc6 O-O Be7 Be3 O-O f4 a6 Qe1 Nxd4 | Score: 16
d4 Nf6 c4 e6 Nf3 Bb4+ Bd2 a5 g3 b6 Bg2 Bb7 O-O O-O Bg5 Be7 Bxf6 Bxf6 Nc3 d6 | Score: 33
e4 c6 d4 d5 Nc3 dxe4 Nxe4 Bf5 Ng3 Bg6 Nf3 Nd7 h4 h6 h5 Bh7 Bd3 Bxd3 Qxd3 e6 | Score: 33
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 d6 c3 Bd7 d4 g6 O-O Bg7 dxe5 dxe5 Be3 Nf6 Nbd2 O-O | Score: 33
e4 c6 d4 d5 Nc3 dxe4 Nxe4 Bf5 Ng3 Bg6 h4 h6 Nf3 Nf6 h5 Bh7 Bd3 Bxd3 Qxd3 e6 | Score: 21
Nf3 Nf6 c4 b6 g3 c5 Bg2 Bb7 O-O e6 Nc3 a6 d4 cxd4 Qxd4 d6 Bg5 Be7 Bxf6 Bxf6 | Score: 31
d4 Nf6 c4 e6 Nf3 b6 g3 Bb7 Bg2 Be7 Nc3 O-O O-O Ne4 Bd2 f5 Qc2 Bf6 Rfd1 Nxc3 | Score: 22
d4 Nf6 c4 g6 Nf3 Bg7 g3 c6 Bg2 d5 cxd5 cxd5 Nc3 O-O Ne5 e6 Bg5 Qb6 Qd2 Nfd7 | Score: 26
d4 Nf6 c4 e6 Nc3 Bb4 e3 O-O Bd3 c5 Nf3 d5 O-O dxc4 Bxc4 Nbd7 Qe2 b6 a3 cxd4 | Score: 18
c4 Nf6 d4 e6 Nf3 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Bg2 c6 Bc3 d5 Ne5 Nfd7 Nxd7 Nxd7 | Score: 15
Nf3 Nf6 c4 e6 g3 d5 d4 Be7 Bg2 O-O O-O dxc4 Qc2 a6 Qxc4 b5 Qc2 Bb7 Bg5 Nbd7 | Score: 15
d4 d5 c4 c6 Nf3 Nf6 Nc3 dxc4 a4 Bf5 e3 e6 Bxc4 Bb4 O-O O-O Qe2 Bg6 Ne5 Nbd7 | Score: 31
d4 Nf6 Nf3 g6 g3 Bg7 Bg2 O-O O-O d6 Nbd2 Nbd7 e4 e5 dxe5 dxe5 b3 Qe7 Qe2 b6 | Score: 28
c4 Nf6 Nf3 e6 d4 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Bg2 c6 Bc3 d5 Ne5 Nfd7 Nxd7 Nxd7 | Score: 12
d4 d5 c4 e6 Nc3 Nf6 cxd5 exd5 Bg5 Nbd7 e3 Be7 Bd3 O-O Nge2 c6 O-O Re8 f3 h6 | Score: 28
c4 g6 d4 Nf6 Nc3 Bg7 e4 O-O f4 d6 Be2 c5 Nf3 cxd4 Nxd4 Bg4 Be3 Qc8 O-O Bxe2 | Score: 28
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Bg2 Bb7 Nc3 d5 cxd5 exd5 O-O O-O | Score: 23
Nf3 Nf6 c4 b6 g3 Bb7 Bg2 e6 O-O Be7 Nc3 O-O Re1 Ne4 Nxe4 Bxe4 d3 Bb7 d4 Be4 | Score: 27
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Be2 e5 Nb3 Be7 O-O O-O Kh1 Bd7 Be3 Bc6 | Score: 15
e4 e5 Nf3 Nf6 Nxe5 d6 Nf3 Nxe4 d4 d5 Bd3 Be7 O-O Nd6 Ne5 O-O Qf3 c6 Re1 Nd7 | Score: 12
d4 Nf6 c4 e6 Nc3 Bb4 Nf3 b6 Qb3 Qe7 g3 Bb7 Bg2 O-O O-O Bxc3 Qxc3 d6 b4 Nbd7 | Score: 32
d4 Nf6 c4 e6 g3 d5 Bg2 Be7 Nf3 O-O O-O dxc4 Qc2 a6 Qxc4 b5 Qc2 Bb7 Bg5 Nbd7 | Score: 15
Nf3 d5 d4 Nf6 c4 c6 Nc3 dxc4 a4 Bf5 e3 e6 Bxc4 Bb4 O-O O-O Qe2 Bg6 Rd1 Nbd7 | Score: 19
e4 Nf6 e5 Nd5 d4 d6 Nf3 Bg4 Be2 e6 O-O Be7 h3 Bh5 c4 Nb6 exd6 cxd6 Nbd2 Nc6 | Score: 23
e4 d5 exd5 Qxd5 Nc3 Qd6 d4 c6 Nf3 Bg4 Be3 Nd7 Bc4 e6 Qe2 Ngf6 h3 Bh5 g4 Bg6 | Score: 23
e4 c6 Nf3 d5 Nc3 Bg4 h3 Bxf3 Qxf3 e6 g3 Nf6 Bg2 Nbd7 d3 Bb4 O-O O-O Ne2 Bd6 | Score: 21
d4 d5 c4 e6 Nc3 Be7 Nf3 Nf6 Bf4 O-O e3 c5 dxc5 Bxc5 a3 Be7 Be2 Nc6 O-O dxc4 | Score: 16
Nf3 d5 d4 Nf6 c4 e6 Bg5 Be7 Nc3 h6 Bxf6 Bxf6 e3 O-O Rc1 c6 Bd3 Nd7 O-O dxc4 | Score: 15
d4 d5 c4 e6 Nc3 Nf6 cxd5 exd5 Bg5 Be7 e3 O-O Qc2 c6 Bd3 h6 Bh4 Re8 Nf3 Nbd7 | Score: 21
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Be3 e5 Nf3 Be7 Bc4 O-O O-O Be6 Bb3 Nc6 | Score: 22
Nf3 d5 d4 Nf6 c4 e6 Nc3 c5 cxd5 Nxd5 e3 Nc6 Bd3 Be7 O-O O-O a3 Nxc3 bxc3 b6 | Score: 30
d4 d5 c4 c6 Nc3 Nf6 Nf3 e6 e3 Nbd7 Qc2 Bd6 Bd3 O-O O-O dxc4 Bxc4 Qe7 Rd1 e5 | Score: 7
d4 e6 Nf3 Nf6 c4 d5 Nc3 Be7 Bg5 h6 Bxf6 Bxf6 e3 O-O Rc1 c6 Bd3 Nd7 O-O dxc4 | Score: 25
e4 c5 Nf3 e6 d4 cxd4 Nxd4 a6 Nc3 Qc7 g3 Nf6 Bg2 Nc6 O-O Be7 Be3 Ne5 Qe2 Nc4 | Score: 31
d4 d5 c4 e6 Nc3 c6 e3 Nf6 Nf3 Nbd7 Qc2 Bd6 Be2 O-O O-O b6 e4 Nxe4 Nxe4 dxe4 | Score: 32
d4 Nf6 c4 e6 Nc3 Bb4 e3 O-O Bd3 d5 Nf3 c5 O-O Nbd7 cxd5 exd5 a3 Ba5 b4 cxb4 | Score: 14
e4 c6 d4 d5 Nc3 dxe4 Nxe4 Nd7 Nf3 Ngf6 Ng3 g6 Be2 Bg7 O-O O-O Re1 Qc7 c3 c5 | Score: 20
c4 Nf6 d4 e6 Nc3 Bb4 e3 c5 Ne2 cxd4 exd4 d5 c5 Ne4 Bd2 Nxd2 Qxd2 a5 a3 Bxc3 | Score: 16
e4 c5 Nf3 e6 d4 cxd4 Nxd4 a6 Nc3 Qc7 Bd3 Nf6 O-O Nc6 Be3 Ne5 h3 Bc5 Na4 Ba7 | Score: 24
Nf3 c5 c4 Nf6 Nc3 e6 g3 b6 Bg2 Bb7 O-O Be7 d4 cxd4 Qxd4 d6 Bg5 a6 Bxf6 Bxf6 | Score: 23
d4 Nf6 Nf3 e6 e3 b6 c4 Bb7 Bd3 Be7 O-O O-O Nc3 d5 cxd5 exd5 b3 Nbd7 Bb2 Ne4 | Score: 25
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Be2 Nbd7 f4 e5 Nf5 Nc5 Ng3 Qb6 Rb1 Be7 | Score: 16
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 g6 Nc3 Bg7 Be3 Nf6 Bc4 Qa5 O-O O-O Bb3 d6 h3 Bd7 | Score: 32
Nf3 Nf6 c4 e6 Nc3 d5 d4 Be7 Bg5 h6 Bxf6 Bxf6 e3 O-O Rc1 c6 Bd3 Nd7 O-O dxc4 | Score: 14
d4 Nf6 c4 e6 Nf3 d5 Nc3 dxc4 e3 a6 a4 c5 Bxc4 Nc6 O-O cxd4 exd4 Be7 d5 exd5 | Score: 14
e4 c6 d4 d5 Nc3 dxe4 Nxe4 Bf5 Ng3 Bg6 h4 h6 Nf3 Nd7 h5 Bh7 Bd3 Bxd3 Qxd3 e6 | Score: 25
d4 Nf6 Nf3 e6 g3 b6 Bg2 Bb7 c4 Be7 Nc3 Ne4 Bd2 d5 cxd5 exd5 O-O O-O Rc1 Nd7 | Score: 23
Nf3 Nf6 g3 b6 Bg2 Bb7 O-O e6 c4 Be7 Nc3 O-O d4 Ne4 Bd2 Nxc3 Bxc3 d5 Ne5 Nd7 | Score: 32
d4 Nf6 Nf3 d5 c4 dxc4 Nc3 c6 a4 Bf5 e3 e6 Bxc4 Bb4 O-O O-O h3 Ne4 Nxe4 Bxe4 | Score: 20
Nf3 Nf6 g3 b6 d4 Bb7 c4 e6 Bg2 Be7 Nc3 Ne4 Bd2 O-O Qc2 Nxd2 Qxd2 Bf6 Rd1 d6 | Score: 32
d4 Nf6 c4 e6 g3 d5 Bg2 Be7 Nf3 O-O O-O dxc4 Qc2 a6 a4 Bd7 Ne5 Bc6 Nxc6 Nxc6 | Score: 22
d4 Nf6 c4 e6 Nf3 d5 Nc3 c6 e3 Nbd7 Qc2 Bd6 Be2 O-O O-O e5 cxd5 cxd5 Nb5 Bb8 | Score: 30
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 e6 Nc3 Qc7 g3 a6 Bg2 Nf6 O-O Be7 b3 Nxd4 Qxd4 d6 | Score: 23
c4 Nf6 Nc3 e6 Nf3 d5 e3 Nbd7 b3 c6 Be2 Bd6 O-O O-O Qc2 Re8 Bb2 e5 cxd5 Nxd5 | Score: 11
Nf3 d5 d4 Nf6 c4 e6 Nc3 Be7 Bg5 h6 Bxf6 Bxf6 e3 O-O Rc1 c6 Bd3 Nd7 O-O dxc4 | Score: 21
Nf3 Nf6 g3 b6 Bg2 Bb7 c4 e6 O-O Be7 d4 O-O Nc3 Ne4 Qc2 Nxc3 Qxc3 c5 Be3 Qc7 | Score: 26
d4 Nf6 c4 e6 Nc3 Bb4 e3 c5 Ne2 cxd4 exd4 O-O a3 Be7 d5 exd5 cxd5 Bc5 b4 Bb6 | Score: 26
d4 d5 Nf3 Nf6 c4 c6 Nc3 e6 Bg5 h6 Bxf6 Qxf6 e3 Nd7 Bd3 dxc4 Bxc4 g6 O-O Bg7 | Score: 22
d4 d5 c4 e6 Nc3 Be7 Nf3 Nf6 Bg5 h6 Bxf6 Bxf6 e3 O-O Rc1 c6 Bd3 Nd7 O-O dxc4 | Score: 18
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 d5 a3 Bxc3+ Qxc3 c5 dxc5 d4 Qg3 Nc6 b4 O-O Bh6 Ne8 | Score: 26
e4 c6 d4 d5 Nd2 dxe4 Nxe4 Bf5 Ng3 Bg6 h4 h6 Nf3 Nd7 h5 Bh7 Bd3 Bxd3 Qxd3 e6 | Score: 33
d4 Nf6 c4 e6 Nc3 Bb4 e3 O-O Bd3 c5 Nf3 d5 O-O dxc4 Bxc4 Nc6 a3 Ba5 Bd3 cxd4 | Score: 23
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 Qa4 Bb7 Bg2 c5 dxc5 bxc5 O-O Be7 Nc3 O-O Rd1 Qb6 | Score: 14
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 g6 c4 Nf6 Nc3 d6 Nc2 Bg7 Be2 O-O O-O Nd7 Qd2 Nc5 | Score: 29
d4 d5 c4 e6 Nc3 Be7 Nf3 Nf6 Bg5 Nbd7 cxd5 exd5 e3 O-O Bd3 Re8 h3 c6 Bf4 Nf8 | Score: 18
Nf3 d5 c4 c6 d4 Nf6 Nc3 dxc4 a4 Bf5 e3 e6 Bxc4 Bb4 O-O O-O Qe2 Nbd7 Ne5 Re8 | Score: 19
c4 Nf6 Nc3 g6 d4 Bg7 e4 d6 h3 O-O Be3 Na6 Nf3 e5 dxe5 dxe5 c5 b6 cxb6 Qxd1+ | Score: 25
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 Nc6 Bg5 e6 Qd2 a6 O-O-O h6 Be3 Bd7 f4 Be7 | Score: 29
d4 Nf6 Nf3 e6 c4 b6 g3 Bb7 Bg2 Be7 O-O O-O Nc3 Ne4 Bd2 d5 cxd5 exd5 Rc1 Nd7 | Score: 18
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 Nbd2 d5 Bg2 Be7 cxd5 exd5 O-O O-O b3 Bb7 Bb2 Na6 | Score: 34
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Be2 e6 O-O Nc6 Be3 Be7 Qe1 O-O Rd1 Qc7 | Score: 30
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 O-O a3 Bxc3+ Qxc3 b6 Bg5 h6 Bh4 c5 dxc5 bxc5 e3 d6 | Score: 10
d4 Nf6 c4 c6 Nf3 d5 e3 Bf5 Nc3 e6 Nh4 Bg6 Be2 Nbd7 g3 Be7 O-O O-O Nxg6 hxg6 | Score: 31
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nf6 Nc3 d6 Be2 Be7 O-O O-O f4 Nc6 Be3 e5 Nb3 exf4 | Score: 11
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Nxe4 d4 b5 Bb3 d5 dxe5 Be6 Be3 Bc5 Qd3 O-O | Score: 30
d4 d5 c4 e6 Nf3 Nf6 Nc3 Bb4 e3 O-O Bd3 c5 O-O dxc4 Bxc4 Nbd7 Qe2 b6 a3 cxd4 | Score: 14
d4 d5 c4 dxc4 Nf3 Nf6 e3 e6 Bxc4 c5 O-O a6 Bb3 Nc6 Nc3 Be7 Qe2 cxd4 Rd1 O-O | Score: 30
c4 c5 Nf3 Nc6 Nc3 Nd4 e3 Nxf3+ Qxf3 g6 b3 Bg7 Bb2 d6 g3 Rb8 Bg2 Nh6 Qd1 O-O | Score: 18
Nf3 Nf6 c4 c5 Nc3 e6 g3 b6 Bg2 Bb7 O-O Be7 d4 cxd4 Qxd4 d6 Bg5 a6 Bxf6 Bxf6 | Score: 30
e4 c6 d4 d5 e5 Bf5 Nf3 e6 Be2 Ne7 O-O c5 c3 cxd4 cxd4 Nbc6 Nc3 Bg4 Nh4 Bxe2 | Score: 25
Nf3 Nf6 c4 e6 g3 d5 d4 Be7 Bg2 O-O O-O dxc4 Qc2 a6 a4 Bd7 Qxc4 Bc6 Bf4 Nbd7 | Score: 28
d4 d5 c4 dxc4 e4 Nf6 e5 Nd5 Bxc4 Nb6 Bd3 Nc6 Be3 Be6 Nc3 Qd7 Nf3 Nb4 Bb5 c6 | Score: 24
d4 d5 Nf3 Nf6 c4 e6 Nc3 Be7 Bg5 h6 Bh4 O-O Rc1 Ne4 Bxe7 Qxe7 e3 c6 Bd3 Nxc3 | Score: 20
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 Qc2 Bb7 Bg2 c5 d5 exd5 cxd5 Nxd5 O-O Be7 Rd1 Qc8 | Score: 29
d4 Nf6 c4 e6 g3 d5 Bg2 Be7 Nf3 O-O O-O dxc4 Qc2 a6 a4 Bd7 Qxc4 Bc6 Bg5 Nbd7 | Score: 22
d4 Nf6 Nf3 e6 c4 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Bg2 c6 Bc3 d5 Ne5 Nfd7 Nxd7 Nxd7 | Score: 17
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 e6 Be2 Be7 O-O O-O f4 Nc6 Be3 a6 Qe1 Nxd4 | Score: 23
e4 e5 Nf3 Nc6 Bc4 Bc5 c3 Nf6 d3 a6 O-O d6 Re1 Ba7 Bb3 O-O Nbd2 Be6 Nf1 Bxb3 | Score: 29
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nf6 Nc3 d6 Be2 Be7 O-O O-O f4 Nc6 Be3 a6 Qe1 Nxd4 | Score: 34
c4 Nf6 Nc3 e6 Nf3 c5 g3 b6 Bg2 Bb7 O-O a6 Re1 d6 d4 cxd4 Nxd4 Bxg2 Kxg2 Be7 | Score: 24
d4 Nf6 c4 e6 Nf3 d5 Nc3 Be7 Bf4 O-O e3 c5 dxc5 Bxc5 a3 Nc6 Rc1 a6 cxd5 exd5 | Score: 17
e4 e5 Nf3 Nc6 Bb5 Nf6 d3 d6 O-O a6 Bxc6+ bxc6 h3 c5 Nc3 Be7 Nh2 Be6 f4 exf4 | Score: 33
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 d5 Bg2 Bb4+ Bd2 Be7 cxd5 exd5 Nc3 O-O O-O Bb7 | Score: 29
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Bc4 e6 Bb3 Nc6 f4 Be7 Be3 O-O Qf3 Nxd4 | Score: 13
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 Qa4 Bb7 Bg2 c5 dxc5 bxc5 O-O Be7 Nc3 O-O Bf4 Qb6 | Score: 21
d4 Nf6 Nf3 e6 c4 b6 g3 Bb7 Bg2 Be7 Nc3 Ne4 Bd2 Bf6 Qc2 Nxd2 Qxd2 O-O O-O d6 | Score: 31
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 Qa4 Bb7 Bg2 c5 dxc5 Bxc5 O-O Be7 Nc3 Na6 Bf4 O-O | Score: 27
d4 Nf6 c4 e6 Nf3 b6 a3 Bb7 Nc3 d5 cxd5 exd5 g3 Be7 Qa4+ c6 Bg2 O-O O-O Nbd7 | Score: 21
d4 Nf6 c4 e6 Nc3 Bb4 Nf3 b6 e3 Ne4 Qc2 Bb7 Bd3 f5 O-O Bxc3 bxc3 O-O Nd2 Qh4 | Score: 22
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Bg2 c6 Bc3 d5 Ne5 Nfd7 Nxd7 Nxd7 | Score: 19
d4 Nf6 c4 e6 Nc3 Bb4 e3 c5 Ne2 cxd4 exd4 O-O a3 Be7 d5 exd5 cxd5 Re8 d6 Bf8 | Score: 30
d4 Nf6 c4 e6 Nf3 d5 Nc3 Be7 Bg5 O-O Rc1 b6 cxd5 exd5 e3 Bb7 Bd3 Nbd7 Qe2 c5 | Score: 27
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Nxe4 d4 b5 Bb3 d5 dxe5 Be6 Qe2 Be7 Rd1 O-O | Score: 17
e4 e5 Nf3 Nf6 Nxe5 d6 Nf3 Nxe4 d4 d5 Bd3 Be7 O-O Nc6 c4 Nf6 h3 Nb4 Be2 dxc4 | Score: 29
Nf3 Nf6 c4 b6 d4 e6 g3 Ba6 b3 Bb4+ Bd2 Be7 Bg2 O-O O-O d5 cxd5 Nxd5 Nc3 Nd7 | Score: 21
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 O-O a3 Bxc3+ Qxc3 b6 Bg5 Bb7 e3 c5 dxc5 bxc5 f3 a5 | Score: 34
Nf3 d6 d4 Nf6 c4 Nbd7 Nc3 c6 e4 e5 Be2 g6 O-O Bg7 dxe5 dxe5 Be3 O-O Nd2 Qe7 | Score: 27
d4 Nf6 Nf3 e6 g3 d5 Bg2 Be7 O-O O-O c4 dxc4 Qc2 a6 Qxc4 b5 Qc2 Bb7 Bg5 Nbd7 | Score: 8
d4 Nf6 c4 e6 Nf3 b6 Nc3 Bb7 a3 d5 cxd5 Nxd5 Qc2 Be7 e4 Nxc3 bxc3 O-O Bd3 c5 | Score: 22
Nf3 Nf6 c4 e6 Nc3 d5 d4 Be7 Bg5 O-O e3 h6 Bh4 Ne4 Bxe7 Qxe7 Rc1 c6 Bd3 Nxc3 | Score: 15
d4 Nf6 c4 b6 Nf3 e6 g3 Ba6 b3 Bb4+ Bd2 Be7 Bg2 c6 Bc3 d5 Ne5 Nfd7 Nxd7 Nxd7 | Score: 22
c4 Nf6 Nc3 e6 Nf3 b6 e4 Bb7 Qe2 Bb4 e5 Ng8 d4 Ne7 Qd3 d5 exd6 cxd6 a3 Bxc3+ | Score: 27
d4 Nf6 c4 e6 Nc3 Bb4 e3 O-O Bd3 d5 Ne2 c5 cxd5 cxd4 exd4 Nxd5 O-O Nc6 a3 Bd6 | Score: 10
Nf3 d5 d4 e6 c4 dxc4 e4 b5 a4 c6 axb5 cxb5 b3 Bb7 bxc4 Bxe4 cxb5 Nf6 Be2 Be7 | Score: 33
d4 d5 c4 c6 Nf3 Nf6 e3 a6 a4 Bg4 Qb3 Qc7 Ne5 Be6 Nc3 Nbd7 Nxd7 Qxd7 Bd2 dxc4 | Score: 9
d4 Nf6 c4 e6 Nc3 Bb4 e3 c5 Bd3 d5 cxd5 Nxd5 Ne2 cxd4 exd4 Nc6 O-O Nf6 Bc2 h6 | Score: 34
d4 Nf6 Nf3 e6 c4 b6 a3 Bb7 Nc3 d5 cxd5 Nxd5 Qc2 Be7 Bd2 Nxc3 Bxc3 O-O e4 Nd7 | Score: 24
Nf3 c5 c4 Nf6 Nc3 e6 e3 d5 d4 cxd4 exd4 Bb4 Bd3 dxc4 Bxc4 O-O O-O b6 Bg5 Bb7 | Score: 19
Nf3 Nf6 c4 e6 Nc3 Bb4 g3 b6 Bg2 Bb7 O-O O-O d3 d5 cxd5 Nxd5 Qc2 Be7 Rd1 Nxc3 | Score: 30
d4 d5 c4 e6 Nf3 c5 cxd5 exd5 g3 Nc6 Bg2 Nf6 O-O Be7 Nc3 O-O dxc5 Bxc5 Bg5 d4 | Score: 18
Nf3 Nf6 c4 c5 g3 b6 Bg2 Bb7 O-O g6 b3 Bg7 Bb2 O-O Nc3 d5 Nxd5 Nxd5 Bxg7 Kxg7 | Score: 14
e4 e6 d4 d5 Nd2 Nf6 e5 Nfd7 Bd3 c5 c3 Nc6 Ne2 cxd4 cxd4 f6 exf6 Nxf6 Nf3 Bd6 | Score: 30
d4 Nf6 c4 g6 Nc3 d5 cxd5 Nxd5 e4 Nxc3 bxc3 Bg7 Bc4 b6 Ne2 Bb7 f3 O-O O-O Nc6 | Score: 33
e4 e5 Nf3 Nc6 d4 exd4 Nxd4 Bc5 Be3 Qf6 c3 Nge7 Bc4 Ne5 Be2 Qg6 O-O d6 f3 O-O | Score: 25
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 b5 cxb5 Bxb5 Bg2 Bc6 O-O Be7 Bg5 O-O Bxf6 Bxf6 | Score: 31
d4 Nf6 c4 e6 Nc3 Bb4 e3 O-O Bd3 c5 Nf3 d5 O-O Nc6 a3 Ba5 cxd5 exd5 dxc5 Bxc3 | Score: 28
c4 Nf6 Nc3 e6 Nf3 b6 e4 Bb4 Qe2 Bb7 e5 Ng8 d4 d6 Bd2 dxe5 dxe5 Na6 O-O-O Qe7 | Score: 16
d4 Nf6 c4 e6 Nc3 Bb4 e3 c5 Bd3 d5 Nf3 cxd4 exd4 dxc4 Bxc4 O-O O-O b6 Bg5 Bb7 | Score: 13
c4 c5 Nf3 Nf6 Nc3 d5 cxd5 Nxd5 d4 Nxc3 bxc3 g6 e3 Bg7 Bd3 O-O O-O Qc7 Rb1 b6 | Score: 21
d4 Nf6 c4 e6 Nf3 b6 Nc3 Bb4 Qb3 Qe7 a3 Bxc3+ Qxc3 Bb7 g3 d6 Bg2 O-O O-O Nbd7 | Score: 33
e4 c6 d4 d5 Nd2 dxe4 Nxe4 Nd7 Ng5 Ngf6 Bc4 e6 Qe2 Nb6 Bd3 h6 N5f3 c5 Be3 Qc7 | Score: 16
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 g6 Be3 Bg7 Bc4 Nc6 h3 O-O Bb3 Nxd4 Bxd4 b5 | Score: 29
e4 c5 Nf3 e6 b3 Nc6 Bb2 d6 d4 cxd4 Nxd4 Nf6 Bd3 Be7 O-O O-O Nd2 Nxd4 Bxd4 b6 | Score: 25
e4 g6 d4 Bg7 Nf3 d6 Bc4 c6 Bb3 Nf6 Nbd2 O-O O-O Qc7 e5 dxe5 dxe5 Nd5 Re1 Na6 | Score: 34
d4 Nf6 c4 e6 Nf3 d5 g3 Bb4+ Bd2 Be7 Bg2 O-O Qc2 c6 O-O Nbd7 Bf4 b6 cxd5 cxd5 | Score: 21
e4 c5 Nf3 e6 d4 cxd4 Nxd4 a6 Nc3 Qc7 Be2 Nf6 O-O Bb4 Qd3 Nc6 Nxc6 bxc6 f4 d5 | Score: 20
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nf6 Nc3 d6 Be2 Be7 O-O O-O f4 Nc6 Be3 e5 fxe5 dxe5 | Score: 26
e4 c6 d4 d5 Nd2 dxe4 Nxe4 Bf5 Ng3 Bg6 Nf3 Nd7 h4 h6 h5 Bh7 Bd3 Bxd3 Qxd3 Qc7 | Score: 34
d4 Nf6 Nf3 e6 e3 b6 Bd3 c5 O-O Bb7 c4 Be7 Nc3 cxd4 exd4 d5 cxd5 Nxd5 Ne5 O-O | Score: 34
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 e6 Be2 Nc6 Be3 Be7 O-O O-O f4 e5 fxe5 dxe5 | Score: 26
c4 e6 Nc3 d5 d4 Be7 cxd5 exd5 Bf4 c6 Qc2 Bd6 Bxd6 Qxd6 e3 Nf6 Bd3 Bg4 f3 Bh5 | Score: 31
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nf6 Nc3 d6 g4 h6 h4 Be7 Bg2 Nc6 g5 hxg5 hxg5 Rxh1+ | Score: 22
Nf3 Nf6 c4 c5 Nc3 e6 g3 b6 Bg2 Bb7 O-O Be7 Re1 d6 d4 cxd4 Nxd4 Bxg2 Kxg2 Qc8 | Score: 26
d4 d5 c4 c6 Nf3 e6 Nbd2 f5 g3 Nf6 Bg2 Bd6 O-O O-O Ne5 Nbd7 Ndf3 Ne4 Bf4 Nxe5 | Score: 32
d4 Nf6 c4 e6 g3 d5 Bg2 dxc4 Nf3 Bd7 Qc2 c5 Qxc4 Bc6 dxc5 Nbd7 Be3 Bd5 Qb4 a5 | Score: 29
d4 Nf6 c4 e6 Nf3 b6 g3 Bb4+ Bd2 Bxd2+ Qxd2 Ba6 b3 O-O Bg2 d5 O-O c5 cxd5 Ne4 | Score: 28
e4 c5 Nf3 d6 Bb5+ Nc6 O-O Bd7 c3 Nf6 Re1 a6 Bf1 e5 d4 cxd4 cxd4 Bg4 Be3 exd4 | Score: 32
c4 b6 d4 e6 Nc3 Bb4 Qb3 Qe7 a3 Bxc3+ Qxc3 Bb7 Nf3 Nf6 g3 d6 Bg2 Nbd7 O-O O-O | Score: 33
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nf6 Nc3 d6 Be2 Be7 O-O Nc6 Be3 O-O f4 e5 fxe5 dxe5 | Score: 24
d4 Nf6 c4 e6 Nc3 Bb4 e3 d5 a3 Bxc3+ bxc3 c5 cxd5 exd5 Bd3 O-O Ne2 b6 O-O Ba6 | Score: 30
e4 c5 Nf3 Nc6 Bb5 g6 O-O Bg7 Bxc6 bxc6 c3 d6 h3 Nf6 Re1 Nd7 d4 cxd4 cxd4 O-O | Score: 29
c4 c5 Nf3 Nf6 Nc3 d5 cxd5 Nxd5 d4 Nxc3 bxc3 g6 e3 Bg7 Bd3 O-O O-O Nc6 Ba3 b6 | Score: 28
d4 d5 c4 e6 Nc3 Nf6 cxd5 exd5 Bg5 Be7 e3 O-O Bd3 Nbd7 Nge2 Re8 O-O Nf8 b4 a6 | Score: 25
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Bg5 Nbd7 Bc4 Qa5 Qd2 e6 O-O Be7 Rad1 h6 | Score: 20
d4 Nf6 Nf3 c5 d5 e6 Nc3 Nxd5 Nxd5 exd5 Qxd5 Be7 e4 O-O Be2 d6 O-O Nc6 c3 Be6 | Score: 30
d4 Nf6 c4 g6 Nc3 Bg7 e4 d6 Nf3 O-O Be2 e5 Be3 Na6 O-O c6 dxe5 dxe5 Qxd8 Rxd8 | Score: 30
d4 Nf6 Nf3 e6 Bf4 c5 e3 b6 h3 Be7 Nbd2 cxd4 exd4 O-O c3 Ba6 Bxa6 Nxa6 a4 Qc8 | Score: 18
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 Nf6 Nc3 e5 Ndb5 d6 Bg5 a6 Na3 Be6 Nc4 Rc8 Ne3 Be7 | Score: 18
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nc6 Nc3 Qc7 Be2 a6 O-O Nf6 Be3 Bb4 Na4 Be7 c4 Nxe4 | Score: 24
c4 e6 Nc3 d5 d4 Be7 Nf3 Nf6 Bg5 h6 Bxf6 Bxf6 e3 O-O Rc1 c6 Bd3 dxc4 Bxc4 Nd7 | Score: 16
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 d5 cxd5 exd5 Bg5 h6 Bh4 c5 dxc5 O-O e3 Be6 Nf3 Nbd7 | Score: 18
d4 d5 c4 c6 Nf3 Nf6 e3 Bf5 Nc3 e6 Nh4 Bg6 Nxg6 hxg6 Bd2 Nbd7 Rc1 a6 Bd3 dxc4 | Score: 14
d4 d5 c4 dxc4 Nf3 e6 e3 a6 Bxc4 c5 O-O Nf6 Bb3 Nc6 Nc3 cxd4 exd4 Be7 Re1 O-O | Score: 23
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 Nf6 Nc3 e5 Ndb5 d6 Bg5 a6 Na3 b5 Bxf6 gxf6 Nd5 f5 | Score: 21
d4 d5 c4 e6 Nc3 c5 cxd5 exd5 Nf3 Nc6 g3 Nf6 Bg2 Be7 O-O O-O dxc5 Bxc5 Bg5 d4 | Score: 17
d4 d5 c4 e6 Nf3 c5 cxd5 exd5 g3 Nf6 Bg2 Be7 O-O O-O Nc3 Nc6 dxc5 Bxc5 Bg5 d4 | Score: 13
e4 c6 d4 d5 exd5 cxd5 Bd3 Nc6 c3 Nf6 Bf4 Bg4 Qb3 Qc8 Nd2 e6 Ngf3 Be7 O-O O-O | Score: 27
d4 Nf6 c4 e6 Nf3 Bb4+ Bd2 c5 Bxb4 cxb4 g3 O-O Bg2 d6 Nbd2 Re8 Nf1 Nc6 Ne3 e5 | Score: 19
d4 Nf6 c4 e6 Nf3 d5 Nc3 Be7 Bf4 O-O e3 c5 dxc5 Bxc5 Rc1 Nc6 cxd5 exd5 Be2 d4 | Score: 11
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 O-O a3 Bxc3+ Qxc3 b6 e3 Bb7 b3 d5 Nf3 Nbd7 Be2 dxc4 | Score: 32
e4 e5 Nf3 Nf6 Nxe5 d6 Nf3 Nxe4 d4 d5 Bd3 Bd6 O-O O-O Re1 Re8 c4 c6 cxd5 cxd5 | Score: 31
d4 d5 c4 dxc4 Nf3 Nf6 e3 e6 Bxc4 c5 O-O a6 b3 Nc6 Bb2 cxd4 Nxd4 Bd7 Nd2 Nxd4 | Score: 25
d4 Nf6 Nf3 e6 Bf4 b6 e3 Be7 h3 Bb7 Bd3 c5 c3 cxd4 exd4 O-O O-O Ba6 Bxa6 Nxa6 | Score: 19
c4 c5 Nf3 Nf6 g3 b6 Bg2 Bb7 O-O g6 d4 cxd4 Nxd4 Bxg2 Kxg2 Qc7 b3 Bg7 Bb2 O-O | Score: 13
e4 e6 d4 d5 Nc3 Nf6 Bg5 Be7 e5 Nfd7 Bxe7 Qxe7 f4 a6 Nf3 c5 dxc5 Nc6 Bd3 Qxc5 | Score: 34
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 g3 Qc7 Bg2 e6 O-O Nc6 Be3 Be7 Nxc6 bxc6 | Score: 30
d4 d5 c4 e6 Nc3 Nf6 Bg5 Be7 e3 O-O Nf3 h6 Bh4 b6 Qc2 Bb7 Bxf6 Bxf6 cxd5 exd5 | Score: 15
e4 c5 Nf3 Nc6 Bb5 g6 O-O Bg7 Re1 Nf6 e5 Nd5 Nc3 Nc7 Bxc6 dxc6 Ne4 Ne6 d3 O-O | Score: 33
d4 d5 c4 dxc4 Nf3 Nf6 e3 e6 Bxc4 c5 O-O a6 Bd3 cxd4 exd4 Be7 Ne5 O-O Be3 Bd7 | Score: 29
d4 d5 c4 dxc4 e4 Nf6 e5 Nd5 Bxc4 Nb6 Bd3 Nc6 Be3 Nb4 Be4 f5 exf6 exf6 Nc3 f5 | Score: 34
e4 d6 d4 Nf6 Nc3 g6 Nf3 Bg7 Be2 O-O O-O c6 Re1 Qc7 Bf4 Nbd7 e5 Nh5 exd6 exd6 | Score: 26
e4 c5 c3 e6 d4 d5 exd5 exd5 Nf3 Bd6 Be3 c4 b3 cxb3 axb3 Ne7 Na3 Nbc6 Nb5 Bb8 | Score: 28
d4 Nf6 c4 e6 Nc3 Bb4 e3 c5 Ne2 cxd4 exd4 d5 a3 Be7 Nf4 dxc4 Bxc4 O-O O-O Nc6 | Score: 26
Nf3 Nf6 c4 b6 g3 Bb7 Bg2 e6 d4 Bb4+ Bd2 Be7 Nc3 d5 Qa4+ c6 cxd5 exd5 Ne5 O-O | Score: 30
d4 Nf6 c4 e6 Nc3 Bb4 e3 O-O Bd3 d5 Nf3 c5 O-O Nbd7 a3 Ba5 Qc2 cxd4 exd4 dxc4 | Score: 33
d4 Nf6 c4 e6 Nf3 b6 a3 Bb7 Nc3 d5 Qc2 Be7 cxd5 Nxd5 Bd2 Nd7 e4 Nxc3 Bxc3 O-O | Score: 25
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 O-O a3 Bxc3+ Qxc3 d6 Nf3 Nbd7 g3 b6 Bg2 Bb7 O-O Qe7 | Score: 28
d4 Nf6 c4 g6 Nc3 d5 Nf3 Bg7 Qb3 dxc4 Qxc4 O-O e4 a6 Qb3 c5 dxc5 Nbd7 Qb4 Qc7 | Score: 20
Nf3 Nf6 c4 b6 g3 Bb7 Bg2 e6 O-O d5 cxd5 Nxd5 Nc3 Be7 Nxd5 Bxd5 Re1 c5 e4 Bb7 | Score: 17
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 e6 Nc3 d6 Be3 Be7 Be2 Nf6 O-O O-O f4 e5 fxe5 dxe5 | Score: 30
Nf3 b6 e3 Nf6 d4 e6 c4 Bb7 Bd3 c5 O-O Be7 Nc3 cxd4 exd4 d5 cxd5 Nxd5 Ne5 O-O | Score: 13
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O d6 c3 Bg4 Re1 Be7 h3 Bh5 Bxc6+ bxc6 d4 exd4 | Score: 20
e4 c5 c3 d5 exd5 Qxd5 d4 Nf6 Nf3 Bg4 Be2 e6 O-O Nc6 Be3 cxd4 cxd4 Bb4 a3 Ba5 | Score: 31
d4 d5 c4 e6 Nc3 Be7 cxd5 exd5 Bf4 Nf6 Qc2 O-O e3 c5 dxc5 Bxc5 Nf3 Nc6 Be2 d4 | Score: 26
d4 Nf6 Nf3 e6 g3 b5 Bg2 Bb7 Bg5 c5 c3 cxd4 Bxf6 gxf6 cxd4 d5 O-O Nd7 Qd3 Qb6 | Score: 34
d4 d5 c4 c6 Nf3 Nf6 Nc3 e6 e3 Nbd7 Bd3 dxc4 Bxc4 b5 Bd3 b4 Ne4 Nxe4 Bxe4 Bb7 | Score: 27
d4 d5 c4 e6 Nc3 Be7 Bf4 c6 e3 Bd6 Bxd6 Qxd6 cxd5 exd5 Bd3 Ne7 f3 Nf5 Qd2 Qh6 | Score: 28
d4 Nf6 c4 e6 Nc3 Bb4 Nf3 c5 e3 d5 Bd3 O-O O-O Nc6 a3 Bxc3 bxc3 dxc4 Bxc4 Qc7 | Score: 17
d4 Nf6 Nf3 e6 c4 c5 e3 d5 Nc3 Nc6 cxd5 Nxd5 Bc4 cxd4 exd4 Be7 O-O O-O Re1 a6 | Score: 22
d4 Nf6 c4 g6 Nc3 Bg7 e4 d6 Be2 O-O f4 c5 Nf3 cxd4 Nxd4 Nc6 Be3 Bg4 Nxc6 Bxe2 | Score: 22
d4 Nf6 Nf3 e6 Bg5 b6 e4 h6 Bxf6 Qxf6 Bd3 Bb7 Nbd2 d6 Qe2 a6 O-O-O Nd7 Kb1 e5 | Score: 25
e4 e5 Nf3 Nf6 Nxe5 d6 Nf3 Nxe4 d4 d5 Bd3 Be7 O-O Nc6 Re1 Bg4 c4 Nf6 Nc3 Nxd4 | Score: 18
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 d5 cxd5 exd5 Bg2 Bb4+ Bd2 Bd6 O-O O-O Nc3 Nbd7 | Score: 29
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 O-O a3 Bxc3+ Qxc3 d6 Nf3 b6 g3 Bb7 Bg2 Nbd7 O-O Qe7 | Score: 30
d4 Nf6 c4 e6 Nf3 Bb4+ Bd2 Qe7 g3 Nc6 Bg2 Bxd2+ Nbxd2 d6 O-O O-O e4 e5 d5 Nb8 | Score: 31
d4 d5 c4 e6 Nc3 Nf6 cxd5 exd5 Bg5 Be7 e3 c6 Qc2 O-O Bd3 Nbd7 Nge2 h6 Bh4 Re8 | Score: 34
e4 c5 Nf3 e6 Nc3 Nc6 d4 cxd4 Nxd4 Qc7 g3 a6 Bg2 d6 O-O Bd7 Re1 Be7 Nxc6 Bxc6 | Score: 30
c4 c5 Nc3 Nf6 Nf3 d5 cxd5 Nxd5 d4 Nxc3 bxc3 g6 e3 Bg7 Bd3 O-O O-O Qc7 Qe2 b6 | Score: 19
d4 d5 c4 c6 Nf3 Nf6 e3 Bf5 Nc3 e6 Nh4 Bg6 Be2 Nbd7 Bd2 Be7 Nxg6 hxg6 Qc2 Qc7 | Score: 27
c4 e6 Nf3 Nf6 Nc3 d5 d4 Be7 Bg5 O-O e3 h6 Bh4 b6 Qb3 Bb7 Bxf6 Bxf6 cxd5 exd5 | Score: 24
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nc6 Nc3 a6 Be3 Qc7 Bd3 Nf6 O-O Bd6 h3 Bf4 Qf3 Bxe3 | Score: 28
c4 Nf6 d4 e6 Nf3 b6 a3 Bb7 Nc3 d5 cxd5 Nxd5 Qc2 Nxc3 bxc3 Nd7 e4 c5 Bf4 cxd4 | Score: 14
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 Nf6 Nc3 d6 Bg5 e6 Qd2 a6 O-O-O h6 Bf4 Bd7 Bg3 Be7 | Score: 20
d4 Nf6 c4 e6 Nc3 Bb4 e3 d5 Bd3 O-O Nf3 c5 O-O Nbd7 a3 Ba5 Qc2 cxd4 exd4 dxc4 | Score: 28
d4 d5 Nf3 Nf6 c4 c6 Nc3 e6 Bg5 Nbd7 e3 Qa5 Nd2 Bb4 Qc2 O-O a3 dxc4 Bxf6 Nxf6 | Score: 20
Nf3 Nf6 c4 e6 Nc3 d5 d4 Be7 Bf4 O-O e3 c5 dxc5 Bxc5 a3 Nc6 Qc2 Qa5 O-O-O Be7 | Score: 26
d4 e6 c4 d5 Nc3 Be7 Nf3 Nf6 Bf4 O-O e3 c5 dxc5 Bxc5 Qc2 Nc6 a3 Qa5 O-O-O Be7 | Score: 31
Nf3 c5 c4 Nf6 g3 e6 Bg2 Be7 d4 d5 cxd5 exd5 O-O O-O b3 Nc6 Bb2 Ne4 dxc5 Bxc5 | Score: 28
c4 e6 Nc3 d5 d4 c5 e3 Nf6 Nf3 Nc6 cxd5 exd5 Bb5 Bd6 dxc5 Bxc5 O-O O-O b3 Bg4 | Score: 33
d4 Nf6 Nf3 e6 c4 d5 Nc3 Be7 Bg5 h6 Bh4 O-O e3 b6 Be2 Bb7 Bxf6 Bxf6 cxd5 exd5 | Score: 23
Nf3 c5 c4 Nc6 Nc3 Nf6 e3 e6 d4 d5 cxd5 exd5 Bb5 Bd6 dxc5 Bxc5 O-O O-O h3 Bf5 | Score: 25
d4 Nf6 c4 e6 Nf3 Bb4+ Nbd2 O-O a3 Bxd2+ Qxd2 b6 b3 Bb7 Bb2 d5 e3 Nbd7 Be2 c5 | Score: 29
d4 Nf6 c4 e6 Nf3 Bb4+ Nbd2 b6 e3 Bb7 Bd3 O-O O-O d5 a3 Be7 b4 Nbd7 cxd5 exd5 | Score: 33
d4 d5 Bf4 c6 e3 Bf5 Nf3 e6 Be2 Bd6 Bxd6 Qxd6 O-O Nd7 c4 Ngf6 Nc3 O-O Nh4 Be4 | Score: 10
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Be2 e5 Nb3 Be7 O-O Be6 Be3 Nbd7 Qd3 Rc8 | Score: 32
e4 g6 d4 d6 Bg5 Bg7 c3 Nf6 Nd2 Na6 Ngf3 O-O Be2 c5 O-O Nc7 dxc5 dxc5 Qc2 Ne6 | Score: 24
d4 Nf6 c4 e6 Nf3 d5 Nc3 c5 cxd5 Nxd5 e3 Nc6 Bc4 Nb6 Bb3 Be7 O-O O-O Ne4 cxd4 | Score: 18
c4 b6 d4 e6 d5 Qh4 Nc3 Bb4 Bd2 Nf6 e3 Bxc3 Bxc3 Ne4 Qc2 Nxc3 Qxc3 O-O g3 Qe4 | Score: 22
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Nc3 O-O e4 d5 cxd5 Bxf1 Kxf1 exd5 | Score: 31
d4 e6 c4 Nf6 Nf3 d5 Nc3 Be7 Bg5 O-O e3 h6 Bh4 b6 Be2 Bb7 Bxf6 Bxf6 cxd5 exd5 | Score: 20
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 Qb3 d5 cxd5 Qxd5 Qc2 c5 Nc3 Qc6 dxc5 Bxc5 Bg2 Bb7 | Score: 16
e4 c5 Nf3 d6 d4 Nf6 Nc3 cxd4 Nxd4 a6 Be2 e5 Nb3 Be7 O-O O-O Be3 Be6 Qd2 Nbd7 | Score: 17
d4 Nf6 c4 e6 Nf3 d5 Nc3 c6 Bg5 Nbd7 e3 Qa5 Nd2 Bb4 Qc2 O-O a3 dxc4 Bxf6 Nxf6 | Score: 21
c4 c5 Nf3 Nc6 e3 Nf6 Nc3 e6 d4 d5 cxd5 Nxd5 Bd3 Be7 O-O O-O a3 cxd4 exd4 Bf6 | Score: 17
d4 d5 c4 c6 Nf3 Nf6 Nc3 dxc4 a4 Bf5 Ne5 e6 f3 c5 dxc5 Qxd1+ Nxd1 Bxc5 e4 Bg6 | Score: 25
Nf3 Nf6 g3 d5 Bg2 c6 O-O Bg4 c4 e6 Ne5 Bh5 d4 Nbd7 Nc3 Be7 Qb3 Qb6 Nxd7 Nxd7 | Score: 19
d4 d5 c4 c6 Nf3 Nf6 e3 e6 Nbd2 Ne4 cxd5 Nxd2 Bxd2 exd5 Qb3 a5 e4 a4 Qe3 dxe4 | Score: 30
d4 Nf6 c4 e6 Nf3 b6 g3 Bb7 Bg2 Be7 Nc3 O-O d5 Bb4 Bd2 Bxc3 Bxc3 exd5 Nh4 Ne4 | Score: 10
e4 e6 d4 d5 exd5 exd5 Nf3 Nf6 Bd3 Be7 h3 Nc6 a3 Ne4 c4 Bf5 O-O dxc4 Bxc4 O-O | Score: 29
d4 Nf6 c4 e6 Nc3 Bb4 e3 c5 Bd3 d5 cxd5 exd5 dxc5 O-O Nf3 Bxc5 O-O Nc6 b3 Bg4 | Score: 15
e4 e5 Nf3 Nf6 d4 Nxe4 Bd3 d5 Nxe5 Bd6 O-O Nc6 Nxc6 bxc6 c4 O-O c5 Be7 f3 Ng5 | Score: 22
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Be2 e5 Nb3 Be7 O-O O-O Be3 Be6 Qd2 Nbd7 | Score: 32
d4 Nf6 c4 e6 Nc3 d5 cxd5 exd5 Bg5 c6 e3 Be7 Bd3 Bg4 Nge2 Bh5 Bxf6 Bxf6 b4 a6 | Score: 33
d4 d5 c4 e6 Nf3 Nf6 Nc3 c6 e3 Nbd7 Bd3 Bb4 O-O O-O Bd2 Qe7 Qb3 dxc4 Qxc4 Bd6 | Score: 27
Nf3 d5 c4 e6 d4 Nf6 Nc3 Be7 Bf4 O-O e3 c5 dxc5 Bxc5 Qc2 Nc6 a3 Qa5 O-O-O Be7 | Score: 22
c4 Nf6 Nc3 e6 Nf3 Bb4 d4 O-O e3 c5 Bd3 d5 O-O dxc4 Bxc4 b6 Qe2 Bb7 dxc5 Bxc5 | Score: 31
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 d5 Bg2 Bb4+ Bd2 Bd6 cxd5 exd5 Nc3 O-O O-O Nbd7 | Score: 5
d4 Nf6 c4 g6 g3 c6 Bg2 d5 cxd5 cxd5 Nf3 Bg7 Nc3 O-O Ne5 e6 O-O Nc6 Nxc6 bxc6 | Score: 23
c4 e6 d4 d5 Nc3 Be7 Nf3 Nf6 Bf4 O-O e3 c5 dxc5 Bxc5 a3 Nc6 Qc2 Qa5 O-O-O Be7 | Score: 34
d4 Nf6 c4 e6 Nf3 Bb4+ Bd2 c5 Bxb4 cxb4 a3 bxa3 Nxa3 d6 g3 b6 Bg2 Bb7 O-O O-O | Score: 26
d4 d5 c4 e6 Nf3 c5 cxd5 exd5 g3 Nc6 Bg2 Nf6 O-O Be7 dxc5 Bxc5 Bg5 O-O Nc3 d4 | Score: 32
d4 Nf6 Nf3 e6 e3 b6 Bd3 c5 c4 Bb7 Nc3 cxd4 exd4 Be7 O-O d5 cxd5 Nxd5 Ne5 O-O | Score: 32
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 e6 Nc3 d6 Bc4 Nf6 Be3 a6 Qe2 Qc7 O-O-O Na5 Bb3 b5 | Score: 27
d4 Nf6 c4 e6 Nc3 Bb4 Nf3 O-O g3 c5 Bg2 cxd4 Nxd4 d5 cxd5 Nxd5 Qb3 Qa5 Bd2 Nc6 | Score: 28
Nf3 Nf6 c4 c5 Nc3 d5 cxd5 Nxd5 d4 Nxc3 bxc3 g6 e3 Bg7 Bd3 O-O O-O Qc7 Rb1 Rd8 | Score: 21
d4 d5 c4 e6 Nc3 Nf6 cxd5 exd5 Bg5 Be7 e3 Nbd7 Bd3 O-O Nge2 Re8 Qc2 c6 O-O Nf8 | Score: 34
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Bg2 d5 cxd5 Nxd5 Nc3 Nd7 Nxd5 exd5 | Score: 23
d4 Nf6 Nf3 c5 d5 e6 Nc3 exd5 Nxd5 Nxd5 Qxd5 Be7 e4 O-O Bc4 d6 O-O Nd7 Qd1 Nb6 | Score: 25
d4 e6 c4 Nf6 Nf3 Bb4+ Bd2 c5 Bxb4 cxb4 g3 b6 Bg2 Bb7 O-O O-O Nbd2 d6 Ne1 Bxg2 | Score: 17
e4 c5 c3 d5 exd5 Qxd5 d4 Nc6 Nf3 Bg4 Be2 Nf6 O-O e6 h3 Bh5 Be3 cxd4 Nxd4 Bxe2 | Score: 21
d4 Nf6 c4 e6 Nc3 Bb4 e3 c5 Bd3 d5 Nf3 cxd4 exd4 dxc4 Bxc4 O-O O-O Nc6 Bg5 Be7 | Score: 31
e4 d6 d4 Nf6 Nc3 g6 Nf3 Bg7 Be2 O-O O-O c6 Re1 Bg4 Bg5 Bxf3 Bxf3 e5 dxe5 dxe5 | Score: 25
c4 Nf6 Nf3 e6 Nc3 c5 g3 b6 Bg2 Bb7 O-O d5 cxd5 Nxd5 d4 Nxc3 bxc3 Nd7 Re1 cxd4 | Score: 25
d4 d5 c4 e6 Nf3 Nf6 e3 c5 cxd5 exd5 Bb5+ Nc6 O-O cxd4 Nxd4 Bd7 b3 Bd6 Bb2 O-O | Score: 9
d4 Nf6 c4 e6 Nf3 b6 g3 Bb4+ Nbd2 Bb7 Bg2 O-O O-O c5 a3 Bxd2 Bxd2 cxd4 Bb4 Re8 | Score: 32
e4 c6 d4 d5 Nc3 dxe4 Nxe4 Bf5 Ng3 Bg6 h4 h6 h5 Bh7 Nf3 Nd7 Bd3 Bxd3 Qxd3 Ngf6 | Score: 30
Nf3 d5 d4 Nf6 c4 e6 Nc3 c6 e3 Nbd7 Qc2 Bd6 e4 e5 cxd5 cxd5 exd5 exd4 Nxd4 O-O | Score: 32
Nf3 Nf6 c4 g6 g3 Bg7 Bg2 O-O O-O d6 d4 Nbd7 Nc3 e5 Qc2 exd4 Nxd4 Nb6 Rd1 Nxc4 | Score: 22
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 d5 cxd5 Qxd5 Nf3 Qf5 Qxf5 exf5 a3 Bd6 Bg5 Nbd7 e3 h6 | Score: 17
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 Nf6 Nc3 d6 Bg5 e6 Qd2 a6 O-O-O Bd7 f4 b5 Nxc6 Bxc6 | Score: 10
e4 c5 c3 d5 exd5 Qxd5 d4 Nf6 Nf3 Bg4 Be2 e6 h3 Bh5 O-O Nc6 Be3 cxd4 Nxd4 Bxe2 | Score: 13
d4 Nf6 c4 e6 Nf3 d5 Nc3 c6 e3 Nbd7 Qc2 Bd6 Be2 O-O O-O e5 cxd5 cxd5 dxe5 Nxe5 | Score: 13
d4 d5 c4 c6 Nf3 Nf6 e3 e6 Nbd2 Nbd7 Bd3 dxc4 Nxc4 b5 Ncd2 Bb7 a4 Nc5 Bc2 Nxa4 | Score: 18
Nf3 d5 d4 e6 g3 c5 Bg2 Nc6 O-O Nf6 c4 dxc4 Ne5 Bd7 Na3 cxd4 Naxc4 Bc5 Qb3 O-O | Score: 32
e4 c5 c3 e6 d4 d5 exd5 exd5 Nf3 Bd6 dxc5 Bxc5 Bd3 Nf6 O-O O-O h3 Nc6 Nbd2 Bb6 | Score: 27
e4 e6 d4 d5 exd5 exd5 Nf3 Nf6 Bd3 Bg4 O-O Be7 Re1 O-O Bg5 Nbd7 Nbd2 Re8 c3 c5 | Score: 29
c4 e6 Nf3 Nf6 Nc3 b6 g3 Bb7 Bg2 d5 cxd5 Nxd5 O-O Be7 d4 Nd7 Re1 Nxc3 bxc3 Be4 | Score: 20
d4 Nf6 c4 e6 Nf3 d5 Nc3 Be7 Bf4 O-O e3 Nbd7 a3 dxc4 Bxc4 c5 O-O cxd4 exd4 Nb6 | Score: 20
c4 Nf6 Nc3 e6 e4 c5 e5 Ng8 Nf3 Nc6 d4 cxd4 Nxd4 Nxe5 Ndb5 f6 Be3 a6 Nd6+ Bxd6 | Score: 23
e4 d5 exd5 Qxd5 Nc3 Qd6 d4 c6 Bc4 Nf6 Nge2 Be6 Bf4 Qd7 Bb3 g6 O-O Bg7 Be5 O-O | Score: 33
Nf3 g6 e4 d6 d4 Nf6 Nc3 Bg7 Be2 O-O O-O Bg4 Be3 Nc6 Qd2 e5 dxe5 dxe5 Rfd1 Qc8 | Score: 20
Nf3 Nf6 c4 c5 Nc3 e6 g3 b6 Bg2 Bb7 O-O Be7 d4 cxd4 Nxd4 Bxg2 Kxg2 Qc8 Qd3 Nc6 | Score: 15
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 Nf6 Nc3 e5 Ndb5 d6 Bg5 a6 Na3 b5 Bxf6 gxf6 Nd5 Bg7 | Score: 30
e4 e5 Nf3 Nf6 Nxe5 d6 Nf3 Nxe4 d4 d5 Bd3 Nc6 O-O Be7 c4 Nf6 Nc3 O-O cxd5 Nxd5 | Score: 34
Nf3 Nf6 c4 c5 Nc3 d5 cxd5 Nxd5 d4 Nxc3 bxc3 g6 e3 Bg7 Bd3 O-O O-O Qc7 Qe2 Rd8 | Score: 28
c4 Nf6 Nf3 b6 g3 Bb7 Bg2 e6 O-O Be7 Nc3 O-O d4 Ne4 Nxe4 Bxe4 Ne1 Bxg2 Nxg2 d5 | Score: 33
c4 e6 g3 Nf6 Bg2 c5 Nf3 Nc6 O-O d5 cxd5 Nxd5 d4 Be7 dxc5 Bxc5 Ng5 Be7 Ne4 O-O | Score: 24
Nf3 Nf6 d4 c5 c4 cxd4 Nxd4 e6 e3 Nc6 Be2 d5 O-O Bd6 b3 O-O cxd5 Nxd4 Qxd4 Qc7 | Score: 26
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Bg5 e6 f4 Qc7 Bxf6 gxf6 Be2 Nc6 Qd3 Nxd4 | Score: 28
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Nc3 d5 cxd5 Nxd5 Bg2 O-O Nxd5 exd5 | Score: 17
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 Nf6 Nc3 d6 Bc4 Bd7 Bb3 g6 f3 Nxd4 Qxd4 Bg7 Bg5 O-O | Score: 17
d4 Nf6 c4 e6 Nf3 b6 g3 Bb7 Bg2 Be7 Nc3 Ne4 Bd2 d5 Ne5 O-O cxd5 Nxc3 Bxc3 exd5 | Score: 31
d4 d5 c4 e6 Nc3 Be7 Nf3 Nf6 Bg5 O-O e3 Nbd7 Rc1 a6 c5 Ne4 Nxe4 dxe4 Bxe7 Qxe7 | Score: 22
e4 e5 Nf3 Nc6 Bb5 f5 Nc3 fxe4 Nxe4 d5 Ng3 Bg4 h3 Bxf3 Qxf3 Nf6 O-O Bd6 Nh5 e4 | Score: 18
d4 Nf6 Nf3 g6 g3 d5 Bg2 Bg7 O-O O-O c4 c6 cxd5 cxd5 Nc3 Ne4 Ne5 Nxc3 bxc3 Nc6 | Score: 26
Nf3 Nf6 c4 g6 Nc3 Bg7 g3 O-O Bg2 d6 d4 Nbd7 O-O e5 Qc2 exd4 Nxd4 Nb6 Rd1 Nxc4 | Score: 21
e4 c6 d4 d5 exd5 cxd5 c4 Nf6 Nc3 e6 Nf3 Bb4 cxd5 Nxd5 Bd2 Nc6 Bd3 O-O O-O Be7 | Score: 33
Nf3 Nf6 c4 e6 Nc3 d5 d4 Nbd7 cxd5 exd5 Bf4 Nb6 Qc2 g6 e3 Bf5 Bd3 Bxd3 Qxd3 c6 | Score: 27
e4 d6 d4 Nf6 Nc3 g6 Nf3 Bg7 Be2 O-O O-O Bg4 Be3 Nc6 Qd2 e5 dxe5 dxe5 Rad1 Qc8 | Score: 29
d4 Nf6 c4 e6 Nf3 b6 g3 Bb7 Bg2 Be7 Nc3 O-O Qc2 d5 cxd5 Nxd5 O-O Nd7 Nxd5 exd5 | Score: 26
d4 d5 c4 e6 Nc3 Nf6 cxd5 exd5 Bg5 Be7 e3 c6 Qc2 O-O Bd3 Nbd7 Nge2 Re8 O-O Nf8 | Score: 31
d4 Nf6 Nf3 e6 c4 d5 g3 Be7 Bg2 O-O O-O c5 cxd5 exd5 dxc5 Bxc5 Qc2 Bb6 Nc3 Nc6 | Score: 31
e4 e6 d4 d5 Nd2 a6 Ngf3 c5 exd5 exd5 Be2 cxd4 Nxd4 Nf6 O-O Be7 b3 O-O Bb2 Nc6 | Score: 20
d4 Nf6 c4 e6 Nf3 d5 Nc3 Be7 Bf4 O-O e3 Nbd7 Be2 dxc4 Bxc4 c5 dxc5 Nxc5 O-O a6 | Score: 33
d4 Nf6 c4 e6 Nf3 b6 g3 Bb4+ Bd2 Bxd2+ Qxd2 Ba6 b3 O-O Bg2 d5 cxd5 exd5 O-O c5 | Score: 33
d4 d5 Nf3 Nf6 c4 e6 Nc3 c6 e3 Nbd7 Bd3 dxc4 Bxc4 b5 Bd3 b4 Ne4 Bb7 Nxf6+ Nxf6 | Score: 31
d4 Nf6 c4 e6 Nc3 Bb4 Nf3 c5 g3 Nc6 Bg2 Ne4 Bd2 Bxc3 bxc3 O-O O-O Na5 dxc5 Qc7 | Score: 16
e4 c6 d4 d5 Nd2 dxe4 Nxe4 Bf5 Ng3 Bg6 h4 h6 Nf3 Nd7 h5 Bh7 Bd3 Bxd3 Qxd3 Ngf6 | Score: 31
e4 c6 d4 d5 exd5 cxd5 c4 Nf6 Nc3 e6 Nf3 Bb4 cxd5 Nxd5 Bd2 Nc6 Bd3 Be7 O-O O-O | Score: 34
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 Nc6 Bg5 e6 Qd2 Be7 O-O-O O-O Nb3 Qb6 f3 Rd8 | Score: 23
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb4+ Bd2 Bxd2+ Qxd2 c6 Qc2 d5 Nbd2 Nbd7 e4 dxe4 | Score: 21
Nf3 Nf6 c4 g6 g3 Bg7 Bg2 c6 d4 d5 O-O O-O cxd5 cxd5 Nc3 Ne4 Ne5 Nxc3 bxc3 Nc6 | Score: 22
e4 c6 d4 d5 exd5 cxd5 c4 Nf6 Nc3 e6 Nf3 Bb4 cxd5 Nxd5 Bd2 Nc6 Bd3 Nf6 Be3 O-O | Score: 33
c4 c5 Nc3 Nf6 Nf3 e6 g3 b6 Bg2 Bb7 O-O Be7 d4 cxd4 Nxd4 Bxg2 Kxg2 Qc8 b3 Qb7+ | Score: 20
c4 e6 Nc3 Nf6 e4 d5 e5 d4 exf6 dxc3 bxc3 Qxf6 d4 e5 Nf3 exd4 Bg5 Qe6+ Be2 Be7 | Score: 27
d4 Nf6 c4 e6 Nf3 d5 Nc3 dxc4 e3 c5 Bxc4 a6 a4 Nc6 O-O Be7 dxc5 Qxd1 Rxd1 Bxc5 | Score: 12
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Nc3 d5 cxd5 Nxd5 Nxd5 exd5 Bg2 Nd7 | Score: 24
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Bg5 e6 f4 Be7 Qf3 Qc7 O-O-O Nbd7 Qg3 Nc5 | Score: 23
d4 Nf6 c4 e6 Nc3 Bb4 e3 c5 Bd3 d5 cxd5 Nxd5 Ne2 cxd4 exd4 Nc6 O-O Nf6 Bg5 Be7 | Score: 30
c4 c6 Nf3 d5 d4 Nf6 e3 Bf5 Bd3 Bxd3 Qxd3 e6 Nc3 Nbd7 O-O Be7 e4 dxe4 Nxe4 O-O | Score: 21
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 Qb3 c6 Bf4 d5 cxd5 Nxd5 Bg5 Be7 Bxe7 Qxe7 Nbd2 O-O | Score: 29
Nf3 d5 c4 c6 d4 Nf6 cxd5 cxd5 Nc3 Nc6 Bf4 e6 e3 Bd6 Bg3 Bxg3 hxg3 Qd6 Bd3 Bd7 | Score: 13
d4 d5 c4 e6 Nf3 c6 e3 Nf6 Nbd2 Nbd7 Bd3 Bd6 O-O O-O b3 e5 cxd5 cxd5 dxe5 Nxe5 | Score: 23
c4 g6 Nc3 Bg7 g3 e5 Bg2 d6 d3 Nc6 e4 Nge7 Nge2 O-O O-O Nd4 Nxd4 exd4 Nd5 Nxd5 | Score: 16
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 Nf6 Nc3 e5 Ndb5 d6 Nd5 Nxd5 exd5 Nb8 c4 a6 Nc3 Be7 | Score: 26
c4 Nf6 Nf3 e6 d4 b6 e3 Bb7 Bd3 c5 O-O Be7 Nc3 cxd4 exd4 d5 cxd5 Nxd5 Bb5+ Bc6 | Score: 28
Nf3 c5 c4 Nf6 g3 b6 Bg2 Bb7 Nc3 g6 O-O Bg7 d4 cxd4 Nxd4 Bxg2 Kxg2 Qc8 b3 Qb7+ | Score: 25
Nf3 Nf6 c4 e6 d4 b6 g3 Bb7 Bg2 Be7 O-O O-O Nc3 Ne4 Nxe4 Bxe4 Ne1 Bxg2 Nxg2 d5 | Score: 27
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 b3 Bb4+ Bd2 Be7 Nc3 d5 cxd5 Nxd5 Nxd5 exd5 Bg2 O-O | Score: 27
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 Qb6 Nb3 Nf6 Nc3 e6 Bd3 Be7 O-O a6 Qe2 d5 exd5 exd5 | Score: 25
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 d5 cxd5 Qxd5 e3 c5 dxc5 Qxc5 Bd2 Nc6 Rc1 O-O a3 Bxc3 | Score: 26
c4 g6 d4 Bg7 Nc3 Nf6 e4 d6 f3 O-O Be3 c5 dxc5 dxc5 Qxd8 Rxd8 Bxc5 Nc6 Nd5 Nd7 | Score: 17
d4 Nf6 Nf3 b6 g3 Bb7 c4 e6 Bg2 Be7 Nc3 Ne4 Bd2 d5 cxd5 exd5 Qa4+ Qd7 Qc2 Nxd2 | Score: 29
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 Nc6 Bg5 e6 Qd2 a6 O-O-O Bd7 f4 b5 Nxc6 Bxc6 | Score: 13
d4 Nf6 Nf3 e6 Bg5 c5 e3 Be7 dxc5 Bxc5 c4 Bb4+ Nbd2 b6 Bd3 Nc6 O-O Be7 Rc1 Bb7 | Score: 34
e4 c5 Nf3 Nf6 Nc3 Nc6 Bb5 Nd4 e5 Nxb5 Nxb5 Nd5 Ng5 f6 Ne4 f5 c4 Nc7 Nxc5 Nxb5 | Score: 28
c4 c5 Nc3 g6 g3 Bg7 Bg2 Nc6 e3 e6 Nge2 Nge7 d4 cxd4 Nxd4 Nxd4 exd4 O-O O-O d5 | Score: 31
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 Nbd2 Bb7 Bg2 c5 O-O cxd4 Nxd4 Bxg2 Kxg2 Qc8 e3 Be7 | Score: 22
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 Nc6 Bc4 Bd7 h3 Nxd4 Qxd4 g6 O-O Bg7 Be3 O-O | Score: 11
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 Nf6 Nc3 e5 Ndb5 d6 Bg5 a6 Na3 b5 Nd5 Be7 Bxf6 Bxf6 | Score: 28
e4 c5 Nf3 Nc6 c3 d5 exd5 Qxd5 d4 cxd4 cxd4 e6 Nc3 Qd6 Bd3 Nf6 O-O Be7 Re1 O-O | Score: 21
d4 d5 c4 c6 Nf3 Nf6 e3 e6 Nbd2 Nbd7 Bd3 Bd6 O-O O-O e4 e5 cxd5 cxd5 exd5 exd4 | Score: 16
Nf3 Nf6 c4 e6 Nc3 d5 d4 dxc4 e3 a6 a4 c5 Bxc4 Nc6 O-O Be7 dxc5 Qxd1 Rxd1 Bxc5 | Score: 17
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 d5 cxd5 Qxd5 Nf3 Qf5 Qxf5 exf5 a3 Bd6 Bg5 Nbd7 e3 c6 | Score: 22
Nf3 c5 c4 Nf6 Nc3 d5 cxd5 Nxd5 d4 Nxc3 bxc3 g6 e3 Bg7 Bd3 O-O O-O Qc7 Qe2 Rd8 | Score: 21
d4 d5 c4 e6 Nc3 Nf6 cxd5 exd5 Bg5 c6 Qc2 Be7 e3 Nbd7 Bd3 O-O Nge2 Re8 O-O Nf8 | Score: 34
d4 d5 c4 dxc4 e4 Nf6 e5 Nd5 Bxc4 Nb6 Bb3 Nc6 Ne2 Bf5 Nbc3 e6 a3 Qd7 Be3 O-O-O | Score: 20
d4 d5 c4 c6 Nf3 e6 Nbd2 Nf6 e3 Nbd7 Bd3 Bd6 e4 e5 cxd5 cxd5 exd5 O-O O-O exd4 | Score: 11
e4 e6 d4 d5 Nc3 Bb4 e5 c5 a3 Bxc3+ bxc3 Ne7 Qg4 Kf8 h4 Qc7 Qd1 cxd4 cxd4 Qc3+ | Score: 33
d4 e6 Nf3 Nf6 c4 Bb4+ Nc3 b6 Qb3 Qe7 Bf4 d5 e3 Bb7 a3 Bxc3+ Qxc3 O-O Be2 dxc4 | Score: 34
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 a6 Bg5 Nc6 Qd2 e6 O-O-O Bd7 f4 b5 Nxc6 Bxc6 | Score: 25
d4 Nf6 c4 g6 Nc3 d5 cxd5 Nxd5 e4 Nxc3 bxc3 Bg7 Be3 c5 Qd2 Qa5 Rb1 a6 Rc1 cxd4 | Score: 16
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 Nc6 Bg5 e6 Qd2 a6 O-O-O Bd7 f4 h6 Bxf6 Qxf6 | Score: 18
d4 Nf6 c4 g6 Nf3 Bg7 g3 O-O Bg2 c6 Nc3 d5 cxd5 cxd5 Ne5 Nc6 Nxc6 bxc6 O-O Bf5 | Score: 27
d4 Nf6 c4 e6 Nf3 b6 g3 Ba6 Nbd2 Bb7 Bg2 c5 e4 cxd4 e5 Ne4 Nxe4 Bxe4 Qxd4 Bb4+ | Score: 32
g3 g6 Bg2 Bg7 Nf3 c5 c3 Nf6 O-O O-O d4 d6 dxc5 dxc5 Qxd8 Rxd8 Be3 Na6 Na3 Nd5 | Score: 32
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nc6 Nc3 a6 g3 Nge7 Bg2 Nxd4 Qxd4 Nc6 Qd1 Be7 O-O d6 | Score: 21
c4 g6 e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 Nf6 Nc3 Nxd4 Qxd4 d6 Be2 Bg7 O-O O-O Bd2 Bd7 | Score: 28
e4 c6 d4 d5 exd5 cxd5 c4 Nf6 Nc3 e6 Nf3 Be7 cxd5 Nxd5 Bc4 Nc6 O-O O-O Re1 Bf6 | Score: 21
c4 Nf6 Nc3 e6 e4 c5 e5 Ng8 Nf3 Nc6 d4 cxd4 Nxd4 Nxe5 Ndb5 f6 Bf4 a6 Nd6+ Bxd6 | Score: 17
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 Qc7 Nc3 e6 g3 a6 Bg2 Nf6 O-O Be7 Re1 Nxd4 Qxd4 Bc5 | Score: 32
d4 d5 c4 e6 Nc3 Nf6 Nf3 Be7 Bg5 Ne4 Bxe7 Qxe7 Qc2 Nxc3 Qxc3 O-O Rc1 c6 g3 Nd7 | Score: 23
d4 Nf6 c4 e6 Nf3 d5 Nc3 Bb4 e3 c5 Be2 O-O O-O dxc4 Bxc4 Nbd7 a3 cxd4 Qxd4 Nb6 | Score: 28
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 g6 Be3 Bg7 f3 O-O Qd2 Nc6 g4 Be6 O-O-O Nxd4 | Score: 25
e4 e6 d4 d5 Nc3 Bb4 e5 c5 a3 Bxc3+ bxc3 Ne7 Qg4 O-O Nf3 Nbc6 Bd3 f5 exf6 Rxf6 | Score: 23
e4 c6 d4 d5 exd5 cxd5 c4 Nf6 Nc3 Nc6 Bg5 Qa5 Bd2 dxc4 Bxc4 e6 Nf3 Be7 Nd5 Qd8 | Score: 30
d4 d5 c4 c6 Nf3 e6 e3 Nf6 Nbd2 Nbd7 Bd3 Bd6 e4 e5 cxd5 cxd5 O-O O-O exd5 exd4 | Score: 25
e4 e6 d4 d5 Nd2 Nc6 Ngf3 dxe4 Nxe4 Nf6 Nxf6+ gxf6 g3 e5 Bg2 Bg4 h3 Bh5 g4 Bg6 | Score: 33
d4 d5 c4 e6 Nc3 Be7 cxd5 exd5 Bf4 Nf6 e3 Bf5 Nge2 O-O Ng3 Be6 Bd3 c5 dxc5 Bxc5 | Score: 24
Nf3 c5 c4 Nf6 Nc3 d5 cxd5 Nxd5 d4 Nxc3 bxc3 g6 e4 Bg7 Be3 Qa5 Qd2 Bg4 Rc1 Bxf3 | Score: 24
d4 Nf6 c4 g6 Nc3 d5 cxd5 Nxd5 e4 Nxc3 bxc3 Bg7 Be3 c5 Qd2 O-O Nf3 Bg4 Ng5 cxd4 | Score: 12
e4 c6 d4 d5 Nd2 dxe4 Nxe4 Nd7 Nf3 Ngf6 Ng3 c5 dxc5 e6 c6 bxc6 Be2 Be7 O-O Qb6 | Score: 26
d4 d5 c4 c6 Nf3 Nf6 e3 Bf5 Bd3 Bxd3 Qxd3 e6 O-O Nbd7 Nc3 Bb4 Bd2 Bxc3 Bxc3 O-O | Score: 28
e4 c5 Nf3 e6 Nc3 Nc6 Bb5 Nge7 O-O Ng6 d4 cxd4 Nxd4 Be7 Be3 O-O f4 a6 Bxc6 bxc6 | Score: 22
e4 c6 d4 d5 Nc3 dxe4 Nxe4 Nd7 Nf3 Ngf6 Bd3 Nxe4 Bxe4 Nf6 Bd3 Bg4 c3 e6 O-O Be7 | Score: 21
c4 e6 Nc3 d5 d4 Nf6 Nf3 Be7 Bf4 O-O e3 c5 dxc5 Bxc5 cxd5 Nxd5 Nxd5 exd5 a3 Nc6 | Score: 24
d4 d5 c4 e6 Nf3 Nf6 Nc3 c6 Bg5 Nbd7 e3 Qa5 Nd2 dxc4 Bxf6 Nxf6 Nxc4 Qc7 Be2 Be7 | Score: 23
e4 c6 d4 d5 exd5 cxd5 c4 Nf6 Nc3 e6 Nf3 Be7 cxd5 exd5 Bb5+ Nc6 Ne5 Bd7 O-O O-O | Score: 24
Nf3 c5 c4 Nf6 Nc3 d5 cxd5 Nxd5 d4 Nxc3 bxc3 g6 e3 Bg7 Bb5+ Bd7 Bd3 O-O O-O Nc6 | Score: 29
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 d5 a3 Bxc3+ Qxc3 Ne4 Qc2 c5 dxc5 Nc6 e3 Qa5+ Bd2 Qxc5 | Score: 34
d4 d5 c4 dxc4 Nf3 a6 e3 Nf6 Bxc4 e6 O-O c5 dxc5 Qxd1 Rxd1 Bxc5 b3 O-O Bb2 Nbd7 | Score: 28
e4 c6 d4 d5 Nc3 dxe4 Nxe4 Nd7 Ng5 Ngf6 Bd3 e6 N1f3 Bd6 c3 h6 Ne4 Nxe4 Bxe4 O-O | Score: 13
e4 e6 d4 d5 Nd2 c5 exd5 exd5 Ngf3 Nc6 Bb5 Bd6 dxc5 Bxc5 O-O Ne7 Nb3 Bd6 c3 Bg4 | Score: 28
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 Nc6 Bg5 e6 Qd2 Be7 O-O-O O-O f4 h6 Bxf6 Bxf6 | Score: 11
c4 Nf6 Nc3 e6 Nf3 d5 d4 c5 cxd5 Nxd5 e3 Be7 Bd3 cxd4 exd4 b6 Nxd5 Qxd5 O-O Nd7 | Score: 24
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nc6 Nc3 Qc7 Be2 Nf6 O-O a6 Be3 Bb4 Na4 O-O Nxc6 dxc6 | Score: 34
d4 d5 c4 dxc4 Nf3 Nf6 e3 e6 Bxc4 a6 O-O c5 dxc5 Bxc5 Qxd8+ Kxd8 b3 Nbd7 Bb2 b6 | Score: 24
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O d6 c3 Nxe4 d4 Bd7 Re1 Nf6 dxe5 dxe5 Nxe5 Nxe5 | Score: 17
e4 c5 Nc3 Nc6 Nge2 Nf6 d4 cxd4 Nxd4 e5 Ndb5 d6 Bg5 a6 Na3 b5 Nd5 Be7 Bxf6 Bxf6 | Score: 22
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 d6 Bxc6+ bxc6 d4 exd4 Qxd4 O-O Nc3 c5 | Score: 30
e4 c5 Nf3 e6 d4 cxd4 Nxd4 a6 Nc3 Qc7 Bd3 Nf6 O-O Bd6 Kh1 Nc6 Be3 Bf4 Bxf4 Qxf4 | Score: 30
d4 d5 c4 e6 Nc3 Be7 Nf3 Nf6 Bf4 O-O e3 c5 dxc5 Bxc5 cxd5 Nxd5 Nxd5 exd5 a3 Nc6 | Score: 20
d4 Nf6 c4 e6 Nf3 Bb4+ Nbd2 b6 g3 Ba6 Qc2 Bb7 Bg2 Be4 Qb3 Bxd2+ Bxd2 O-O O-O d6 | Score: 24
d4 e6 c4 Nf6 Nf3 d5 Nc3 Be7 Bg5 O-O Qc2 c5 dxc5 dxc4 e3 Qa5 Bxc4 Qxc5 Bd3 Nbd7 | Score: 17
Nf3 d5 d4 Nf6 c4 e6 Nc3 c6 Bg5 Nbd7 cxd5 exd5 e3 Be7 Bd3 Ne4 Bxe7 Qxe7 O-O O-O | Score: 28
e4 e5 Nf3 d6 d4 exd4 Nxd4 g6 Nc3 Bg7 Be2 Nc6 Be3 Nf6 O-O O-O Re1 Re8 Nxc6 bxc6 | Score: 19
d4 Nf6 c4 e6 Nf3 d5 Nc3 Be7 Bf4 O-O e3 c5 dxc5 Bxc5 cxd5 Nxd5 Nxd5 exd5 a3 Nc6 | Score: 17
e4 c6 d4 d5 Nc3 dxe4 Nxe4 Nd7 Bc4 Ngf6 Ng5 e6 Qe2 Nb6 Bd3 h6 N5f3 c5 dxc5 Bxc5 | Score: 18
d4 d5 c4 e6 Nc3 Nf6 cxd5 exd5 Bg5 c6 e3 Bf5 Qf3 Bg6 Bxf6 Qxf6 Qxf6 gxf6 g3 Nd7 | Score: 18
c4 c6 e4 d5 exd5 cxd5 d4 Nf6 Nc3 e6 Nf3 Be7 cxd5 exd5 Bb5+ Nc6 Ne5 Bd7 O-O O-O | Score: 33
e4 c6 d4 d5 Nd2 dxe4 Nxe4 Nd7 Bc4 Ngf6 Nxf6+ Nxf6 c3 Qc7 Nf3 Bg4 h3 Bh5 O-O e6 | Score: 20
Nf3 Nf6 c4 e6 d4 d5 Nc3 Be7 Bg5 O-O e3 Nbd7 Rc1 c6 Bd3 dxc4 Bxc4 Nd5 Bxe7 Qxe7 | Score: 34
d4 Nf6 c4 e6 Nf3 b6 g3 Bb4+ Nbd2 Bb7 Bg2 O-O O-O c5 a3 Bxd2 Qxd2 cxd4 Qxd4 Nc6 | Score: 24
d4 Nf6 c4 e6 Nf3 d5 Nc3 Bb4 Bg5 h6 Bxf6 Qxf6 e3 c5 cxd5 exd5 Bb5+ Bd7 O-O Bxc3 | Score: 13
d4 Nf6 c4 e6 g3 d5 Bg2 dxc4 Nf3 c5 O-O Nc6 Ne5 Bd7 Na3 cxd4 Naxc4 Rc8 Qb3 Nxe5 | Score: 19
e4 c5 Nf3 Nc6 Nc3 Nf6 Bb5 Qc7 O-O Nd4 Re1 a6 Bc4 d6 Nd5 Nxd5 exd5 g6 Nxd4 cxd4 | Score: 33
d4 Nf6 c4 e6 Nc3 d5 cxd5 exd5 Bg5 Be7 e3 c6 Qc2 Nbd7 Bd3 O-O Nf3 Re8 O-O-O Nf8 | Score: 22
d4 d5 c4 e6 Nf3 Nf6 g3 dxc4 Bg2 c5 Qa4+ Bd7 Qxc4 Bc6 dxc5 Nbd7 Be3 Bd5 Qa4 Bc6 | Score: 21
e4 c6 Nc3 d5 Nf3 dxe4 Nxe4 Nf6 Nxf6+ gxf6 Bc4 Qc7 O-O Bg4 d4 e6 Re1 Nd7 h3 Bh5 | Score: 26
c4 Nf6 Nc3 e6 e4 c5 e5 Ng8 Nf3 Nc6 d4 cxd4 Nxd4 Nxe5 Ndb5 a6 Nd6+ Bxd6 Qxd6 f6 | Score: 17
d4 Nf6 c4 e6 Nc3 Bb4 e3 O-O Bd3 d5 Nf3 c5 O-O dxc4 Bxc4 Nbd7 a3 cxd4 exd4 Bxc3 | Score: 25
d4 Nf6 c4 e6 Nf3 d5 g3 dxc4 Bg2 Nc6 Qa4 Bb4+ Bd2 Bd6 O-O O-O Qxc4 e5 dxe5 Nxe5 | Score: 16
d4 Nf6 c4 e6 Nf3 d5 Nc3 Be7 Bg5 O-O e3 h6 Bh4 Ne4 Bxe7 Qxe7 Qc2 Nxc3 Qxc3 dxc4 | Score: 10
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 d5 a3 Bxc3+ Qxc3 Ne4 Qc2 Nc6 e3 e5 cxd5 Qxd5 Bc4 Qa5+ | Score: 32
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 d5 a3 Bxc3+ Qxc3 Ne4 Qc2 c5 dxc5 Nc6 e3 Qa5+ Bd2 Nxd2 | Score: 29
d4 Nf6 Nf3 e6 c4 d5 Nc3 Be7 Bf4 O-O e3 c5 dxc5 Bxc5 a3 Nc6 cxd5 Nxd5 Nxd5 exd5 | Score: 21
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nf6 Nc3 d6 f4 Nc6 Be3 e5 Nxc6 bxc6 Be2 Be7 fxe5 dxe5 | Score: 16
e4 c6 d4 d5 Nc3 dxe4 Nxe4 Nd7 Nf3 Ngf6 Nxf6+ Nxf6 c3 Bg4 h3 Bh5 Be2 e6 O-O Bd6 | Score: 25
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 Nc6 Bg5 e6 Qd2 Be7 O-O-O O-O Nb3 Qb6 Be3 Qc7 | Score: 29
c4 e6 Nc3 Nf6 e4 c5 e5 Ng8 Nf3 Nc6 d4 cxd4 Nxd4 Nxe5 Ndb5 a6 Nd6+ Bxd6 Qxd6 f6 | Score: 34
d4 Nf6 c4 e6 Nc3 d5 Nf3 Be7 Bf4 O-O e3 c5 dxc5 Bxc5 cxd5 Nxd5 Nxd5 exd5 a3 Nc6 | Score: 34
d4 d5 c4 dxc4 e4 e5 Nf3 exd4 Bxc4 Nc6 O-O Nf6 e5 Ne4 Re1 Nc5 Bg5 Be7 Bxe7 Qxe7 | Score: 11
e4 e5 Nf3 Nc6 d4 exd4 Nxd4 Bb4+ c3 Bc5 Nxc6 bxc6 Bd3 Qh4 Qe2 Nf6 h3 O-O g3 Qh5 | Score: 27
d4 Nf6 c4 e6 Nf3 d5 Nc3 Be7 Bg5 O-O e3 c6 Rc1 Nbd7 Bd3 dxc4 Bxc4 Nd5 Bxe7 Qxe7 | Score: 30
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 e6 Nc3 a6 Be2 Nge7 Bf4 Ng6 Be3 Qc7 O-O b5 Nxc6 Qxc6 | Score: 31
d4 Nf6 c4 e6 Nf3 Bb4+ Bd2 Bxd2+ Qxd2 d5 g3 Nbd7 Bg2 c6 Qc2 O-O Nbd2 b6 e4 dxe4 | Score: 21
e4 c6 d4 d5 Nd2 dxe4 Nxe4 Nd7 Ng5 Ngf6 Bc4 e6 Qe2 Nb6 Bd3 h6 N5f3 c5 dxc5 Bxc5 | Score: 29
e4 c6 d4 d5 Nc3 dxe4 Nxe4 Nd7 Nf3 Ngf6 Nxf6+ Nxf6 Ne5 Nd7 Nd3 g6 c3 Bg7 Be2 e5 | Score: 24
e4 e6 d4 d5 Nd2 c5 exd5 exd5 Bb5+ Bd7 Qe2+ Be7 dxc5 Nf6 Nb3 O-O Nf3 Re8 Be3 a6 | Score: 12
d4 Nf6 c4 e6 g3 d5 Bg2 dxc4 Nf3 c5 O-O Nc6 Ne5 Bd7 Nxc4 cxd4 Bf4 Nd5 Nd6+ Bxd6 | Score: 21
d4 Nf6 c4 g6 Nc3 d5 cxd5 Nxd5 e4 Nxc3 bxc3 Bg7 Nf3 c5 Be3 Qa5 Qd2 O-O Rc1 cxd4 | Score: 30
e4 c5 Nf3 d6 Bb5+ Nd7 d4 Nf6 Nc3 cxd4 Qxd4 e5 Qd3 h6 Nd2 Be7 Nc4 O-O Bxd7 Bxd7 | Score: 22
d4 Nf6 c4 g6 Nf3 Bg7 g3 d5 cxd5 Nxd5 Bg2 Nb6 O-O Nc6 Nc3 Nxd4 Nxd4 Qxd4 Nb5 Qc4 | Score: 26
c4 c5 Nf3 Nf6 Nc3 e6 g3 d5 cxd5 Nxd5 Bg2 Nc6 O-O Be7 d4 O-O Nxd5 exd5 dxc5 Bxc5 | Score: 24
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 Nc6 Bg5 e6 Qd2 Be7 O-O-O O-O Nb3 a6 Bxf6 gxf6 | Score: 23
d4 Nf6 c4 e6 Nc3 d5 cxd5 exd5 Bg5 c6 e3 Be7 Bd3 Nbd7 Nge2 Nh5 Bxe7 Qxe7 g4 Nhf6 | Score: 22
e4 e6 d4 d5 Nd2 c5 Ngf3 Nc6 exd5 exd5 Bb5 Bd6 dxc5 Bxc5 O-O Ne7 Nb3 Bd6 Re1 O-O | Score: 32
c4 Nf6 Nc3 g6 d4 d5 Nf3 Bg7 cxd5 Nxd5 e4 Nxc3 bxc3 c5 Be3 Bg4 Qa4+ Nc6 Ne5 Bxe5 | Score: 7
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 Nf6 Nc3 d6 Bg5 e6 Qd2 Be7 O-O-O O-O Nb3 a6 Bxf6 gxf6 | Score: 27
d4 Nf6 c4 d5 Nc3 g6 cxd5 Nxd5 e4 Nxc3 bxc3 c5 Be3 Bg7 Qd2 cxd4 cxd4 Nc6 Rd1 O-O | Score: 16
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 d5 cxd5 Nxd5 a3 Nxc3 bxc3 Ba5 Nf3 c5 Bd2 cxd4 cxd4 Nc6 | Score: 21
d4 d5 c4 e6 Nf3 Nf6 Nc3 Be7 Bg5 h6 Bh4 O-O e3 Ne4 Bxe7 Qxe7 cxd5 Nxc3 bxc3 exd5 | Score: 22
e4 e5 Nf3 d6 d4 exd4 Nxd4 g6 Nc3 Bg7 Bf4 Nf6 Qd2 O-O O-O-O Re8 f3 Nc6 Nxc6 bxc6 | Score: 27
d4 Nf6 c4 e6 Nf3 Bb4+ Bd2 Bxd2+ Qxd2 O-O Nc3 d5 e3 Qe7 Rc1 Rd8 Qc2 dxc4 Bxc4 c5 | Score: 25
d4 Nf6 c4 e6 Nc3 Bb4 g3 c5 Nf3 Ne4 Qd3 Qa5 Qxe4 Bxc3+ Bd2 Bxd2+ Nxd2 Nc6 d5 Nd4 | Score: 20
Nf3 Nf6 c4 e6 Nc3 d5 d4 c5 e3 Nc6 cxd5 Nxd5 Bc4 Be7 Bxd5 exd5 dxc5 Be6 O-O Bxc5 | Score: 20
d4 d5 c4 dxc4 Nf3 Nf6 e3 e6 Bxc4 c5 O-O a6 dxc5 Qxd1 Rxd1 Bxc5 Nbd2 O-O Nb3 Be7 | Score: 28
e4 d5 exd5 Qxd5 Nc3 Qd8 d4 Nf6 Bc4 Bg4 Nge2 e6 O-O c6 Bg5 Be7 h3 Bxe2 Nxe2 Nbd7 | Score: 28
e4 c6 Nc3 d5 Nf3 Bg4 h3 Bxf3 Qxf3 e6 d4 Nf6 Bd3 dxe4 Nxe4 Nbd7 c3 Nxe4 Qxe4 Nf6 | Score: 33
Nf3 c5 c4 Nf6 g3 e6 Bg2 Be7 O-O O-O Nc3 d5 cxd5 Nxd5 d4 Nc6 Nxd5 exd5 dxc5 Bxc5 | Score: 22
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 O-O Nf3 c5 dxc5 Na6 g3 Nxc5 Bg2 Nce4 O-O Nxc3 bxc3 Be7 | Score: 18
e4 c5 Nf3 Nc6 d4 cxd4 Nxd4 Nf6 Nc3 d6 Bc4 Bd7 O-O g6 Nxc6 Bxc6 Bg5 Bg7 Nd5 Bxd5 | Score: 29
d4 d5 c4 e6 Nc3 c5 e3 Nf6 Nf3 Nc6 cxd5 exd5 Bb5 cxd4 exd4 Bb4 O-O O-O Bxc6 bxc6 | Score: 21
c4 Nf6 g3 e6 Bg2 c5 Nf3 d5 O-O Nc6 cxd5 Nxd5 d4 Be7 Nc3 O-O Nxd5 exd5 dxc5 Bxc5 | Score: 25
e4 e6 d4 d5 Nd2 c5 exd5 exd5 Ngf3 Nc6 Bb5 Bd6 dxc5 Bxc5 O-O Ne7 Nb3 Bd6 Bg5 O-O | Score: 28
c4 c5 Nf3 Nf6 Nc3 e6 g3 Nc6 Bg2 d5 cxd5 Nxd5 O-O Be7 d4 O-O Nxd5 exd5 dxc5 Bxc5 | Score: 26
d4 Nf6 c4 e6 Nf3 Bb4+ Bd2 Qe7 Nc3 Bxc3 Bxc3 Ne4 Qc2 Nxc3 Qxc3 d6 g3 O-O Bg2 Nd7 | Score: 31
d4 Nf6 c4 g6 Nc3 d5 cxd5 Nxd5 e4 Nxc3 bxc3 Bg7 Be3 c5 Qd2 cxd4 cxd4 Nc6 Rd1 Qa5 | Score: 23
d4 Nf6 c4 e6 Nf3 b6 g3 Bb7 Bg2 Bb4+ Bd2 Bxd2+ Qxd2 O-O O-O d6 Nc3 Ne4 Nxe4 Bxe4 | Score: 21
d4 Nf6 Nf3 d5 c4 e6 Nc3 c5 cxd5 Nxd5 e4 Nxc3 bxc3 cxd4 cxd4 Nc6 Bc4 b5 Bb3 Bb4+ | Score: 32
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O Be7 Re1 d6 Bxc6+ bxc6 d4 exd4 Nxd4 Bd7 Nc3 O-O | Score: 31
d4 Nf6 c4 e6 Nf3 Bb4+ Bd2 Bxd2+ Qxd2 O-O g3 b6 Bg2 Bb7 Nc3 Ne4 Nxe4 Bxe4 O-O d6 | Score: 15
Nf3 Nf6 c4 e6 Nc3 Bb4 d4 c5 g3 cxd4 Nxd4 O-O Bg2 d5 cxd5 Nxd5 Bd2 Nxc3 bxc3 Be7 | Score: 22
e4 c6 d4 d5 Nc3 dxe4 Nxe4 Nd7 Nf3 Ngf6 Nxf6+ Nxf6 Ne5 Be6 Be2 g6 O-O Bg7 c4 O-O | Score: 21
e4 c5 Nf3 Nc6 Bb5 e6 O-O Nge7 Re1 a6 Bxc6 Nxc6 d4 cxd4 Nxd4 d6 Nxc6 bxc6 Qg4 e5 | Score: 26
Nf3 g6 e4 Bg7 d4 d6 c3 Nf6 Bd3 O-O O-O Nc6 Nbd2 Re8 Nc4 e5 dxe5 Nxe5 Nfxe5 dxe5 | Score: 21
d4 Nf6 c4 e6 Nc3 d5 cxd5 exd5 Bg5 Be7 e3 c6 Bd3 Nbd7 Nge2 Nh5 Bxe7 Qxe7 g4 Nhf6 | Score: 21
e4 e6 d4 d5 Nd2 c5 Ngf3 Nc6 exd5 exd5 Bb5 Bd6 dxc5 Bxc5 Nb3 Bd6 O-O Ne7 Bg5 O-O | Score: 25
d4 d5 Nf3 Nf6 c4 dxc4 e3 e6 Bxc4 c5 O-O a6 dxc5 Bxc5 Qxd8+ Kxd8 Be2 Ke7 b3 Nbd7 | Score: 34
d4 Nf6 c4 e6 Nc3 Bb4 e3 c5 Bd3 cxd4 exd4 d5 cxd5 Nxd5 Ne2 Nc6 O-O O-O Nxd5 exd5 | Score: 20
e4 e6 d4 d5 Nd2 c5 exd5 exd5 Ngf3 Nc6 Bb5 Bd6 O-O Ne7 dxc5 Bxc5 Nb3 Bd6 Bg5 O-O | Score: 20
e4 e5 Nf3 Nc6 Bb5 Nd4 Nxd4 exd4 O-O Bc5 d3 c6 Ba4 Ne7 Nd2 d5 exd5 Nxd5 Re1+ Be6 | Score: 25
d4 Nf6 c4 e6 Nf3 d5 Nc3 Be7 Bg5 O-O e3 h6 Bh4 Ne4 Bxe7 Qxe7 cxd5 Nxc3 bxc3 exd5 | Score: 12
d4 Nf6 c4 e6 Nc3 Bb4 Nf3 c5 g3 O-O Bg2 cxd4 Nxd4 d5 cxd5 Nxd5 Qb3 Qb6 Bxd5 exd5 | Score: 33
Nf3 c5 c4 Nf6 g3 g6 Bg2 Bg7 O-O d5 cxd5 Nxd5 d4 cxd4 Nxd4 O-O Nc3 Nxc3 bxc3 Nc6 | Score: 23
d4 Nf6 c4 g6 Nc3 d5 cxd5 Nxd5 e4 Nxc3 bxc3 Bg7 Be3 c5 Qd2 cxd4 cxd4 Nc6 Bb5 O-O | Score: 18
d4 d5 Nf3 Nf6 c4 dxc4 e3 e6 Bxc4 c5 O-O a6 dxc5 Bxc5 Qxd8+ Kxd8 Nbd2 Ke7 Be2 b6 | Score: 33
e4 e6 d4 d5 Nd2 c5 exd5 exd5 Ngf3 Nc6 Bb5 Bd6 O-O cxd4 Nb3 Ne7 Nbxd4 O-O c3 Bg4 | Score: 15
d4 d5 c4 e6 Nc3 Be7 Nf3 Nf6 Bf4 O-O e3 Nbd7 a3 c5 cxd5 Nxd5 Nxd5 exd5 dxc5 Nxc5 | Score: 17
d4 Nf6 c4 e6 Nf3 Bb4+ Bd2 Bxd2+ Qxd2 d5 Nc3 O-O e3 Qe7 Rd1 Rd8 Qc2 dxc4 Bxc4 c5 | Score: 27
d4 Nf6 c4 e6 g3 d5 Bg2 dxc4 Nf3 Bd7 Ne5 Bc6 Nxc6 Nxc6 O-O Qd7 Nc3 Nxd4 Bxb7 Rb8 | Score: 22
e4 e6 d4 d5 Nd2 c5 Ngf3 Nc6 exd5 exd5 Bb5 Qe7+ Be2 Qc7 c4 Nf6 O-O Be6 dxc5 Bxc5 | Score: 23
Nf3 c5 c4 Nf6 g3 b6 Bg2 Bb7 O-O Nc6 Nc3 e6 d4 Nxd4 Nxd4 Bxg2 Kxg2 cxd4 Qxd4 Be7 | Score: 19
d4 Nf6 c4 e6 Nf3 d5 Nc3 Be7 Bf4 O-O e3 Nbd7 a3 c5 cxd5 Nxd5 Nxd5 exd5 dxc5 Nxc5 | Score: 26
d4 Nf6 c4 e6 g3 d5 Bg2 Be7 Nf3 O-O Nc3 dxc4 Ne5 c5 dxc5 Qxd1+ Nxd1 Bxc5 Bd2 Nd5 | Score: 23
e4 e5 Nf3 Nc6 Bb5 Nf6 O-O Nxe4 d4 Be7 Qe2 Nd6 Bxc6 bxc6 dxe5 Nb7 Nc3 O-O Rd1 d5 | Score: 26
d4 Nf6 Nf3 g6 c4 Bg7 Nc3 d5 Bg5 Ne4 Bf4 Nxc3 bxc3 c5 e3 O-O cxd5 cxd4 cxd4 Qxd5 | Score: 16
Nf3 Nf6 c4 c5 g3 e6 Bg2 Nc6 O-O d5 cxd5 Nxd5 Nc3 Be7 d4 O-O Nxd5 exd5 dxc5 Bxc5 | Score: 22
e4 e6 d4 d5 Nd2 c5 Ngf3 Nc6 exd5 exd5 Bb5 Bd6 dxc5 Bxc5 O-O Ne7 Nb3 Bd6 Bg5 O-O | Score: 22
d4 d5 c4 dxc4 Nf3 e6 e3 a6 Bxc4 c5 O-O Nf6 dxc5 Bxc5 Qxd8+ Kxd8 Ne5 Ke7 Be2 Bd7 | Score: 30
e4 e5 Nf3 Nc6 Bb5 a6 Ba4 Nf6 O-O d6 Bxc6+ bxc6 d4 exd4 Qxd4 Be7 Nc3 O-O Re1 Nd7 | Score: 23
e4 d5 exd5 Qxd5 Nc3 Qd6 d4 c6 Nf3 Nf6 h3 Bf5 Bd3 Bxd3 Qxd3 Nbd7 O-O e6 Ne4 Nxe4 | Score: 29
e4 e6 d4 d5 Nd2 c5 exd5 exd5 Ngf3 Nc6 Bb5 Bd6 dxc5 Bxc5 Nb3 Bd6 O-O Ne7 c4 dxc4 | Score: 23
Nf3 Nf6 c4 e6 Nc3 d5 d4 Be7 Bg5 h6 Bh4 O-O e3 Ne4 Bxe7 Qxe7 cxd5 Nxc3 bxc3 exd5 | Score: 21
e4 c5 Nf3 e6 c3 d5 exd5 exd5 Bb5+ Nc6 O-O Bd6 d4 Ne7 Nbd2 O-O dxc5 Bxc5 Nb3 Bb6 | Score: 30
d4 d5 c4 dxc4 Nf3 Nf6 e3 e6 Bxc4 a6 O-O c5 dxc5 Bxc5 Qxd8+ Kxd8 Nbd2 Ke7 b3 Nbd7 | Score: 28
d4 d5 c4 dxc4 Nf3 Nf6 e3 e6 Bxc4 c5 O-O a6 dxc5 Bxc5 Qxd8+ Kxd8 Nbd2 Nc6 Be2 Ke7 | Score: 33
d4 d5 c4 c6 Nf3 Nf6 Nc3 e6 Bg5 Nbd7 cxd5 exd5 e3 Be7 Qc2 Nh5 Bxe7 Qxe7 O-O-O Nb6 | Score: 19
e4 d6 d4 Nf6 Nc3 g6 Be3 c6 Qd2 Nbd7 O-O-O Qa5 Kb1 b5 Bd3 Nb6 Nd5 Qxd2 Nxf6+ exf6 | Score: 17
e4 e6 d4 d5 Nd2 c5 exd5 exd5 Ngf3 Nc6 Bb5 Bd6 O-O Ne7 dxc5 Bxc5 Nb3 Bd6 Nbd4 O-O | Score: 25
Nf3 c5 c4 Nf6 Nc3 d5 cxd5 Nxd5 d4 Nxc3 bxc3 g6 e4 Bg7 Rb1 O-O Be2 cxd4 cxd4 Qa5+ | Score: 17
e4 c6 d4 d5 Nd2 dxe4 Nxe4 Nd7 Nf3 Ngf6 Nxf6+ Nxf6 h3 Bf5 Bd3 Bg6 Qe2 e6 Bg5 Qa5+ | Score: 21
e4 c5 Nf3 d6 d4 cxd4 Nxd4 Nf6 Nc3 Nc6 Bg5 e6 Qd2 Be7 O-O-O Nxd4 Qxd4 O-O e5 dxe5 | Score: 20
d4 Nf6 c4 e6 Nf3 Bb4+ Bd2 Qe7 g3 Bxd2+ Qxd2 Nc6 Nc3 d5 cxd5 exd5 Bg2 O-O O-O Bg4 | Score: 33
e4 e5 Nf3 Nc6 Bb5 Nf6 O-O Nxe4 d4 Be7 Qe2 Nd6 Bxc6 bxc6 dxe5 Nb7 Nc3 O-O Re1 Nc5 | Score: 24
d4 d5 c4 dxc4 e4 e5 Nf3 exd4 Bxc4 Nc6 O-O Be6 Bxe6 fxe6 Qb3 Qd7 Qxb7 Rb8 Qa6 Nf6 | Score: 28
e4 e6 d4 d5 Nc3 dxe4 Nxe4 Nd7 Nf3 Ngf6 Bg5 Be7 Nxf6+ Bxf6 h4 O-O Bd3 c5 Qe2 cxd4 | Score: 28
d4 Nf6 c4 e6 Nf3 Bb4+ Bd2 Bxd2+ Qxd2 O-O Nc3 d5 e3 Qe7 Rd1 Rd8 Qc2 Nbd7 Be2 dxc4 | Score: 18
c4 c5 Nf3 Nf6 d4 cxd4 Nxd4 e6 g3 Bb4+ Nc3 O-O Bg2 d5 cxd5 Nxd5 Qb3 Qb6 Bxd5 exd5 | Score: 27
d4 d5 c4 dxc4 Nf3 Nf6 e3 e6 Bxc4 c5 O-O a6 dxc5 Bxc5 Qxd8+ Kxd8 Nbd2 Ke7 b3 Nbd7 | Score: 24
e4 e5 Nf3 Nc6 Bb5 d6 d4 Bd7 Bxc6 Bxc6 Nc3 Nf6 Qd3 exd4 Nxd4 Be7 Nf5 g6 Nxe7 Qxe7 | Score: 29
e4 c5 Nc3 Nc6 Nf3 e6 Bb5 Nge7 O-O a6 Bxc6 Nxc6 d4 cxd4 Nxd4 d6 Nxc6 bxc6 Qg4 Rb8 | Score: 24
d4 Nf6 c4 e6 Nc3 Bb4 Qc2 c5 dxc5 Bxc5 Nf3 Nc6 Bg5 Qa5 Bxf6 gxf6 Nd2 Bb4 Rc1 Bxc3 | Score: 13
Nf3 d5 d4 Nf6 c4 e6 g3 dxc4 Bg2 a6 Ne5 c5 Na3 Qxd4 Qxd4 cxd4 Naxc4 Nbd7 O-O Nxe5 | Score: 20
d4 d5 c4 c6 Nc3 Nf6 e3 Bg4 Qb3 Qb6 Qxb6 axb6 cxd5 Nxd5 Nxd5 cxd5 Bd2 Bd7 Nf3 Nc6 | Score: 21
e4 d5 exd5 Qxd5 Nc3 Qd6 d4 c6 h3 Bf5 Nf3 Nd7 Be3 e6 Qd2 Ngf6 O-O-O Ne4 Nxe4 Bxe4 | Score: 32
d4 Nf6 c4 e6 Nf3 Bb4+ Bd2 Bxd2+ Qxd2 d5 g3 Nbd7 Bg2 c6 Na3 Ne4 Qd3 Qa5+ Nd2 Nxd2 | Score: 20
e4 e6 d4 d5 Nc3 Nf6 Bg5 dxe4 Nxe4 Nbd7 Nxf6+ Nxf6 Nf3 c5 Bc4 cxd4 O-O Be7 Qe2 h6 | Score: 23
e4 e5 Nf3 Nc6 Bb5 Nf6 O-O Nxe4 d4 Nd6 Bxc6 dxc6 dxe5 Nf5 Qxd8+ Kxd8 Nc3 Ke8 h3 h5 | Score: 28
d4 Nf6 c4 e6 g3 d5 Bg2 Be7 Nf3 O-O O-O dxc4 Ne5 Nc6 Bxc6 bxc6 Nxc6 Qe8 Nxe7+ Qxe7 | Score: 25
d4 Nf6 c4 e6 Nf3 d5 e3 c5 cxd5 exd5 Bb5+ Nc6 O-O Bd6 dxc5 Bxc5 Bxc6+ bxc6 Qc2 Qd6 | Score: 15
d4 Nf6 c4 e6 g3 d5 Bg2 dxc4 Nf3 Nbd7 Nbd2 Nb6 Nxc4 Nxc4 Qa4+ Bd7 Qxc4 Bc6 O-O Be7 | Score: 33
e4 e5 Nf3 Nc6 Nc3 Nf6 d4 exd4 Nxd4 Bb4 Nxc6 bxc6 Bd3 d5 exd5 cxd5 O-O O-O Bg5 Be6 | Score: 12
e4 c5 Nf3 Nf6 e5 Nd5 Nc3 e6 Nxd5 exd5 d4 Nc6 dxc5 Bxc5 Qxd5 d6 exd6 Qb6 Bc4 Bxf2+ | Score: 15
e4 e5 Nf3 Nc6 Bb5 Nf6 O-O Be7 Re1 d6 d4 exd4 Bxc6+ bxc6 Qxd4 O-O Nc3 Bg4 Qd3 Bxf3 | Score: 25
c4 Nf6 Nc3 e6 Nf3 d5 d4 Be7 g3 O-O Bg2 dxc4 Ne5 Nc6 Bxc6 bxc6 Nxc6 Qe8 Nxe7+ Qxe7 | Score: 20
e4 e6 d4 d5 Nc3 Nf6 Bg5 dxe4 Nxe4 Be7 Bxf6 Bxf6 Nf3 Nd7 Qd2 O-O O-O-O Be7 Qc3 Nf6 | Score: 31
d4 d5 c4 dxc4 e4 Nf6 e5 Nd5 Bxc4 Nb6 Bb3 c5 dxc5 Qxd1+ Kxd1 N6d7 e6 fxe6 Bxe6 Na6 | Score: 20
e4 e5 Nf3 Nc6 Bb5 Nf6 O-O Nxe4 d4 Nd6 Bxc6 dxc6 dxe5 Nf5 Qxd8+ Kxd8 Nc3 Ke8 b3 h5 | Score: 22
d4 d5 c4 e6 Nc3 c5 cxd5 cxd4 Qa4+ Bd7 Qxd4 exd5 Qxd5 Nf6 Qb3 Na6 Nf3 Nc5 Qd1 Nce4 | Score: 32
d4 Nf6 c4 e6 Nf3 d5 Nc3 dxc4 e4 Bb4 Bg5 c5 Bxc4 cxd4 Nxd4 Bxc3+ bxc3 Qa5 Nb5 Nxe4 | Score: 17
e4 e5 Nf3 Nc6 Bb5 Nf6 O-O Nxe4 d4 Nd6 Bxc6 dxc6 dxe5 Nf5 Qxd8+ Kxd8 Nc3 Be6 b3 h6 | Score: 20
e4 e5 Nf3 Nc6 Bb5 Nf6 O-O Nxe4 d4 Nd6 Bxc6 dxc6 dxe5 Nf5 Qxd8+ Kxd8 Nc3 h6 b3 Be6 | Score: 21
e4 e5 Nf3 Nc6 Bb5 Nf6 O-O Nxe4 d4 Nd6 Bxc6 dxc6 dxe5 Nf5 Qxd8+ Kxd8 Nc3 Bd7 b3 h6 | Score: 25
e4 e5 Nf3 Nf6 Nxe5 d6 Nf3 Nxe4 Nc3 Nxc3 dxc3 Be7 Be3 Nd7 Qd2 Ne5 O-O-O O-O h4 Ng4 | Score: 26
d4 Nf6 c4 e6 g3 d5 Bg2 Be7 Nf3 O-O Nc3 dxc4 Ne5 Nc6 Bxc6 bxc6 Nxc6 Qe8 Nxe7+ Qxe7 | Score: 18
c4 c5 Nf3 Nc6 d4 cxd4 Nxd4 e6 Nb5 Nf6 Bf4 Bb4+ N1c3 O-O Bd6 Bxd6 Nxd6 Qb6 Qd2 Ne8 | Score: 25
e4 e6 d4 d5 exd5 exd5 Bf4 Bf5 Bd3 Bxd3 Qxd3 c6 Nd2 Bd6 Bxd6 Qxd6 Ngf3 Ne7 O-O Nd7 | Score: 21
d4 e6 Nf3 Nf6 c4 Bb4+ Nbd2 c5 a3 Bxd2+ Qxd2 cxd4 Nxd4 O-O e3 d5 cxd5 Qxd5 Nb5 Qc6 | Score: 27
c4 c6 e4 d5 exd5 cxd5 d4 Nf6 Nc3 Nc6 Nf3 Bg4 cxd5 Nxd5 Qb3 Bxf3 gxf3 e6 Qxb7 Nxd4 | Score: 30
e4 e5 Nf3 Nc6 Bb5 Nf6 O-O Nxe4 d4 Nd6 Bxc6 dxc6 dxe5 Nf5 Qxd8+ Kxd8 Nc3 h6 h3 Bd7 | Score: 2
e4 e5 Nf3 Nc6 Bb5 Nf6 O-O Nxe4 d4 Nd6 Bxc6 dxc6 dxe5 Nf5 Qxd8+ Kxd8 Nc3 h6 h3 Ke8 | Score: 19
e4 c6 d4 d5 Nc3 dxe4 Nxe4 Nd7 Nf3 Ngf6 Nxf6+ Nxf6 h3 Bf5 Bd3 Bxd3 Qxd3 e6 O-O Be7 | Score: 25
Nf3 d5 d4 Nf6 c4 e6 Nc3 Be7 g3 O-O Bg2 dxc4 Ne5 Nc6 Bxc6 bxc6 Nxc6 Qe8 Nxe7+ Qxe7 | Score: 16
e4 c5 Nf3 e6 d4 cxd4 Nxd4 Nc6 Nc3 d6 Be3 Nf6 f4 e5 fxe5 dxe5 Nxc6 Qxd1+ Rxd1 bxc6 | Score: 28
e4 c6 d4 d5 Nd2 dxe4 Nxe4 Nd7 Bc4 Ngf6 Nxf6+ Nxf6 c3 Qc7 Ne2 e6 Bf4 Bd6 Bxd6 Qxd6 | Score: 28
e4 e5 Nf3 Nc6 Bb5 Nf6 O-O Nxe4 d4 Nd6 Bxc6 dxc6 dxe5 Nf5 Qxd8+ Kxd8 Nc3 Ke8 h3 Be7 | Score: 20
e4 e6 d4 d5 Nc3 Nf6 Bg5 dxe4 Nxe4 Nbd7 Nxf6+ Nxf6 Nf3 Be7 Bd3 c5 Qe2 cxd4 O-O-O a6 | Score: 24
e4 e6 d4 d5 Nd2 c5 exd5 Qxd5 Ngf3 cxd4 Bc4 Qd6 O-O Nf6 Nb3 Nc6 Nbxd4 Nxd4 Nxd4 Be7 | Score: 31
e4 e5 Nf3 Nf6 Nxe5 d6 Nf3 Nxe4 Nc3 Nxc3 dxc3 Be7 Be3 O-O Qd2 Nd7 O-O-O Ne5 Be2 Ng4 | Score: 0
e4 e6 d4 d5 Nd2 c5 Ngf3 cxd4 exd5 Qxd5 Bc4 Qd6 O-O Nf6 Nb3 Nc6 Nbxd4 Nxd4 Nxd4 Be7 | Score: 30
e4 c6 d4 d5 Nd2 dxe4 Nxe4 Nd7 Bc4 Ngf6 Nxf6+ Nxf6 c3 Qc7 Qf3 Bg4 Qg3 Qxg3 hxg3 Bf5 | Score: 32
e4 d5 exd5 Qxd5 d4 e5 Nf3 Nc6 Nc3 Bb4 Bd2 Bxc3 Bxc3 e4 Ne5 Nxe5 dxe5 Ne7 Qxd5 Nxd5 | Score: 17
d4 d5 c4 dxc4 e4 e5 Nf3 exd4 Bxc4 Bb4+ Bd2 Bxd2+ Nbxd2 Qf6 O-O Ne7 e5 Qg6 Nxd4 Nbc6 | Score: 20
d4 Nf6 c4 e6 Nf3 d5 Nc3 dxc4 e4 Bb4 Bg5 c5 Bxc4 cxd4 Nxd4 Bxc3+ bxc3 Qa5 Bxf6 Qxc3+ | Score: 32
d4 Nf6 c4 e6 Nf3 d5 Nc3 c5 cxd5 Nxd5 e4 Nxc3 bxc3 cxd4 cxd4 Bb4+ Bd2 Bxd2+ Qxd2 O-O | Score: 32
e4 e6 d4 d5 Nd2 c5 Ngf3 cxd4 exd5 Qxd5 Bc4 Qd6 O-O Nf6 Nb3 Nc6 Nfxd4 Nxd4 Qxd4 Qxd4 | Score: 17
e4 e5 Nf3 Nc6 Bb5 Nf6 O-O Nxe4 d4 Nd6 Bxc6 dxc6 dxe5 Nf5 Qxd8+ Kxd8 Nc3 h6 Rd1+ Ke8 | Score: 31
Nf3 Nf6 c4 e6 Nc3 d5 d4 c5 cxd5 Nxd5 e4 Nxc3 bxc3 cxd4 cxd4 Bb4+ Bd2 Bxd2+ Qxd2 O-O | Score: 22
c4 Nf6 Nc3 e6 Nf3 d5 d4 c5 cxd5 Nxd5 e4 Nxc3 bxc3 cxd4 cxd4 Bb4+ Bd2 Bxd2+ Qxd2 O-O | Score: 26
e4 Nf6 Nc3 d5 e5 d4 exf6 dxc3 fxg7 cxd2+ Qxd2 Qxd2+ Bxd2 Bxg7 O-O-O Nc6 Nf3 Bg4 Be2 | Score: -25
e4 c5 c3 e6 Nf3 d5 exd5 exd5 Bb5+ Bd7 Bxd7+ Qxd7 O-O Bd6 d4 Nc6 dxc5 Bxc5 Nbd2 Nge7 | Score: 32
e4 e6 d4 d5 Nd2 c5 Ngf3 Nf6 exd5 exd5 Bb5+ Bd7 Bxd7+ Nbxd7 O-O Be7 dxc5 Nxc5 Nd4 Qd7 | Score: 15
e4 e6 d4 d5 Nc3 Nf6 Bg5 dxe4 Nxe4 Nbd7 Nf3 Be7 Nxf6+ Bxf6 Qd2 Bxg5 Nxg5 Nf6 Be2 Qd6 | Score: 26
e4 c6 d4 d5 Nd2 dxe4 Nxe4 Nd7 Nf3 Ngf6 Nxf6+ Nxf6 Ne5 Nd7 Be3 Nxe5 dxe5 Bf5 Qxd8+ Rxd8 | Score: 25
e4 e6 d4 d5 Nd2 c5 exd5 exd5 Bb5+ Bd7 Qe2+ Qe7 Bxd7+ Nxd7 dxc5 Nxc5 Nb3 Qxe2+ Nxe2 Nxb3 | Score: 33
)";

#endif // CONSTS_H
