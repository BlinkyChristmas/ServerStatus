// Copyright © 2024 Charles Kerr. All rights reserved.

#include "ConnectionEntry.hpp"

#include "utility/strutil.hpp"

using namespace std::string_literals ;

static const std::string clientError = "#FF8888"s;
static const std::string neverConnected = "#FFFF99"s;

// ================================================================================================
ConnectionEntry::ConnectionEntry():isConnected(false) {
    
}

// ================================================================================================
ConnectionEntry::ConnectionEntry(const std::string &value):ConnectionEntry(){
    auto values = util::parse(value,",");
    if (values.size() <3) {
        throw std::runtime_error("Invalid string value for ConnectionEntry: "s + value );
    }
    timestamp = util::stringToSysTime(values[0]);
    isConnected = values[1] == "Connected"  ;
    ip = values[2];
}

// ================================================================================================
auto ConnectionEntry::operator<(const ConnectionEntry &value) const -> bool {
    return this->timestamp < value.timestamp ;
}

// ================================================================================================
auto ConnectionEntry::timeValue() const -> std::string {
    const auto formattime = "%a - %b %d %H:%M:%S"s;
    return util::sysTimeToString(timestamp,formattime) ;
}
