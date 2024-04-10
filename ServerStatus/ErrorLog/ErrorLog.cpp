// Copyright © 2024 Charles Kerr. All rights reserved.

#include "ErrorLog.hpp"
#include <stdexcept>
#include <algorithm>

#include "utility/strutil.hpp"

using namespace std::string_literals ;


// ========================================================
auto ErrorLog::processKeyValue(const std::string &key, const std::string &value) ->void {
    auto iter = errors.find(key) ;
    if (iter == errors.end()) {
        // the entry doesn't exist, we get to add one
        auto queue = std::deque<ErrorEntry>();
        queue.emplace_back(value);
        errors.insert_or_assign(key,queue);
    }
    else {
        iter->second.emplace_back(value);
    }
}

// ===========================================================
auto ErrorLog::beginLoad() -> void {
    errors  = std::unordered_map<std::string, std::deque<ErrorEntry>>() ;
}

// ========================================================
ErrorLog::ErrorLog():BaseConfiguration(){
    
}

// ========================================================
ErrorLog::ErrorLog(const std::filesystem::path &path) :ErrorLog() {
    if (!load(path)){
        throw std::runtime_error("Error processing: "s + path.string());
    }
}

// ========================================================
auto ErrorLog::load(const std::filesystem::path &path) -> bool {
    if (!BaseConfiguration::load(path)){
        return false ;
    }
    for (auto &[name,queue]:errors){
        std::sort(queue.begin(),queue.end());
    }
    return true ;
}

// ========================================================
auto ErrorLog::allErrors() const -> const std::unordered_map<std::string, std::deque<ErrorEntry>>& {
    return errors ;
}

// ========================================================
auto ErrorLog::allErrors() -> std::unordered_map<std::string, std::deque<ErrorEntry>>& {
    return errors ;
}

// ========================================================
auto ErrorLog::size() const -> size_t {
    return errors.size() ;
}

// ========================================================
auto ErrorLog::empty() const -> bool {
    return errors.empty();
}

// ========================================================
auto ErrorLog::operator[](const std::string &clientname) const -> const std::deque<ErrorEntry>& {
    static const std::deque<ErrorEntry> notfound ;
    auto iter = errors.find(clientname) ;
    if (iter == errors.end()){
        return notfound;
    }
    return iter->second ;
}

// ========================================================
auto ErrorLog::allClients() -> std::vector<std::string> {
    auto clients = std::vector<std::string>() ;
    for (const auto &[name,data]:errors) {
        clients.push_back(name) ;
    }
    return clients ;
}
