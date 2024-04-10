// Copyright © 2024 Charles Kerr. All rights reserved.

#ifndef ServerEntry_hpp
#define ServerEntry_hpp

#include <stdio.h>
#include <string>

#include "utility/timeutil.hpp"
struct ServerEntry {
    static const std::string disconnectedColor;
    static const std::string serverIdle;
    static const std::string serverShow;
    static const std::string neverConnected ;
    
    bool isRunning ;
    bool isListening ;
    bool isActive ;
    bool inShow ;
    util::ourclock::time_point timestamp ;
    
    ServerEntry() ;
    ServerEntry(const std::string &value) ;
    
    auto describe() const -> std::string ;
    auto fullState() const -> std::string ;
    auto operator<(const ServerEntry&) const -> bool ;
    auto color() const -> const std::string& ;
};

#endif /* ServerEntry_hpp */
