#ifndef TAEKWONDO_GLOBAL_H
#define TAEKWONDO_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(TAEKWONDO_LIBRARY)
#  define TAEKWONDO_EXPORT Q_DECL_EXPORT
#else
#  define TAEKWONDO_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(taekwondoLog)

#endif // TAEKWONDO_GLOBAL_H
