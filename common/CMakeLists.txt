project(Common)

set(common_source_files Vector.h BitStack.cpp BitStack.h)

add_library(Common ${common_source_files})
target_include_directories(Common PUBLIC ../common)
set_target_properties(Common PROPERTIES LINKER_LANGUAGE CXX)