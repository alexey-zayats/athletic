DEFINES += FASTCGI_LIBRARY

QT += \
	network

include(../../../athleticplugin.pri)

SOURCES += \
	beginrequestrecord.cpp \
	debughandler.cpp \
	endrequestrecord.cpp \
	fastcgiinterface.cpp \
	fastcgisocketmanager.cpp \
	fastcgistream.cpp \
	parametersrecord.cpp \
	recordheader.cpp \
	standardinputrecord.cpp \
	standardoutputrecord.cpp \
	unsignedbytearray.cpp \
	socketserver.cpp \
	fastcgiplugin.cpp \

HEADERS += \
	beginrequestrecord.h \
	debughandler.h \
	endrequestrecord.h \
	fastcgi.h \
	fastcgiinterface.h \
	fastcgisocketmanager.h \
	fastcgistream.h \
	parametersrecord.h \
	recordheader.h \
	socketserver.h \
	standardinputrecord.h \
	standardoutputrecord.h \
	unsignedbytearray.h \
	fastcgiplugin.h \
	fastcgi_global.h
