// Copyright © 2024 Charles Kerr. All rights reserved.

#include "ClientList.hpp"
#include <stdexcept>
#include "utility/strutil.hpp"

using namespace std::string_literals ;

// ==============================================================================================================
auto ClientList::processKeyValue(const std::string &key, const std::string &value) ->void  {
    auto ukey = util::upper(key) ;
    if (ukey == "CLIENT") {
        clients.emplace_back(value) ;
    }
}
// ===========================================================
auto ClientList::beginLoad() -> void {
    clients = std::vector<ClientName>() ;
}

// ==============================================================================================================
ClientList::ClientList():BaseConfiguration(){
    
}
// ==============================================================================================================
ClientList::ClientList(const std::filesystem::path &path):ClientList(){
    if (!load(path)){
        throw std::runtime_error("Error processing: "s + path.string());
    }
}

// ==============================================================================================================
auto ClientList::allClients() const -> const std::vector<ClientName>& {
    return clients ;
}

// ==============================================================================================================
auto ClientList::allClients() -> std::vector<ClientName>& {
    return clients ;
}

// ==============================================================================================================
auto ClientList::size() const -> size_t {
    return clients.size() ;
}
// ==============================================================================================================
auto ClientList::empty() const -> bool {
    return clients.empty() ;
}
