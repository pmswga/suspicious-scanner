cmake_minimum_required(VERSION 3.5)

project(suspicious-scanner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    suspicious-scanner
    main.cpp
    logger.h
    scanner.h
    validator.h
    validator_rule.h
    logger_entry.h
    validator_code.h
    )
