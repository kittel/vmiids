bin_PROGRAMS=VMIstop VMImodule
VMIstop_SOURCES=vmistop.cpp \
							VmiIDSrpc.h \
							VmiIDSrpc.cpp

VMIstop_CFLAGS = -I $(top_builddir)/src/include
VMIstop_CXXFLAGS = $(CPPUNIT_CFLAGS) -I $(top_builddir)/src/include
VMIstop_LDFLAGS = -lpthread -lnsl

VMImodule_SOURCES=vmimodule.cpp \
							VmiIDSrpc.h \
							VmiIDSrpc.cpp

VMImodule_CFLAGS = -I $(top_builddir)/src/include
VMImodule_CXXFLAGS = $(CPPUNIT_CFLAGS) -I $(top_builddir)/src/include
VMImodule_LDFLAGS = -lpthread -lnsl


