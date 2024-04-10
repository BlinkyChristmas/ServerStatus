// Copyright © 2024 Charles Kerr. All rights reserved.

#ifndef ClientName_hpp
#define ClientName_hpp

#include <iostream>
#include <string>

struct ClientName {
    std::string name ;
    bool has_audio ;
    ClientName() ;
    ClientName(const std::string &entry) ;
};

#endif /* ClientName_hpp */
