DEFINES += FIGHTCONTROL_LIBRARY

QT += \
	network \
	printsupport \
	sql

include(../../athleticplugin.pri)

SOURCES += \
	fightcontrol.cpp \
	fightcontrolmode.cpp

HEADERS += \
	fightcontrol.h \
	fightcontrol_global.h \
	fightcontrolmode.h

RESOURCES += \
	fightcontrol.qrc \

