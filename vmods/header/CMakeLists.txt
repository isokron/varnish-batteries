cmake_minimum_required (VERSION 3.0.2)
project (vmod C)
include(../../varnish.cmake vmod)

add_vmod(vmod_header vmod_header.vcc "header module for Varnish"
	vmod_header.c
)

# VCL import name is "header"
vmod_add_tests(vmod_header header
	tests/01-test.vtc
)
