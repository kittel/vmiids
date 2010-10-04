AM_CPPFLAGS = -Wall -Wextra -Werror @AM_CPPFLAGS@
AM_CXXFLAGS = -fpic -I $(top_builddir)/src @AM_CXXFLAGS@ -rdynamic
AM_CFLAGS = -fpic  -I $(top_builddir)/src @AM_CFLAGS@ 

libdir = @libdir@/vmiids/modules/detection

lib_LTLIBRARIES = libexampledetectionmodule.la \
                  libstatechangerdetectionmodule.la \
                  librkhunterdetectionmodule.la \
                  libprocesslistdetectionmodule.la \
                  libfilelistdetectionmodule.la \
                  libfilecontentdetectionmodule.la

libexampledetectionmodule_la_SOURCES = ExampleDetectionModule.h \
					ExampleDetectionModule.cpp \
					../sensor/QemuMonitorSensorModule.h \
					../sensor/FileSystemSensorModule.h \
					../sensor/ShellSensorModule.h
					
libstatechangerdetectionmodule_la_SOURCES = StateChangerDetectionModule.h \
					StateChangerDetectionModule.cpp 


librkhunterdetectionmodule_la_SOURCES = RkHunterDetectionModule.h \
					RkHunterDetectionModule.cpp 

libprocesslistdetectionmodule_la_SOURCES = ProcessListDetectionModule.h \
					ProcessListDetectionModule.cpp 
libprocesslistdetectionmodule_la_CPPFLAGS = @MEMTOOL_CXXFLAGS@ @QT_CXXFLAGS@ @AM_CPPFLAGS@

libfilelistdetectionmodule_la_SOURCES = FileListDetectionModule.h \
					FileListDetectionModule.cpp 
					
libfilecontentdetectionmodule_la_SOURCES = FileContentDetectionModule.h \
					FileContentDetectionModule.cpp 
					
