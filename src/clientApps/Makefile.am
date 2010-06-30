bin_PROGRAMS=VMIstop VMImodule
VMIstop_SOURCES=vmistop.cpp \
							vmiids_rpc_clnt.c \
							../include/vmiids_rpc.h

VMIstop_CFLAGS = -I $(top_builddir)/src/include
VMIstop_CXXFLAGS = $(CPPUNIT_CFLAGS) -I $(top_builddir)/src/include
VMIstop_LDFLAGS = -lpthread -lnsl

VMImodule_SOURCES=vmimodule.cpp \
							vmiids_rpc_clnt.c \
							../include/vmiids_rpc.h

VMImodule_CFLAGS = -I $(top_builddir)/src/include
VMImodule_CXXFLAGS = $(CPPUNIT_CFLAGS) -I $(top_builddir)/src/include
VMImodule_LDFLAGS = -lpthread -lnsl


