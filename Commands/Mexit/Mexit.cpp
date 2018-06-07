//
// Created by pch on 27/05/18.
//

#include "Mexit.h"


Mexit::Mexit() : Command("mexit") {}

void Mexit::execute(std::vector<std::string> args) {
    args.erase(args.begin());
    int exit_code = 0;

    for (const auto &arg : args) {
        if (arg == "--help" || arg == "-h") {
            help();
            return;
        } else {
            exit_code = std::stoi(arg);
        }
    }

    std::cout << "Exiting with code " << exit_code << std::endl;
    exit(exit_code);
}

void Mexit::help() {
    std::cout << "mexit help" << std::endl;
}
