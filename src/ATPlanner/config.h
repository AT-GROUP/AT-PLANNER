#ifndef ATPLANNER_GLOBAL_H
#define ATPLANNER_GLOBAL_H

#include <QtCore/qglobal.h>
/*
#ifdef ATPLANNER_LIB
# define AT_PLANNER_API Q_DECL_EXPORT
#else
# define AT_PLANNER_API Q_DECL_IMPORT
#endif*/

#include <ATCore/config.h>
/*
#ifdef AT_PLANNER_EXPORT
	#define AT_PLANNER_API __declspec(dllexport)
#elif defined(AT_PLANNER_IMPORT)
	#define AT_PLANNER_API __declspec(dllimport)
#else
	#define AT_PLANNER_API 
#endif*/

#ifdef AT_PLANNER_EXPORT
	#define AT_PLANNER_API Q_DECL_EXPORT
#elif defined(AT_PLANNER_IMPORT)
	#define AT_PLANNER_API Q_DECL_IMPORT
#else
	#define AT_PLANNER_API 
#endif

#endif // ATPLANNER_GLOBAL_H
