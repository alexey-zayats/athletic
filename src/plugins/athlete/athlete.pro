DEFINES += ATHLETE_LIBRARY
QT += \
	network \
	widgets \

include(../../athleticplugin.pri)

SOURCES += \
	athlete.cpp \
	athletemode.cpp \
	athleteicons.cpp

HEADERS += \
	athlete.h \
	athletemode.h \
	athlete_global.h \
	athleteicons.h \
	athleteconstants.h

RESOURCES += \
	athlete.qrc \

