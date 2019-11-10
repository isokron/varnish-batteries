
# Varnish Cache with batteries (vmods)

This is a collection of extension modules aimed at extending
Varnish Cache without spending too much work on deployment.


Main platform to run on is Ubuntu LTS, currently 18.04/bionic.
Main Varnish version is the latest LTS, currently 6.0.


## Installation

You need cmake, varnish-dev and a compiler.

```
cmake .
make
sudo make install
```


## FAQ


### Why cmake and not autotools?

Cmake is working on Linux, FreeBSD and MacOS.

It is a lot easier to work with, and seem fairly well thought out. For greatness
it is very important to be able to master your tools, and with cmake that feels
like a possibility.



## Adding another module

```
git submodule add https://github.com/user/libvmod-foo foreign/user-foo

mkdir -p foo/tests && cd foo
# symlink sources into foo/

cp ../template_CMakeLists.txt CMakeLists.txt
# edit CMakeLists.txt to taste.

cd ..
```
