// Copyright © 2024 Charles Kerr. All rights reserved.

#include "ProcessData.hpp"

#include <string>
#include <deque>
#include <fstream>
#include "ConnectionLog/ConnectionLog.hpp"
#include "ErrorLog/ErrorLog.hpp"
#include "ClientList/ClientList.hpp"
#include "ServerLog/ServerLog.hpp"

#include "utility/strutil.hpp"


using namespace std::string_literals ;

const std::string ClientEntry::clientError = "#FF8888";
const std::string ClientEntry::neverConnected = "#FFFF99";

auto ClientEntry::describe() const -> std::string{
    auto entry= " "s;
    if (hasBeenSeen()){
        entry = (isConnected?"Connected   "s:"Disconnected"s) + " "s + time ;
    }
    return name + " - "s + entry + (hasError?"Error"s:"    "s) + " "s + ip ;
}

// =================================================================================================================
auto processData(const ClientList &clientList,  const ConnectionLog &connectionLog, const ErrorLog &errorLog) -> std::deque<ClientEntry> {
    
    std::deque<ClientEntry> clientValues ;
    for (const auto &entry:clientList.allClients()){
        auto connect = connectionLog[entry.name] ;
        if (connect.empty()) {
            // this client has never been connected,
            clientValues.emplace_back(entry.name);
        }
        else {
            clientValues.push_back(processClientEntry(entry.name, connect, errorLog[entry.name]));
        }
    }
    return clientValues ;
}

auto processClientEntry(const std::string &name, const std::deque<ConnectionEntry> &connections, const std::deque<ErrorEntry> &errors) -> ClientEntry {
    ClientEntry entry(name) ;
    if (connections.empty()) {
        return entry ;
    }
    
    // There is a connection , lets get it
    auto last = *connections.rbegin() ;
    entry.time = last.timeValue() ;
    entry.ip = last.ip ;
    entry.isConnected = last.isConnected ;
    if (!errors.empty()){
        // Lets see if the last error was after this connection
        auto lasterror = *errors.rbegin() ;
        if (lasterror.timestamp >= last.timestamp){
            entry.hasError = true ;
        }
    }
    return entry ;
}


