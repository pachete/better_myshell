//
// Created by pch on 27/05/18.
//

#ifndef MYSHELL_CMDFUNCTIONS_H
#define MYSHELL_CMDFUNCTIONS_H

#include <iostream>
#include <cstdlib>
#include "../ForkExec/ForkExec.h"
#include "../Commands/Command.h"
#include "../Commands/Merrno/Merrno.h"
#include "../Commands/Mpwd/Mpwd.h"
#include "../Commands/Mcd/Mcd.h"
#include "../Commands/Mexit/Mexit.h"
#include "../Commands/Msource/Msource.h"
#include "../Commands/Mecho/Mecho.h"
#include "../Commands/Mexport/Mexport.h"
#include "../Commands/MexportFull/MexportFull.h"

class CmdFunctions {

private:
    std::string removeComments(std::string line);

public:
    CmdFunctions();

    Mexport mexport;

    MexportFull mexport_full;

    std::set<std::string> env_vars;

    std::vector<Command *> createCommands();

    void runCmd(std::string &input, std::vector<Command *> &commands, ForkExec &fork_exec);

    void setPath();

    void handleScript(std::string script);

    std::vector<std::string> get_args(std::string input);
};


#endif //MYSHELL_CMDFUNCTIONS_H
