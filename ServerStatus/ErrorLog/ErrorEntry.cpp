// Copyright © 2024 Charles Kerr. All rights reserved.

#include "ErrorEntry.hpp"

#include "utility/strutil.hpp"
#include <stdexcept>

using namespace std::string_literals ;
// ==================================================================================
ErrorEntry::ErrorEntry(){
    
}

// ==================================================================================
ErrorEntry::ErrorEntry(const std::string &value):ErrorEntry(){
    auto values = util::parse(value,",") ;
    if (values.size() < 2  ) {
        throw std::runtime_error("Invalid values for ErrorEntry: "s + value);
    }
    timestamp = util::stringToSysTime(values[0]) ;
    type = values[1] ;
    if (values.size() > 2){
        filename = values[2] ;
    }
}

// ==================================================================================
auto ErrorEntry::operator<(const ErrorEntry& value) const -> bool{
    return this->timestamp < value.timestamp ;
}
