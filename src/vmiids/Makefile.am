AM_CPPFLAGS = -Wall -Wextra -Werror
AM_CXXFLAGS = -fpic -I $(top_builddir)/src/include -rdynamic
AM_CFLAGS = -fpic  -I $(top_builddir)/src/include

bin_PROGRAMS=vmiids vmiids-clearfscache
vmiids_SOURCES=VmiIDS.cpp \
               ../include/VmiIDS.h \
               ../include/DetectionModule.h \
               ../include/NotificationModule.h \
               ../include/SensorModule.h \
               SimpleDetectionModule.h \
               SimpleDetectionModule.cpp \
               ../libvmi/Debug.h
               
               
               

#vmiids_LIBADD = 
vmiids_LDADD = $(top_builddir)/src/libvmi/libvmi.la
vmiids_LDFLAGS = -lpthread -lnsl -ldl -lconfig++
vmiids_includedir=$(includedir)
vmiids_include_HEADERS = ../include/VmiIDS.h \
												 ../include/DetectionModule.h \
												 ../include/NotificationModule.h \
												 ../include/SensorModule.h 
vmiids_clearfscache_SOURCES=clearfscache.cpp

lib_LTLIBRARIES = libdynamicdetectionmodule.la
libdynamicdetectionmodule_la_LIBADD = 
libdynamicdetectionmodule_la_LDFLAGS =
libdynamicdetectionmodule_la_SOURCES = DynamicDetectionModule.h \
					DynamicDetectionModule.cpp 


