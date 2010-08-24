AM_CPPFLAGS = -Wall -Wextra -Werror @AM_CPPFLAGS@
AM_CXXFLAGS = -fpic -I $(top_builddir)/src @AM_CXXFLAGS@ -rdynamic
AM_CFLAGS = -fpic  -I $(top_builddir)/src @AM_CFLAGS@ 

lib_LTLIBRARIES = libvmiidsrpcclient.la

libvmiidsrpcclient_ladir = $(includedir)/vmiids/rpc
libvmiidsrpcclient_la_HEADERS = RpcClient.h
libvmiidsrpcclient_la_SOURCES = RpcClient.cpp
libvmiidsrpcclient_la_CPPFLAGS = @AM_CPPFLAGS@
libvmiidsrpcclient_la_LDFLAGS = @AM_LDFLAGS@ 

noinst_LTLIBRARIES = libvmiidsrpcserver.la

libvmiidsrpcserver_ladir = $(includedir)/vmiids/rpc
libvmiidsrpcserver_la_HEADERS = RpcServer.h
libvmiidsrpcserver_la_SOURCES = RpcServer.cpp
libvmiidsrpcserver_la_CPPFLAGS = @AM_CPPFLAGS@
libvmiidsrpcserver_la_LDFLAGS = @AM_LDFLAGS@ 