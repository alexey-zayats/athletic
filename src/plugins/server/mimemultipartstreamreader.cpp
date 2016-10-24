#include "mimemultipartstreamreader.h"
#include "mimemultipartstreamreader_private.h"
#include "mimepartiodevice.h"

#include <QDebug>

namespace Server
{

    MimeMultipartStreamReader::MimeMultipartStreamReader(QIODevice* device, const QByteArray& boundary)
    : d(new Private(device, boundary))
    {
    }

    MimeMultipartStreamReader::~MimeMultipartStreamReader()
    {
        delete d;
    }

    bool MimeMultipartStreamReader::atEnd() const
    {
        return d->m_device->atEnd() || tokenType() == EndDocument || tokenType() == Invalid;
    }

    MimeMultipartStreamReader::TokenType MimeMultipartStreamReader::tokenType() const
    {
        return d->m_tokenType;
    }

    QString MimeMultipartStreamReader::headerName() const
    {
        return d->m_headerName;
    }

    QString MimeMultipartStreamReader::headerValue() const
    {
        return d->m_headerValue;
    }

    QIODevice* MimeMultipartStreamReader::content() const {
        return d->m_content;
    }

    QIODevice* MimeMultipartStreamReader::device() const
    {
        return d->m_device;
    }

    MimeMultipartStreamReader::TokenType MimeMultipartStreamReader::readNext()
    {
        d->m_headerName.clear();
        d->m_headerValue.clear();

        const QByteArray boundaryPattern("--" + d->m_boundary);

//        switch(tokenType()) {

//        case StartDocument:
//            const QByteArray contents = device()->read(boundaryPattern.length());
//            if ( boundaryPattern == contents ) {
//                d->m_tokenType = StartPart;
//                qDebug() << device()->readLine(); // read '\r' '\n' chars
//            } else {
//                d->m_tokenType = Invalid;
//            }
//        case StartPart:
//            const QByteArray line = device()->readLine();

//        case PartHeader:
//            const QByteArray line = device()->readLine();
//            if(line.isEmpty())
//            {
//                d->m_content = new MimePartIODevice(device(), d->m_boundary);
//                d->m_content->open(QIODevice::ReadOnly);
//            }
//            else
//            {
//                const int splitPoint = line.indexOf(": ");
//                Q_ASSERT(splitPoint != -1);
//                if(splitPoint == -1)
//                {
//                    d->m_tokenType = Invalid;
//                    break;
//                }

//                ///@todo: encoded-word
//                d->m_headerName = QString::fromLocal8Bit(line.left(splitPoint));
//                d->m_headerValue = QString::fromLocal8Bit(line.mid(splitPoint + 1));
//            }
//            break;
//        case PartContent:
//        case EndPart:
//            break;
//        case EndDocument:
//            break;
//        case Invalid:
//        default:
//            break;


//            case IgnoredContent:
//            case PartContent:
//                Q_ASSERT(d->m_content->isOpen());
//                d->m_content->readAll();
//                delete d->m_content;
//                d->m_tokenType = EndPart;
//                break;
//            case EndPart:
//                {
//                    const QByteArray pattern("--" + d->m_boundary);
//                    const QByteArray contents = device()->read(pattern.length());
//                    const bool matches = pattern == contents;
//                    if(matches)
//                    {
//                        const QByteArray peeked = device()->peek(2);
//                        if(peeked[0] == '-' && peeked[1] == '-')
//                        {
//                            d->m_tokenType = EndDocument;
//                        }
//                        else
//                        {
//                            d->m_tokenType = Invalid;
//                        }
//                        device()->readLine();
//                        break;
//                    }
//                    else
//                    {
//                        d->m_tokenType = Invalid;
//                    }
//                }
//                break;
//            case StartPart:
//                d->m_tokenType = PartHeader;
//                break;
//            case PartHeader:
//                {

//                }
//                break;
//            default:
//                d->m_tokenType = Invalid;
//                break;
//        }
        return tokenType();
    }
};
