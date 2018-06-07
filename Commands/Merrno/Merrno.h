//
// Created by pch on 27/05/18.
//

#ifndef MYSHELL_MERRNO_H
#define MYSHELL_MERRNO_H

#include "../Command.h"


class Merrno : public Command {

public:

    Merrno();

    void execute(std::vector<std::string> args) override;

    void help() override;
};


#endif //MYSHELL_MERRNO_H
