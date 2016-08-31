#ifndef WIDGETS_GLOBAL_H
#define WIDGETS_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(APP_WIDGETS_LIB)
#  define ATHLETIC_WIDGETS_EXPORT Q_DECL_EXPORT
#else
#  define ATHLETIC_WIDGETS_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(widgetsLog)

#endif // WIDGETS_GLOBAL_H
