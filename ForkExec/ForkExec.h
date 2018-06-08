//
// Created by pch on 27/05/18.
//

#ifndef MYSHELL_FORKEXEC_H
#define MYSHELL_FORKEXEC_H

#include <glob.h>
#include <unistd.h>
#include <queue>
#include <map>
#include <vector>
#include <algorithm>
#include <sys/wait.h>
#include <sys/types.h>

#include <boost/algorithm/string/replace.hpp>
#include <boost/regex.hpp>

#include "../Commands/Command.h"
#include "../CmdFunctions/CmdFunctions.h"


class ForkExec : public Command {

public:
    std::map<std::string, std::string> exec_flags;

    const std::map<std::string, std::string> &getExec_flags() const;

    void setExec_flags(const std::map<std::string, std::string> &exec_flags);

    std::string bin;

    ForkExec();

    bool compare(const std::string &input) override;

    void pipeAll(std::string &input);

    void executeAndRedirect(std::string input, std::string redirect);

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
