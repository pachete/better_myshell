//
// Created by pch on 27/05/18.
//

#ifndef MYSHELL_COMMAND_H
#define MYSHELL_COMMAND_H

#include <iostream>
#include <utility>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>


class Command {

public:
    explicit Command(std::string cmd_in) : cmd(std::move(cmd_in)) {};

    std::string cmd;

    static std::string cwd;
    static int my_error;

    virtual bool compare(const std::string &input); // TODO remove virtual

    virtual void execute(std::vector<std::string> input) = 0;

    virtual void help() = 0;

};


#endif //MYSHELL_COMMAND_H
