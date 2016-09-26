DEFINES += WRESTLING_LIBRARY
QT += \
	network \

include(../../../athleticplugin.pri)

SOURCES += \
	wrestling.cpp \
	wrestlingsport.cpp \
	wrestlingicons.cpp \
    matchboard.cpp \
    matchcontrol.cpp

HEADERS += \
	wrestling.h \
	wrestling_global.h \
	wrestlingsport.h \
	wrestlingicons.h \
    matchboard.h \
    matchcontrol.h

RESOURCES += \
	wrestling.qrc
