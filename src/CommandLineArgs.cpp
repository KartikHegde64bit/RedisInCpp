#include <CommandLineArgs.hpp>
#include <string>




CommandLineArgs::CommandLineArgs(/* args */){
}

void CommandLineArgs::setDir(std::string dir) {
    this->dir = dir;
}

std::string CommandLineArgs::getDir() {
    return this->dir;
}

void CommandLineArgs::setDbFilename(std::string dbfilename) {
    this->dbfilename = dbfilename;
}

std::string CommandLineArgs::getDbFilename() {
    return this->dbfilename;
}

CommandLineArgs::~CommandLineArgs(){
}

