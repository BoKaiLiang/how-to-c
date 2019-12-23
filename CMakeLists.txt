cmake_minimum_required(VERSION 3.1)

project(IO_read_file)

set (CMAKE_C_STANDARD 11)

# IO
add_executable(
    IO_read_file
    src/io/read_file_to_string
)