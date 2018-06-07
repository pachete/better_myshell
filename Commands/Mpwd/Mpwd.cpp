//
// Created by pch on 27/05/18.
//

#include "Mpwd.h"


Mpwd::Mpwd() : Command("mpwd") {}

void Mpwd::execute(std::vector<std::string> args) {
    args.erase(args.begin());

    for (const auto &arg : args) {
        if (boost::starts_with(arg, "-")) {
            if (arg == "--help" || arg == "-h") {
                help();
                return;
            } else {
                my_error = 22;
                std::cerr << "myshell: mpwd: " << arg << ": invalid option" << std::endl;
                return;
            }
        }
    }

    std::cout << cwd << std::endl;
}

void Mpwd::help() {
    //TODO better help message
    std::cout << "mpwd help" << std::endl;
}
