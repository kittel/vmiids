AM_CPPFLAGS = -Wall -Wextra -Werror
AM_CXXFLAGS = -fpic -I $(top_builddir)/src/include
AM_CFLAGS = -fpic  -I $(top_builddir)/src/include

bin_PROGRAMS=VMIstop VMImodule
VMIstop_SOURCES=vmistop.cpp \
							VmiIDSrpc.h \
							VmiIDSrpc.cpp
VMIstop_LDFLAGS = -lpthread -lnsl

VMImodule_SOURCES=vmimodule.cpp \
							VmiIDSrpc.h \
							VmiIDSrpc.cpp
VMImodule_LDFLAGS = -lpthread -lnsl


