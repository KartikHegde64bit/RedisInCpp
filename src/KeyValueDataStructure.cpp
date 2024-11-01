#include <KeyValueDataStructure.hpp>
#include <iostream>
#include <unordered_map>
#include <string>
#include <exception>

// class KeyValueDataStructure {
//     public:
//         KeyValueDataStructure();
//         std::string setKeyValue(int client_fd, const std::string& key, const std::string& value);
//         std::string getKeyValue(int client_fd, const std::string& key);
//         ~KeyValueDataStructure();

//     private:
//         std::unordered_map<int, std::unordered_map<std::string, std::string>> keyValueDataStructure;
// };

KeyValueDataStructure::KeyValueDataStructure() {}

std::string KeyValueDataStructure::setKeyValue(int client_fd, const std::string& key, const std::string& value) {
    if (!key.empty()) {
        keyValueDataStructure[client_fd][key] = value;
        return "SUCCESS";
    }
    return "ERROR";
}

std::string KeyValueDataStructure::getKeyValue(int client_fd, const std::string& key) {
    if (keyValueDataStructure.find(client_fd) != keyValueDataStructure.end() && 
        keyValueDataStructure[client_fd].find(key) != keyValueDataStructure[client_fd].end()) {
        return keyValueDataStructure[client_fd][key];
    }
    return "";
}

KeyValueDataStructure::~KeyValueDataStructure() {
    // No need for manual deletion; unordered_map handles memory automatically
}
