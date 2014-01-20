#ifndef EDFDEDITOR_GLOBAL_H
#define EDFDEDITOR_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef EDFDEDITOR_LIB
# define EDFDEDITOR_EXPORT Q_DECL_EXPORT
#else
# define EDFDEDITOR_EXPORT Q_DECL_IMPORT
#endif

#endif // EDFDEDITOR_GLOBAL_H
