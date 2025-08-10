#ifndef SHELL_H
#define SHELL_H

#include <string>
#include <vector>

// Starts the shell loop (main entry point for shell execution)
void runShell();

// Executes a single command (supports built-in commands, redirection, pipes, etc.)
void executeCommand(const std::vector<std::string>& args);

// Checks if a command is built-in and executes it
bool handleBuiltInCommand(const std::vector<std::string>& args);

// Executes a single, non-piped command (supports redirection)
void executeSingleCommand(const std::string& input);

#endif // SHELL_H
