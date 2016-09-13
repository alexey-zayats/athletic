DEFINES += SCHEDULE_LIBRARY

QT += \
	network \
	printsupport

include(../../athleticplugin.pri)

SOURCES += \
	schedule.cpp \
	schedulemode.cpp

HEADERS += \
	schedule.h \
	schedule_global.h \
	schedulemode.h

FORMS += \
	schedule.ui

RESOURCES += \
	schedule.qrc \

