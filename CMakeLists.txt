cmake_minimum_required(VERSION 3.10)
project(feup_aed2)

set(CMAKE_CXX_STANDARD 11)

file(COPY dataset/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/dataset/)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(feup_aed2 main.cpp
        src/Airport.cpp
        include/Airport.h
        src/City.cpp
        include/City.h
        src/Country.cpp
        include/Country.h
        src/Airline.cpp
        include/Airline.h
        src/Dataset.cpp
        include/Dataset.h
        include/Graph.h
        src/Flight.cpp
        include/Flight.h
        src/Program.cpp
        include/Program.h
)

add_subdirectory(docs)
