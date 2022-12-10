#include "advent.h"
#include <cmath>
#include <complex>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>

using namespace std::complex_literals;
#define Complex std::complex<int>

const Complex DELTAS[4] {1, -1, 1i, -1i};

Complex getDelta (const char direction) {
    if (direction == 'L') return DELTAS[1];
    if (direction == 'U') return DELTAS[2];
    if (direction == 'D') return DELTAS[3];
    return DELTAS[0];
}

// this is fine
bool isAdjacent(const Complex& a, const Complex& b) {
    return std::max(abs(a.real() - b.real()), abs(a.imag() - b.imag())) <= 1;
}

// this is fine
void moveCardinal(Complex& obj, const Complex& delta) {
    obj += delta;
}

// must take into account whether direction is vertical or horizontal... and then add the correct opposing delta
void moveDiagonal(Complex& obj, const Complex& target, const Complex& direction) {
    moveCardinal(obj, direction);
    if (isAdjacent(obj + 1, target)) {
        obj += 1;
    } else if (isAdjacent(obj - 1, target)) {
        obj -= 1;
    }
}

auto day09() -> int {
    std::string line;
    std::fstream inFile("input/day09.txt");
    assert (inFile.is_open());

    std::complex<int> h{0}, t{0}, target{0};
    std::unordered_set<std::string> positionsVisitedByTail{"00"};

    char hFlag, tFlag;
    while (getline(inFile, line)) {

        char direction = line[0];
        int distance = line[2] - '0';
        hFlag = direction;
        Complex currentDelta = getDelta(direction);
        target = h + (distance * currentDelta);

        while (h != target) {
            moveCardinal(h, currentDelta); //moveCardinal standard deltas according to taxicab geometry
            if (h.real() == 4 && h.imag() == 2) {
                std::cout << "stop";
            }
            if (!isAdjacent(h, t)) {
                if (tFlag != hFlag) {
                    moveDiagonal(t, h, currentDelta);
                } else {
                    moveCardinal(t, currentDelta);
                }
            }
            tFlag = hFlag;
            std::stringstream ss;
            ss << t.real() << t.imag();
            positionsVisitedByTail.insert(ss.str());
        }
        //std::cout << "H: [" << h.real() << ", " << h.imag() << "]\n";
        //std::cout << "T: [" << t.real() << ", " << t.imag() << "]\n";
    }

    std::cout << "This will not work...";

    return 0;
}
