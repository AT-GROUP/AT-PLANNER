#ifndef DSFEDITOR_GLOBAL_H
#define DSFEDITOR_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef DSFEDITOR_LIB
# define DSFEDITOR_EXPORT Q_DECL_EXPORT
#else
# define DSFEDITOR_EXPORT Q_DECL_IMPORT
#endif

#endif // DSFEDITOR_GLOBAL_H
