#include "advent.h"
#include "parser.h"
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include <variant>

#define NoValue LONG_MIN

struct Equation {
    std::variant<std::string, long> a, b;
    char op;
    Equation(auto &_a, auto &_b, char _op) : a(_a), b(_b), op(_op) {}

    [[nodiscard]] long eval() const {
        if (std::holds_alternative<long>(a) && std::holds_alternative<long>(b)) {
            long num_a = std::get<long>(a);
            long num_b = std::get<long>(b);
            switch (op) {
                case '+':
                    return num_a + num_b;
                case '-':
                    return num_a - num_b;
                case '*':
                    return num_a * num_b;
                case '/':
                    return num_a / num_b;
            }
        }
        return NoValue;
    }

    void set_a(const auto &a) { this->a = a; }
    void set_b(const auto &b) { this->b = b; }
};

auto day21a() -> int {
    std::string line;
    std::fstream inFile("input/day21.txt");
    assert (inFile.is_open());

    std::unordered_map<std::string, std::optional<Equation>> equations;
    std::unordered_map<std::string, long> literals;

    while (getline(inFile, line)) {
        std::vector<std::string> halves = parser::split(line, ": ");
        auto val = halves[0];
        if (parser::is_number(halves[1])) {
            literals.insert({val, std::stoi(halves[1])});
        } else {
            auto eq = parser::split(halves[1], " ");
            auto e = Equation(eq[0], eq[2], eq[1].at(0));
            equations.insert({val, e});
        }
    }

    auto try_update = [&literals, &equations](const auto& val, auto& tmp, const auto& k, bool is_b = false) {
        if (std::holds_alternative<std::string>(val)
            && literals.find(std::get<std::string>(val)) != literals.end()) {

            if (is_b) {
                tmp.set_b(literals.at(std::get<std::string>(val)));
            } else {
                tmp.set_a(literals.at(std::get<std::string>(val)));
            }
            equations[k] = tmp;
        }
    };

    while (literals.find("root") == literals.end()) {
        for (const auto& [k, v] : equations) {
            if (v.has_value()) {

                Equation tmp = v.value();
                try_update(tmp.a, tmp, k);
                try_update(tmp.b, tmp, k, true);

                long res = tmp.eval();
                if (res != NoValue) {
                    literals[k] = res;
                    equations[k] = std::nullopt;
                }
            }
        }
    }
    std::cout << "\n\nDay 10:\nThe monkey named [root] will yell out the number " << literals["root"] << ".\n";

    return 0;
}