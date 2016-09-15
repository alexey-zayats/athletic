#ifndef TABLETENNIS_GLOBAL_H
#define TABLETENNIS_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(TABLETENNIS_LIBRARY)
#  define TABLETENNIS_EXPORT Q_DECL_EXPORT
#else
#  define TABLETENNIS_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(tabletennisLog)

#endif // TABLETENNIS_GLOBAL_H
