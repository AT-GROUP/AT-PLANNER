#ifndef ARCHEDITOR_GLOBAL_H
#define ARCHEDITOR_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef ARCHEDITOR_LIB
# define ARCHEDITOR_EXPORT Q_DECL_EXPORT
#else
# define ARCHEDITOR_EXPORT Q_DECL_IMPORT
#endif

#endif // ARCHEDITOR_GLOBAL_H
