cmake_minimum_required (VERSION 3.0.2)
project (all_vmods C)

#set(VARNISH_VMOD_LIBRARY_MODE TRUE)
add_subdirectory(curl)
add_subdirectory(dns)
add_subdirectory(encoding)
#add_subdirectory(foo)

enable_testing()
