# Info
cmake_minimum_required(VERSION 3.25)
project(C_Data_Structures_And_Algorithms C)

# Setup
enable_language(C)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Add Headers Files
include_directories(include) 

# Create List With Files To Test
set(FILES
        Structures/array/simple_array.c

        Structures/list/singly_list.c
        Structures/list/doubly_list.c
        Structures/list/circular_list.c
        Structures/list/doubly_circular_list.c
        Structures/list/unrolled_list.c

        Structures/stack/array_stack.c
        Structures/stack/list_stack.c

        Structures/queue/array_queue.c
        Structures/queue/circular_queue.c
        Structures/queue/list_queue.c
        Structures/queue/stack_queue.c
        Structures/queue/double_ended_queue.c

        Structures/tree/binary_tree.c


        Algorithms/conversion/infix_to_postfix.c
        Algorithms/conversion/infix_to_prefix.c
)

# Make Tests
enable_testing()

# Make Binaries And Tests
foreach(SOURCE_PATH IN LISTS FILES)
        get_filename_component(EXECUTABLE_NAME ${SOURCE_PATH} NAME_WE)
        add_executable(${EXECUTABLE_NAME} ${SOURCE_PATH})
        add_test(NAME ${EXECUTABLE_NAME} COMMAND ${EXECUTABLE_NAME})
endforeach()
