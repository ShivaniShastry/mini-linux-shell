#include "prompt.h"
#include<iostream>
#include <unistd.h>
#include <pwd.h>
#include <limits.h>
#include <iostream>
#include <string>
using namespace std; 


std::string Prompt::getPrompt() const {
    char hostname[1024];
    gethostname(hostname, sizeof(hostname));
    struct passwd *pw = getpwuid(getuid());
    std::string username = pw->pw_name;
    std::string cwd;
    char buff[PATH_MAX];
    if (getcwd(buff, sizeof(buff)) != nullptr) {
        cwd = buff;
    }
    return username + "@" + hostname + ":" + cwd + "$ ";
}

void showPrompt() {
    char hostname[HOST_NAME_MAX];
    char cwd[PATH_MAX];
    gethostname(hostname, sizeof(hostname));
    getcwd(cwd, sizeof(cwd));
    string user = getpwuid(getuid())->pw_name;
    cout << "\033[1;36m" << user << "@" << hostname
         << "\033[0m:\033[1;34m" << cwd << "\033[0m$ ";
}
