//
// Created by pch on 07/06/18.
//

#ifndef MYSHELL_MEXPORT_H
#define MYSHELL_MEXPORT_H

#include <set>
#include "../Command.h"

class Mexport : public Command {
private:
    std::set<std::string> env_vars;

public:
    Mexport();

    bool compare(std::string &input);

    void execute(std::vector<std::string> args) override;

    void help() override;

    const std::set<std::string> &getEnv_vars() const;

    void setEnv_vars(const std::set<std::string> &env_vars);
};


#endif //MYSHELL_MEXPORT_H
