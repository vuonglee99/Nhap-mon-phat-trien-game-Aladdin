#include"KeyBoard.h"


CKeyHandler * CKeyHandler::_instance = NULL;

int CKeyHandler::isKeyDown(int KeyCode)
{
	return (keyState[KeyCode] & 0x80) > 0;
}


void CKeyHandler::ProcessKeyBoard()
{
	HRESULT result;

	result = didv->GetDeviceState(sizeof(keyState), keyState);

	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv->Acquire();
			if (h == DI_OK)
			{
				//DebugOut(L"[INFO] Keyboard re-acquired!\n");
			}
			else
			{
				return;
			}
		}
		else
		{
			MessageBox(NULL,"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n","Error",MB_OK);
			return;
		}
	}



	SceneManager::GetInstance()->KeyState((BYTE *)&keyState);

	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	result = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), KeyEvents, &dwElements, 0);
	if (FAILED(result))
	{
		MessageBox(NULL, "[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", "Error", MB_OK);
		return;
	}

	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = KeyEvents[i].dwOfs;
		int KeyState = KeyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
		{
			SceneManager::GetInstance()->OnKeyDown(KeyCode);
		}
		else
		{
			SceneManager::GetInstance()->OnKeyUp(KeyCode);
		}
	}


}

void CKeyHandler::InitKeyBoard(LPKEYEVENTHANDLER handler)
{
	HWND hWnd = CGame::GetInstance()->hWnd;
	HRESULT
		result = DirectInput8Create
		(
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&di, NULL
		);
	if (result != DI_OK)
	{
		return;
	}
	result = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);
	if (result != DI_OK)
	{
		return;
	}

	result = didv->SetDataFormat(&c_dfDIKeyboard);
	result = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE;

	result = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	result = didv->Acquire();
	if (result != NULL)
	{
		return;
	}
	this->keyHandler = handler;

}


CKeyHandler::CKeyHandler()
{
	InitKeyBoard(this->keyHandler);
}
CKeyHandler * CKeyHandler::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CKeyHandler();
	}
	return _instance;
}
void CKeyHandler::KeyState(BYTE * state)
{


}
void CKeyHandler::OnKeyDown(int KeyCode)
{

}
void CKeyHandler::OnKeyUp(int KeyCode)
{

}