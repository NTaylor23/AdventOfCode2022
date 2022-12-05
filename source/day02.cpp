#include "advent.h"
#include <fstream>
#include <iostream>

auto day02() -> int {
    std::string play;
    std::fstream inFile("input/day02.txt");
    assert(inFile.is_open());

    int part1 = 0, part2 = 0;
    while (getline(inFile, play)) {
        int them = play.at(0) - 'A', us = play.at(2) - 'X';
        if (them == (us + 2) % 3) {
            part1 += 6; // win
        }  else if (us == them) {
            part1 += 3; //draw
        }

        part1 += 1 + us;
        part2 += (us * 3) + std::min<uint>((us + them) % 3 - 1, 2) + 1;
        // ^ Values of a move must fall between 1 and 3. Subtract the move's numeric value (between 0 and 2),
        // and you'll get -1 when the correct opposing move goes to 3 from 1.
        // unsigned int underflow will make any negative value into some huge number, and from there, we just find
        // std::min of that value and 2, then add 1.
    }
    inFile.close();
    std::cout << "Day 2:\nIf everything goes exactly according to my Rock/Paper/Scissors strategy guide, "
                 "my score will be " << part1 << ".\n";
    std::cout << "But my instructions were updated, and now my score works out to " << part2 << ".\n\n";
    return 0;
}