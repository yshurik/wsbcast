QT += core
QT -= gui
QT += websockets

CONFIG += c++11

TARGET = wsbcast
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
	bcastserver.cpp

HEADERS += \
	bcastserver.h

CONFIG += debug_and_release
!debug_and_release|build_pass {
	CONFIG(debug, debug|release) {
			TARGET = wsbcastd
			DESTDIR = $$PWD
	 } else {
			TARGET = wsbcast
			DESTDIR = $$PWD
	 }
}

