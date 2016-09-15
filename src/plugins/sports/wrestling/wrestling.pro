DEFINES += WRESTLING_LIBRARY
QT += \
	network \

include(../../../athleticplugin.pri)

SOURCES += \
	wrestling.cpp \
	wrestlingsport.cpp \
	wrestlingicons.cpp

HEADERS += \
	wrestling.h \
	wrestling_global.h \
	wrestlingsport.h \
	wrestlingicons.h

RESOURCES += \
	wrestling.qrc
