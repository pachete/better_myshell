//
// Created by pch on 27/05/18.
//

#include "Merrno.h"


Merrno::Merrno() : Command("merrno") {}

void Merrno::execute(std::vector<std::string> args) {
    args.erase(args.begin());

    for (const auto &arg : args) {
        if (arg == "-h" || arg == "--help") {
            help();
            return;
        } else {
            my_error = 22;
            std::cerr << "myshell: merrno: " << arg << ": invalid option" << std::endl;
            return;
        }
    }

    std::cout << my_error << std::endl;
}

void Merrno::help() {
    std::cout << "merrno: merrno [-h|--help]" << std::endl;
    std::cout << "  Return exit code of previously run program or 0 if no programs ." << std::endl;
    std::cout << "  Options:" << std::endl;
    std::cout << "      -h|--help - returns help" << std::endl;
    // std::cout << "  Exit status:" << std::endl;
    // std::cout << "  Set errno to 0 unless invalid option is given. " << std::endl;
}
