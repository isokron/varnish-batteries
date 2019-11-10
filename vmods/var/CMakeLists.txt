cmake_minimum_required (VERSION 3.0.2)
project (vmod C)
include(../../varnish.cmake vmod)

add_vmod(vmod_var vmod_var.vcc "var module for Varnish"
	vmod_var.c
)

# VCL import name is "var"
vmod_add_tests(vmod_var var
	tests/01-test.vtc
)
