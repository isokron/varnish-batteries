
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

cmake works on the most common platforms, like Linux, FreeBSD and MacOS. It is a
lot easier to work with than m4 and autotools, and gets the job done without
extra effort.


## Adding another module

```
git submodule add https://github.com/user/libvmod-foo foreign/user-foo

mkdir vmods/foo && cd vmods/foo
cp ../_templates/* .
# edit CMakeLists.txt to taste.

# Either symlink sources from ../../foreign/user-foo/, or use ./import-upstream if
# modifications are needed.

cd ../../
# add to top-level CMakeLists.txt

```
