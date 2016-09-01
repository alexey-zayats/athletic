APP_NAME   = "Srv"

include(../../athletic.pri)

TEMPLATE = app
VERSION = $$APP_VERSION
TARGET = $${APP_TARGET}.$${APP_NAME}
DESTDIR = $$APP_BIN_PATH

include(../rpath.pri)

LIBS *= -l$$qtLibraryName(extensionsystem) -l$$qtLibraryName(utils)

APP_GIT_REVISION = $$system(git --git-dir $$APP_SOURCE_TREE/.git --work-tree $$APP_BUILD_TREE describe --always --tags)

win32 {
        RC_FILE = srv.rc
        target.path = $$APP_BIN_PATH
        INSTALLS += target
} else:macx {
        CONFIG -= app_bundle
        LIBS += -framework CoreFoundation
} else {
        target.path  = $$APP_BIN_PATH
        INSTALLS    += target
}

DISTFILES += srv.rc \
        $$PWD/srv_version.h.in \
        Info.plist \

QMAKE_SUBSTITUTES += $$PWD/srv_version.h.in

CONFIG += no_batch

SOURCES += \
    srv.cpp

FORMS += \

