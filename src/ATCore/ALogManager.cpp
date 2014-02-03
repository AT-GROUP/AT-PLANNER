//
//  USLogManager.cpp
//  UltraSimpleEngine
//
//  Created by Yuri Blokhin on 29.10.12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "ALogManager.h"
#include <stdio.h>
#include <fstream>
#include <sys/stat.h> // for stat and mkdir
#include <vector>

//====================Log manager===============================

ALog::ALog(const std::string & name, const std::string & dir_path)
	:ANamedObject(name), mDirPath(string(dir_path)), mFileName(string(name) + ".txt"), mOutputType(OutputType::None), mStarted(false)
{
}

void ALog::start()
{
	mStarted = true;
}

void ALog::finish()
{
	mStarted = false;
}

void ALog::vprintf(const char * _Format, va_list Arg_list)
{
	FILE * log_file = fopen(filePath().c_str(), "a+");
	//fprintf(log_file, "%s:: ", USTime::getCurrentTime().toString().c_str());
	vfprintf(log_file, _Format, Arg_list);
	fclose(log_file);
}

void ALog::printf(const char * _Format, ...)
{
	FILE * log_file = fopen(filePath().c_str(), "a+");
    if(log_file)
    {
        va_list args;
        va_start(args, _Format);
        vfprintf(log_file, _Format, args);
        va_end(args);
        fclose(log_file);
    }
    else
        std::printf("Error opening log file with path: %s.\n", filePath().c_str());
}

void ALog::setOutputType(ALog::OutputType _type)
{
	mOutputType = _type;
}

ALog::OutputType ALog::outputType()
{
	return mOutputType;
}

bool ALog::started()
{
	return mStarted;
}

const string ALog::filePath()
{
	return mDirPath + "/" + mFileName;
}

void ALog::setDirPath(const std::string & dir_absolute_path)
{
	mDirPath = dir_absolute_path;
}

//==================Log manager=================================
ALogManager::ALogManager()
{
	setDelegate(0);
	setLogOutputType("errors", ALog::OutputType::All);
}

ALogManager::~ALogManager()
{
	for(auto l : mLogs)
	{
		l.second->finish();
		delete l.second;
	}

	mLogs.clear();
}

ALog * ALogManager::logWithName(const std::string & log_name)
{
	ALog * log = mLogs[log_name];
	if(!log)
	{
		//char log_path[2048];
		//sprintf(&log_path[0], "%s/%s.txt", mLogsDirectoryAbs, log_name.c_str());
		
		log = new ALog(log_name.c_str(), mLogsDirectoryAbs);
		log->setOutputType(mDefaultOutputType);
		mLogs[log_name] = log;
		//log->start();
	}
	return log;
}

void ALogManager::log_printf(const std::string & log_name, const char * _Format, ...)
{
	ALog * log = logWithName(log_name);

	if(!log->started())
		log->start();


	va_list args;
	va_start(args, _Format);
	
	if((log->outputType() == ALog::OutputType::FileOnly) || (log->outputType() == ALog::OutputType::All))
	{
		log->vprintf(_Format, args);
	}
	
	if((log->outputType() == ALog::OutputType::ConsoleOnly) || (log->outputType() == ALog::OutputType::All))
	{
		printf("%s: ", log_name.c_str());
        vprintf(_Format, args);
		DELEGATE()->logMessagePrinted(log_name, _Format, args);
	}

	va_end(args);
}

void ALogManager::setLogOutputType(const std::string & log_name, ALog::OutputType output_type)
{
	ALog * log = logWithName(log_name);
	log->setOutputType(output_type);
}

void ALogManager::setDefaultLogOutput(ALog::OutputType default_type)
{
	mDefaultOutputType = default_type;
}

ALogManager * logger_singleton()
{
	return LogManager::singleton();
}


