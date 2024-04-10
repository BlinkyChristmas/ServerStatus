cmake_minimum_required(VERSION 3.25)
project(ServerStatus VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(ServerStatus
    ./ServerStatus/main.cpp

    ./ServerStatus/ProcessData.cpp
    ./ServerStatus/ProcessData.hpp
    ./ServerStatus/FormatData.cpp
    ./ServerStatus/FormatData.hpp

    
    ./SeverStatus/ConnectionLog/ConnectionLog.cpp
    ./SeverStatus/ConnectionLog/ConnectionLog.hpp
    ./SeverStatus/ConnectionLog/ConnectionEntry.cpp
    ./SeverStatus/ConnectionLog/ConnectionEntry.hpp

    ./SeverStatus/ErrorLog/ErrorEntry.cpp
    ./SeverStatus/ErrorLog/ErrorEntry.hpp
    ./SeverStatus/ErrorLog/ErrorLog.cpp
    ./SeverStatus/ErrorLog/ErrorLog.hpp

    ./SeverStatus/ClientList/ClientList.cpp
    ./SeverStatus/ClientList/ClientList.hpp
    ./SeverStatus/ClientList/ClientName.cpp
    ./SeverStatus/ClientList/ClientName.hpp

    ./SeverStatus/ServerLog/ServerLog.cpp
    ./SeverStatus/ServerLog/ServerLog.hpp
    ./SeverStatus/ServerLog/ServerEntry.cpp
    ./SeverStatus/ServerLog/ServerEntry.hpp


    ./utility/BaseConfiguration.cpp
    ./utility/BaseConfiguration.hpp
    ./utility/buffer.cpp
    ./utility/buffer.hpp
    ./utility/dbgutil.hpp
    ./utility/mapfile.cpp
    ./utility/mapfile.hpp
    ./utility/strutil.hpp
    ./utility/timeutil.cpp
    ./utility/timeutil.hpp
    

)

if (WIN32)
    target_compile_definitions(ServerStatus PRIVATE
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG=1>
        __WINDOWS_DS__
        _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
        _WIN32_WINNT=0x0A00
    )

    target_compile_options(ServerStatus PRIVATE
        $<$<CONFIG:Release>:/O2>
    )

else()
    target_compile_definitions(ServerStatus PRIVATE
        $<$<CONFIG:Debug>:DEBUG=1>
    )

    target_compile_options(ServerStatus PRIVATE
        $<$<CONFIG:Release>:-O2>
        -Wno-deprecated-declarations
    )
    if (APPLE)

    else ()

    endif (APPLE)
    
endif (WIN32)

target_include_directories(ServerStatus
    PUBLIC
        ${PROJECT_SOURCE_DIR}/
)


