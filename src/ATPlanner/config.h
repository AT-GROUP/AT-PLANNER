#ifndef ATPLANNER_GLOBAL_H
#define ATPLANNER_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef ATPLANNER_LIB
# define AT_PLANNER_API Q_DECL_EXPORT
#else
# define AT_PLANNER_API Q_DECL_IMPORT
#endif

#endif // ATPLANNER_GLOBAL_H
