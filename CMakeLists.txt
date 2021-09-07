# set minimum cmake version required
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(xeus-asm LANGUAGES CXX 
    VERSION 0.0.1
    DESCRIPTION "Jupyter Kernel for ASM"
    HOMEPAGE_URL "https://github.com/itssingh/xeus-asm")

include_directories(include/xasm)
