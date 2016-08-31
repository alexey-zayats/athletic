depfile = $$replace(_PRO_FILE_PWD_, ([^/]+$), \\1/\\1_dependencies.pri)
exists($$depfile) {
    include($$depfile)
    isEmpty(APP_PLUGIN_NAME): \
        error("$$basename(depfile) does not define APP_PLUGIN_NAME.")
} else {
    isEmpty(APP_PLUGIN_NAME): \
        error("APP_PLUGIN_NAME is empty. Maybe you meant to create $$basename(depfile)?")
}
TARGET = $$APP_PLUGIN_NAME

plugin_deps = $$APP_PLUGIN_DEPENDS
plugin_test_deps = $$APP_TEST_DEPENDS
plugin_recmds = $$APP_PLUGIN_RECOMMENDS

include(../athletic.pri)

defineReplace(dependencyName) {
    dependencies_file =
    for(dir, APP_PLUGIN_DIRS) {
        exists($$dir/$$1/$${1}_dependencies.pri) {
            dependencies_file = $$dir/$$1/$${1}_dependencies.pri
            break()
        }
    }
    isEmpty(dependencies_file): \
        error("Plugin dependency $$dep not found")
    include($$dependencies_file)
    return($$APP_PLUGIN_NAME)
}

# for substitution in the .json
dependencyList =
for(dep, plugin_deps) {
    dependencyList += "        { \"Name\" : \"$$dependencyName($$dep)\", \"Version\" : \"$$APP_VERSION\" }"
}
for(dep, plugin_recmds) {
    dependencyList += "        { \"Name\" : \"$$dependencyName($$dep)\", \"Version\" : \"$$APP_VERSION\", \"Type\" : \"optional\" }"
}
for(dep, plugin_test_deps) {
    dependencyList += "        { \"Name\" : \"$$dependencyName($$dep)\", \"Version\" : \"$$APP_VERSION\", \"Type\" : \"test\" }"
}
dependencyList = $$join(dependencyList, ",$$escape_expand(\\n)")

dependencyList = "\"Dependencies\" : [$$escape_expand(\\n)$$dependencyList$$escape_expand(\\n)    ]"

isEmpty(USE_USER_DESTDIR) {
    DESTDIR = $$APP_PLUGIN_PATH
} else {
    win32 {
        DESTDIRAPPNAME = "athletic"
        DESTDIRBASE = "$$(LOCALAPPDATA)"
        isEmpty(DESTDIRBASE):DESTDIRBASE="$$(USERPROFILE)\Local Settings\Application Data"
    } else:macx {
        DESTDIRAPPNAME = "Athletic"
        DESTDIRBASE = "$$(HOME)/Library/Application Support"
    } else:unix {
        DESTDIRAPPNAME = "athletic"
        DESTDIRBASE = "$$(XDG_DATA_HOME)"
        isEmpty(DESTDIRBASE):DESTDIRBASE = "$$(HOME)/.local/share/data"
        else:DESTDIRBASE = "$$DESTDIRBASE/data"
    }
    DESTDIR = "$$DESTDIRBASE/AlexeyZayats/$$DESTDIRAPPNAME/plugins/$$APP_VERSION"
}
LIBS += -L$$DESTDIR
INCLUDEPATH += $$OUT_PWD

# copy the plugin spec
isEmpty(TARGET) {
    error("athleticplugin.pri: You must provide a TARGET")
}

PLUGINJSON = $$_PRO_FILE_PWD_/$${TARGET}.json
PLUGINJSON_IN = $${PLUGINJSON}.in
exists($$PLUGINJSON_IN) {
    DISTFILES += $$PLUGINJSON_IN
    QMAKE_SUBSTITUTES += $$PLUGINJSON_IN
    PLUGINJSON = $$OUT_PWD/$${TARGET}.json
} else {
    # need to support that for external plugins
    DISTFILES += $$PLUGINJSON
}

QMAKE_LFLAGS_SONAME = -Wl,-install_name,@rpath/../plugins/

include(rpath.pri)

contains(QT_CONFIG, reduce_exports):CONFIG += hide_symbols

TEMPLATE = lib
CONFIG += plugin plugin_with_soname
linux*:QMAKE_LFLAGS += $$QMAKE_LFLAGS_NOUNDEF

!macx {
    target.path = $$INSTALL_PLUGIN_PATH
    INSTALLS += target
}

TARGET = $$qtLibraryName($$TARGET)
