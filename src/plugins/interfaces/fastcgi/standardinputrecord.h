#ifndef STANDARD_INPUT_RECORD_H
#define STANDARD_INPUT_RECORD_H

#include <QByteArray>

namespace FastCgi
{
    class RecordHeader;
    /** @internal
     * @brief Class to parse a FastCGI standard input record.
     *
     * These records contain POST data.
     *
     * All this class does is chop off the padding.
     */
    class StandardInputRecord
    {
        public:
            /** Create a StandardInputRecord.
             *
             * @param header is the header for this record.
             * @param data is the data of this record.
             */
            StandardInputRecord(const RecordHeader& header, const QByteArray& data);
            /// The actual POST data in this record.
            QByteArray streamData() const;
        private:
            QByteArray m_streamData;
    };
}

#endif // STANDARD_INPUT_RECORD_H
