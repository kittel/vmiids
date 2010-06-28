bin_PROGRAMS=VMIstop
VMIstop_SOURCES=vmistop.cpp \
								vmiids_rpc_clnt.c \
								../vmiids/vmiids_rpc.h

#vmiids_LIBADD = 
VMIstop_CFLAGS = -I $(top_builddir)/src/vmiids
VMIstop_LDFLAGS = -lpthread -lnsl
libvmi_la_includedir=$(includedir)/vmiids
#libvmi_la_include_HEADERS = libvmi.h

