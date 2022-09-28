#ifndef DBDYN_GLOBAL_H
#define DBDYN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DBDYN_LIBRARY)
#  define DBDYN_EXPORT Q_DECL_EXPORT
#else
#  define DBDYN_EXPORT Q_DECL_IMPORT
#endif

#endif // DBDYN_GLOBAL_H
