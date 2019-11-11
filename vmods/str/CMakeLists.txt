cmake_minimum_required (VERSION 3.0.2)
project (vmod C)
include(../../varnish.cmake vmod)

add_vmod(vmod_str vmod_str.vcc "str module for Varnish"
	vmod_str.c
)

# VCL import name is "str"
vmod_add_tests(vmod_str str
	tests/test01.vtc
	tests/test02.vtc
	tests/test05.vtc
	tests/test08.vtc
	tests/test06.vtc
	tests/test03.vtc
	tests/test04.vtc
)
