DEFINES += FIGHTBOARD_LIBRARY

QT += \
	network \
	printsupport \
	sql

include(../../athleticplugin.pri)

SOURCES += \
	fightboard.cpp \

HEADERS += \
	fightboard.h \
	fightboard_global.h
