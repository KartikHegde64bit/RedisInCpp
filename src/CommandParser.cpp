#include <iostream>
#include <vector>
#include <string>
#include <format>


#include <CommandParser.hpp>
#include <CommandLineArgs.hpp>

CommandParser::CommandParser() {
    // Constructor implementation
}

CommandParser::~CommandParser() {
    // Destructor implementation
}
// Additional function definitions as needed




/**
 * @param buf
 * @returns command_arr
 */
std::vector<std::string> CommandParser::parse_redis_request_command(const std::string& buf) {
	// create string of received char array buffer
	std::string rec_msg(buf);

    std::vector<std::string> command_arr;

	// case of array i.e command
	if(rec_msg[0] == '*') {
		int arr_len = 0;
        int msg_ind = 1; // excluding the asterik

        while(rec_msg.substr(msg_ind, 2) != "\r\n") {   // move the index till you encounter first "\r\n"
            msg_ind += 1;
        }
        // since the fist argument after asterik is going to be the length of command array
        std::string comm_arr_len_strng = rec_msg.substr(1, msg_ind);
        int command_arr_len = std::stoi(comm_arr_len_strng);

        // vector to store the command words
        command_arr.reserve(command_arr_len);

        bool isLenStrng = false;
        int prev = msg_ind;

        while(msg_ind < rec_msg.size()) {
            if(rec_msg.substr(msg_ind, 2) == "\r\n") {
                // reached the end of a word in command, so append to array
                if(!isLenStrng) {
                    std::string current_word = rec_msg.substr(prev, msg_ind - prev);
                    if(current_word != "") {
                        command_arr.push_back(rec_msg.substr(prev, msg_ind - prev));
                    }
                }
                isLenStrng = !isLenStrng;
                msg_ind += 1;
                prev  = msg_ind + 1;
            }
            msg_ind++;
        }
	}
    return command_arr;
}

std::string CommandParser::generate_redis_response(const std::string &res_msg){
    return std::format("${}\r\n{}\r\n", res_msg.size(), res_msg);
}

std::string CommandParser::generate_config_response(std::string argument, CommandLineArgs* commandLineArgs) {
    std::string response = "*2\r\n";
    std::string dir = commandLineArgs->getDir();
    int dir_size = dir.size();
    std::string dbfilename = commandLineArgs->getDbFilename();
    int dbfilename_size = dbfilename.size();
    response += "$" + std::to_string(argument.size()) + "\r\n" + argument + "\r\n";
    if(argument == "dir") {
        response += "$" + std::to_string(dir_size) + "\r\n" + commandLineArgs->getDir() + "\r\n";
    } else if(argument == "dbfilename") {
        response += "$" + std::to_string(dbfilename_size) + "\r\n" + commandLineArgs->getDbFilename() + "\r\n";
    }
    std::cout << "config response: " << response << std::endl;
    return response;

}