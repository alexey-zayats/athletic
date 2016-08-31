APP_NAME   = "Loader"

include(../../athletic.pri)

TEMPLATE = app
VERSION = $$APP_VERSION
TARGET = $${APP_TARGET}.$${APP_NAME}
DESTDIR = $$APP_BIN_PATH

QT += network widgets printsupport

include(../rpath.pri)

LIBS *= -l$$qtLibraryName(extensionsystem) \
    -l$$qtLibraryName(utils) \
     -l$$qtLibraryName(widgets)

APP_GIT_REVISION = $$system(git --git-dir $$APP_SOURCE_TREE/.git --work-tree $$APP_BUILD_TREE describe --always --tags)

win32 {
        RC_FILE = loader.rc
        target.path = $$INSTALL_BIN_PATH
        INSTALLS += target
} else:macx {
        CONFIG -= app_bundle
        LIBS += -framework CoreFoundation
} else {
        target.path  = $$INSTALL_BIN_PATH
        INSTALLS    += target
}

DISTFILES += loader.rc \
        $$PWD/loader_version.h.in \
        Info.plist \

QMAKE_SUBSTITUTES += $$PWD/loader_version.h.in

CONFIG += no_batch

HEADERS = licensewizard.h \
    loader_global.h \

SOURCES = licensewizard.cpp \
    loader.cpp \

RESOURCES = loader.qrc

