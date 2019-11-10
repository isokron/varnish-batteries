cmake_minimum_required (VERSION 3.0.2)
project (vmod C)
include(../varnish.cmake vmod)

add_vmod(vmod_hashids vmod_hashids.vcc "hashids module for Varnish"
	vmod_hashids.c
	vmod_hashids.h
	hashids.c
	hashids.h
)

# VCL import name is "hashids"
vmod_add_tests(vmod_hashids hashids
	tests/01-test.vtc
)
