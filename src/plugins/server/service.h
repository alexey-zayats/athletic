#ifndef SERVICE_H
#define SERVICE_H

#include <QDateTime>
#include <QMap>
#include <QObject>
#include <QPair>
#include <QRegExp>
#include <QString>

#include "server_global.h"

namespace Server
{
    class Request;
    /** Interface exposing public slots to the web.
     *
     * urlMap() should be overridden to provide a regex->slot mapping;
     * dispatchRequest() will call the first slot in this map with a
     * matching regex.
     *
     * QString parameters to the slots are supported, as long as the number
     * of parameters is the same as the number of captured subexpressions in
     * expression in the map.
     *
     * Service subclasses should be used in conjunction with a ServiceMapper
     * subclass, providing an easy way to map /foo/bar/baz to Foo::bar(baz)
     * (for example).
     *
     * These objects are semi-persistent, in that one will be created per
     * thread (which may be more than one request) - there is no guarantee
     * that all requests in the same session will go to the same instance of
     * your subclass.
     *
     * Service also maintains two caches:
     *  - A file cache
     *  - A request cache
     *
     * The file cache caches data from the readFile call.
     *
     * The request cache caches urlFragment -> result pairs. This is only
     * used if a slot calls cacheThisRequest(). You can expire a cache
     * entry by reimplementing isExpired.
     *
     * These caches are currently per-process. In the future, they may be
     * shared between processes via memcached or similar. They default to a
     * maximum size of 10MiB.
     *
     * @see ServiceMapper
     * @ingroup services
     */
    class SERVER_EXPORT Service : public QObject
    {
        Q_OBJECT
        public:
            Service(QObject* parent);

            /// Destructor.
            virtual ~Service();
        public slots:
            /** Call a slot based on the current URL.
             *
             * The result may be cached.
             *
             * The mapping depends on what urlMap() returns.
             *
             * If you want to override this function, see
             * dispatchUncachedRequest()
             *
             * @see dispatchUncachedRequest()
             * @see urlMap()
             */
            void respond(Server::Request* request);
        protected:
            /** Call a slot based on an URL fragment.
             *
             * @see respond()
             */
            virtual void dispatchUncachedRequest(const QByteArray& suffix);

            /// A pointer to the current request.
            Request* request() const;

            /** A map of regular expressions to slots.
             *
             * This is a pair of regularExpressionString ->
             * publicSlot - for example:
             * 	myUrlMap.insert("(.+)", SLOT(foo(QString)));
             *
             * @see urlMap()
             */
            class SERVER_EXPORT UrlMap : public QList<QPair<QString, const char*> >
            {
                public:
                    void append(const QString& regexp, const char* slot);
            };

            /** Next time a similar request is made, return the same data.
             *
             * To have effect, this must be called before any data
             * is written to the output device.
             *
             * @see isExpired()
             */
            void cacheThisRequest();

            /** Return a mapping of regular expressions to slots.
             *
             * This is used to map requests.
             *
             * @see dispatchRequest()
             * @see UrlMap
             */
            virtual UrlMap urlMap() const = 0;

            /** Whether or not a cached result for the given urlFragment is still valid.
             *
             * @param urlFragment is the URL fragment for the request.
             * @param generated is the time the cached version was generated.
             *
             * If you have content that may change, but you wish to
             * cache the results, you'll want to reimplement this
             * function, and make your slots call cacheThisRequest().
             *
             * If the cached result is invalid, you should return
             * true, and refresh any internal caches in your service.
             *
             * @see cacheThisRequest()
             * @see requestCacheSize()
             * @see setRequestCacheSize()
             * @returns false
             */
            virtual bool isExpired(const QString& urlFragment, const QDateTime& generated);
        private:
            class Private;
            Private* d;
    };
}
#endif // SERVICE_H
