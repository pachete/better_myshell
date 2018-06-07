//
// Created by pch on 27/05/18.
//

#ifndef MYSHELL_MECHO_H
#define MYSHELL_MECHO_H

#include "../Command.h"


class Mecho : public Command {
public:
    Mecho();

    void execute(std::vector<std::string> args) override;

    void help() override;
};


#endif //MYSHELL_MECHO_H
