cmake_minimum_required (VERSION 3.0.2)
project (all_vmods C)

#set(VARNISH_VMOD_LIBRARY_MODE TRUE)
add_subdirectory(vmods/curl)
add_subdirectory(vmods/digest)
add_subdirectory(vmods/dns)
#add_subdirectory(vmods/encoding)
#add_subdirectory(foo)

enable_testing()
