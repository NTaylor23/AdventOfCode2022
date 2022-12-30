#include "advent.h"
#include <complex>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std::complex_literals;
#define Complex std::complex<int>

const Complex DELTAS[4] {1, -1, 1i, -1i};

// Return the proper scalar according to the char read from the input
Complex getDelta (const char direction) {
    if (direction == 'L') return DELTAS[1];
    if (direction == 'U') return DELTAS[2];
    if (direction == 'D') return DELTAS[3];
    return DELTAS[0];
}

// Compute Chebyshev distance. If it's more than 1, tail must move
bool isAdjacent(const Complex& a, const Complex& b) {
    return std::max(abs(a.real() - b.real()), abs(a.imag() - b.imag())) <= 1;
}

// Check if head/tail are in the same row if moving up/down, or the same column if moving right/left
bool sharesCommonAxis(const Complex& a, const Complex& b, char direction) {
    if (direction == 'L' || direction == 'R') {
        return a.imag() == b.imag();
    }
    return a.real() == b.real();
}

// Move one space according to the direction in the input
void moveCardinal(Complex& obj, const Complex& delta) {
    obj += delta;
}

// Move one space cardinally (according to input direction), then find the appropriate direction for a diagonal move
void moveDiagonal(Complex& obj, const Complex& target, const Complex& scalar, char direction) {
    moveCardinal(obj, scalar);
    for (const Complex& d : DELTAS) {
        if (isAdjacent(obj + d, target) && sharesCommonAxis(obj + d, target, direction)) {
            obj += d;
            return;
        }
    }
}

// Add the xy value to the lookup table
void addToTable(int x, int y, auto& table) {
    if (table.find(x) == table.end()) {
        table.insert({x, std::unordered_set<int>{y}});
    } else {
        table[x].insert(y);
    }
}

auto day09() -> int {
    std::string line;
    std::fstream inFile("input/day09.txt");
    assert (inFile.is_open());

    std::complex<int> head{0}, tail{0}, target{0};
    std::unordered_map<int, std::unordered_set<int>> lookup;

    while (getline(inFile, line)) {
        char direction = line[0]; // U, D, L, R
        int distance = std::stoi(line.substr(2)); // Distance to move
        Complex scalar = getDelta(direction);
        target = head + (distance * scalar);

        while (head != target) {
            moveCardinal(head, scalar); // move the head one place
            if (!isAdjacent(head, tail)) { // check if the tail is adjacent or overlapping
                if (sharesCommonAxis(head, tail, direction)) { // tail is in the same row/col as the head, can be moved cardinally
                    moveCardinal(tail, scalar);
                } else { // tail is not in the same row/col and must be moved diagonally
                    moveDiagonal(tail, head, scalar, direction);
                }
            }
            addToTable(tail.real(), tail.imag(), lookup);
        }
    }
    int part1 {0};
    // the sum of all sets of y values will be the number of unique points visited
    // this is kind of an awkward implementation, but works as a kludge to avoid hashing the Complex data type
    for (auto& [k, v] : lookup) {
        part1 += v.size();
    }

    std::cout << part1;

    return 0;
}