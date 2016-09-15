DEFINES += ROWING_LIBRARY
QT += \
	network \

include(../../../athleticplugin.pri)

SOURCES += \
	rowing.cpp \
	rowingicons.cpp \
	rowingsport.cpp \

HEADERS += \
	rowing.h \
	rowing_global.h \
	rowingicons.h \
	rowingsport.h \

RESOURCES += \
	rowing.qrc
