#include "advent.h"
#include <fstream>
#include <iostream>
#include <vector>


static int y{0};
std::vector<std::vector<char>> CRT;

int addSignalStrength(const int &cycles, const int &x) {
    return cycles * x;
}

void drawPixel(int cycle, int x, const int row) {
    if (x - 1 == cycle || x == cycle || x + 1 == cycle) {
        CRT[row][cycle] = '#';
    }
}

void cycle(int &cycles, int &signalStrength, int &x) {
    drawPixel(cycles % 40, x, y);
    cycles++;

    if (cycles == 20 || (cycles - 20) % 40 == 0) {
        signalStrength += addSignalStrength(cycles, x);
    }

    if (cycles % 40 == 0 && cycles > 0) {
        y++;
    }
}

auto day10() -> int {
    std::string line;
    std::fstream inFile("input/day10.txt");
    assert (inFile.is_open());

    int x = 1, cycles = 0, signalStrength = 0;

    for (int i = 0; i < 6; i++) {
        std::vector<char> row;
        for (int j = 0; j < 40; j++) {
            row.emplace_back('.');
        }
        CRT.emplace_back(row);
    }

    while (getline(inFile, line)) {
        if (line == "noop") {
            cycle(cycles, signalStrength, x);
        } else if (line.starts_with("addx")) {
            int value = std::stoi(line.substr(5));
            cycle(cycles, signalStrength, x);
            cycle(cycles, signalStrength, x);
            x += value;
        }
    }

    inFile.close();
    std::cout << "Day 10:\nThe sum of the signals' strengths after 220 cycles is " << signalStrength << ".\n"
    << "The message on the CRT is the following:\n";

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 40; j++) {
            std::cout << CRT[i][j] << " ";
        }
        std::cout << '\n';
    }

    return 0;
}