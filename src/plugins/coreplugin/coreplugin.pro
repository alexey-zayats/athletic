DEFINES += CORE_LIBRARY
QT += \
	help \
	network \
	printsupport \
	sql \

# embedding build time information prevents repeatedly binary exact versions from same source code
isEmpty(APP_SHOW_BUILD_DATE): APP_SHOW_BUILD_DATE = $$(APP_SHOW_BUILD_DATE)
!isEmpty(APP_SHOW_BUILD_DATE): DEFINES += APP_SHOW_BUILD_DATE

include(../../athleticplugin.pri)

msvc: QMAKE_CXXFLAGS += -wd4251 -wd4290 -wd4250

SOURCES += \
	coreplugin.cpp \

HEADERS += \
	coreplugin.h \
	core_global.h \

RESOURCES += \
	coreplugin.qrc \
