cmake_minimum_required(VERSION 3.14)
project(feup_aed2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
        src/FlightPath.cpp
        include/FlightPath.h
        src/utils.cpp
        include/utils.h
)

add_subdirectory(docs)
add_subdirectory(test)

enable_testing()

add_executable(tests test/tests.cpp
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
        src/FlightPath.cpp
        include/FlightPath.h
        src/utils.cpp
        include/utils.h
)
target_link_libraries(
        tests
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
