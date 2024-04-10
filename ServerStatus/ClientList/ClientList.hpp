// Copyright © 2024 Charles Kerr. All rights reserved.

#ifndef ClientList_hpp
#define ClientList_hpp

#include <iostream>
#include <vector>
#include <string>

#include "utility/BaseConfiguration.hpp"
#include "ClientName.hpp"

class ClientList : public BaseConfiguration {
    std::vector<ClientName> clients ;
    
    auto processKeyValue(const std::string &key, const std::string &value) ->void final ;
    auto beginLoad() -> void final ;

public:
    ClientList();
    ClientList(const std::filesystem::path &path) ;
    
    auto allClients() const -> const std::vector<ClientName>& ;
    auto allClients() -> std::vector<ClientName>& ;
    auto size() const -> size_t ;
    auto empty() const -> bool ;
};
#endif /* ClientList_hpp */
