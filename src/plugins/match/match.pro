DEFINES += MATCH_LIBRARY

QT += \
	network \
	widgets

include(../../athleticplugin.pri)

SOURCES += \
	match.cpp \
	matchmode.cpp \
	matchicons.cpp

HEADERS += \
	match.h \
	match_global.h \
	matchmode.h \
	matchicons.h \
	matchconstants.h

RESOURCES += \
	match.qrc \

