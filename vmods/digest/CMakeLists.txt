cmake_minimum_required (VERSION 3.0.2)
project (vmod C)
include(../../varnish.cmake vmod)



add_vmod(vmod_digest vmod_digest.vcc "digest module for Varnish"
	vmod_digest.c
)

target_link_libraries(vmod_digest mhash)


# VCL import name is "digest"
vmod_add_tests(vmod_digest digest
	tests/test01.vtc
	tests/test02.vtc
	tests/test_hash.vtc

	tests/test_hex.vtc
	tests/test_nullstring.vtc
)
