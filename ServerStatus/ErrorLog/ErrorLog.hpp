// Copyright © 2024 Charles Kerr. All rights reserved.

#ifndef ErrorLog_hpp
#define ErrorLog_hpp

#include <iostream>
#include <deque>
#include <string>
#include <unordered_map>
#include <vector>


#include "utility/BaseConfiguration.hpp"
#include "ErrorEntry.hpp"

class ErrorLog : public BaseConfiguration {
    std::unordered_map<std::string, std::deque<ErrorEntry>> errors ;
    
    auto processKeyValue(const std::string &key, const std::string &value) ->void final ;
    auto beginLoad() -> void final ;

public:
    ErrorLog();
    ErrorLog(const std::filesystem::path &path) ;
    auto load(const std::filesystem::path &path) -> bool ;
    auto allErrors() const -> const std::unordered_map<std::string, std::deque<ErrorEntry>>& ;
    auto allErrors() -> std::unordered_map<std::string, std::deque<ErrorEntry>>& ;
    auto size() const -> size_t ;
    auto empty() const -> bool ;
    auto operator[](const std::string &clientname) const -> const std::deque<ErrorEntry>& ;
    auto allClients() -> std::vector<std::string> ;
};

#endif /* ErrorLog_hpp */
