//
// Created by pch on 27/05/18.
//

#include "Command.h"


std::string Command::cwd = "";
int Command::my_error = 0;

bool Command::compare(const std::string &input) {
    return input == cmd;
}
