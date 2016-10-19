DEFINES += HELLO_LIBRARY

QT += \
	network

include(../../../athleticplugin.pri)

SOURCES += \
	helloplugin.cpp \
    helloservice.cpp \
    helloserviceprefix.cpp

HEADERS += \
	hello_global.h \
	helloplugin.h \
    helloservice.h \
    helloserviceprefix.h

