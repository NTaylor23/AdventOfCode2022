#ifndef ADVENT_H
#define ADVENT_H

#include <fstream>
#include <iostream>
#include <vector>

#define VecStr std::vector<std::string>
#define VecInt std::vector<int>

class parser {
private:
    std::vector<int> intList;
    std::vector<std::string> strList;
    std::string path, type;

public:
    /// Constructor (path to .txt file, text type ("str" for plaintext, "int" for numbers)
    /// Other types are not implemented but easy enough to workaround
    /// \param filepath path to .txt file
    /// \param type text type
    parser(std::string filepath, std::string type);

    /// getter for string vector output
    /// \return vector of strings (akin to readlines() in python)
    std::vector<std::string> getStrs() { return strList; };

    /// getter for int vector output
    /// \return vector of integers
    std::vector<int> getInts() { return intList; }

    static std::vector<std::string> split(std::string s, const std::string& delim);

    /// runner function called in constructor
    void parse();

    static bool is_number(const std::string &s);
};

#endif //ADVENT_H
