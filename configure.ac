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
				tests/Makefile)

AC_CONFIG_SRCDIR([src/Makefile.am])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
LT_INIT

# Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

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
