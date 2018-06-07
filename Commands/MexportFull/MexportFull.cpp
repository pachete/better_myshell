//
// Created by pch on 07/06/18.
//

#include "MexportFull.h"

MexportFull::MexportFull() : Command("mexport") {}

void MexportFull::execute(std::vector<std::string> args) {
    args.erase(args.begin());

    std::string var;
    std::string var_val;
    unsigned long position;

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
            position = arg.find('=');
            if (position != std::string::npos) {
                var = arg.substr(0, position);
                var_val = arg.substr(position + 1);
            } else {
                var = arg;
                var_val = getenv(var.c_str());
            }
            if (env_vars.find(var) != env_vars.end()) {
                env_vars.erase(var);
            }
            setenv(var.c_str(), var_val.c_str(), 1);
        }
    }
}

void MexportFull::help() {
    std::cout << "mexport help" << std::endl;
}

const std::set<std::string> &MexportFull::getEnv_vars() const {
    return env_vars;
}

void MexportFull::setEnv_vars(const std::set<std::string> &env_vars) {
    MexportFull::env_vars = env_vars;
}
