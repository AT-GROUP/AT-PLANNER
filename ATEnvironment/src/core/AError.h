#ifndef ATEnvironment_USError_h
#define ATEnvironment_USError_h

/*
Class defines error with it's own errorcode and message.
*/

enum
{
	US_ERROR_FILE_NOT_FOUND,
	US_ERROR_FILE_UNKOWN_FORMAT,
	US_ERROR_COMMAND_NOT_FOUND,
	US_ERROR_PRESENTATION_NOT_FOUND,
	US_ERROR_INVALID_XML,
	US_ERROR_NOT_ENOUGH_PARAMETERS,
	US_ERROR_NODE_NOT_FOUND,
	US_ERROR_XML_NODE_NOT_FOUND,
	US_ERROR_XML_ATTRIBUTE_NOT_FOUND,
	US_ERROR_INVALID_FILE,
	US_ERROR_INVALID_SYNTAX,
	US_ERROR_ZERO_POINTER,
	US_ERROR_RENDERER_FAILURE,
	US_ERROR_INPUT_SYSTEM_FAILURE,
	US_ERROR_EXCEPTION_CAUGHT,
	US_ERROR_INTERNAL,
	US_ERROR_NOT_FOUND,
	US_ERROR_FILE_OLD_FORMAT,
	US_ERROR_UNKNOWN,
	US_ERROR_OK	//If everything is OK
};

class USError
{
public:
	/*
	Simple constructor. If no message is specifies - default
	text will be returned on request.
	*/
	USError(int error_code = US_ERROR_OK, const char * text = 0);
	USError(const USError & err);
	~USError();
	USError& operator=(const USError& rhs);
	USError operator&&(const USError& rhs);

	const char * text() const;
	int code() const;

	/*
	Returns true, if no error.
	*/
	bool OK() const;

	static void criticalErrorOccured(USError error);
private:
	static void criticalErrorOccured(const char * text);

	char * m_pText;
	int mErrorCode;
};

#endif
