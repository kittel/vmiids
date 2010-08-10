AM_CPPFLAGS = -Wall -Wextra -Werror @AM_CPPFLAGS@
AM_CXXFLAGS = -fpic -I $(top_builddir)/src @AM_CXXFLAGS@ -rdynamic
AM_CFLAGS = -fpic  -I $(top_builddir)/src @AM_CFLAGS@ 

SUBDIRS=detection notification sensor

bin_PROGRAMS=vmiids vmiids-clearfscache

vmiidsdir = $(includedir)/vmiids
vmiids_HEADERS=VmiIDS.h \
				Module.h \
				DetectionModule.h \
				NotificationModule.h \
				SensorModule.h \
				ConsoleMonitor.h

vmiids_SOURCES=VmiIDS.cpp \
			   $(vmiids_HEADERS) \
               ./Debug.h \
               ./ConsoleMonitor.cpp 
               
               
#vmiids_LIBADD = 
vmiids_LDFLAGS = -lpthread -lnsl -ldl -lconfig++ @AM_LDFLAGS@ 

vmiids_clearfscache_SOURCES=clearfscache.cpp
