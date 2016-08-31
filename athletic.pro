include(athletic.pri)

!minQtVersion(5, 5, 0) {
    message("Cannot build Athletic with Qt version $${QT_VERSION}.")
    error("Use at least Qt 5.5.0.")
}

TEMPLATE=subdirs
SUBDIRS=src
