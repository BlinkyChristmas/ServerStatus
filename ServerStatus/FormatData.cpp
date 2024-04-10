// Copyright © 2024 Charles Kerr. All rights reserved.

#include "FormatData.hpp"
#include <fstream>

#include "ServerLog/ServerEntry.hpp"

#include "utility/strutil.hpp"

using namespace std::string_literals ;

const std::string disconnectedColor = "#D0D0D0"s;
const std::string serverIdle = "#99CCFF"s;
const std::string serverShow = "#99FF99"s;
const std::string clientError = "#FF8888"s;
const std::string neverConnected = "#FFFF99"s;

std::string serverColor = neverConnected ;


auto formatData(const std::filesystem::path &path,const ServerEntry &serverState, const std::deque<ClientEntry> &clients) -> void {
    auto output = std::ofstream(path.string()) ;
    if (output.is_open()){
        output << "<!DOCTYPE html>\n";
        output << "<html>\n";
        output << "<head>\n";
        output << "     <meta http-equiv = \"refresh\" content = \"10\" >\n";
        output << "<style>\n";
        output << "table,th,td{border:2px solid black;border-collapse:collapse}\n";
        output << "</style>\n";
        output << "</head>\n";
        
        
        output << "\t<table style=\"font-family: Arial;font-size:16px;margin-left:40px;\">\n";
        output << "\t\t<thead>\n";
        output << "\t\t\t<tr>\n";
        output << "\t\t\t<th style = \"text-align:center;color:"<< serverState.color() <<";background-color:#303030;width:423px\" scope=\"col\">" << util::sysTimeToString(util::ourclock::now()) << "</th>\n";
        output << "\t\t\t</tr>\n";
        output << "\t\t\t<tr>\n";
        output << "\t\t\t<th style = \"text-align:center;color:#FFFFFF;background-color:#303030;width:423px\" scope=\"col\">Server Status</th>\n";
        output << "\t\t\t</tr>\n";
        output << "\t\t\t<tr>\n";
        output << "\t<table style=\"font-family: Arial;font-size:14px;margin-left:40px;\">\n";
        output << "\t\t\t<td style = \"text-align:center;color:#000000;background-color:"<< serverState.color() <<";width:423px\" scope=\"col\">" << serverState.describe() << "</td>\n";
        output << "\t\t\t</tr>\n";
        output << "\t</table>\n";

        output << "\t<table style=\"font-family: Arial;font-size:16px;margin-left:40px;\">\n";
        output << "\t\t<thead>\n";
        output << "\t\t\t<tr>\n";
        output << "\t\t\t<th style = \"text-align:center;color:#FFFFFF;background-color:#303030;width:423px\" scope=\"col\">Client Status</th>\n";
        output << "\t\t\t</tr>\n";
        output << "\t</table>\n";


        output << "\t<table style=\"font-family: Arial;font-size:14px;margin-left:40px;\">\n";
        output << "\t\t\t<tr>\n";
        output << "\t\t\t<th style=\"text-align:center;background-color:#A0A0A0;width:190px\" scope=\"col\">Client/Status</th>\n";
        output << "\t\t\t<th style=\"text-align:center;background-color:#A0A0A0;width:185px\" scope=\"col\">Timestamp</th>\n";
        output << "\t\t\t<th style=\"text-align:center;background-color:#A0A0A0;width:40px\" scope=\"col\">Error</th>\n";
         output << "\t\t\t</tr>\n";
        output << "\t\t</thead>\n";
        output << "\t\t<tbody>\n";
        
        for (const auto &entry:clients){
            output << "\t\t\t<tr style=\"text-align:center;\">\n";
            auto connected_color = (entry.isConnected?serverState.color():ServerEntry::disconnectedColor) ;
            auto conn_color = (entry.hasBeenSeen()?connected_color:ClientEntry::neverConnected);
            output << "\t\t\t\t<td style=\"background-color:" << conn_color <<";\">" << entry.name << "</td>\n";
            output << "\t\t\t\t<td style=\"background-color:" << conn_color << ";\">" << entry.time << "</td>\n";
        }
        output << "\t\t</tbody>\n";
        output << "\t</table>\n";

    }
}

