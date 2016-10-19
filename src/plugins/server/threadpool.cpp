#include "threadpool.h"

#include "threadpool_worker.h"

#include <extensionsystem/pluginmanager.h>\

#include <QDebug>
#include <QSettings>

namespace Server
{
    ThreadPool::ThreadPool(QObject* parent)
    : QObject(parent)
    , m_nextWorker(0)
    , m_threadCount(-1)
    , m_threads(0)
    , m_workers(0)
    {
        QSettings *settings = ExtensionSystem::PluginManager::settings();
        const int threadSetting = settings->value(QLatin1String("Server/numberOfThreads"), -1).toInt();
        if(threadSetting == -1)
        {
            m_threadCount = QThread::idealThreadCount();
        }
        else
        {
            Q_ASSERT(threadSetting > 0);
            m_threadCount = threadSetting;
        }

        Q_ASSERT(m_threadCount > 0);

        m_threads = new QThread*[m_threadCount];
        m_workers = new Worker*[m_threadCount];

        for(int i = 0; i < m_threadCount; ++i)
        {
            QThread* thread = new QThread(this);
            m_threads[i] = thread;
            thread->start();
            Worker* worker = new Worker(0);
            worker->moveToThread(thread);
            m_workers[i] = worker;
        }
    }

    ThreadPool::~ThreadPool()
    {
        for(int i = 0; i < m_threadCount; ++i)
        {
            m_threads[i]->quit();
            m_threads[i]->wait(10000); // 10 seconds
            delete m_threads[i];
            delete m_workers[i];
        }
        delete[] m_workers;
        delete[] m_threads;
    }

    void ThreadPool::start(QRunnable* runnable, QObject* payload)
    {
        Worker* worker = m_workers[m_nextWorker];
        payload->moveToThread(worker->thread());
        worker->enqueue(runnable);
        m_nextWorker = (m_nextWorker + 1) % m_threadCount;
    }
};
