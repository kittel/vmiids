dnl Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([libvmi], [0.1], [kittel@fs.tum.de])

AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE([-Wall])

#Include CPPUnit
AM_PATH_CPPUNIT(1.12.1)

AC_CONFIG_FILES(Makefile 
				src/Makefile
				src/vmiids/Makefile
				src/vmiidsmodules/Makefile
				src/vmiidsmodules/detection/Makefile
				src/vmiidsmodules/notification/Makefile
				src/vmiidsmodules/sensor/Makefile
				src/clientApps/Makefile)

AC_CONFIG_SRCDIR([src/Makefile.am])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
LT_INIT

# Checks for programs.
AM_PROG_CC_C_O
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_LIBTOOL_DLOPEN

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])

PKG_CHECK_MODULES([LIBCONFIGXX], [libconfig++ >= 1.3],,
	AC_MSG_ERROR([libconfig++ 1.3 or newer not found.])
)

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.


AM_PATH_LIBGCRYPT(1.4.5,
                  , AC_MSG_ERROR([libgcrypt 1.4 or newer not found.]))

dnl AM_PATH_LIBGCRYPT ([1.4],[],
dnl 	AC_MSG_ERROR([libgcrypt 1.4 or newer not found.])
dnl)

if test $cross_compiling = no; then
  AM_MISSING_PROG(HELP2MAN, help2man)
else
  HELP2MAN=:
fi

######################################################################
# DOXYGEN SUPPORT
######################################################################

DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(OFF)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(OFF)
DX_PS_FEATURE(OFF)

DX_INIT_DOXYGEN([$PACKAGE_NAME],[doxygen.cfg])

######################################################################

AC_OUTPUT
