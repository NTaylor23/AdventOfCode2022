#include "advent.h"
#include <complex>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <unistd.h>

using namespace std::complex_literals;
#define Complex std::complex<int>

const Complex DELTAS[4] {1, -1, 1i, -1i}; // R L U D
const int ROPE_LENGTH{10}, ZERO_X = 11, ZERO_Y = 14;
Complex rope[ROPE_LENGTH] {0};

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

//Move one space cardinally (according to input direction), then find the appropriate direction for a diagonal move
void moveDiagonal(Complex& obj, const Complex& target, const Complex& scalar, char direction) {
    moveCardinal(obj, scalar);
    for (const Complex& d : DELTAS) {
        bool adj = isAdjacent(obj + d, target);
        //bool ca = sharesCommonAxis(obj + d, target, direction);
        if (adj && d != scalar) {
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

void move(const Complex& head, Complex& follower, const Complex& scalar, char direction) {
    while (!isAdjacent(head, follower)) {
        if (sharesCommonAxis(head, follower, direction)) {
            std::cout << "Cardinal\n";
            moveCardinal(follower, scalar);
        } else {
            std::cout << "Diagonal\n";
            moveDiagonal(follower, head, scalar, direction);
        }
    }
}

void clearTable(auto& table) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 26; j++) {
            table[i][j] = '.';
        }
    }
}

void printTable(auto& table) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 26; j++) {
            std::cout << table[i][j];
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void adjustTrailing(const Complex& scalar, char direction, auto& table) {
    for (int i = 1; i < ROPE_LENGTH; i++) {
        move(rope[i - 1], rope[i], scalar, direction);
        table[ZERO_Y - rope[i].imag()][ZERO_X + rope[i].real()] = '0' + i;
    }
}

auto day09() -> int {
    std::string line;
    std::fstream inFile("input/day09.txt");
    assert (inFile.is_open());

    std::complex<int> target{0};
    std::unordered_map<int, std::unordered_set<int>> lookupTail;
    std::unordered_map<int, std::unordered_set<int>> lookupRope;

    std::vector<std::vector<char>> table;
    for (int i = 0; i < 20; i++) {
        std::vector<char> row;
        for (int j = 0; j < 26; j++) {
            row.emplace_back('.');
        }
        table.emplace_back(row);
    }

    clearTable(table);

    std::cout << "Initial: [" << rope[0].real() << ", " << rope[0].imag() << "]\n";
    while (getline(inFile, line)) {

        char direction = line[0]; // U, D, L, R
        int distance = std::stoi(line.substr(2)); // Distance to move
        Complex scalar = getDelta(direction); // Direction variable represented as complex number
        target = rope[0] + (distance * scalar);
        std::cout << "~~~~~~~~~~~~ " << line << " ~~~~~~~~~~~~\n";

        while (rope[0] != target) {

            moveCardinal(rope[0], scalar); // move the head
            table[ZERO_Y - rope[0].imag()][ZERO_X + rope[0].real()] = 'H';

            if (line == "L 8") {
                std::cout << "";
            }

            adjustTrailing(scalar, direction, table);
            std::cout << direction << "\n";
            printTable(table);
            usleep(300000);
            clearTable(table);
            addToTable(rope[1].real(), rope[1].imag(), lookupTail);
            addToTable(rope[9].real(), rope[9].imag(), lookupRope);
        }
    }
    inFile.close();
    int part1{0}, part2{0};
    for (auto& [k, v] : lookupTail) {
        part1 += v.size();
    }

    for (auto& [k, v] : lookupRope) {
        part2 += v.size();
    }

    std::cout << part1 << " " << part2;

    /*
     * We want to see...
     * Initial 0, 0
     *
     * R 5  -> 0, 0
     * U 8  -> 0, 0
     * L 8  -> 1, 3
     * D 3  -> 1, 3
     * R 17 -> 5, 5
     * D 10 -> 10, 0
     * L 25 -> -1, -5
     * U 20 -> -11, 6
     */

    return 0;
}