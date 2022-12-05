#include "advent.h"
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

void shift(std::vector<int>& max, int num) {
    int i = 0;
    while (max[i] > num && i < 3) {i++;}
    std::shift_right(max.begin() + i, max.end(), 1);
    max[i] = num;
}

auto day01() -> int {
    std::string buf;
    std::fstream inFile("input/day01.txt");
    assert(inFile.is_open());

    int current = 0;
    std::vector<int> max {0, 0, 0};
    while (getline(inFile, buf)) {
        if (buf.empty()) {
            shift(max, current);
            current = 0;
        } else {
            current += std::stoi(buf);
        }
    }

    inFile.close();
    std::cout << "Day 1!\nThe elf carrying the most calories has " << max[0] << " calories.\n";
    std::cout << "The three elves carrying the most calories have "
              << std::accumulate(max.begin(), max.end(), 0) << " combined calories.\n\n";
    return 0;
}
