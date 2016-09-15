DEFINES += CANOEING_LIBRARY
QT += \
	network \

include(../../../athleticplugin.pri)

SOURCES += \
	canoeing.cpp \
	canoeingsport.cpp \
	canoeingicons.cpp \

HEADERS += \
	canoeing.h \
	canoeing_global.h \
	canoeingsport.h \
	canoeingicons.h \

RESOURCES += \
	canoeing.qrc
