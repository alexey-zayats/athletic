include($$replace(_PRO_FILE_PWD_, ([^/]+$), \\1/\\1_dependencies.pri))
TARGET = $$APP_LIB_NAME

include(../athletic.pri)

win32 {
	DLLDESTDIR = $$APP_BIN_PATH
}

DESTDIR = $$APP_LIBRARY_PATH
#CONFIG += plugin plugin_with_soname
QMAKE_LFLAGS_SONAME = -Wl,-install_name,@rpath/../$$APP_LIBRARY_BASENAME/

include(rpath.pri)

TARGET = $$qtLibraryName($$TARGET)

TEMPLATE = lib
CONFIG += shared dll

contains(QT_CONFIG, reduce_exports):CONFIG += hide_symbols

!macx {
	win32 {
		dlltarget.path = $$INSTALL_BIN_PATH
		INSTALLS += dlltarget
	} else {
		target.path = $$INSTALL_LIBRARY_PATH
		INSTALLS += target
	}
}
