#ifndef GEODATAACCESSOR_GLOBAL_H
#define GEODATAACCESSOR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GEODATAACCESSOR_LIBRARY)
#  define GEODATAACCESSOR_EXPORT Q_DECL_EXPORT
#else
#  define GEODATAACCESSOR_EXPORT Q_DECL_IMPORT
#endif

#endif // GEODATAACCESSOR_GLOBAL_H
