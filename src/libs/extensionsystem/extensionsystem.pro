
include(../../athleticlibrary.pri)

DEFINES += EXTENSIONSYSTEM_LIBRARY

unix:LIBS += $$QMAKE_LIBS_DYNLOAD

!isEmpty(vcproj) {
	DEFINES += IDE_TEST_DIR=\"$$IDE_SOURCE_TREE\"
} else {
	DEFINES += IDE_TEST_DIR=\\\"$$IDE_SOURCE_TREE\\\"
}

HEADERS += \
	invoker.h \
	iplugin.h \
	iplugin_p.h \
	extensionsystem_global.h \
	pluginmanager.h \
	pluginmanager_p.h \
	pluginspec.h \
	pluginspec_p.h \
	plugincollection.h \
	plugindetailsview.h \
	pluginerroroverview.h \
	pluginerrorview.h \
	pluginview.h \

SOURCES += \
	invoker.cpp \
	iplugin.cpp \
	pluginmanager.cpp \
	pluginspec.cpp \
	plugincollection.cpp \
	extentionsystem.cpp \
	plugindetailsview.cpp \
	pluginerroroverview.cpp \
	pluginerrorview.cpp \
	pluginview.cpp \

FORMS += \
	plugindetailsview.ui \
	pluginerroroverview.ui \
	pluginerrorview.ui \

RESOURCES += \
	pluginview.qrc \

