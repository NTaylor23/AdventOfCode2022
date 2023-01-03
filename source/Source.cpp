#include "advent.h"
#include <chrono>
#include <iostream>
using namespace std::chrono;

int main() {
    auto start = high_resolution_clock::now();

    // Puzzles!
    //day01();
    //day02();
    //day03();
    //day04();
    //day05();
    //day06();
    //day07();
    //day08();
    //day09(); //incomplete
    //day10();
    //day11();
    day12();
    //day13();
    //day21a();
    //day21b();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    std::cout << "\n\n~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n"
                 "Total processing time: " << duration.count() << " ms.\n";

    return 0;
}
