#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>


// argc -> argument count
// argv -> argument vector ( command line arguments )
int main(int argc, char **argv) {
	// Flush after every std::cout / std::cerr
	// i.e useful for debugging, flush the ouput without buffering for real time logging
	std::cout << std::unitbuf;
	std::cerr << std::unitbuf;
}
