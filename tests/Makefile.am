AM_CPPFLAGS = -Wall -Wextra -Werror
AM_CXXFLAGS = -fpic -I $(top_builddir)/src/include
AM_CFLAGS = -fpic  -I $(top_builddir)/src/include

#check_PROGRAMS=libvmiTest
bin_PROGRAMS=libvmiTest
libvmiTest_SOURCES= libvmiTest.cpp \
					QemuMonitorTest.h \
					QemuMonitorTest.cpp \
					libvmi.h
libvmiTest_LDADD = $(top_builddir)/src/libvmi/libvmi.la
libvmiTest_CXXFLAGS = $(CPPUNIT_CFLAGS) $(AM_CFLAGS)
libvmiTest_LDFLAGS = $(CPPUNIT_LIBS) -ldl
