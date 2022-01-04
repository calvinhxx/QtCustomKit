#ifndef KITS_GLOBAL_H
#define KITS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(KITS_LIBRARY)
#  define KITS_EXPORT Q_DECL_EXPORT
#else
#  define KITS_EXPORT Q_DECL_IMPORT
#endif

#endif // KITS_GLOBAL_H
