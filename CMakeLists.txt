cmake_minimum_required(VERSION 3.10)
project(Proyecto1_Datos2)

set(CMAKE_CXX_STANDARD 14)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(Proyecto1_Datos2
       main.cpp
       Lista.hpp
       GarbageCollector.hpp
       VSPtr.hpp
       )


target_link_libraries(Proyecto1_Datos2 Threads::Threads)
include_directories(.)