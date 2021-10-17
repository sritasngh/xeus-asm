# set minimum cmake version required
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(xeus-asm LANGUAGES CXX 
    VERSION 0.0.1
    DESCRIPTION "Jupyter Kernel for ASM"
    HOMEPAGE_URL "https://github.com/itssingh/xeus-asm")

set(EXECUTABLE_NAME xasm)

# Configuration
# =============

include(GNUInstallDirs)
# We generate the kernel.json file, given the installation prefix and the executable name
configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/share/jupyter/kernels/xasm/kernel.json.in"
        "${CMAKE_CURRENT_SOURCE_DIR}/share/jupyter/kernels/xasm/kernel.json")

option(XEUS_STATIC_DEPENDENCIES "link statically with xeus dependencies" OFF)
if (XEUS_STATIC_DEPENDENCIES)
    set(xeus_target "xeus-static")
else ()
    set(xeus_target "xeus")
endif ()

# Dependencies
# ============

# Be sure to use recent versions
set(xeus_REQUIRED_VERSION 0.19.1)
set(cppzmq_REQUIRED_VERSION 4.3.0)

find_package(xeus ${xeus_REQUIRED_VERSION} REQUIRED)
find_package(cppzmq ${cppzmq_REQUIRED_VERSION} REQUIRED)
find_package(Threads)

# Flags
# =====

include(CheckCXXCompilerFlag)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    CHECK_CXX_COMPILER_FLAG("-std=c++17" HAS_CPP17_FLAG)
    if (HAS_CPP17_FLAG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
    else ()
        message(FATAL_ERROR "Unsupported compiler -- xeus requires C++17 support!")
    endif ()
endif ()

# Target and link
# ===============

# My kernel executable
add_executable(${EXECUTABLE_NAME} "")
target_sources(${EXECUTABLE_NAME} PRIVATE src/main.cc src/instruction.cc src/interpreter.cc src/utils.cc src/xasm_interpreter.cc)
target_include_directories(${EXECUTABLE_NAME}
        PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${xeus_target} Threads::Threads)
if (APPLE)
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES MACOSX_RPATH ON)
else ()
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES
            BUILD_WITH_INSTALL_RPATH 1
            SKIP_BUILD_RPATH FALSE)
endif ()

set_target_properties(${EXECUTABLE_NAME} PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

# Installation
# ============

# Install xasm
install(TARGETS ${EXECUTABLE_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# Configuration and data directories for jupyter and xasm
set(XJUPYTER_DATA_DIR "share/jupyter" CACHE STRING "Jupyter data directory")

# Install Jupyter kernelspecs
set(xasmSPEC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/share/jupyter/kernels)
install(DIRECTORY ${xasmSPEC_DIR}
        DESTINATION ${XJUPYTER_DATA_DIR}
        PATTERN "*.in" EXCLUDE)
