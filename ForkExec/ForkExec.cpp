//
// Created by pch on 27/05/18.
//

#include <fcntl.h>
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

void recursivePipe(std::deque<std::string> commands_queue,
                   int std_in, int std_out, int std_err) {

    CmdFunctions cmd_functions;

    if (commands_queue.size() == 1) {
        dup2(std_out, 1);
        dup2(std_err, 2);

        cmd_functions.runCmd(commands_queue.front());

        dup2(std_in, 0);
        return;
    }

    int pipe_file_descriptor[2];
    pipe(pipe_file_descriptor);

    int in_pipe = pipe_file_descriptor[0];
    int out_pipe = pipe_file_descriptor[1];

    std::string command = commands_queue.front();
    boost::trim(command);
    commands_queue.pop_front();

    pid_t pid = fork();

    if (pid == -1) {
        dup2(std_err, 2);
        Command::my_error = 22;
        return;
    }
    if (pid > 0) {
        // batya process
        close(in_pipe);

        dup2(out_pipe, 1);
        dup2(out_pipe, 2);

        std::cout << "1:" << command << ":" << std::endl;

        command;
        cmd_functions.runCmd(command);

        close(1);
        close(2);

        close(out_pipe);

        int status;
        waitpid(pid, &status, 0);
    } else {
        // synok process
        close(out_pipe);

        dup2(in_pipe, 0);

        close(in_pipe);

        return recursivePipe(commands_queue, std_in, std_out, std_err);
    }

}

void ForkExec::pipeAll(std::string &input) {

    std::vector<std::string> commands_vector;
    boost::split(commands_vector, input, boost::is_any_of("|"));

    std::deque<std::string> commands_queue;
    std::copy(commands_vector.begin(), commands_vector.end(), std::back_inserter(commands_queue));

    int std_in = dup(0);
    int std_out = dup(1);
    int std_err = dup(2);

    recursivePipe(commands_queue, std_in, std_out, std_err);

    dup2(std_in, 0);
    dup2(std_out, 1);
    dup2(std_err, 2);
}

void ForkExec::executeAndRedirect(std::string input, std::string redirect) {

    boost::trim(input);
    boost::trim(redirect);
    std::vector<std::string> args;
    boost::split(args, input, boost::is_any_of(" "));

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

        if (boost::ends_with(redirect, "&")) {
            close(0);
            close(1);
            close(2);
        } else if (boost::ends_with(redirect, "2>&1")) {
            int fd = open(redirect.substr(2).c_str(),O_CREAT | O_WRONLY | O_TRUNC);
            dup2(fd, 1);
            dup2(fd, 2);
        } else if (boost::starts_with(redirect, ">")) {
            int fd = open(redirect.substr(2).c_str(), O_CREAT | O_WRONLY | O_TRUNC);
            dup2(fd, 0);
        } else if (boost::starts_with(redirect, "2<")) {
            int fd = open(redirect.substr(3).c_str(), O_CREAT | O_RDONLY);
            dup2(fd, 1);
        }

        execvp(cmd.c_str(), const_cast<char *const *>(char_args.data()));

        perror("Error");
        std::cerr << "Failed to execute " << cmd << std::endl;

        exit(EXIT_FAILURE);

    }
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

void ForkExec::setExec_flags(const std::map<std::string, std::string> &exec_flags) {
    ForkExec::exec_flags = exec_flags;
}

const std::map<std::string, std::string> &ForkExec::getExec_flags() const {
    return exec_flags;
}
