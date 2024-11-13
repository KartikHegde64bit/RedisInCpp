#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<KeyValueDataStructure.hpp>

class RdbFileReader{
    public:
        RdbFileReader();
        ~RdbFileReader();
        
        std::string generateRdbFileStream();

    private:
        std::string magicString;
        std::unordered_map<std::string, std::string>> metaDataMap;
        int keyValueTableSize;
        int keyExpireTableSize;

        // the below data structure covers both key - value store and key-expiry store
        KeyValueDataStructure::KeyValueDataStructure keyValueDataStructure;

};