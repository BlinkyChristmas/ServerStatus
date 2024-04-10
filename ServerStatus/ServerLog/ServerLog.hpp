// Copyright © 2024 Charles Kerr. All rights reserved.

#ifndef ServerLog_hpp
#define ServerLog_hpp

#include <iostream>
#include <deque>
#include <string>

#include "utility/BaseConfiguration.hpp"
#include "ServerEntry.hpp"

class ServerLog : public BaseConfiguration {
    std::deque<ServerEntry> states ;
    
    auto processKeyValue(const std::string &key, const std::string &value) ->void final ;
    auto beginLoad() -> void final ;
    
public:
    ServerLog();
    ServerLog(const std::filesystem::path &path) ;
    auto load(const std::filesystem::path &path) -> bool ;
    auto allStates() const -> const std::deque<ServerEntry>& ;
    auto allStates() -> std::deque<ServerEntry>& ;
    auto size() const -> size_t ;
    auto empty() const -> bool ;
    auto lastState() const -> ServerEntry ;
};

#endif /* ServerLog_hpp */
