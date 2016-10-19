APP_NAME   = "RestWs"

include(../../../athletic.pri)

TEMPLATE = app
VERSION = $$APP_VERSION
TARGET = $${APP_TARGET}.$${APP_NAME}

DESTDIR = $$APP_BIN_PATH

#macx:DESTDIR = $$APP_BUILD_TREE
#else:DESTDIR = $$APP_BIN_PATH

QT += network

include(../../rpath.pri)

LIBS *= -l$$qtLibraryName(extensionsystem) \
	-l$$qtLibraryName(utils)

APP_GIT_REVISION = $$system(git --git-dir $$APP_SOURCE_TREE/.git --work-tree $$APP_BUILD_TREE describe --always --tags)

win32 {
#        RC_FILE = restws.rc
		target.path = $$APP_BIN_PATH
		INSTALLS += target
} else:macx {
		CONFIG -= app_bundle
		LIBS += -framework CoreFoundation
} else {
		target.path  = $$APP_BIN_PATH
		INSTALLS    += target
}

QMAKE_SUBSTITUTES += $$PWD/restws_version.h.in

CONFIG += crypto

SOURCES += \
	restws.cpp \

HEADERS += \
	restws.h \

