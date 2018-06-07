//
// Created by pch on 27/05/18.
//

#ifndef MYSHELL_MPWD_H
#define MYSHELL_MPWD_H

#include "../Command.h"


class Mpwd : public Command {

public:

    Mpwd();

    void execute(std::vector<std::string> args) override;

    void help() override;
};


#endif //MYSHELL_MPWD_H
