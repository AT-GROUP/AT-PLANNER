#include "AError.h"
#include <string>

USError::USError(int error_code, const char * text)
	:m_pText(0), mErrorCode(error_code)
{
	if(text)
	{
		m_pText = new char[strlen(text) + 1];
		strcpy(m_pText, text);
	}
}

USError::USError(const USError & err)
{
	mErrorCode = err.mErrorCode;

	if(err.m_pText)
	{
		m_pText = new char[strlen(err.m_pText) + 1];
		strcpy(m_pText, err.m_pText);
	}
	else
		m_pText = 0;
}

USError::~USError()
{
	if(m_pText)
		delete m_pText;
}

USError& USError::operator=(const USError& rhs)
{
	mErrorCode = rhs.mErrorCode;

	if(m_pText)
		delete m_pText;

	if(rhs.m_pText)
	{
		m_pText = new char[strlen(rhs.m_pText) + 1];
		strcpy(m_pText, rhs.m_pText);
	}

	return *this;
}

USError USError::operator&&(const USError& rhs)
{
	USError result;

	if(mErrorCode == rhs.mErrorCode)
		result = *this;
	else
	{
		if(mErrorCode != US_ERROR_OK)
			result = *this;
		else
			result = rhs;
	}

	return result;
}

const char * USError::text() const
{
	if(m_pText)
	{
		return m_pText;
	}
	else
	{
		switch(mErrorCode)
		{
		case US_ERROR_FILE_NOT_FOUND:
			return "File not found.";
			break;
		case US_ERROR_OK:
			return "No error.";
			break;
		case US_ERROR_INVALID_XML:
			return "Invalid XML.";
			break;
		case US_ERROR_COMMAND_NOT_FOUND:
			return "Command not found.";
			break;
		case US_ERROR_NOT_ENOUGH_PARAMETERS:
			return "Not enough parameters.";
			break;
		case US_ERROR_PRESENTATION_NOT_FOUND:
			return "Presentation not found.";
			break;
		case US_ERROR_RENDERER_FAILURE:
			return "Renderer initializtion failed.";
			break;
		case US_ERROR_INVALID_FILE:
			return "Invalid XML schema.";
			break;
		default:
			return "Unknown error.";
			break;
		};
	}
}

int USError::code() const
{
	return mErrorCode;
}

bool USError::OK() const
{
	return (mErrorCode == US_ERROR_OK);
}

void USError::criticalErrorOccured(const char * text)
{/*
	wstring wstr = get_wstring(string(text));
#ifdef US_OS_WIN
	int msgboxID = MessageBox(NULL, (LPCWSTR)wstr.c_str(), (LPCWSTR)L"Critical Error", MB_ICONERROR | MB_OK);
#endif*/
}

void USError::criticalErrorOccured(USError error)
{
	/*char error_code[256];
	sprintf(error_code, "%d", error.code());

	string error_text = "Error " + string(error_code) + "." + string(error.text());

	LOG_PRINT("errors", error_text.c_str());

	criticalErrorOccured(error_text.c_str());*/
}
