#include "builtins.h"
#include <iostream>
#include <unistd.h> // for chdir
#include <cstdlib>  // for exit
using namespace std;

bool handleBuiltInCommand(const vector<string>& tokens) {
    if (tokens.empty()) return false;
    if (tokens[0] == "exit") exit(0);
    if (tokens[0] == "cd") {
        const char* path = tokens.size() > 1 ? tokens[1].c_str() : getenv("HOME");
        if (chdir(path) != 0) perror("cd");
        return true;
    }
    if (tokens[0] == "help") {
        cout << "Built-in commands:\n"
             << "  cd [dir]       Change directory\n"
             << "  exit           Exit shell\n"
             << "  help           Show help\n"
             << "Supports |, <, >, >>, &\n";
        return true;
    }
    return false;
}