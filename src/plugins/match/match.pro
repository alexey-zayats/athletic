DEFINES += MATCH_LIBRARY

QT += \
	network \
	printsupport \
	sql

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

