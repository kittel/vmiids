AM_CPPFLAGS = -Wall -Wextra -Werror
AM_CXXFLAGS = -fpic -I $(top_builddir)/src/include -rdynamic
AM_CFLAGS = -fpic  -I $(top_builddir)/src/include


lib_LTLIBRARIES = libqemumonitorsensormodule.la libfilesystemsensormodule.la libshellsensormodule.la

libqemumonitorsensormodule_la_SOURCES = QemuMonitorSensorModule.h \
					QemuMonitorSensorModule.cpp 

libfilesystemsensormodule_la_SOURCES = FileSystemSensorModule.h \
					FileSystemSensorModule.cpp 

libshellsensormodule_la_SOURCES = ShellSensorModule.h \
					ShellSensorModule.cpp 