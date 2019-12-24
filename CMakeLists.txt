cmake_minimum_required(VERSION 3.1)

project(IO_read_file)
project(IO_formatted_io)

set (CMAKE_C_STANDARD 11)

# IO
add_executable(
    IO_read_file
    src/io/read_file_to_string.c
)

add_executable(
    IO_formatted_io
    src/io/formatted_io.c
)