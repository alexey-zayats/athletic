#include "communicationinterface.h"
#include "communicationinterface_worker.h"
#include "requestfactory.h"

#include <QCoreApplication>
#include <QDebug>
#include <QThread>

namespace Server
{
    CommunicationInterface::CommunicationInterface(QObject* parent)
    : QObject(parent)
    {
    }

    CommunicationInterface::~CommunicationInterface()
    {
    }

    bool CommunicationInterface::start(const QString& backend)
    {
        m_extraHeaders.clear();
        m_extraHeaders.insert("X_ATHLETIC_BACKEND", backend.toLatin1());
        m_extraHeaders.insert("X_ATHLETIC_BACKEND_CLASS", metaObject()->className());
        return startBackend(backend);
    }

    void CommunicationInterface::configureHttpd(const QString& backend)
    {
        Q_UNUSED(backend);
    }

    void CommunicationInterface::addWorker(Worker* worker)
    {
        connect(
            worker,
            SIGNAL(newRequest(ClientIODevice*)),
            SLOT(addRequest(ClientIODevice*))
        );
    }

    QStringList CommunicationInterface::detectedBackends() const
    {
        return QStringList();
    }

    bool CommunicationInterface::requiresConfiguration(const QString& backend) const
    {
        Q_UNUSED(backend);
        return true;
    }

    void CommunicationInterface::addRequest(ClientIODevice* device)
    {
        connect(device, SIGNAL(destroyed()), this, SLOT(closeIfFinished()));
        Request* request = RequestFactory::createRequest(device, m_extraHeaders, 0);
        emit newRequest(request);
        if(!request->parent())
        {
            delete request;
        }
    }

    void CommunicationInterface::closeIfFinished()
    {
        if(isFinished())
        {
            QCoreApplication::exit(0);
        }
    }
};
