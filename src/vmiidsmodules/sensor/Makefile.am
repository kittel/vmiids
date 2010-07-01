
lib_LTLIBRARIES = libqemumonitorsensormodule.la libfilesystemsensormodule.la

libqemumonitorsensormodule_la_LIBADD = 
libqemumonitorsensormodule_la_LDFLAGS =
libqemumonitorsensormodule_la_SOURCES = QemuMonitorSensorModule.h \
					QemuMonitorSensorModule.cpp 
libqemumonitorsensormodule_la_CFLAGS = -I $(top_builddir)/src/include
libqemumonitorsensormodule_la_CXXFLAGS = $(CPPUNIT_CFLAGS) -I $(top_builddir)/src/include -rdynamic

libfilesystemsensormodule_la_LIBADD = 
libfilesystemsensormodule_la_LDFLAGS =
libfilesystemsensormodule_la_SOURCES = FileSystemSensorModule.h \
					FileSystemSensorModule.cpp 
libfilesystemsensormodule_la_CFLAGS = -I $(top_builddir)/src/include
libfilesystemsensormodule_la_CXXFLAGS = $(CPPUNIT_CFLAGS) -I $(top_builddir)/src/include -rdynamic