#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
// #include <winsock2.h>
// #include <ws2tcpip.h>
#include <thread>
#include <unordered_map>

// custom header files
#include <CommandParser.hpp>
#include <KeyValueDataStructure.hpp>

/**
 * @param client_fd -> client file descriptor
 */
// this will be called for every new client connection
void handle_client_connection(int client_fd, KeyValueDataStructure* keyValueDataStructure) {
	std::string pong_msg = "+PONG\r\n";
	// continuously listen for incoming requests by this client
	while(true) {
		char buf[1024];
		// 0 -> indicates no special flags are used to read this data
		// rec -> no of bytes received 0 or less indicates closed connection.
		int rec = recv(client_fd, &buf, sizeof(buf), 0);
		if(rec <= 0) {
			close(client_fd);
			break;
		}
		CommandParser* commandParser = new CommandParser();
		std::vector<std::string> command_arr = commandParser->parse_redis_request_command(buf);

		// PING command
		if(command_arr[0] == "PING") {
			std::cout<< "pong" << std::endl;
			//c_str -> C style string i.e, null terminated string
			write(client_fd, pong_msg.c_str(), pong_msg.size());
		// ECHO command
		} 
		else if(command_arr[0] == "ECHO") {
			std::cout<< "echo" << std::endl;
			std::string echo_resp_msg = commandParser->generate_redis_response(command_arr[1]);
			std::cout<<"echo msg"<<echo_resp_msg<<std::endl;
			write(client_fd, echo_resp_msg.c_str(), echo_resp_msg.size());
		}
		else if(command_arr[0] == "SET") {
			std::string key = command_arr[1];
			std::string value = command_arr[2];
			std::cout<< "SET command" << std::endl;
			std::string setResponse = keyValueDataStructure->setKeyValue(client_fd, key, value);
			if(setResponse == "SUCCESS") {
				setResponse = "+OK\r\n";
				write(client_fd, setResponse.c_str(), setResponse.size());
			}
			

		} else if(command_arr[0] == "GET") {
			std::string getResponse = "";
			std::string key = command_arr[1];
			std::string value = keyValueDataStructure->getKeyValue(client_fd, key);
			if(value == "") {
				getResponse = "$-1\r\n";
			} else {
				getResponse = commandParser->generate_echo_response(value);
			}
			write(client_fd, getResponse.c_str(), getResponse.size());
		}
		
	}
}

// argc -> argument count
// argv -> argument vector ( command line arguments )
int main(int argc, char **argv) {
	// Flush after every std::cout / std::cerr
	// i.e useful for debugging, flush the ouput without buffering for real time logging
	// KB_1.0
	std::cout << std::unitbuf;
	std::cerr << std::unitbuf;

	// You can use print statements as follows for debugging, they'll be visible when running tests.
	std::cout << "Logs from your program will appear here!\n";

	// KB_1.1, KB_1.2
	// this line creates a TCP(SOCK_STREAM) socket using IPv4(AF_INET)
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0) {
		std::cerr << "Failed to create server socket\n";
		return 1;
	}

	int reuse = 1;
	// KB_1.3
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
		std::cerr << "setsockopt failed\n";
		return 1;
	}

	// KB_1.4
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(6379);

	// bind the socket to port 6379 ( default TCP socket port )
	if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {
		std::cerr << "Failed to bind to port 6379\n";
		return 1;
	}

		// max length of pending connections
		int connection_backlog = 5;
		if (listen(server_fd, connection_backlog) != 0) {
			std::cerr << "listen failed\n";
			return 1;
		}
		
		struct sockaddr_in client_addr;
		int client_addr_len = sizeof(client_addr);
		
		std::cout << "Waiting for a client to connect...\n";

		while(true){
			// accept new client request
			int client_fd = accept(server_fd, (struct sockaddr *) &client_addr, (socklen_t *) &client_addr_len);
			if(client_fd >= 0 ) {
				std::cout << "Client connected\n";
			}
		KeyValueDataStructure* keyValueDataStructure = new KeyValueDataStructure();
		std::thread nw(handle_client_connection, client_fd, keyValueDataStructure);
		nw.detach();
	}
	close(server_fd);

	return 0;
}
