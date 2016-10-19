#ifndef THREADPOOL_WORKER_H
#define THREADPOOL_WORKER_H
#include "threadpool.h"

#include <QMutex>

namespace Server
{
    /**@internal Worker object for ThreadPool.
     *
     * This queues Runnables, and executes them in
     * the owner thread.
     */
    class ThreadPool::Worker : public QObject
    {
        Q_OBJECT
        public:
            Worker(QObject* parent);
            void enqueue(QRunnable*);
        private slots:
            void flushQueue();
        private:
            QMutex m_queueMutex;
            QQueue<QRunnable*> m_queue;
    };
};
#endif // THREADPOOL_WORKER_H
