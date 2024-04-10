// Copyright © 2024 Charles Kerr. All rights reserved.

#ifndef ErrorEntry_hpp
#define ErrorEntry_hpp

#include <iostream>
#include <string>

#include "utility/timeutil.hpp"

struct ErrorEntry {
    util::ourclock::time_point timestamp ;
    std::string type ;
    std::string filename ;
    
    ErrorEntry();
    ErrorEntry(const std::string &value) ;
    auto operator<(const ErrorEntry& value) const -> bool ;
};

#endif /* ErrorEntry_hpp */
