#ifndef COMMANDLINEARGS_HPP
#define COMMANDLINEARGS_HPP

#include <string>

class CommandLineArgs {
    private:
        std::string dir;
        std::string dbfilename;
    public:
        CommandLineArgs(/* args */);
        ~CommandLineArgs();

        void setDir(std::string dir);
        std::string getDir();

        void setDbFilename(std::string dbfilename);
        std::string getDbFilename();
};



#endif