// Copyright © 2024 Charles Kerr. All rights reserved.

#ifndef ConnectionEntry_hpp
#define ConnectionEntry_hpp

#include <iostream>
#include <string>
#include "utility/timeutil.hpp"

struct ConnectionEntry {
 
    util::ourclock::time_point timestamp ;
    bool isConnected ;
    std::string ip ;
    ConnectionEntry();
    ConnectionEntry(const std::string &value);
    auto operator<(const ConnectionEntry &value) const -> bool ;
    auto timeValue() const -> std::string ;
};

#endif /* ConnectionEntry_hpp */
