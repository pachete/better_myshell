//
// Created by pch on 27/05/18.
//

#include "Msource.h"


Msource::Msource() : Command(".") {}

void Msource::execute(std::vector<std::string> args) {

    std::string script;
    CmdFunctions cmd_functions;

    for (const auto &arg : args) {
        if (boost::starts_with(arg, "-")) {
            if (arg == "--help" || arg == "-h") {
                help();
                return;
            } else {
                std::cout << arg << " is not a valid option" << std::endl;
                my_error = -1;
                return;
            }
        } else {
            script = arg;
        }
    }

    cmd_functions.handleScript(script);
}

void Msource::help() {
    std::cout << "script running help" << std::endl;

}