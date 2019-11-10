cmake_minimum_required (VERSION 3.0.2)
project (vmod C)
include(../../varnish.cmake vmod)

add_vmod(vmod_xcounter vmod_xcounter.vcc "xcounter module for Varnish"
	vmod_xcounter.c
)

# VCL import name is "xcounter"
vmod_add_tests(vmod_xcounter xcounter
	tests/01-test.vtc
)
