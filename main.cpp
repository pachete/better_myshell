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

    ForkExec fork_exec = ForkExec();


    std::vector<Command *> commands = cmd_functions.createCommands();

    std::string msg;

    bool exit = false;

    while (!exit) {

        msg = Command::cwd;
        msg += "$ ";

        std::string input = readline(msg.c_str());

        if (!input.empty()) {
            add_history(input.c_str());
        } else {
            continue;
        }

        cmd_functions.runCmd(input, commands, fork_exec);
    }
}
