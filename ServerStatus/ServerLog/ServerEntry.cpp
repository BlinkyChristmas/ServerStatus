// Copyright © 2024 Charles Kerr. All rights reserved.

#include "ServerEntry.hpp"

#include "utility/strutil.hpp"
#include "utility/dbgutil.hpp"
using namespace std::string_literals ;

const std::string ServerEntry::disconnectedColor = "#D0D0D0"s;
const std::string ServerEntry::serverIdle = "#99CCFF"s;
const std::string ServerEntry::serverShow = "#99FF99"s;
const std::string ServerEntry::neverConnected = "#FFFF99"s;

// ================================================================================
ServerEntry::ServerEntry():isRunning(false),isActive(false),isListening(false),inShow(false){
    
}

// ================================================================================
ServerEntry::ServerEntry(const std::string &value) : ServerEntry() {
    
    auto [time,states] = util::split(value,",") ;
    timestamp = util::stringToSysTime(time) ;
    
    
    auto values = util::parse(states,",") ;
    for (const auto &entry:values){
        auto [name,condition] = util::split(entry,"-") ;
        //DBGMSG(std::cout, "Name is: "s + name + " Value: "s + condition);
        auto rvalue = false ;
        
        if (util::upper(condition) == "ON"){
            rvalue = true ;
        }
        auto uname = util::upper(name) ;
        if (uname == "RUN"){
            isRunning = rvalue ;
        }
        else if (uname == "LISTENING"){
            isListening = rvalue ;
        }
        else if (uname == "ACTIVE"){
            isActive = rvalue ;
        }
        else if (uname == "SHOW"){
            inShow = rvalue ;
        }
    }
    
}
auto ServerEntry::color() const -> const std::string& {
    if (!isRunning){
        return neverConnected ;
    }
    if (inShow) {
        return serverShow;
    }
    if (isActive){
        return serverIdle ;
    }
    if (isListening){
        return serverIdle ;
    }
    return disconnectedColor;

}
// ============================================================================
auto ServerEntry::describe() const -> std::string {
    if (!isRunning) {
        return "Stopped" ;
    }
    if (inShow) {
        return "ShowTime";
    }
    if (isActive){
        return "Pending" ;
    }
    if (isListening){
        return "Idle" ;
    }
    return "Inactive";
}

// ============================================================================
auto ServerEntry::operator<(const ServerEntry& value) const -> bool {
    return this->timestamp < value.timestamp ;
}
// ============================================================================
auto ServerEntry::fullState() const -> std::string {
    const std::string format = "%s - %s , %s - %s, %s - %s , %s - %s "s ;
    
    auto msg = util::format(format,"Running",(isRunning?"On":"Off"),"Listening",(isListening?"On":"Off"), "Active",(isActive?"On":"Off") ,"Show",(inShow?"On":"Off")  );
    return msg ;
}
