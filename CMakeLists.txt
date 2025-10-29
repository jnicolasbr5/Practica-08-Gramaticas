cmake_minimum_required(VERSION 3.10)

project(Gramaticas)

include_directories(include)

file(GLOB SOURCES "src/*.cc")

add_executable(Grammar2CNF ${SOURCES})