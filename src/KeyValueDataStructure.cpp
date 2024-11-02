#include <KeyValueDataStructure.hpp>
#include <iostream>
#include <unordered_map>
#include <string>
#include <exception>
#include <chrono>

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

std::string KeyValueDataStructure::setKeyValue(int client_fd, const std::string& key, const std::string& value, const std::string& exp_command, const std::string& exp_time) {
    if (!key.empty()) {
        keyValueDataStructure[client_fd][key] = value;
        if(exp_command != "") {
            int exp_time_int = std::stoi(exp_time);
            long long current_time = getCurrentTimeMilli();
            clientKeyExpiryTime[client_fd][key] = std::make_pair(current_time, exp_time_int);
        }
        return "SUCCESS";
    }
    return "ERROR";
}

std::string KeyValueDataStructure::getKeyValue(int client_fd, const std::string& key) {

    if (keyValueDataStructure.find(client_fd) != keyValueDataStructure.end() && 
        keyValueDataStructure[client_fd].find(key) != keyValueDataStructure[client_fd].end()) {
            // check for expiry if any
            if(clientKeyExpiryTime.find(client_fd) != clientKeyExpiryTime.end() && 
                clientKeyExpiryTime[client_fd].find(key) != clientKeyExpiryTime[client_fd].end()) {
                    int exp_time_int = clientKeyExpiryTime[client_fd][key].second;
                    long long set_time = clientKeyExpiryTime[client_fd][key].first;
                    long long time_elapsed = getCurrentTimeMilli() - set_time;
                    std::cout << time_elapsed << std::endl;
                    if(time_elapsed > exp_time_int) {
                        return "";
                    } else{
                        return keyValueDataStructure[client_fd][key];
                    }
                }
            return keyValueDataStructure[client_fd][key];
    }
    return "";
}

long long KeyValueDataStructure::getCurrentTimeMilli() {
    // Get the current time point
    auto now = std::chrono::system_clock::now();
    // Convert to milliseconds since epoch
    long long epoch = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

    return epoch;
}

KeyValueDataStructure::~KeyValueDataStructure() {
    // No need for manual deletion; unordered_map handles memory automatically
}
