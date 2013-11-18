######################################################################
# Automatically generated by qmake (2.01a) Wed Aug 28 22:18:36 2013
######################################################################

# add opengl functionality
QT += opengl

# add phonon
QT += phonon

# ---------- Set Me! ------------
_BOOST_ROOT = /usr/include
_BULLET_ROOT = /usr/include/bullet
_IMAGE_MAGICK_ROOT = /usr/include/ImageMagick
_ASSIMP_ROOT = /usr/include/assimp
# -------------------------------

isEmpty(_BOOST_ROOT) {
    message(\"Boost Library\" qmake value not detected...)
            _BOOST_ROOT = $$(BOOST_ROOT)
}
isEmpty(_BOOST_ROOT) {
    message(\"Boost Library\" qmake value not detected...)
            _BOOST_ROOT = /usr/local/include
}
isEmpty(_BOOST_ROOT) {
    message(\"Boost Library\" environment variable not detected...)
        !build_pass:error(Please set the environment variable `BOOST_ROOT`. For example, BOOST_ROOT=c:\\boost_1_53_0)
} else {
    message(\"Boost Library\" detected in BOOST_ROOT = \"$$_BOOST_ROOT\")
        INCLUDEPATH += $$_BOOST_ROOT
}

isEmpty(_BULLET_ROOT) {
    message(\"Bullet Library\" qmake value not detected...)
            _BULLET_ROOT = $$(BULLET_ROOT)
}
isEmpty(_BULLET_ROOT) {
    message(\"Bullet Library\" qmake value not detected...)
            _BULLET_ROOT = /usr/local/include/bullet
}
isEmpty(_BULLET_ROOT) {
    message(\"Bullet Library\" environment variable not detected...)
        !build_pass:error(Please set the environment variable `BULLET_ROOT`.
} else {
    message(\"Bullet Library\" detected in BULLET_ROOT = \"$$_BULLET_ROOT\")
        INCLUDEPATH += $$_BULLET_ROOT
}

isEmpty(_ASSIMP_ROOT) {
    message(\"Assimp Library\" qmake value not detected...)
            _ASSIMP_ROOT = $$(ASSIMP_ROOT)
}
isEmpty(_ASSIMP_ROOT) {
    message(\"Assimp Library\" qmake value not detected...)
            _ASSIMP_ROOT = /usr/local/include/assimp
}
isEmpty(_ASSIMP_ROOT) {
    message(\"Assimp Library\" environment variable not detected...)
        !build_pass:error(Please set the environment variable `ASSIMP_ROOT`.
} else {
    message(\"Assimp Library\" detected in ASSIMP_ROOT = \"$$_ASSIMP_ROOT\")
        INCLUDEPATH += $$_ASSIMP_ROOT
}

isEmpty(_IMAGE_MAGICK_ROOT) {
    message(\"Image Magick Library\" qmake value not detected...)
            _IMAGE_MAGICK_ROOT = $$(IMAGEMAGICK_ROOT)
}
isEmpty(_IMAGE_MAGICK_ROOT) {
    message(\"Image Magick Library\" qmake value not detected...)
            _IMAGE_MAGICK_ROOT = /usr/local/include/ImageMagick
}
isEmpty(_IMAGE_MAGICK_ROOT) {
    message(\"Image Magick Library\" qmake value not detected...)
            _IMAGE_MAGICK_ROOT = /usr/include/GraphicsMagick
}
isEmpty(_IMAGE_MAGICK_ROOT) {
    message(\"Image Magick Library\" environment variable not detected...)
        !build_pass:error(Please set the environment variable `IMAGE_MAGICK_ROOT`.
} else {
    message(\"Image Magick Library\" detected in IMAGE_MAGICK_ROOT = \"$$_IMAGE_MAGICK_ROOT\")
        INCLUDEPATH += $$_IMAGE_MAGICK_ROOT
}


TEMPLATE = lib
TARGET = ../lib/qglcommon
DEPENDPATH += ../include/ ../src/
INCLUDEPATH += ../include
LIBS += -lGLEW -lassimp -lMagick++ -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath -lphonon
VERSION = 1.0
QMAKE_CXXFLAGS += -std=c++0x -fopenmp -g
QMAKE_CXX = g++-4.6

CONFIG += debug staticlib

# Input
SOURCES += ../src/*.cpp
HEADERS += ../include/*.hpp

