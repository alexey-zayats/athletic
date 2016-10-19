DEFINES += MEMCACHE_LIBRARY

QT += \
	network

include(../../../athleticplugin.pri)

SOURCES += \
	memcacheplugin.cpp \
	memcachedcache.cpp \

HEADERS += \
	memcache_global.h \
	memcachedcache.h \
	memcacheplugin.h

!win32 {
	INCLUDEPATH += /opt/local/include
	LIBS += -L/opt/local/lib
	LIBS += -lmemcached
}
