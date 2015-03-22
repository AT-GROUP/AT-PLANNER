#ifndef KMPZ_GLOBAL_H
#define KMPZ_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef KMPZ_LIB
# define KMPZ_EXPORT Q_DECL_EXPORT
#else
# define KMPZ_EXPORT Q_DECL_IMPORT
#endif

#endif // KMPZ_GLOBAL_H
