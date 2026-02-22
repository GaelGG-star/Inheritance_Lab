cmake_minimum_required(VERSION 4.0)
project(Inheritance_Lab)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Inheritance_Lab
        BankAccount.cpp
        BankAccount.h
        main.cpp)
