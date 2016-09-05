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
	styledbar.cpp \
	appmainwindow.cpp \
	mainwindow.cpp \
	stringutils.cpp \
	stylehelper.cpp \
	theme/theme.cpp \
	icon.cpp \
	proxyaction.cpp \
	fadingindicator.cpp \
	lineedit.cpp \
	completinglineedit.cpp \
	execmenu.cpp \
	historycompleter.cpp \
	headerviewstretcher.cpp \
	checkablemessagebox.cpp \
	qtcolorbutton.cpp \
	categorysortfiltermodel.cpp \
	itemviews.cpp \
	treemodel.cpp \

HEADERS += \
	hostosinfo.h \
	osspecificaspects.h \
	savefile.h \
	fileutils.h \
	systemid.h \
	utils_global.h \
	emailvalidator.h \
	systemid_p.h \
	styledbar.h \
	appmainwindow.h \
	mainwindow.h \
	stringutils.h \
	algorithm.h \
	stylehelper.h \
	theme/theme.h \
	theme/theme_p.h \
	icon.h \
	proxyaction.h \
	fadingindicator.h \
	lineedit.h \
	completinglineedit.h \
	execmenu.h \
	historycompleter.h \
	utilsicons.h \
	headerviewstretcher.h \
	checkablemessagebox.h \
	qtcolorbutton.h \
	categorysortfiltermodel.h \
	itemviews.h \
	treemodel.h \

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

win32: LIBS += -luser32 -lshell32
win32: LIBS += -liphlpapi -lws2_32
