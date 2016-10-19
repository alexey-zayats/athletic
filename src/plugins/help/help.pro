QT += help network printsupport sql

!isEmpty(QT.htmlviewwidgets.name): QT += htmlviewwidgets htmlview
else:!isEmpty(QT.webkitwidgets.name): QT += webkitwidgets webkit
else: DEFINES += QT_NO_WEBKIT

INCLUDEPATH += $$PWD

include(../../athleticplugin.pri)

DEFINES += \
	QT_CLUCENE_SUPPORT \
	HELP_LIBRARY

HEADERS += \
	centralwidget.h \
	docsettingspage.h \
	filtersettingspage.h \
	generalsettingspage.h \
	helpconstants.h \
	helpfindsupport.h \
	helpindexfilter.h \
	localhelpmanager.h \
	helpmode.h \
	helpplugin.h \
	helpviewer.h \
	openpagesmanager.h \
	openpagesmodel.h \
	openpagesswitcher.h \
	openpageswidget.h \
	remotehelpfilter.h \
	searchwidget.h \
	xbelsupport.h \
	qtwebkithelpviewer.h \
	textbrowserhelpviewer.h \
	helpwidget.h \
	bookmarkmanager.h \
	contentwindow.h \
	filternamedialog.h \
	indexwindow.h \
	topicchooser.h \
	helpicons.h \

#	searchtaskhandler.h \

SOURCES += \
	centralwidget.cpp \
	docsettingspage.cpp \
	filtersettingspage.cpp \
	generalsettingspage.cpp \
	helpfindsupport.cpp \
	helpindexfilter.cpp \
	localhelpmanager.cpp \
	helpmode.cpp \
	helpplugin.cpp \
	helpviewer.cpp \
	openpagesmanager.cpp \
	openpagesmodel.cpp \
	openpagesswitcher.cpp \
	openpageswidget.cpp \
	remotehelpfilter.cpp \
	searchwidget.cpp \
	xbelsupport.cpp \
	qtwebkithelpviewer.cpp \
	textbrowserhelpviewer.cpp \
	helpwidget.cpp \
	bookmarkmanager.cpp \
	contentwindow.cpp \
	filternamedialog.cpp \
	indexwindow.cpp \
	topicchooser.cpp \

#	searchtaskhandler.cpp \

FORMS += docsettingspage.ui \
	filtersettingspage.ui \
	generalsettingspage.ui \
	remotehelpfilter.ui \
	bookmarkdialog.ui \
	filternamedialog.ui \
	topicchooser.ui

QT += webenginewidgets widgets

HEADERS += webenginehelpviewer.h
SOURCES += webenginehelpviewer.cpp
DEFINES += WEBENGINE_HELPVIEWER

osx {
	DEFINES += MAC_NATIVE_HELPVIEWER
	QT += macextras
	HEADERS += macwebkithelpviewer.h
	OBJECTIVE_SOURCES += macwebkithelpviewer.mm
	LIBS += -framework WebKit -framework AppKit

	!isEmpty(USE_QUICK_WIDGET) {
		DEFINES += MAC_NATIVE_HELPVIEWER_DEFAULT
	}
}

RESOURCES += help.qrc
