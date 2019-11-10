cmake_minimum_required (VERSION 3.0.2)
project (all_vmods C)

#set(VARNISH_VMOD_LIBRARY_MODE TRUE)
add_subdirectory(encoding)
#add_subdirectory(example)

enable_testing()
