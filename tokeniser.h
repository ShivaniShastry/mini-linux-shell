#ifndef TOKENISER_H
#define TOKENISER_H

#include <string>
#include <vector>

// Splits a string by a given delimiter character
std::vector<std::string> split(const std::string &str, char delimiter);

// Tokenizes a string by spaces (and possibly handles quotes in future)
std::vector<std::string> tokenize(const std::string &input);

#endif
