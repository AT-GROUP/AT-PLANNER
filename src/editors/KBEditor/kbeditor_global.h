#ifndef KBEDITOR_GLOBAL_H
#define KBEDITOR_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef KBEDITOR_LIB
# define KBEDITOR_EXPORT Q_DECL_EXPORT
#else
# define KBEDITOR_EXPORT Q_DECL_IMPORT
#endif

#endif // KBEDITOR_GLOBAL_H
