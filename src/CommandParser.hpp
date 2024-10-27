#ifndef COMMANDPARSER_HPP
#define COMMANDPARSER_HPP

#include <string>
#include <vector>
class CommandParser {
public:
    CommandParser();           // Constructor
    ~CommandParser();          // Destructor

    std::vector<std::string> parse_redis_request_command(const std::string& buf);
    std::string generate_redis_response(const std::string &res_msg);
    // Other function declarations as needed

private:
    // Private helper functions and data members
};

#endif // COMMANDPARSER_HPP

