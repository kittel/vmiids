AM_CPPFLAGS = -Wall -Wextra -Werror
AM_CXXFLAGS = -fpic -I $(top_builddir)/src @AM_CXXFLAGS@ -rdynamic
AM_CFLAGS = -fpic  -I $(top_builddir)/src @AM_CFLAGS@ 

lib_LTLIBRARIES = libqemumonitorsensormodule.la \
                  libfilesystemsensormodule.la \
                  libshellsensormodule.la \
                  libmemorysensormodule.la

libqemumonitorsensormodule_ladir = $(includedir)/vmiids/sensor
libqemumonitorsensormodule_la_HEADERS = QemuMonitorSensorModule.h
libqemumonitorsensormodule_la_SOURCES = $(libqemumonitorsensormodule_la_HEADERS) \
					QemuMonitorSensorModule.cpp 
					
libfilesystemsensormodule_ladir = $(includedir)/vmiids/sensor
libfilesystemsensormodule_la_HEADERS = FileSystemSensorModule.h
libfilesystemsensormodule_la_SOURCES = $(libfilesystemsensormodule_la_HEADERS) \
					FileSystemSensorModule.cpp 
libfilesystemsensormodule_la_CPPFLAGS = $(LIBGCRYPT_CFLAGS)
libfilesystemsensormodule_la_LDFLAGS = $(LIBGCRYPT_LIBS)

libshellsensormodule_ladir = $(includedir)/vmiids/sensor
libshellsensormodule_la_HEADERS = ShellSensorModule.h
libshellsensormodule_la_SOURCES = $(libshellsensormodule_la_HEADERS) \
					ShellSensorModule.cpp 
					
libmemorysensormodule_ladir = $(includedir)/vmiids/sensor
libmemorysensormodule_la_HEADERS = MemorySensorModule.h
libmemorysensormodule_la_SOURCES = $(libmemorysensormodule_la_HEADERS) \
                    MemorySensorModule.cpp                     