#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "prompt.h"
#include "builtins.h"
#include "piping.h"
#include "shell.h"

int main() {
    Prompt prompt;
    std::string input;

    while (true) {
        // Display the prompt
        std::cout << prompt.getPrompt();

        // Get user input
        if (!std::getline(std::cin, input)) {
            break; // Exit on EOF
        }

        // Exit condition
        if (input == "exit") {
            break;
        }

        // Tokenize input
        std::vector<std::string> tokens;
        std::istringstream iss(input);
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        // Handle built-in commands
        if (handleBuiltInCommand(tokens)) {
            continue;
        }

        // Check if the command has pipes
        if (input.find('|') != std::string::npos) {
            executePipedCommands(input);
        } else {
            executeSingleCommand(input);
        }
    }

    return 0;
}
