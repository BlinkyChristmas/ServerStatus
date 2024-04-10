// Copyright © 2024 Charles Kerr. All rights reserved.

#ifndef ConnectionLog_hpp
#define ConnectionLog_hpp

#include <iostream>
#include <deque>
#include <string>
#include <unordered_map>
#include <vector>

#include "utility/BaseConfiguration.hpp"
#include "ConnectionEntry.hpp"

class ConnectionLog : public BaseConfiguration {
    std::unordered_map<std::string, std::deque<ConnectionEntry>> connections ;
    
    auto processKeyValue(const std::string &key, const std::string &value) ->void final ;
    auto beginLoad() -> void final ;

public:
    ConnectionLog();
    ConnectionLog(const std::filesystem::path &path) ;
    auto allConnections() const -> const std::unordered_map<std::string, std::deque<ConnectionEntry>>& ;
    auto allConnections() -> std::unordered_map<std::string, std::deque<ConnectionEntry>>& ;
    auto load(const std::filesystem::path &path) -> bool ;
    auto size() const -> size_t ;
    auto empty() const -> bool ;
    auto operator[](const std::string &clientname) const -> const std::deque<ConnectionEntry>& ;
    auto allClients() -> std::vector<std::string> ;
};

#endif /* ConnectionLog_hpp */
