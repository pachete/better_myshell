//
// Created by pch on 27/05/18.
//

#include "ForkExec.h"


ForkExec::ForkExec() : Command("/") {
    bin = cwd;
    bin += "/bin";
}

void ForkExec::findWildcard(std::vector<std::string> &args, std::string criteria) {

    boost::filesystem::path wdir = criteria;
    wdir = wdir.parent_path();

    if (wdir.empty()) { wdir = cwd; }
    boost::filesystem::directory_iterator end_itr;
    for (boost::filesystem::directory_iterator itr(wdir); itr != end_itr; ++itr) {

        if (MatchTextWithWildcards(itr->path().filename().string(), criteria, true)) {
            args.push_back(itr->path().string());
        }
    }

}

bool ForkExec::isWildcard(const std::string &str) {
    char wildcards[] = {'*', '?', '[', ']', '/', '$'};
    for (char wildcard : wildcards) {
        if (str.find(wildcard) != std::string::npos) {
            return true;
        }
    }
    return false;
}

void ForkExec::execute(std::vector<std::string> vargs) {

    std::string cmd = vargs[0];
    std::vector<std::string> args;
    args.emplace_back(vargs[0].c_str());

    for (int j = 1; j < vargs.size(); ++j) {
        if (isWildcard(vargs[j])) {
            findWildcard(args, vargs[j]);
        } else {
            args.emplace_back(vargs[j].c_str());
        }
    }

    std::vector<const char *> char_args;
    for (const auto &x : args) {
        char_args.push_back(x.c_str());
    }

    char_args.emplace_back(nullptr);

    pid_t pid = fork();

    if (pid == -1) {
        std::cerr << "Failed to fork()" << std::endl;
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    } else {

        for (const auto &var : env_vars) {
            unsetenv(var.c_str());
        }

        execvp(cmd.c_str(), const_cast<char *const *>(char_args.data()));

        perror("Error");
        std::cerr << "Failed to execute " << cmd << std::endl;

        exit(EXIT_FAILURE);

    }
}

bool ForkExec::MatchTextWithWildcards(const std::string &text, std::string wildcardPattern, bool caseSensitive) {
    EscapeRegex(wildcardPattern);
    boost::replace_all(wildcardPattern, "\\?", ".");
    boost::replace_all(wildcardPattern, "\\*", ".*");
    boost::regex pattern(wildcardPattern, caseSensitive ? boost::regex::normal : boost::regex::icase);
    return regex_match(text, pattern);
}

void ForkExec::EscapeRegex(std::string &regex) {
    boost::replace_all(regex, "\\", "\\\\");
    boost::replace_all(regex, "^", "\\^");
    boost::replace_all(regex, ".", "\\.");
    boost::replace_all(regex, "$", "\\$");
    boost::replace_all(regex, "|", "\\|");
    boost::replace_all(regex, "(", "\\(");
    boost::replace_all(regex, ")", "\\)");
    boost::replace_all(regex, "[", "\\[");
    boost::replace_all(regex, "]", "\\]");
    boost::replace_all(regex, "*", "\\*");
    boost::replace_all(regex, "+", "\\+");
    boost::replace_all(regex, "?", "\\?");
    boost::replace_all(regex, "/", "\\/");
}

void ForkExec::setEnv_vars(const std::set<std::string> &env_vars) {
    ForkExec::env_vars = env_vars;
}

const std::set<std::string> &ForkExec::getEnv_vars() const {
    return env_vars;
}

void ForkExec::help() {}

bool ForkExec::compare(const std::string &input) {}
