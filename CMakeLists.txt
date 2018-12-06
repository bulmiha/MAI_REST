Project(mai)
cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH /usr/lib/x86_64-linux-gnu/cmake/ )

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-O3")

find_package(cpprestsdk REQUIRED)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp WeaterServer.cpp WeaterServer.h WeaterServerForecast.cpp WeaterServerForecast.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} cpprestsdk::cpprest ${Boost_LIBRARIES} -lboost_system)
