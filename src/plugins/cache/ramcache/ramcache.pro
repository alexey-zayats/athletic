DEFINES += RAMCACHE_LIBRARY

QT += \
	network

include(../../../athleticplugin.pri)

SOURCES += \
	ramcache.cpp \
	ramcacheplugin.cpp \

HEADERS += \
	ramcache_global.h \
	ramcache.h \
	ramcacheplugin.h \

