
lib_LTLIBRARIES = libexampledetectionmodule.la \
                  libstatechangerdetectionmodule.la \
                  librkhunterdetectionmodule.la

libexampledetectionmodule_la_LIBADD = 
libexampledetectionmodule_la_LDFLAGS =
libexampledetectionmodule_la_SOURCES = ExampleDetectionModule.h \
					ExampleDetectionModule.cpp \
					../sensor/QemuMonitorSensorModule.h \
					../sensor/FileSystemSensorModule.h \
					../sensor/ShellSensorModule.h
libexampledetectionmodule_la_CFLAGS = -I $(top_builddir)/src/include
libexampledetectionmodule_la_CXXFLAGS = $(CPPUNIT_CFLAGS) -I $(top_builddir)/src/include -rdynamic

libstatechangerdetectionmodule_la_LIBADD = 
libstatechangerdetectionmodule_la_LDFLAGS =
libstatechangerdetectionmodule_la_SOURCES = StateChangerDetectionModule.h \
					StateChangerDetectionModule.cpp 
libstatechangerdetectionmodule_la_CFLAGS = -I $(top_builddir)/src/include
libstatechangerdetectionmodule_la_CXXFLAGS = $(CPPUNIT_CFLAGS) -I $(top_builddir)/src/include -rdynamic

librkhunterdetectionmodule_la_LIBADD = 
librkhunterdetectionmodule_la_LDFLAGS =
librkhunterdetectionmodule_la_SOURCES = RkHunterDetectionModule.h \
					RkHunterDetectionModule.cpp 
librkhunterdetectionmodule_la_CFLAGS = -I $(top_builddir)/src/include
librkhunterdetectionmodule_la_CXXFLAGS = $(CPPUNIT_CFLAGS) -I $(top_builddir)/src/include -rdynamic
