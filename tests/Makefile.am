#check_PROGRAMS=libvmiTest
bin_PROGRAMS=libvmiTest
libvmiTest_SOURCES= libvmiTest.cpp \
					QemuMonitorTest.h \
					QemuMonitorTest.cpp \
					libvmi.h
libvmiTest_LDADD = $(top_builddir)/src/libvmi/libvmi.la
libvmiTest_CXXFLAGS = $(CPPUNIT_CFLAGS) -I $(top_builddir)/src/include
libvmiTest_LDFLAGS = $(CPPUNIT_LIBS) -ldl
