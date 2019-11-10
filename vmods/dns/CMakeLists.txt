cmake_minimum_required (VERSION 3.0.2)
project (vmod C)
include(../../varnish.cmake vmod)

set(CMAKE_C_FLAGS, "${CMAKE_C_FLAGS} -D_GNU_SOURCE")


add_vmod(vmod_dns vmod_dns.vcc "dns module for Varnish"
	vmod_dns.c
)

# VCL import name is "dns"
vmod_add_tests(vmod_dns dns
	tests/01-test.vtc
)
