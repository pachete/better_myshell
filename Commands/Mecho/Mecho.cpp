//
// Created by pch on 27/05/18.
//

#include "Mecho.h"


Mecho::Mecho() : Command("mecho") {}

void Mecho::execute(std::vector<std::string> args) {
    args.erase(args.begin());

    std::string var_name;
    std::string out_str;
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
            if(boost::starts_with(arg, "$")) {
                var_name = (std::string) arg.substr(1);
                if (getenv(var_name.c_str())){
                    out_str = getenv( var_name.c_str() );
                } else {
                    out_str = "";
                }
            } else {
                out_str = arg;
            }
            std::cout << out_str << ' ';
        }
    }
    std::cout << std::endl;
}

void Mecho::help() {
    std::cout << "mecho help" << std::endl;
}
