cmake_minimum_required(VERSION 3.28)
project(HeiMa_last)

set(CMAKE_CXX_STANDARD 17)

add_executable(HeiMa_last main.cpp
        identity.h
        student.h
        student.cpp
        teacher.h
        teacher.cpp
        manager.h
        manager.cpp
        globalFile.h
        computerRoom.h
        orderFile.h
        orderFile.cpp
)
