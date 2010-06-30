bin_PROGRAMS=vmiids
vmiids_SOURCES=VmiIDS.cpp \
               ../include/VmiIDS.h \
               ../include/vmiids_rpc.h \
               vmiids_rpc_svc.c \
               ../include/DetectionModule.h \
               ../include/NotificationModule.h \
               ../include/SensorModule.h \
               SimpleDetectionModule.h \
               SimpleDetectionModule.cpp \
               ../libvmi/Debug.h

#vmiids_LIBADD = 
vmiids_LDFLAGS = -lpthread -lnsl -ldl
vmiids_CFLAGS = -I $(top_builddir)/src/include
vmiids_CXXFLAGS = $(CPPUNIT_CFLAGS) -I $(top_builddir)/src/include -rdynamic
vmiids_includedir=$(includedir)
vmiids_include_HEADERS = ../include/VmiIDS.h \
												 ../include/vmiids_rpc.h \
												 ../include/DetectionModule.h \
												 ../include/NotificationModule.h \
												 ../include/SensorModule.h 

lib_LTLIBRARIES = libdynamicdetectionmodule.la
libdynamicdetectionmodule_la_LIBADD = 
libdynamicdetectionmodule_la_LDFLAGS =
libdynamicdetectionmodule_la_SOURCES = DynamicDetectionModule.h \
					DynamicDetectionModule.cpp 
libdynamicdetectionmodule_la_CFLAGS = -I $(top_builddir)/src/include
libdynamicdetectionmodule_la_CXXFLAGS = $(CPPUNIT_CFLAGS) -I $(top_builddir)/src/include
#libdynamicdetectionmodule_la_includedir=$(includedir)/libvmi
#libdynamicdetectionmodule_la_include_HEADERS = libvmi.h

