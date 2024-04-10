// 
#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <string>
#include <filesystem>
#include <thread>

#include "utility/strutil.hpp"

#include "ProcessData.hpp"
#include "FormatData.hpp"

#include "ConnectionLog/ConnectionLog.hpp"
#include "ErrorLog/ErrorLog.hpp"
#include "ClientList/ClientList.hpp"
#include "ServerLog/ServerLog.hpp"


using namespace std::string_literals ;

// This takes four inputs, and one output

int main(int argc, const char * argv[]) {
    auto exitcode = EXIT_SUCCESS ;
    try {
        if (argc < 6){
            throw std::runtime_error("Insufficent parameters. Format: clientlist serverlog connectionlog errorlog outputfile");
        }
        auto clientlist_path = std::filesystem::path(argv[1]) ;
        auto serverlog_path = std::filesystem::path(argv[2]) ;
        auto connectionlog_path = std::filesystem::path(argv[3]) ;
        auto errorlog_path = std::filesystem::path(argv[4]) ;
        auto output_path = std::filesystem::path(argv[5]) ;
        
        ServerLog serverLog ;
        ClientList clientList ;
        ErrorLog errorLog ;
        ConnectionLog connectionLog ;
        serverLog.load(serverlog_path) ;
        clientList.load(clientlist_path) ;
        connectionLog.load(connectionlog_path);
        errorLog.load(errorlog_path) ;
        auto clients = processData(clientList, connectionLog, errorLog);
        
        formatData(output_path, serverLog.lastState(), clients) ;
        auto loop = true ;
        while (loop) {
            auto one = clientList.refresh() ;
            auto two = serverLog.refresh()  ;
            auto three = connectionLog.refresh();
            auto four = errorLog.refresh();
            if (one || two || three || four) {
                auto clients = processData(clientList, connectionLog, errorLog);
                
                formatData(output_path, serverLog.lastState(), clients) ;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        
    }
    catch(const std::exception &e) {
        std::cerr << e.what()<< std::endl;
        exitcode = EXIT_FAILURE ;
    }
    catch(...) {
        std::cerr << "Unknown error!" << std::endl;
        exitcode = EXIT_FAILURE;
    }
    return exitcode;
}


