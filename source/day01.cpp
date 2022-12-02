#include "advent.h"
#include "parser.h"
#include <iostream>
#include <algorithm>
#include <numeric>

void shift(VecInt& max, int num) {
    int i = 0;
    while (max[i] > num && i < 3) {i++;}
    std::shift_right(max.begin() + i, max.end(), 1);
    max[i] = num;
}

auto day01() -> int {
    parser p("input/day01.txt", "str");
    VecStr in = p.getStrs();
    VecInt max{0, 0, 0};

    int current = 0;
    for (const std::string& item : in){
        if (item.empty()) {
            shift(max, current);
            current = 0;
        } else {
            current += std::stoi(item);
        }
    }

    std::cout << "Day 1!\nThe elf carrying the most calories has " << max[0] << " calories.\n";
    std::cout << "The three elves carrying the most calories have "
    << std::accumulate(max.begin(), max.end(), 0) << " combined calories.\n\n";
    return 0;
}