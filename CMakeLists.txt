Project(mai)
cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 14)

set ( CMAKE_PREFIX_PATH /usr/lib/x86_64-linux-gnu/cmake/ )

# BOOST PACKAGE
set(Boost_USE_MULTITHREADED      ON) # Default ON
set(Boost_USE_STATIC_LIBS        ON) # Default OFF
set(Boost_USE_DEBUG_RUNTIME     OFF) # Default ON
set(Boost_USE_DEBUG_PYTHON      OFF) # Default OFF
set(Boost_USE_STLPORT           OFF) # Default OFF
find_package(Boost REQUIRED COMPONENTS
        atomic
        chrono
        date_time
        exception
        filesystem
        program_options
        random
        regex
        system
        serialization
        thread
        )
IF (!Boost_FOUND)
    MESSAGE("*** ERROR *** Boost package not found")
    RETURN()
ENDIF ()

find_package(cpprestsdk REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
# MESSAGE("Boost_INCLUDE_DIRS:\t" ${Boost_INCLUDE_DIRS})

# Open SSL Package
# set(OpenSSL_INCLUDE /usr/local/opt/openssl/include)
# set(OpenSSL_LIBRARIES
#     /usr/local/opt/openssl/lib/libcrypto.dylib
#     /usr/local/opt/openssl/lib/libssl.dylib)
# include_directories(${OpenSSL_INCLUDE})

# Microsoft RESTful API Package (Casablanca)
# set(CppREST_INCLUDE /usr/local/opt/cpprestsdk/include)
# set(CppREST_LIBRARIES /usr/local/opt/cpprestsdk/lib/libcpprest.dylib)
# include_directories(${cpprestsdk_INCLUDE})

# Compile and link
# Build the core library and executable
set(SOURCE_FILES main.cpp WeaterServer.cpp WeaterServer.h WeaterServerForecast.cpp WeaterServerForecast.h)
# set(LINK_LIBRARIES
#     ${Boost_LIBRARIES}
#     ${OpenSSL_LIBRARIES}
#     ${cpprestsdk_LIBRARIES}
#     )
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} cpprestsdk::cpprest Boost::system)