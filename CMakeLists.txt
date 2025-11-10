cmake_minimum_required(VERSION 3.10)
project(parallel_encryptor_os)

set(CMAKE_CXX_STANDARD 17)

add_executable(main
    main.cpp
    encryptor.cpp
    job_thread.cpp
)
