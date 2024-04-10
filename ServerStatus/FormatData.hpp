// Copyright © 2024 Charles Kerr. All rights reserved.

#ifndef FormatData_hpp
#define FormatData_hpp

#include <string>
#include <deque>
#include <filesystem>
#include "ProcessData.hpp"
struct ServerEntry ;
auto formatData(const std::filesystem::path &path,const ServerEntry &serverState, const std::deque<ClientEntry> &clients) -> void ;


#endif /* FormatData_hpp */
