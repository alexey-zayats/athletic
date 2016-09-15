DEFINES += SCHEDULE_LIBRARY

QT += \
	network \
	printsupport

include(../../athleticplugin.pri)

SOURCES += \
	schedule.cpp \
	schedulemode.cpp \
    scheduleicons.cpp

HEADERS += \
	schedule.h \
	schedule_global.h \
	schedulemode.h \
    scheduleconstants.h \
    scheduleicons.h

FORMS += \
	schedule.ui

RESOURCES += \
	schedule.qrc \

