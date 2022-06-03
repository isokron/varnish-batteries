cmake_minimum_required (VERSION 3.0.2)
project (vmod C)
include(../../varnish.cmake vmod)

add_vmod(vmod_vsthrottle vmod_vsthrottle.vcc "vsthrottle module for Varnish"
	vmod_vsthrottle.c
)

# VCL import name is "vsthrottle"
vmod_add_tests(vmod_vsthrottle vsthrottle
	tests/test01.vtc
	tests/test02.vtc
	tests/test03.vtc
	tests/test04.vtc
)
