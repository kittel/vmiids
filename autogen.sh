#! /bin/sh

echo "running libtoolize"
libtoolize --force --copy || exit 1

echo "running aclocal"
aclocal --force || exit 1

echo "running autoheader"
autoheader || exit 1

echo "running automake"
automake -a --gnu --add-missing  || exit 1

echo "running autoconf"
autoconf || exit 1

