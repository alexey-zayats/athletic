DEFINES += CGI_LIBRARY

QT += \
	network

include(../../../athleticplugin.pri)

SOURCES += \
	cgiinterface.cpp \
	cgirequest.cpp \
	cgiplugin.cpp \

HEADERS += \
	cgiinterface.h \
	cgirequest.h \
	cgiplugin.h \
	cgi_global.h \

