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
    VecStr getStrs() { return strList; };

    /// getter for int vector output
    /// \return vector of integers
    VecInt getInts() { return intList; }

    /// Tokenize a string into a list based on a delimiter
    /// "The cat, the bat, the hat" with delim ',' ---> {"The cat", "the bat", "the hat"}
    /// \param input_string the string you want to tokenize
    /// \param delim the delimiter
    /// \param out the vector of strings to insert values into
    /// \param strip remove leading/trailing whitespace if true, leave alone otherwise
    void split(const std::string& input_string, char delim, VecStr& out, bool strip = false);

    static VecStr split_to_new(const std::string& input_string, char delim, bool strip = false);


    /// remove leading and trailing whitespace from a string
    /// "     The cat, the bat, the hat     " ---> "The cat, the bat, the hat"
    /// \param input_string the string you want to remove whitespace from
    void strip(std::string& input_string);

    /// runner function called in constructor
    void parse();

};

#endif //ADVENT_H
