
# Varnish Cache with batteries

This is a collection of extension modules aimed at extending
Varnish Cache without spending too much work on deployment.

Contents:
* vmods you will need often. (cookie, var, header, etc)
* Useful VCL snippets. (planned)
* Extension scripts, like cronjobs for logging 5xx safely with log rotation (planned)

Main platform to run on is Ubuntu LTS. (currently 18.04/bionic)
Main Varnish version is the latest LTS. (currently 6.0)


## Installation

You need cmake, varnish-dev and a compiler.

```
cmake .
make
sudo make install  # soon
```

## Packaging

There will be binary packages (for Ubuntu) made available.

They are meant to be used with the LTS packages that Varnish Cache
(or, specificly, VS) have on packagecloud.io.


## FAQ

### What about maintenance, bug fixes and so on?

For anything that is imported verbatim (most vmods), you should file bugs upstream.

Look in `foreign/*/README.rst` and see if that helps you find the correct bug/issue tracker.

If you don't get any traction there and you have business needs, Isokron AS who
packaged this up is doing consulting and can help you out. Email
<contact@isokron.no> and we'll be in touch.

### What the pull request policy?

PRs are welcome.


### What is your issue policy?

Stale issues will be closed after 60 days of inactivity. There is no benefit for
anyone having an unmanageable amount of open issues.

If you feel strongly about a bug or feature request, keep polling and we'll
know about it.

### Can you add vmod x?

Maybe.

Key questions: Is the code quality ok? Is anyone maintaining it? Will we want to use it
ourselves?

If it is trivial (no third party libs), has documentation and tests, the answer is most
likely yes.


### Why cmake and not autotools?

cmake works on the most common platforms, like Linux, FreeBSD and MacOS. It is a
lot easier to work with than m4 and autotools, and gets the job done without
extra effort.

### Will you make tarballs for third party packaging?

Most likely not.

Tarballs is another thing to care for, and it suddenly opens a can of worms with
signed hashes, gpg keys and a distribution site to make sure it is the original.

Clone (or submodule) the git repo and you have all this without any extra work.


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
