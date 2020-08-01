#pragma once
#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024
#include<dinput.h>
#include"CGame.h"
#include"SceneManager.h"


class CKeyEventHandler
{
protected:
	LPDIRECTINPUT8 di;// The DirectInput object
	LPDIRECTINPUTDEVICE8 didv; //The keyboard device

	BYTE keyState[256];
	DIDEVICEOBJECTDATA KeyEvents[KEYBOARD_BUFFER_SIZE];

public:
	virtual void KeyState(BYTE *state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
};


typedef CKeyEventHandler * LPKEYEVENTHANDLER;
class CKeyHandler : public CKeyEventHandler
{
	LPKEYEVENTHANDLER keyHandler;

	static CKeyHandler * _instance;



public:
	int isKeyDown(int KeyCode);
	void ProcessKeyBoard();
	void InitKeyBoard(LPKEYEVENTHANDLER handler);

	CKeyHandler();
	static CKeyHandler * GetInstance();


	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

};