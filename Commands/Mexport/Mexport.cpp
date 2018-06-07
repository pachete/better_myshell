//
// Created by pch on 07/06/18.
//

#include "Mexport.h"

Mexport::Mexport() : Command("=") {}

bool Mexport::compare(std::string &input) {
    return input.find(Command::cmd) != std::string::npos;
}

void Mexport::execute(std::vector<std::string> args) {
    for (auto &arg : args) {
        if (!compare(arg)) {
            Command::my_error = 2;
            return;
        }
    }

    std::string var;
    std::string var_val;
    unsigned long position;

    for (const auto &arg : args) {
        position = arg.find('=');
        var = arg.substr(0, position);
        var_val = arg.substr(position + 1);
        env_vars.insert(var);
        setenv(var.c_str(), var_val.c_str(), 1);
    }
}

void Mexport::help() {}

const std::set<std::string> &Mexport::getEnv_vars() const {
    return env_vars;
}

void Mexport::setEnv_vars(const std::set<std::string> &env_vars) {
    Mexport::env_vars = env_vars;
}
