DEFINES += SCHEDULE_LIBRARY

QT += \
	network \
	widgets

include(../../athleticplugin.pri)

SOURCES += \
	schedule.cpp \
	schedulemode.cpp \
	scheduleicons.cpp \
	schedulewidget.cpp \
	generalschedule.cpp \
	bydayschedule.cpp \
	dayselector.cpp \
	schedulesportstable.cpp \
	schedulesportsmodel.cpp \
	schedulesportsview.cpp \
	monthline.cpp

HEADERS += \
	schedule.h \
	schedule_global.h \
	schedulemode.h \
	scheduleconstants.h \
	scheduleicons.h \
	schedulewidget.h \
	generalschedule.h \
	bydayschedule.h \
	dayselector.h \
	schedulesportstable.h \
	schedulesportsmodel.h \
	schedulesportsview.h \
	monthline.h

FORMS += \
	schedule.ui

RESOURCES += \
	schedule.qrc \

