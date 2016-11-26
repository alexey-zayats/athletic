#ifndef UNSIGNEDBYTEARRAY_H
#define UNSIGNEDBYTEARRAY_H

#include <QByteArray>

namespace FastCgi
{
    /// @internal Read-only access to a QByteArray as unsigned data.
    class UnsignedByteArray : public QByteArray
    {
        public:
            UnsignedByteArray(const QByteArray&);
            quint8 at(int i) const;
            quint8 operator[](int i) const;
    };
}

#endif // UNSIGNEDBYTEARRAY_H
