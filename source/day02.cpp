#include "advent.h"
#include "parser.h"
#include <iostream>

auto day02() -> int {
    parser p("input/day02.txt", "str");
    VecStr rps = p.getStrs();

    int part1 = 0, part2 = 0;

    for (const std::string& play : rps) {
        //Normalize both numbers to [0 .. 2]
        int them = play.at(0) - 'A', us = play.at(2) - 'X';
        if (them == (us + 2) % 3) {
            part1 += 6; // win
        }  else if (us == them) {
            part1 += 3; //draw
        } //else part1 += 0

        part1 += 1 + us; //[0 .. 2] turns to [1 .. 3] and matches the move types
        //exploit uint underflow to save a conditional step
        part2 += (us * 3) + std::min<uint>((us + them) % 3 - 1, 2) + 1;
    }

    std::cout << "Day 2:\nIf everything goes exactly according to my Rock/Paper/Scissors strategy guide, "
                 "my score will be " << part1 << ".\n";
    std::cout << "But my instructions were updated, and now my score works out to " << part2 << ".\n\n";
    return 0;
}