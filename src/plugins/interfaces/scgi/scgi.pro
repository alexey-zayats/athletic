DEFINES += SCGI_LIBRARY

QT += \
	network

include(../../../athleticplugin.pri)

SOURCES += \
	scgiinterface.cpp \
	scgirequest.cpp \
	scgiplugin.cpp \

HEADERS += \
	scgiinterface.h \
	scgirequest.h \
	scgiplugin.h \
	scgi_global.h \
