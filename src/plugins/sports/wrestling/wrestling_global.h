#ifndef WRESTLING_GLOBAL_H
#define WRESTLING_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(WRESTLING_LIBRARY)
#  define WRESTLING_EXPORT Q_DECL_EXPORT
#else
#  define WRESTLING_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(wrestlingLog)

#endif // WRESTLING_GLOBAL_H
