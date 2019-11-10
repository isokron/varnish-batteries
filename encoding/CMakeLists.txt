cmake_minimum_required (VERSION 3.0.2)
project (vmod C)
include(../varnish.cmake vmod)

add_vmod(vmod_encoding vmod_encoding.vcc "encoding module for Varnish"
	vmod_encoding.c
	base64.c
	urlcode.c
)
# VCL import name is "encoding"
vmod_add_tests(vmod_encoding encoding
	tests/01-url.vtc
	tests/02-b64.vtc
)
