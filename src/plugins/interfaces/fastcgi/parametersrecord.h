#ifndef PARAMETERS_RECORD_H
#define PARAMETERS_RECORD_H

#include <server/clientiodevice.h>

namespace FastCgi
{
    class RecordHeader;
    /** @internal
     * @brief Class for reading FastCGI parameter records.
     *
     * These contain the data that is presented in environment variables in
     * CGI.
     */
    class ParametersRecord
    {
        public:
            /** Create a ParametersRecord object.
             *
             * @param header is the header for the current record.
             * @param data is the payload for this record.
             */
            ParametersRecord(const RecordHeader& header, const QByteArray& data);
            /// Whether or not an empty record was given.
            bool isEmpty() const;
            /** The parameters given in this record.
             *
             * @see isEmpty()
             */
            Server::ClientIODevice::HeaderMap parameters() const;
        private:
            Server::ClientIODevice::HeaderMap m_parameters;
    };
}

#endif // PARAMETERS_RECORD_H
