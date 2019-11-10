
# Varnish Cache with batteries (vmods)

This is a collection of extension modules aimed at extending
Varnish Cache without spending too much work on deployment.


## Add another vmod

::

	git submodule add https://github.com/user/libvmod-foo foreign/user-foo

	mkdir -p foo/tests && cd foo
        # symlink sources into foo/

	cp ../template_CMakeLists.txt CMakeLists.txt

	lib/libvmod_foo$ ../../lib/libvcc/vmodtool.py -b  # Make boilerplate file
        # add to man/Makefile.am (twice!)

::
	git submodule foreach git submodule init
	git submodule foreach git submodule update

