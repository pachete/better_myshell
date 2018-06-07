cmake_minimum_required(VERSION 3.5.1)
project(myshell)

find_package(Boost COMPONENTS program_options filesystem regex REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

add_executable(myshell main.cpp
        CmdFunctions/CmdFunctions.cpp CmdFunctions/CmdFunctions.h
        ForkExec/ForkExec.cpp ForkExec/ForkExec.h
        Commands/Command.cpp Commands/Command.h
        Commands/Merrno/Merrno.cpp Commands/Merrno/Merrno.h
        Commands/Mpwd/Mpwd.cpp Commands/Mpwd/Mpwd.h
        Commands/Mcd/Mcd.cpp Commands/Mcd/Mcd.h
        Commands/Mexit/Mexit.cpp Commands/Mexit/Mexit.h
        Commands/Msource/Msource.cpp Commands/Msource/Msource.h
        Commands/Mecho/Mecho.cpp Commands/Mecho/Mecho.h
        Commands/Mexport/Mexport.cpp Commands/Mexport/Mexport.h
        Commands/MexportFull/MexportFull.cpp Commands/MexportFull/MexportFull.h)

target_link_libraries(myshell ${Boost_LIBRARIES} ${Boost_FILESYSTEM_LIBRARY} readline)