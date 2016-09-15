DEFINES += COMPETITION_LIBRARY
QT += \
	network \

include(../../athleticplugin.pri)

SOURCES += \
	competition.cpp \
	competitionmode.cpp \
    competitionicons.cpp

HEADERS += \
	competition.h \
	competition_global.h \
	competitionmode.h \
    competitionconstants.h \
    competitionicons.h

RESOURCES += \
	competition.qrc
