AM_CPPFLAGS = -Wall -Wextra -Werror @AM_CPPFLAGS@
AM_CXXFLAGS = -fpic -I $(top_builddir)/src @AM_CXXFLAGS@ -rdynamic
AM_CFLAGS = -fpic  -I $(top_builddir)/src @AM_CFLAGS@ 

lib_LTLIBRARIES = libqemumonitorsensormodule.la \
                  libfilesystemsensormodule.la \
                  libshellsensormodule.la \
                  libmemorysensormodule.la

libqemumonitorsensormodule_ladir = $(includedir)/vmiids/modules/sensor
libqemumonitorsensormodule_la_HEADERS = QemuMonitorSensorModule.h
libqemumonitorsensormodule_la_SOURCES = $(libqemumonitorsensormodule_la_HEADERS) \
					QemuMonitorSensorModule.cpp 
					
libfilesystemsensormodule_ladir = $(includedir)/vmiids/modules/sensor
libfilesystemsensormodule_la_HEADERS = FileSystemSensorModule.h
libfilesystemsensormodule_la_SOURCES = $(libfilesystemsensormodule_la_HEADERS) \
					FileSystemSensorModule.cpp 
libfilesystemsensormodule_la_CPPFLAGS = $(LIBGCRYPT_CFLAGS) @AM_CPPFLAGS@
libfilesystemsensormodule_la_LDFLAGS = $(LIBGCRYPT_LIBS) @AM_LDFLAGS@

libshellsensormodule_ladir = $(includedir)/vmiids/modules/sensor
libshellsensormodule_la_HEADERS = ShellSensorModule.h
libshellsensormodule_la_SOURCES = $(libshellsensormodule_la_HEADERS) \
					ShellSensorModule.cpp 
					
libmemorysensormodule_ladir = $(includedir)/vmiids/modules/sensor
libmemorysensormodule_la_HEADERS = MemorySensorModule.h
libmemorysensormodule_la_SOURCES = $(libmemorysensormodule_la_HEADERS) \
                    MemorySensorModule.cpp
libmemorysensormodule_la_CPPFLAGS = @AM_CPPFLAGS@
libmemorysensormodule_la_LDFLAGS = @MEMTOOL_LDFLAGS@ @AM_LDFLAGS@