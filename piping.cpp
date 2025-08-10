#include "piping.h"
#include "tokeniser.h"
#include <vector>
#include <string>
#include <cstring>        // for strdup
#include <unistd.h>       // for fork, execvp, pipe, dup2
#include <fcntl.h>        // for open
#include <sys/wait.h>     // for wait
#include <iostream>
#include <cstdlib>        // for free

using namespace std;

void executePipedCommands(const string& input) {
    vector<string> commands = split(input, '|');
    int num_cmds = commands.size();
    int pipefd[2 * (num_cmds - 1)];

    for (int i = 0; i < num_cmds - 1; i++) {
        if (pipe(pipefd + i * 2) == -1) {
            perror("pipe");
            exit(1);
        }
    }

    for (int i = 0; i < num_cmds; i++) {
        vector<string> redirectTokens = split(commands[i], ' ');
        string infile, outfile;
        bool redirect_in = false, redirect_out = false, append_out = false;

        for (size_t j = 0; j < redirectTokens.size(); j++) {
            if (redirectTokens[j] == "<" && j + 1 < redirectTokens.size()) {
                redirect_in = true;
                infile = redirectTokens[j + 1];
                redirectTokens.erase(redirectTokens.begin() + j, redirectTokens.begin() + j + 2);
                j--;
            } else if (redirectTokens[j] == ">" && j + 1 < redirectTokens.size()) {
                redirect_out = true;
                outfile = redirectTokens[j + 1];
                redirectTokens.erase(redirectTokens.begin() + j, redirectTokens.begin() + j + 2);
                j--;
            } else if (redirectTokens[j] == ">>" && j + 1 < redirectTokens.size()) {
                append_out = true;
                outfile = redirectTokens[j + 1];
                redirectTokens.erase(redirectTokens.begin() + j, redirectTokens.begin() + j + 2);
                j--;
            }
        }

        string cleanCmd;
        for (auto& tok : redirectTokens) cleanCmd += tok + " ";
        vector<string> strArgs = tokenize(cleanCmd);

        // Convert to char* for execvp
        vector<char*> args;
        for (auto &s : strArgs) {
            args.push_back(strdup(s.c_str())); // duplicate so execvp can use it
        }
        args.push_back(nullptr); // execvp expects a null terminator

        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            if (i != 0) dup2(pipefd[(i - 1) * 2], STDIN_FILENO);
            if (i != num_cmds - 1) dup2(pipefd[i * 2 + 1], STDOUT_FILENO);

            if (redirect_in) {
                int fd = open(infile.c_str(), O_RDONLY);
                if (fd < 0) { perror("input redirect"); exit(1); }
                dup2(fd, STDIN_FILENO); close(fd);
            }
            if (redirect_out) {
                int fd = open(outfile.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0644);
                if (fd < 0) { perror("output redirect"); exit(1); }
                dup2(fd, STDOUT_FILENO); close(fd);
            }
            if (append_out) {
                int fd = open(outfile.c_str(), O_CREAT | O_WRONLY | O_APPEND, 0644);
                if (fd < 0) { perror("append redirect"); exit(1); }
                dup2(fd, STDOUT_FILENO); close(fd);
            }

            for (int j = 0; j < 2 * (num_cmds - 1); j++) close(pipefd[j]);

            execvp(args[0], args.data());
            perror("execvp");
            exit(1);
        }

        // Free strdup()'d args in parent
        for (char* arg : args) {
            free(arg);
        }
    }

    // Close pipes in parent
    for (int i = 0; i < 2 * (num_cmds - 1); i++) close(pipefd[i]);
    for (int i = 0; i < num_cmds; i++) wait(nullptr);
}
