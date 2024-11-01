#ifndef KEYVALUEDATASTRUCTURE_HPP
#define KEYVALUEDATASTRUCTURE_HPP

#include<string>
#include<unordered_map>
#include<vector>

class KeyValueDataStructure {
    public:
        KeyValueDataStructure();
        ~KeyValueDataStructure();
        std::string setKeyValue(int client_fd, const std::string& key, const std::string& value);
        std::string getKeyValue(int client_fd, const std::string& key);


    private:
        // unordered map<client_fd , unordered_map<<key, value >>>
        std::unordered_map<int, std::unordered_map<std::string, std::string>> keyValueDataStructure;
};


#endif