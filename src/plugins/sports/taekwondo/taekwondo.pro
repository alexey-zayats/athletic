DEFINES += TAEKWONDO_LIBRARY
QT += \
	network \

include(../../../athleticplugin.pri)

SOURCES += \
	taekwondo.cpp \
	taekwondoicons.cpp \
	taekwondosport.cpp \

HEADERS += \
	taekwondo.h \
	taekwondoicons.h \
	taekwondosport.h \
	taekwondo_global.h \

RESOURCES += \
	taekwondo.qrc \
