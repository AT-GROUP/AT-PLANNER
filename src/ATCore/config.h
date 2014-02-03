
#ifndef ATCore_config_h
#define ATCore_config_h

#if defined(WIN32) || defined(WIN64)
    #define AT_OS_WINDOWS 1
#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #define AT_OS_OSX 1
#else
    #define AT_OS_UNSUPPORTED 1
#endif



#ifdef AT_CORE_EXPORT
	#define AT_CORE_API __declspec(dllexport)
#elif defined(AT_CORE_IMPORT)
	#define AT_CORE_API __declspec(dllimport)
#else
	#define AT_CORE_API 
#endif

#endif
