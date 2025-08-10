#include "shell.h"
#include "tokeniser.h"
#include "piping.h"
#include "builtins.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <pwd.h>
#include <limits.h>
#include <fcntl.h>
#include <cstring>
#include <cstdlib>

using namespace std;



void executeSingleCommand(const std::string &command) {
    std::vector<std::string> tokens = tokenize(command);

    std::vector<char*> argv;
    for (auto &tok : tokens) {
        argv.push_back(strdup(tok.c_str()));
    }
    argv.push_back(nullptr);

    execvp(argv[0], argv.data());

    perror("execvp failed");

    for (char *arg : argv) {
        free(arg);
    }
}
