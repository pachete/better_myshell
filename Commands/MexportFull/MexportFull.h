//
// Created by pch on 07/06/18.
//

#ifndef MYSHELL_MEXPORTFULL_H
#define MYSHELL_MEXPORTFULL_H

#include <set>
#include "../Command.h"

class MexportFull : public Command {
private:
    std::set<std::string> env_vars;

public:
    MexportFull();

    void execute(std::vector<std::string> args) override;

    void help() override;

    const std::set<std::string> &getEnv_vars() const;

    void setEnv_vars(const std::set<std::string> &env_vars);
};


#endif //MYSHELL_MEXPORTFULL_H
