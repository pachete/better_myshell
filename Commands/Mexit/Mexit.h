//
// Created by pch on 27/05/18.
//

#ifndef MYSHELL_MEXIT_H
#define MYSHELL_MEXIT_H

#include "../Command.h"


class Mexit : public Command {

public:

    Mexit();

    void execute(std::vector<std::string> args) override;

    void help() override;

};


#endif //MYSHELL_MEXIT_H
