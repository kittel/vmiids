bin_PROGRAMS=VMIstop VMImodule
VMIstop_SOURCES=vmistop.cpp \
							vmiids_rpc_clnt.c \
							../vmiids/vmiids_rpc.h

VMIstop_CFLAGS = -I $(top_builddir)/src/vmiids
VMIstop_CXXFLAGS = $(CPPUNIT_CFLAGS) -I $(top_builddir)/src/vmiids
VMIstop_LDFLAGS = -lpthread -lnsl

VMImodule_SOURCES=vmimodule.cpp \
							vmiids_rpc_clnt.c \
							../vmiids/vmiids_rpc.h

VMImodule_CFLAGS = -I $(top_builddir)/src/vmiids
VMImodule_CXXFLAGS = $(CPPUNIT_CFLAGS) -I $(top_builddir)/src/vmiids
VMImodule_LDFLAGS = -lpthread -lnsl


