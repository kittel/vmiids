AM_CPPFLAGS = -Wall -Wextra -Werror @AM_CPPFLAGS@
AM_CXXFLAGS = -fpic -I $(top_builddir)/src @AM_CXXFLAGS@ -rdynamic
AM_CFLAGS = -fpic  -I $(top_builddir)/src @AM_CFLAGS@ 

bin_PROGRAMS=gui
gui_SOURCES= \
	QtGui.cpp \
	MainWindow.cpp \
	DetectionModuleWidget.cpp
nodist_gui_SOURCES = \
	moc_MainWindow.cpp \
	moc_DetectionModuleWidget.cpp
gui_CXXFLAGS = @QT_CXXFLAGS@
gui_LDFLAGS = @QT_LDFLAGS@

EXTRA_DIST = $(nodist_gui_SOURCES:moc_%.cpp=%.h)

# This line ensures that generated moc_*.cpp and resources.cpp files are
# deleted when we make clean.
CLEANFILES = $(filter moc_%.cpp,$(gui_SOURCES))

# This rule lets GNU make create any moc_*.cpp from the equivalent *.h
moc_%.cpp: %.h
	moc $< -o $@


