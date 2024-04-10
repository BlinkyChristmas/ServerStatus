// Copyright © 2024 Charles Kerr. All rights reserved.

#ifndef ProcessData_hpp
#define ProcessData_hpp

#include <filesystem>
#include <utility>
#include <deque>
#include <string>

#include "ErrorLog/ErrorEntry.hpp"
#include "ConnectionLog/ConnectionEntry.hpp"

struct ClientEntry {
    static const std::string clientError ;
    static const std::string neverConnected ;

    std::string name ;
    std::string time ;
    bool hasError ;
    bool isConnected ;
    std::string ip ;
    ClientEntry(const std::string &value = ""):name(value),hasError(false),isConnected(false){}
    auto hasBeenSeen() const -> bool { return !time.empty();}
    auto describe() const -> std::string ;
};

auto processClientEntry(const std::string &name, const std::deque<ConnectionEntry> &connections, const std::deque<ErrorEntry> &errors) -> ClientEntry ;

class ClientList ;
class ServerLog ;
class ConnectionLog ;
class ErrorLog ;

auto processData(const ClientList &clientList, const ConnectionLog &connectionLog, const ErrorLog &errorLog ) -> std::deque<ClientEntry> ;


#endif /* ProcessData_hpp */

