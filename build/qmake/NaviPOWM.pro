TEMPLATE = app
TARGET = bin/NaviPOWM
CONFIG += warn_on \
          qt \
          thread \
          rtti \
QMAKE_CXXFLAGS += -Wall
LIBS += -lgps

INCLUDEPATH += ../../src/common \
               ../../src/qt \
               ../../src/linux
DEPENDPATH += ../../src/common \
               ../../src/qt \
               ../../src/linux

OBJECTS_DIR = obj
CONFIG += release
CONFIG -= debug

SOURCES =   ../../src/common/*.cpp \
            ../../src/qt/*.cpp \
            ../../src/linux/*.cpp

HEADERS =   ../../src/common/*.h \
            ../../src/common/*.hpp \
            ../../src/qt/*.hpp \
            ../../src/linux/*.hpp
