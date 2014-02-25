
#ifndef ATGUI_config_h
#define ATGUI_config_h

#ifdef AT_GUI_EXPORT
	#define AT_GUI_API __declspec(dllexport)
#elif defined(AT_GUI_IMPORT)
	#define AT_GUI_API __declspec(dllimport)
#else
	#define AT_GUI_API 
#endif

#define AT_CORE_IMPORT

#include <ATCore/config.h>

#endif
