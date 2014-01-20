#include "AError.h"
#include <string>

AError::AError(int error_code, const std::string & text)
	:mText(text), mErrorCode(error_code)
{
}

const char * AError::text() const
{
	if(mText != "")
	{
		return mText.c_str();
	}
	else
	{
		switch(mErrorCode)
		{
		case AT_ERROR_FILE_NOT_FOUND:
			return "File not found.";
			break;
		case AT_ERROR_OK:
			return "No error.";
			break;
		case AT_ERROR_INVALID_XML:
			return "Invalid XML.";
			break;
		case AT_ERROR_COMMAND_NOT_FOUND:
			return "Command not found.";
			break;
		case AT_ERROR_NOT_ENOUGH_PARAMETERS:
			return "Not enough parameters.";
			break;
		case AT_ERROR_PRESENTATION_NOT_FOUND:
			return "Presentation not found.";
			break;
		case AT_ERROR_RENDERER_FAILURE:
			return "Renderer initializtion failed.";
			break;
		case AT_ERROR_INVALID_FILE:
			return "Invalid XML schema.";
			break;
		default:
			return "Unknown error.";
			break;
		};
	}
}

int AError::code() const
{
	return mErrorCode;
}

bool AError::OK() const
{
	return (mErrorCode == AT_ERROR_OK);
}

void AError::criticalErrorOccured(const char * text)
{/*
	wstring wstr = get_wstring(string(text));
#ifdef US_OS_WIN
	int msgboxID = MessageBox(NULL, (LPCWSTR)wstr.c_str(), (LPCWSTR)L"Critical Error", MB_ICONERROR | MB_OK);
#endif*/
}

void AError::criticalErrorOccured(AError error)
{
	/*char error_code[256];
	sprintf(error_code, "%d", error.code());

	string error_text = "Error " + string(error_code) + "." + string(error.text());

	LOG_PRINT("errors", error_text.c_str());

	criticalErrorOccured(error_text.c_str());*/
}
