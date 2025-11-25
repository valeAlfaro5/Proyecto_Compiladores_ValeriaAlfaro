cmake_minimum_required(VERSION 3.16)
project(Proyecto_Compiladores_ValeriaAlfaro VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Proyecto_Compiladores_ValeriaAlfaro
    main.cpp
    Lexer.cpp
    Lexer.h
    Parser.h
    Parser.cpp
)