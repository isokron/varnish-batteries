cmake_minimum_required (VERSION 3.0.2)
project (all_vmods C)

#set(VARNISH_VMOD_LIBRARY_MODE TRUE)
add_subdirectory(vmods/cookie)
add_subdirectory(vmods/curl)
add_subdirectory(vmods/digest)
add_subdirectory(vmods/dns)
add_subdirectory(vmods/header)
add_subdirectory(vmods/str)
add_subdirectory(vmods/var)
add_subdirectory(vmods/xcounter)
add_subdirectory(vmods/vsthrottle)
#add_subdirectory(vmods/encoding)
#add_subdirectory(foo)

enable_testing()
