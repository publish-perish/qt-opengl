######################################################################
# Automatically generated by qmake (2.01a) Wed Aug 28 22:18:36 2013
######################################################################

# add opengl functionality
QT += opengl

# add phonon
QT += phonon

# ---------- Set Me! ------------
_BULLET_ROOT = /usr/include/bullet
_IMAGE_MAGICK_ROOT = /usr/include/ImageMagick
# -------------------------------

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


TEMPLATE = app
TARGET = ../bin/assignment09
DEPENDPATH += ../src/ ../../common/include/ ../../common/src/
INCLUDEPATH += ../src ../../common/include 
LIBS += -L../../common/lib -lqglcommon -lGLEW -lassimp -lMagick++ -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath -lGLU -lphonon
QMAKE_CXX = g++-4.6
QMAKE_CXXFLAGS += -std=c++0x

libqglcommon.target = ../../common/lib/libqglcommon.a
libqglcommon.commands = cd ../../common && make
libqglcommon.depends = FORCE
QMAKE_EXTRA_TARGETS += libqglcommon
PRE_TARGETDEPS += ../../common/lib/libqglcommon.a

CONFIG += debug

# Input
SOURCES += ../src/*.cpp
HEADERS += ../src/*.hpp ../../common/include/*.hpp
