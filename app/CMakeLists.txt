project(HuffmanCodingApp)

set(COMPILE_FLAGS "${COMPILE_FLAGS} -Wall -Wextra -Werror -m64")
set(LINK_FLAGS    "-static")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}" )
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${LINK_FLAGS}" )

set(SOURCE_FILES main.cpp)
add_executable(HuffmanCoding ${SOURCE_FILES})
target_link_libraries(HuffmanCoding Huffman)