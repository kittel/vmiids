AM_CPPFLAGS = -Wall -Wextra -Werror
AM_CXXFLAGS = -fpic -I $(top_builddir)/src/include
AM_CFLAGS = -fpic  -I $(top_builddir)/src/include

bin_PROGRAMS=vmiids
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
vmiids_LDFLAGS = -lpthread -lnsl -ldl
vmiids_includedir=$(includedir)
vmiids_include_HEADERS = ../include/VmiIDS.h \
												 ../include/DetectionModule.h \
												 ../include/NotificationModule.h \
												 ../include/SensorModule.h 

lib_LTLIBRARIES = libdynamicdetectionmodule.la
libdynamicdetectionmodule_la_LIBADD = 
libdynamicdetectionmodule_la_LDFLAGS =
libdynamicdetectionmodule_la_SOURCES = DynamicDetectionModule.h \
					DynamicDetectionModule.cpp 


