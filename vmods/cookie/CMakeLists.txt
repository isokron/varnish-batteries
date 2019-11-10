cmake_minimum_required (VERSION 3.0.2)
project (vmod C)
include(../../varnish.cmake vmod)

add_vmod(vmod_cookie vmod_cookie.vcc "cookie module for Varnish"
	vmod_cookie.c
)

# VCL import name is "cookie"
vmod_add_tests(vmod_cookie cookie
	tests/01-test.vtc
)
