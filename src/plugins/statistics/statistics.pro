DEFINES += STATISTICS_LIBRARY
QT += \
	network \

include(../../athleticplugin.pri)

SOURCES += \
	statistics.cpp \
	statisticsmode.cpp \
    statisticsicons.cpp

HEADERS += \
	statistics.h \
	statisticsmode.h \
	statistics_global.h \
    statisticsconstants.h \
    statisticsicons.h

RESOURCES += \
	statistics.qrc \

