cmake_minimum_required(VERSION 3.4.1...3.17.2)

project(AltSign)

set (CMAKE_CXX_STANDARD 17)
set (CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mno-sse")
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

FILE(GLOB ALTSIGN_SOURCES *.cpp)

list(APPEND ALTSIGN_SOURCES
    minizip/ioapi.c
    minizip/zip.c
    minizip/unzip.c
    ldid/ldid.cpp
    ldid/lookup2.c
)

# Static library
add_library(AltSign
    ${ALTSIGN_SOURCES}
)

# Help finding Homebrew's OpenSSL on macOS
if (APPLE)
    # This is for apple silicon (M1)
    set(HOMEBREW_PREFIX "/opt/homebrew"
        CACHE PATH "Path to Homebrew installation")

    # This is for apple x86
    # set(HOMEBREW_PREFIX "/usr/local"
    #     CACHE PATH "Path to Homebrew installation")

    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${HOMEBREW_PREFIX}/opt/openssl/lib)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${HOMEBREW_PREFIX}/opt/openssl/include)


    # This OPENSSL_FOUND check is to help find a cmake manually configured OpenSSL
    if (NOT OPENSSL_FOUND)
        find_package(OpenSSL REQUIRED)
    endif()
    message(STATUS "OpenSSL: " ${OPENSSL_VERSION} ${OPENSSL_INCLUDE_PATH})

    add_definitions(${OPENSSL_DEFINITIONS})
    target_include_directories(AltSign PUBLIC
            ${HOMEBREW_PREFIX}/include
            ${OPENSSL_INCLUDE_DIR}
            ../corecrypto/include/
            ../libplist/include
            minizip/
            )
endif()
