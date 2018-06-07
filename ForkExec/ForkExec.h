//
// Created by pch on 27/05/18.
//

#ifndef MYSHELL_FORKEXEC_H
#define MYSHELL_FORKEXEC_H

#include <glob.h>
#include <unistd.h>
#include <boost/algorithm/string/replace.hpp>
#include <boost/regex.hpp>
#include <sys/wait.h>
#include <sys/types.h>
#include "../Commands/Command.h"


class ForkExec : public Command {

public:
    std::string bin;

    ForkExec();

    bool compare(const std::string &input) override;

    void execute(std::vector<std::string> input) override;

    void help() override;

    const std::set<std::string> &getEnv_vars() const;

    void setEnv_vars(const std::set<std::string> &env_vars);

private:
    std::set<std::string> env_vars;

    bool MatchTextWithWildcards(const std::string &text, std::string wildcardPattern, bool caseSensitive /*= true*/);

    void EscapeRegex(std::string &regex);

    void findWildcard(std::vector<std::string> &args, std::string criterea);

    bool isWildcard(const std::string &str);

};


#endif //MYSHELL_FORKEXEC_H
