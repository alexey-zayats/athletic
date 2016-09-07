APP_NAME   = "App"

include(../../../athletic.pri)

TEMPLATE = app
VERSION = $$APP_VERSION
TARGET = $${APP_TARGET}.$${APP_NAME}
DESTDIR = $$APP_BIN_PATH

QT += network

include(../../rpath.pri)

LIBS *= -l$$qtLibraryName(extensionsystem) \
	-l$$qtLibraryName(utils) \
	-l$$qtLibraryName(widgets)

APP_GIT_REVISION = $$system(git --git-dir $$APP_SOURCE_TREE/.git --work-tree $$APP_BUILD_TREE describe --always --tags)

win32 {
#	RC_FILE = athletic.rc
	target.path = $$APP_BIN_PATH
	INSTALLS += target
} else:macx {
	CONFIG -= app_bundle
	LIBS += -framework CoreFoundation
	ASSETCATALOG.files = $$PWD/qtcreator.xcassets
	macx-xcode {
		QMAKE_BUNDLE_DATA += ASSETCATALOG
	} else {
		ASSETCATALOG.output = $$APP_DATA_PATH/qtcreator.icns
		ASSETCATALOG.commands = xcrun actool \
			--app-icon qtcreator \
			--output-partial-info-plist $$shell_quote($(TMPDIR)/qtcreator.Info.plist) \
			--platform macosx \
			--minimum-deployment-target 10.7 \
			--compile $$shell_quote($$IDE_DATA_PATH) \
			$$shell_quote($$PWD/qtcreator.xcassets) > /dev/null
		ASSETCATALOG.input = ASSETCATALOG.files
		ASSETCATALOG.CONFIG += no_link target_predeps
		QMAKE_EXTRA_COMPILERS += ASSETCATALOG
	}
	QMAKE_INFO_PLIST = Info.plist
} else {
	target.path  = $$APP_BIN_PATH
	INSTALLS    += target
}

QMAKE_SUBSTITUTES += $$PWD/athletic_version.h.in

FORMS += \

SOURCES += \
	athletic.cpp

RESOURCES += \

HEADERS += \
	athletic.h
