######################################################################
# Automatically generated by qmake (2.01a) Wed Aug 28 22:18:36 2013
######################################################################

# add opengl functionality
QT += opengl


# ---------- Set Me! ------------
_BOOST_ROOT = /usr/include
# -------------------------------

isEmpty(_BOOST_ROOT) {
    message(\"Boost Library\" qmake value not detected...)

        # Try to use the system environment value.
            _BOOST_ROOT = $$(BOOST_ROOT)
}
isEmpty(_BOOST_ROOT) {
    message(\"Boost Library\" environment variable not detected...)
        !build_pass:error(Please set the environment variable `BOOST_ROOT`. For example, BOOST_ROOT=c:\\boost_1_53_0)
} else {
    message(\"Boost Library\" detected in BOOST_ROOT = \"$$_BOOST_ROOT\")
        INCLUDEPATH += $$_BOOST_ROOT
}

TEMPLATE = lib
TARGET = ../lib/qglcommon
DEPENDPATH += ../include ../src
INCLUDEPATH += ../include
LIBS += -lGLEW -lassimp
VERSION = 1.0
QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXX = gcc-4.7

CONFIG += debug staticlib

# Input
SOURCES += ../src/*
HEADERS += ../include/*

