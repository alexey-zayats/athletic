DEFINES += UPDATER_LIBRARY
QT += \
	network \

# embedding build time information prevents repeatedly binary exact versions from same source code
isEmpty(APP_SHOW_BUILD_DATE): APP_SHOW_BUILD_DATE = $$(APP_SHOW_BUILD_DATE)
!isEmpty(APP_SHOW_BUILD_DATE): DEFINES += APP_SHOW_BUILD_DATE

include(../../athleticplugin.pri)

SOURCES += \
	updater.cpp \

HEADERS += \
	updater.h \
	updater_global.h \
