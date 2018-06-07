//
// Created by pch on 27/05/18.
//

#ifndef MYSHELL_MCD_H
#define MYSHELL_MCD_H

#include "../Command.h"

class Mcd : public Command {

private:
    std::string home;

public:

    Mcd();

    void execute(std::vector<std::string> input) override;

    void help() override;
};


#endif //MYSHELL_MCD_H
