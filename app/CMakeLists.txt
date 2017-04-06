project(HuffmanCodingApp)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(COMPILE_FLAGS "${COMPILE_FLAGS} -O3")
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(COMPILE_FLAGS "${COMPILE_FLAGS} -Og")
endif ()

set(COMPILE_FLAGS "${COMPILE_FLAGS} -g -Wall -Wextra -Werror -m64")
set(LINK_FLAGS    "-static")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}" )
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${LINK_FLAGS}" )

set(SOURCE_FILES main.cpp)
add_executable(HuffmanCoding ${SOURCE_FILES})
target_link_libraries(HuffmanCoding Huffman)