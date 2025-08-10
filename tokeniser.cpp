#include "tokeniser.h"
#include <sstream>

// Split by a single char delimiter
std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(str);

    while (std::getline(ss, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

// Tokenize by spaces
std::vector<std::string> tokenize(const std::string &input) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream iss(input);

    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}
