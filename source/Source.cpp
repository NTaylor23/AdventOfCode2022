#include "advent.h"
#include <chrono>
#include <iostream>
using namespace std::chrono;

int main() {
    auto start = high_resolution_clock::now();

    // Puzzles!
    //day01();
    //day02();
    day03();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "\n\n~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n"
                 "Total processing time: " << duration.count() << " microseconds.\n";

    return 0;
}
