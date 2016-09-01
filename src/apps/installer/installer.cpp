#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include <installer/installer_version.h>

#include "installer_global.h"
#include "installwizard.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(installer);
    QLoggingCategory::setFilterRules( QLatin1String("athletic.*.debug=true") );

    QApplication app(argc, argv);
    QApplication::setApplicationName( QLatin1String(Core::Constants::APP_NAME_C) );
    QApplication::setApplicationVersion( QLatin1String(Core::Constants::APP_VERSION_C) );

#ifndef QT_NO_TRANSLATION
    QString translatorFileName = QLatin1String("qt_");
    translatorFileName += QLocale::system().name();
    QTranslator *translator = new QTranslator(&app);
    if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        app.installTranslator(translator);
#endif

    InstallWizard wizard;
    wizard.show();
    return app.exec();
}
