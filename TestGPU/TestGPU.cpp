// TestGPU.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "iface.h"
#include "idkit.h"

#define BUFFER_LENGTH	1024
#define CHAR_LENGTH		256

using namespace std;

string messageError = "OK IFACE";
int errorCode;

string GetMessageError(int errorCode) {	
	char errorBuffer[BUFFER_LENGTH];
	char msg[CHAR_LENGTH];
	string msgError;	
	

	errorCode = IFACE_GetErrorMessage(errorCode,
		BUFFER_LENGTH, errorBuffer);
	if (errorCode == IFACE_OK)
	{
		sprintf_s(msg, "Error occurs! %s (code: %d)\n", errorBuffer, errorCode);
		msgError = msg;
	}
	
	return msgError;

}

bool InitParamsGraphicProcessor() {	
	errorCode = IFACE_SetParam(nullptr,
		IFACE_PARAMETER_GLOBAL_GPU_ENABLED, "true");
	if (errorCode == IFACE_OK) {
		errorCode = IFACE_SetParam(nullptr,
			IFACE_PARAMETER_GLOBAL_GPU_DEVICE_ID, "0");
		if (errorCode != IFACE_OK) {
			messageError = GetMessageError(errorCode);			
			return false;
		}
	}
	else {
		messageError = GetMessageError(errorCode);
		return false;
	}
	return true;
}

void InitLibrary() {
	
	errorCode = IFACE_Init();
	if (errorCode != IFACE_OK) {
		messageError = GetMessageError(errorCode);
	}
	// Comment and it works, add IFace.dll and throw GPU error.
	errorCode = IEngine_InitModule();
	if (errorCode != IENGINE_E_NOERROR) {
		messageError = IEngine_GetErrorMsg(errorCode);
	}	
	
}

int main()
{
	if (InitParamsGraphicProcessor())
	{
		InitLibrary();
	}
    std::cout << messageError.c_str();
}
