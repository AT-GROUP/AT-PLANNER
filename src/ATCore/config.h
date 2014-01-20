
#ifndef ATCore_config_h
#define ATCore_config_h

#ifdef AT_CORE_EXPORT
	#define AT_CORE_API __declspec(dllexport)
#elif defined(AT_CORE_IMPORT)
	#define AT_CORE_API __declspec(dllimport)
#else
	#define AT_CORE_API 
#endif

#endif
