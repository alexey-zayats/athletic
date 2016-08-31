
macx {
    QMAKE_LFLAGS += -Wl,-rpath,@loader_path/../$${APP_LIBRARY_BASENAME}/,-rpath,@executable_path/../$${APP_LIBRARY_BASENAME}/
	QMAKE_RPATHDIR =
} else:linux-* {
    QMAKE_LFLAGS += -Wl,-z,origin \'-Wl,-rpath,../$${APP_LIBRARY_BASENAME}/\'
    QMAKE_RPATHDIR =
}
