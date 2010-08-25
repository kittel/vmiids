AM_CPPFLAGS = -Wall -Wextra -Werror @AM_CPPFLAGS@
AM_CXXFLAGS = -fpic -I $(top_builddir)/src @AM_CXXFLAGS@ -rdynamic
AM_CFLAGS = -fpic  -I $(top_builddir)/src @AM_CFLAGS@ 

SUBDIRS=util modules rpc modules_extern

sysconf_DATA = vmiids.cfg

bin_PROGRAMS=vmiids vmiids-clearfscache

vmiidsdir = $(includedir)/vmiids
vmiids_HEADERS=VmiIDS.h \
				Module.h \
				OutputModule.h \
				DetectionModule.h \
				NotificationModule.h \
				SensorModule.h \
				ConsoleMonitor.h

vmiids_SOURCES=main.cpp \
			   VmiIDS.cpp \
			   DetectionThread.h \
			   DetectionThread.cpp \
			   $(vmiids_HEADERS) \
			   NotificationModule.cpp \
               ./Debug.h \
               ./ConsoleMonitor.cpp 
               
               
vmiids_LDFLAGS = -lpthread -lnsl -ldl -lconfig++ @AM_LDFLAGS@ \
				-L./util/ -lutil \
				-L./rpc/ -lvmiidsrpcserver \
				-L./modules/notification/ -lbuffernotificationmodule

vmiids_clearfscache_SOURCES=clearfscache.cpp
