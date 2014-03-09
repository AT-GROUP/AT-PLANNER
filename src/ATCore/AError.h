
#ifndef ATCore_AError_h
#define ATCore_AError_h

#include "config.h"
#include "ASingleton.h"
#include <string>
#include <exception>

/*
Class defines error with it's own errorcode and message.
*/

enum ErrorType {
	AT_ERROR_FILE_NOT_FOUND,
	AT_ERROR_FILE_UNKOWN_FORMAT,
	AT_ERROR_COMMAND_NOT_FOUND,
	AT_ERROR_PRESENTATION_NOT_FOUND,
	AT_ERROR_INVALID_XML,
	AT_ERROR_NOT_ENOUGH_PARAMETERS,
	AT_ERROR_NODE_NOT_FOUND,
	AT_ERROR_XML_NODE_NOT_FOUND,
	AT_ERROR_XML_ATTRIBUTE_NOT_FOUND,
	AT_ERROR_INVALID_FILE,
	AT_ERROR_INVALID_SYNTAX,
	AT_ERROR_ZERO_POINTER,
	AT_ERROR_RENDERER_FAILURE,
	AT_ERROR_INPUT_SYSTEM_FAILURE,
	AT_ERROR_EXCEPTION_CAUGHT,
	AT_ERROR_INTERNAL,
	AT_ERROR_NOT_FOUND,
	AT_ERROR_FILE_OLD_FORMAT,
	AT_ERROR_NO_ACTIVE_PROJECT,
	AT_ERROR_PROJECT_DATA,
	AT_ERROR_UNKNOWN,
	AT_ERROR_OK	//If everything is OK
};

class AT_CORE_API AError
{
public:
	/*
	Simple constructor. If no message is specifies - default
	text will be returned on request.
	*/
	AError(int error_code = AT_ERROR_OK, const std::string & text = "");

	const char * text() const;
	int code() const;

	/*
	Returns true, if no error.
	*/
	bool OK() const;

	static void criticalErrorOccured(AError error);
private:
	static void criticalErrorOccured(const char * text);

	std::string mText;
	int mErrorCode;
};

class AT_CORE_API AException : public std::exception
{
public:
	AException(const std::string & msg)
		:exception(), mText(msg)
	{}
    
    virtual const char * what()
    {
        return mText.c_str();
    }
private:
    const std::string mText;
};

class AErrorMessenger
{
public:
	virtual void criticalErrorOccured(const AError & error){};
};

typedef ASingleton<AErrorMessenger> ErrorMessenger;

AT_CORE_API AErrorMessenger * error_messenger();
AT_CORE_API void set_error_messenger(AErrorMessenger * messnger);

#endif
