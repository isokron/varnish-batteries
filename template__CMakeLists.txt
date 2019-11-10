cmake_minimum_required (VERSION 3.0.2)
project (vmod C)
include(../varnish.cmake vmod)

add_vmod(vmod_foo vmod_foo.vcc "foo module for Varnish"
	vmod_foo.c
)

# VCL import name is "foo"
vmod_add_tests(vmod_foo foo
	tests/01-test.vtc
)
