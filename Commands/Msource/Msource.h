//
// Created by pch on 27/05/18.
//

#ifndef MYSHELL_MSOURCE_H
#define MYSHELL_MSOURCE_H

#include "../Command.h"
#include "../../CmdFunctions/CmdFunctions.h"


class Msource : public Command {

public:
    Msource();

    void execute(std::vector<std::string> args) override;

    void help() override;
};


#endif //MYSHELL_MSOURCE_H
