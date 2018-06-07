//
// Created by pch on 27/05/18.
//

#include "Mcd.h"


Mcd::Mcd() : Command("mcd") {
    home = cwd;
}

void Mcd::execute(std::vector <std::string> args) {
    std::string path;
    args.erase(args.begin());

    if (args.empty()) {
        path = home;
    }

    if (args.size() > 1) {
        my_error = 22;
        std::cerr << "myshell: mcd: too many arguments" << std::endl;
        return;
    } else {
        auto arg = args[0];
        if (boost::starts_with(arg, "-")) {
            if (arg == "--help" || arg == "-h") {
                help();
                return;
            } else {
                my_error = 22;
                std::cerr << "myshell: mcd: " << arg << ": invalid option" << std::endl;
                return;
            }
        } else {
            path = arg;
        }
    }

    if (path == "~") {
        path = home;
    }

    if (boost::filesystem::exists(path)) {
        if (boost::filesystem::is_directory(path)) {
            chdir(path.c_str());
            cwd = boost::filesystem::current_path().string();
            my_error = 0;
        } else {
            my_error = 20;
            std::cerr << "myshell: mcd: " << path << ": Not a directory" << std::endl;
            return;
        }
    } else {
        my_error = 2;
        std::cerr << "myshell: mcd: No such file or directory" << std::endl;
        return;
    }

}

void Mcd::help() {
    std::cout << "mcd help" << std::endl;
}
