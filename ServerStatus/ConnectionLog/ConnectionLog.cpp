// Copyright © 2024 Charles Kerr. All rights reserved.

#include "ConnectionLog.hpp"
#include <stdexcept>
#include <algorithm>

#include "utility/strutil.hpp"

using namespace std::string_literals ;


// ========================================================
auto ConnectionLog::processKeyValue(const std::string &key, const std::string &value) ->void {
    auto iter = connections.find(key) ;
    if (iter == connections.end()) {
        // the entry doesn't exist, we get to add one
        auto queue = std::deque<ConnectionEntry>();
        queue.emplace_back(value);
        connections.insert_or_assign(key,queue);
    }
    else {
        iter->second.emplace_back(value);
    }
}

// ===========================================================
auto ConnectionLog::beginLoad() -> void {
    connections  = std::unordered_map<std::string, std::deque<ConnectionEntry>>() ;
}

// ========================================================
ConnectionLog::ConnectionLog():BaseConfiguration(){
    
}

// ========================================================
ConnectionLog::ConnectionLog(const std::filesystem::path &path) :ConnectionLog() {
    if (!load(path)){
        throw std::runtime_error("Error processing: "s + path.string());
    }
}

// ========================================================
auto ConnectionLog::load(const std::filesystem::path &path) -> bool {
    if (!BaseConfiguration::load(path)){
        return false ;
    }
    for (auto &[name,queue]:connections){
        std::sort(queue.begin(),queue.end());
    }
    return true ;
}

// ========================================================
auto ConnectionLog::allConnections() const -> const std::unordered_map<std::string, std::deque<ConnectionEntry>>& {
    return connections ;
}

// ========================================================
auto ConnectionLog::allConnections() -> std::unordered_map<std::string, std::deque<ConnectionEntry>>& {
    return connections ;
}

// ========================================================
auto ConnectionLog::size() const -> size_t {
    return connections.size() ;
}

// ========================================================
auto ConnectionLog::empty() const -> bool {
    return connections.empty();
}

// ========================================================
auto ConnectionLog::operator[](const std::string &clientname) const -> const std::deque<ConnectionEntry>& {
    static const std::deque<ConnectionEntry> notfound ;
    auto iter = connections.find(clientname) ;
    if (iter == connections.end()){
        return notfound;
    }
    return iter->second ;
}

// ========================================================
auto ConnectionLog::allClients() -> std::vector<std::string> {
    auto clients = std::vector<std::string>() ;
    for (const auto &[name,data]:connections) {
        clients.push_back(name) ;
    }
    return clients ;
}
