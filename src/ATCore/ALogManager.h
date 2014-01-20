//
//  USLogManager.h
//  UltraSimpleEngine
//
//  Created by Yuri Blokhin on 29.10.12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//



#ifndef ATCore_ALogManager_h
#define ATCore_ALogManager_h
#include "config.h"
#include "ASingleton.h"
#include "ANamedObject.h"
#include "ADelegatedObject.h"

#include <map>
#include <string>
#include <stdio.h>
#include <stdarg.h>

using namespace std;

#define LOG_PRINT(log_name, ...) logger_singleton()->log_printf(log_name, __VA_ARGS__);

class AT_CORE_API ALog : public ANamedObject
{
public:
	enum class OutputType {None, FileOnly, ConsoleOnly, All};

	ALog(const std::string & name, const std::string & dir_path);
	void start();
	void finish();
	void vprintf(const char * _Format, va_list Arg_list);
	void printf(const char * _Format, ...);
	void setOutputType(OutputType _type);
	OutputType outputType();
	bool started();
	const std::string filePath();
	void setDirPath(const std::string & dir_absolute_path);
private:
	std::string mFileName, mDirPath;
	OutputType mOutputType;
	bool mStarted;
};

class AT_CORE_API ALogManagerDelegate
{
public:
	virtual void logMessagePrinted(const std::string & logName, const char * _Format, va_list Arg_list)=0;
};

class AT_CORE_API ALogManager : public ADelegatedObject<ALogManagerDelegate>
{
public:
	ALogManager();
	~ALogManager();
	ALog * logWithName(const std::string & log_name);
	void log_printf(const std::string & log_name, const char * _Format, ...);
	void setLogOutputType(const std::string & log_name, ALog::OutputType output_type);

	void setDefaultLogOutput(ALog::OutputType default_type);
private:
	map<string, ALog*> mLogs;
	std::string mLogsDirectoryAbs;
	ALog::OutputType mDefaultOutputType;
};

typedef AAutocreateSingleton<ALogManager> LogManager;

AT_CORE_API ALogManager * logger_singleton();

#endif
