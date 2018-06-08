#include <iostream>
#include <cstdlib>
#include <readline/history.h>
#include <readline/readline.h>

#include "CmdFunctions/CmdFunctions.h"

int main(int argc, char *argv[]) {

    CmdFunctions cmd_functions = CmdFunctions();

    if (argc > 1) {
        cmd_functions.handleScript(argv[1]);
        exit(0);
    }

    cmd_functions.setPath();

    std::string input;
    std::string msg;

    for (;;) {

        msg = Command::cwd;
        msg += "$ ";

        input = readline(msg.c_str());

        if (!input.empty()) {
            add_history(input.c_str());
        } else {
            continue;
        }

        cmd_functions.runCmd(input);
    }
}
