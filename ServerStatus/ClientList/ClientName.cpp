// Copyright © 2024 Charles Kerr. All rights reserved.

#include "ClientName.hpp"
#include "utility/strutil.hpp"

// ===================================================================================
ClientName::ClientName():has_audio(false){
    
}

// ===================================================================================
ClientName::ClientName(const std::string &entry) :ClientName() {
    auto [one,two] = util::split(entry,",") ;
    this->name= one ;
    if (!two.empty()){
        try {
            has_audio = std::stoi(entry,nullptr,0) != 0;
        }
        catch(...) {}
    }
}
