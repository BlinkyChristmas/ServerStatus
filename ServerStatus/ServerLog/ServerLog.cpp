// Copyright © 2024 Charles Kerr. All rights reserved.

#include "ServerLog.hpp"

#include "utility/strutil.hpp"
#include <algorithm>

using namespace std::string_literals ;

// ===========================================================
auto ServerLog::processKeyValue(const std::string &key, const std::string &value) ->void {
    auto ukey = util::upper(key);
    if (ukey == "STATE") {
        states.emplace_back(value) ;
    }
}

// ===========================================================
auto ServerLog::beginLoad() -> void {
    states = std::deque<ServerEntry>() ;
}

// ===========================================================
ServerLog::ServerLog(): BaseConfiguration(){
}
// ===========================================================
ServerLog::ServerLog(const std::filesystem::path &path):ServerLog() {
    if (!load(path)){
        throw std::runtime_error("Error processing: "s + path.string());
    }
}

// ===========================================================
auto ServerLog::load(const std::filesystem::path &path) -> bool {
    if (BaseConfiguration::load(path)) {
        std::sort(states.begin(),states.end());
        return true ;
    }
    return false ;
}

// ===========================================================
auto ServerLog::allStates() const -> const std::deque<ServerEntry>& {
    return states ;
}
// ===========================================================
auto ServerLog::allStates() -> std::deque<ServerEntry>& {
    return states ;
}
// ===========================================================
auto ServerLog::size() const -> size_t {
    return states.size() ;
}
// ===========================================================
auto ServerLog::empty() const -> bool {
    return states.empty() ;
}

// ===========================================================
auto ServerLog::lastState() const -> ServerEntry {
    ServerEntry noState ;
    
    if (states.empty()){
        return noState ;
    }
    return *states.rbegin();
}

