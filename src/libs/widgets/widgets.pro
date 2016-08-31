include(../../athleticlibrary.pri)

DEFINES += APP_WIDGETS_LIB

QT += gui network

SOURCES += \
    filechooser.cpp \
    widgets.cpp

HEADERS += \
    filechooser.h \
    widgets_global.h \

DEFINES += APP_REL_TOOLS_PATH=$$shell_quote(\"$$relative_path($$APP_LIBEXEC_PATH, $$APP_BIN_PATH)\")
