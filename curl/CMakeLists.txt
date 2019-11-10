cmake_minimum_required (VERSION 3.0.2)
project (vmod C)
include(../varnish.cmake vmod)

add_vmod(vmod_curl vmod_curl.vcc "curl module for Varnish"
	vmod_curl.c
)

# VCL import name is "curl"
vmod_add_tests(vmod_curl curl
	tests/01-test.vtc
)
