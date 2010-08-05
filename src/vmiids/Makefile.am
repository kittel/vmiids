AM_CPPFLAGS = -Wall -Wextra -Werror
AM_CXXFLAGS = -fpic -I $(top_builddir)/src/include -rdynamic
AM_CFLAGS = -fpic  -I $(top_builddir)/src/include

bin_PROGRAMS=vmiids vmiids-clearfscache
vmiids_SOURCES=VmiIDS.cpp \
               ../include/VmiIDS.h \
               ../include/DetectionModule.h \
               ../include/NotificationModule.h \
               ../include/SensorModule.h \
               ./Debug.h \
               ./ConsoleMonitor.cpp \
               ../include/ConsoleMonitor.h
               
               
#vmiids_LIBADD = 
vmiids_LDFLAGS = -lpthread -lnsl -ldl -lconfig++
vmiids_includedir=$(includedir)
vmiids_include_HEADERS = ../include/VmiIDS.h \
												 ../include/DetectionModule.h \
												 ../include/NotificationModule.h \
												 ../include/SensorModule.h \
												 ../include/ConsoleMonitor.h
vmiids_clearfscache_SOURCES=clearfscache.cpp
