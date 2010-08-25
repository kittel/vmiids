AM_CPPFLAGS = -Wall -Wextra -Werror @AM_CPPFLAGS@
AM_CXXFLAGS = -fpic -I $(top_builddir)/src @AM_CXXFLAGS@ -rdynamic
AM_CFLAGS = -fpic  -I $(top_builddir)/src @AM_CFLAGS@ 

lib_LTLIBRARIES = libshellnotificationmodule.la libfilenotificationmodule.la

noinst_LTLIBRARIES = libbuffernotificationmodule.la

libshellnotificationmodule_ladir = $(includedir)/vmiids/modules/notification
libshellnotificationmodule_la_HEADERS = ShellNotificationModule.h
libshellnotificationmodule_la_SOURCES = $(libshellnotificationmodule_la_HEADERS) \
					ShellNotificationModule.cpp 

libfilenotificationmodule_ladir = $(includedir)/vmiids/modules/notification
libfilenotificationmodule_la_HEADERS = FileNotificationModule.h
libfilenotificationmodule_la_SOURCES = $(libfilenotificationmodule_la_HEADERS) \
					FileNotificationModule.cpp 
					
libbuffernotificationmodule_ladir = $(includedir)/vmiids/modules/notification
libbuffernotificationmodule_la_HEADERS = BufferNotificationModule.h
libbuffernotificationmodule_la_SOURCES = $(libbuffernotificationmodule_la_HEADERS) \
					BufferNotificationModule.cpp 