#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <thread>

/**
 * @param client_fd -> client file descriptor
 */
void connection_handler(int client_fd){
	std:string msg = "+PONG\r\n";
	// continuously listen for incoming requests by this client.
	while(true) {
		// assuming client data fits within this buffer
		char buf[1024];
		// 0 -> indicates no special flags are used to read this data
		// rec -> no of bytes received 0 or less indicates closed connection.
		int rec = recv(client_fd, &buf, sizeof(buf), 0);
		if(rec <= 0) {
			close(client_fd);
			break;
		}
		//c_str -> C style string i.e, null terminated string
		write(client_fd, msg.c_str(), msg.size());
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

	// KB_1.1 
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

	while(true) {
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
			std::thread nw(connection_handler, client_fd);
			nw.detach();
		}
	}
	
}
