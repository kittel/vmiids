AM_CPPFLAGS = -Wall -Wextra -Werror @AM_CPPFLAGS@
AM_CXXFLAGS = -fpic -I $(top_builddir)/src @AM_CXXFLAGS@ -rdynamic
AM_CFLAGS = -fpic  -I $(top_builddir)/src @AM_CFLAGS@ 

#util_includedir=$(includedir)/vmiids/util
#util_include_HEADERS = Thread.h

noinst_LTLIBRARIES = libutil.la

libutil_ladir = $(includedir)/vmiids/util
libutil_la_HEADERS = Thread.h \
					 MutexLocker.h
libutil_la_SOURCES = $(libutil_la_HEADERS) \
					Thread.cpp 