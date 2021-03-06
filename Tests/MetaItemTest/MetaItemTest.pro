#       MetaItemTest+libRamio
#       Проверка использования айтемов.

TARGET = MetaItemTest
TEMPLATE = app

ROOT_DIR = $$PWD/../../

DESTDIR		 = $$ROOT_DIR/Bin

DEFINES += TARGET_AUTHOR="\\\"Smithcoder\\\""
DEFINES += TARGET_NAME="\\\"MetaItemTest\\\""

INCLUDEPATH			 += ../Items/ $$ROOT_DIR/Include $$ROOT_DIR/Source

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS  += -Wno-unused-parameter
QT	   += core gui widgets testlib xml

unix {
LIBS += "-L$$ROOT_DIR/Lib" -lRamio
}
win32 {
LIBS += "-L$$ROOT_DIR/Lib" -lRamio0
}

SOURCES += main.cpp \
	SuperItemTest.cpp \
	../Items/SuperItem.cpp \
	../Items/TestItems.cpp \

HEADERS += \
	SuperItemTest.h \
	../Items/SuperItem.h \
	../Items/TestItems.h \

