project(Common)

set(common_source_files Vector.h)

add_library(Common ${common_source_files})
set_target_properties(Common PROPERTIES LINKER_LANGUAGE CXX)