
TARGET = ItemSetClient
TEMPLATE = app

ROOT_DIR = $$PWD/../../

DESTDIR		= $$ROOT_DIR/Bin

DEFINES += TARGET_AUTHOR="\\\"Smithcoder\\\""
DEFINES += TARGET_NAME="\\\"ItemSetClientExample\\\""

INCLUDEPATH		+= $$ROOT_DIR/Include $$ROOT_DIR/Source

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS	+= -Wno-unused-parameter

QT		+= core gui widgets xml sql network

unix {
LIBS += "-L$$ROOT_DIR/Lib" -lRamio
}
win32 {
LIBS += "-L$$ROOT_DIR/Lib" -lRamio0
}

SOURCES += main.cpp \
	MainWidget.cpp \
	ItemSetClient.cpp \
	TasksSimpleWidget.cpp \
	TaskSimpleWidget.cpp \
	LoginWidget.cpp \
	../ItemSetServer/Tasks.cpp \
	../ItemSetServer/Users.cpp

HEADERS += \
	MainWidget.h \
	ItemSetClient.h \
	TasksSimpleWidget.h \
	TaskSimpleWidget.h \
	LoginWidget.h \
	../ItemSetServer/Tasks.h \
	../ItemSetServer/Users.h

RESOURCES += \
	resource.qrc

