#ifndef END_REQUEST_RECORD_H
#define END_REQUEST_RECORD_H

#include <QByteArray>

namespace FastCgi
{
    /** @internal
     * @brief Class providing function to create a FastCGI end-request record.
     *
     * One of these must be sent once a request has been responded to.
     */
    class EndRequestRecord
    {
        public:
            /** Create a FastCGI end-request record.
             *
             * @param requestId is the FastCGI ID for the request
             * 	that has been finished.
             *
             * @returns a FastCGI end-request record in a QByteArray.
             */
            static QByteArray create(quint16 requestId);
    };
}

#endif // END_REQUEST_RECORD_H
