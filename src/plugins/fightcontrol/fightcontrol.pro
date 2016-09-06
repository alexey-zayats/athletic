DEFINES += FIGHTCONTROL_LIBRARY

QT += \
	network \
	printsupport \
	sql

include(../../athleticplugin.pri)

SOURCES += \
	fightcontrol.cpp \

HEADERS += \
	fightcontrol.h \
	fightcontrol_global.h
