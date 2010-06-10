bin_PROGRAMS=libvmiMain
libvmiMain_SOURCES=libvmiMain.cpp

lib_LTLIBRARIES = libvmi.la
libvmi_la_LIBADD = 
libvmi_la_LDFLAGS = -lpthread
libvmi_la_SOURCES = libvmi.cpp \
					ConsoleMonitor.h \
					ConsoleMonitor.cpp \
					QemuMonitorParser.h \
					QemuMonitorParser.cpp \
					QemuMonitor.h \
					QemuMonitor.cpp \
					ShellParser.h \
					ShellParser.cpp \
					Debug.h
libvmi_la_includedir=$(includedir)/libvmi
libvmi_la_include_HEADERS = libvmi.h
