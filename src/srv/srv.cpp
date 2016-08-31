#include <QtCore/QCoreApplication>
#include <QDebug>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName( QLatin1String("Athletcic.Srv") );
    QCoreApplication::setApplicationVersion( QLatin1String("0.1") );

//    Server server(threads);

//    if (!server.listen(QHostAddress::LocalHost, port)) {
//        qCritical() << server.errorString();
//        exit(1);
//    }

//    qDebug() << "Run server on" << port << "threads" << threads;
    return app.exec();
}
