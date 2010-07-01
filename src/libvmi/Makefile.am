
bin_PROGRAMS=libvmiMain shell
libvmiMain_SOURCES=libvmiMain.cpp

lib_LTLIBRARIES = libvmi.la
libvmi_la_LIBADD = 
libvmi_la_LDFLAGS = -lpthread
libvmi_la_SOURCES = libvmi.cpp \
					ConsoleMonitor.h \
					ConsoleMonitor.cpp \
					QemuMonitorParser.h \
					QemuMonitorParser.cpp \
					QemuMonitor.h \
					QemuMonitor.cpp \
					ShellParser.h \
					ShellParser.cpp \
					Shell.cpp \
					Shell.h \
					Debug.h
libvmi_la_includedir=$(includedir)/libvmi
libvmi_la_include_HEADERS = ../include/libvmi.h
libvmi_la_CXXFLAGS = $(CPPUNIT_CFLAGS) -I $(top_builddir)/src/include


shell_SOURCES= 
shell_LDADD = $(top_builddir)/src/libvmi/libvmi.la
shell_CXXFLAGS = $(CPPUNIT_CFLAGS) -I $(top_builddir)/src/include
shell_LDFLAGS = $(CPPUNIT_LIBS) -ldl
