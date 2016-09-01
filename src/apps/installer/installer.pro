APP_NAME   = "Installer"

include(../../../athletic.pri)

TEMPLATE = app
VERSION = $$APP_VERSION
TARGET = $${APP_TARGET}.$${APP_NAME}
DESTDIR = $$APP_BIN_PATH

QT += network widgets printsupport

include(../../rpath.pri)

LIBS *= -l$$qtLibraryName(extensionsystem) \
    -l$$qtLibraryName(utils) \
     -l$$qtLibraryName(widgets)

APP_GIT_REVISION = $$system(git --git-dir $$APP_SOURCE_TREE/.git --work-tree $$APP_BUILD_TREE describe --always --tags)

win32 {
#        RC_FILE = loader.rc
        target.path = $APP_BIN_PATH
        INSTALLS += target
} else:macx {
        CONFIG -= app_bundle
        LIBS += -framework CoreFoundation
} else {
        target.path  = $$APP_BIN_PATH
        INSTALLS    += target
}

QMAKE_SUBSTITUTES += $$PWD/installer_version.h.in

CONFIG += no_batch

HEADERS = \
    installer_global.h \
    installwizard.h

SOURCES = \
    installer.cpp \
    installwizard.cpp

RESOURCES = installer.qrc

