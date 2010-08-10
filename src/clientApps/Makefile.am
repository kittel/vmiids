AM_CPPFLAGS = -Wall -Wextra -Werror @AM_CPPFLAGS@
AM_CXXFLAGS = -fpic -I $(top_builddir)/src @AM_CXXFLAGS@ -rdynamic
AM_CFLAGS = -fpic  -I $(top_builddir)/src @AM_CFLAGS@ 

bin_PROGRAMS=VMIstop VMImodule
VMIstop_SOURCES=vmistop.cpp \
							VmiIDSrpc.h \
							VmiIDSrpc.cpp
VMIstop_LDFLAGS = -lpthread -lnsl @AM_LDFLAGS@ 

VMImodule_SOURCES=vmimodule.cpp \
							VmiIDSrpc.h \
							VmiIDSrpc.cpp
VMImodule_LDFLAGS = -lpthread -lnsl @AM_LDFLAGS@ 


