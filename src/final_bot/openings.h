#ifndef OPENINGS_H
#define OPENINGS_H

#include <map>
#include <vector>
#include <string>
#include <fstream>

#include "chess-library/include/chess.hpp"
#include "utils.h"





std::map<std::string, std::vector<ScoreMovePair>> loadOpeningsFromFile(const std::string& file_path);

#endif // OPENINGS_H