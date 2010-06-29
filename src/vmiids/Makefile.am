bin_PROGRAMS=vmiids
vmiids_SOURCES=VmiIDS.cpp \
               VmiIDS.h \
               vmiids_rpc.h \
               vmiids_rpc_svc.c \
               DetectionModule.h \
               NotificationModule.h \
               SensorModule.h \
               SimpleDetectionModule.h \
               SimpleDetectionModule.cpp \
               ../libvmi/Debug.h

#vmiids_LIBADD = 
vmiids_CXXFLAGS = -rdynamic
vmiids_LDFLAGS = -lpthread -lnsl -ldl
#libvmi_la_includedir=$(includedir)/libvmi
#libvmi_la_include_HEADERS = libvmi.h

lib_LTLIBRARIES = libdynamicdetectionmodule.la
libdynamicdetectionmodule_la_LIBADD = 
libdynamicdetectionmodule_la_LDFLAGS =
libdynamicdetectionmodule_la_SOURCES = DynamicDetectionModule.h \
					DynamicDetectionModule.cpp 
#libdynamicdetectionmodule_la_includedir=$(includedir)/libvmi
#libdynamicdetectionmodule_la_include_HEADERS = libvmi.h

