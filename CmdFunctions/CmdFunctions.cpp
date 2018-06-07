//
// Created by pch on 27/05/18.
//

#include "CmdFunctions.h"

CmdFunctions::CmdFunctions() {
    std::set<std::string> env_vars = {};
}

std::vector<Command *> CmdFunctions::createCommands() {
    auto *mcd = new Mcd();
    auto *mpwd = new Mpwd();
    auto *mexit = new Mexit();
    auto *merrno = new Merrno();
    auto *mecho = new Mecho();
    auto *msource = new Msource();

    std::vector<Command *> commands = {mcd, mpwd, mexit, merrno, mecho, msource};

    return commands;
}

std::vector<std::string> CmdFunctions::get_args(std::string input) {
    std::vector<std::string> args;

    char quote = '\'';
    char double_quote = '\"';

    if (input.length() == 0) {
        return args;
    }

    bool in_double_quotes = false;
    bool in_quotes = false;

    unsigned long input_length = input.length();
    unsigned long arg_length = 0;
    for (unsigned long i = 0; i < input_length; i++) {
        unsigned long start = i;
        if (input[i] == double_quote) {
            in_double_quotes = true;
        } else if (input[i] == quote) in_quotes = true;

        if (in_quotes) {
            i++;
            start++;

            while (i < input_length && input[i] != quote) i++;

            if (i < input_length) {
                in_quotes = false;
            }

            arg_length = i - start;
            i++;
        } else if (in_double_quotes) {
            i++;
            start++;

            while (i < input_length && input[i] != double_quote) i++;

            if (i < input_length) {
                in_double_quotes = false;
            }

            arg_length = i - start;
            i++;
        } else {
            while (i < input_length && input[i] != ' ') i++;
            arg_length = i - start;
        }
        args.push_back(input.substr(start, arg_length));
    }


    return args;
}

void CmdFunctions::runCmd(std::string &input, std::vector<Command *> &commands, ForkExec &fork_exec) {
    std::vector<std::string> args = get_args(input);
    if (args.empty()) {
        return;
    }

    std::string command = args[0];

    for (auto cmd : commands) {
        if (cmd->compare(command)) {
            cmd->execute(args);
            args.clear();
            return;
        }
        if (mexport_full.compare(command)) {
            mexport_full.setEnv_vars(env_vars);
            mexport_full.execute(args);
            env_vars = mexport_full.getEnv_vars();
            return;
        }
    }

    if (mexport.compare(command)) {
        mexport.setEnv_vars(env_vars);
        mexport.execute(args);
        env_vars = mexport.getEnv_vars();
        return;
    }

    fork_exec.setEnv_vars(env_vars);
    fork_exec.execute(args);

}

std::string CmdFunctions::removeComments(std::string line) {
    bool in_quotes = false;
    bool in_double_quotes = false;

    char quotes = '\'';
    char double_quotes = '\"';
    char sharp = '#';

    unsigned long position = 0;

    for (char ch : line) {
        position++;
        if (ch == quotes) {
            in_quotes = !in_quotes;
        }
        if (ch == double_quotes) {
            in_double_quotes = !in_double_quotes;
        }

        if (in_quotes || in_double_quotes) {
            continue;
        } else {
            if (ch == sharp) {
                return line.substr(0, position - 1);
            }
        }
    }
    return line;
}

void CmdFunctions::setPath() {
    Command::cwd = boost::filesystem::current_path().c_str();

    std::string tmp = getenv("PATH");
    tmp += ":";
    tmp += Command::cwd;
    tmp += "/bin";

    setenv("PATH", tmp.c_str(), 1);
}

void CmdFunctions::handleScript(std::string script) {
    if (!boost::ends_with(script, ".msh")) {
        std::cout << "File should have extension .msh" << std::endl;
        exit(2);
    }

    setPath();

    ForkExec fork_exec = ForkExec();

    std::vector<Command *> commands = createCommands();

    std::ifstream file(script);
    std::string line;

    while (file && getline(file, line)) {

        if (line.length() == 0) continue;

        if (boost::starts_with(line, "#")) continue;

        if (line.find('#') != std::string::npos) {
            line = removeComments(line);
        }

        runCmd(line, commands, fork_exec);
    }
}
