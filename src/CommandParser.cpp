#include "CommandParser.hpp"
#include <iostream>

CommandParser::CommandParser() {
    // Constructor implementation
}

CommandParser::~CommandParser() {
    // Destructor implementation
}
// Additional function definitions as needed




/**
 * @param buf
 */
std::string CommandParser::handleCommand(char[] buf) {
	// create string of received char array buffer
	std::string rec_msg(buf);

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
	}
}