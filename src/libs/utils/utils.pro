include(../../athleticlibrary.pri)

DEFINES += APP_UTILS_LIB

QT += gui network

SOURCES += \
	hostosinfo.cpp \
	fileutils.cpp \
	savefile.cpp \
	systemid.cpp \
	utils.cpp \
	emailvalidator.cpp \

HEADERS += \
	hostosinfo.h \
	osspecificaspects.h \
	savefile.h \
	fileutils.h \
	systemid.h \
	utils_global.h \
	emailvalidator.h \
	systemid_p.h

!macx {
	win32 {
	   SOURCES += systemid_win.cpp
	} else {
	   SOURCES += systemid_unix.cpp
	}
} else {
	SOURCES += systemid_mac.cpp
}

osx {
	HEADERS += \
		fileutils_mac.h
	OBJECTIVE_SOURCES += \
		fileutils_mac.mm
	LIBS += -framework Foundation
}

DEFINES += APP_REL_TOOLS_PATH=$$shell_quote(\"$$relative_path($$APP_LIBEXEC_PATH, $$APP_BIN_PATH)\")
