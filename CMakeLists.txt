cmake_minimum_required(VERSION 3.1)

project(IO_read_file)
project(IO_formatted_io)
project(OOP_struct_with_union)
project(DS_dyn_array_hold_static_array)

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

# OOP
add_executable(
    OOP_struct_with_union
    src/oop/struct_with_union.c
)

# DS
add_executable(
    DS_dyn_array_hold_static_array
    src/ds/dyn_array_hold_static_array.c
)