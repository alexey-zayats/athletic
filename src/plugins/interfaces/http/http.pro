DEFINES += HTTP_LIBRARY

QT += \
	network

include(../../../athleticplugin.pri)

SOURCES += \
	httpinterface.cpp \
	httprequest.cpp \
	httpplugin.cpp \

HEADERS += \
	httpinterface.h \
	httprequest.h \
	httpplugin.h \
	http_global.h \
