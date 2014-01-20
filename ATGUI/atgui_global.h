#ifndef ATGUI_GLOBAL_H
#define ATGUI_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef ATGUI_LIB
# define ATGUI_EXPORT Q_DECL_EXPORT
#else
# define ATGUI_EXPORT Q_DECL_IMPORT
#endif

#endif // ATGUI_GLOBAL_H
