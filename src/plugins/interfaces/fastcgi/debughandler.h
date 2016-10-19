#ifndef DEBUG_HANDLER_H
#define DEBUG_HANDLER_H

#include <QByteArray>
#include <QObject>
#include <QtGlobal>

namespace FastCgi
{
    /** @internal
     * @brief Class for redirecting qDebug, qFatal, and so on to somewhere useful.
     *
     * This redirects to syslog, as required by the FastCGI spec.
     */
    class DebugHandler : public QObject
    {
        public:
            /** Start redirecting messages.
             *
             * Also opens syslog for this process.
             */
            DebugHandler(QObject* parent = NULL);
            /** Stop redirecting messages.
             *
             * Also closes sylog for this process.
             */
            ~DebugHandler();
        private:
            /// Send the specified message to syslog.
            static void syslogHandler(QtMsgType type, const QMessageLogContext &context, const QString &message);

            /// The old Qt message handler.
            QtMessageHandler m_oldHandler;
    };
}

#endif // DEBUG_HANDLER_H
