#include "debughandler.h"

#include <QByteArray>
#include <QCoreApplication>
#include <QDebug>
#include <QMutex>
#include <QMutexLocker>
#include <QTextStream>

#include <syslog.h>

namespace FastCgi
{
    DebugHandler::DebugHandler(QObject* parent)
        :
            QObject(parent)
    {
        qInstallMessageHandler(syslogHandler);
    }

    void DebugHandler::syslogHandler(QtMsgType type,
                                     const QMessageLogContext &/*context*/,
                                     const QString &message)
    {
        QTextStream err(stderr);
        static QMutex mutex;
        QMutexLocker lock(&mutex);
        QByteArray name = QCoreApplication::applicationName().toUtf8();
        ::openlog(name, LOG_PID, LOG_USER);
        switch(type)
        {
            case QtDebugMsg:
                err << "DEBUG: " << message << endl;
                ::syslog(LOG_DEBUG, "DEBUG: %s", message.toLatin1().constData());
                break;
            case QtWarningMsg:
                err << "WARNING: " << message << endl;
                ::syslog(LOG_WARNING, "WARNING: %s", message.toLatin1().constData());
                break;
            case QtCriticalMsg:
                err << "CRITICAL: " << message << endl;
                ::syslog(LOG_CRIT, "CRITICAL: %s", message.toLatin1().constData());
                break;
            case QtFatalMsg:
                err << "FATAL: " << message << endl;
                ::syslog(LOG_CRIT, "FATAL: %s", message.toLatin1().constData());
                abort();
            default:
                ::syslog(LOG_CRIT, "UNKNOWN: %s", message.toLatin1().constData());
                abort();
        }
        ::closelog();
    }

    DebugHandler::~DebugHandler()
    {
        qInstallMessageHandler(m_oldHandler);
    }
}
