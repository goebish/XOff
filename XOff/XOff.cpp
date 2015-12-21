/*
 Power Off a wireless XInput Controller when POWEROFF_COMBO buttons are held down for more than 1 second
 Goebish 2013

 This project is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Deviation is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Deviation.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "stdafx.h"
#include "XOff.h"
#include <windows.h>
#include <iostream>
#include "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Include\\XInput.h"

#pragma comment(lib, "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Lib\\x86\\XInput.lib")
#define POWEROFF_COMBO	(WORD)(XINPUT_GAMEPAD_BACK | XINPUT_GAMEPAD_A | XINPUT_GAMEPAD_B | XINPUT_GAMEPAD_X | XINPUT_GAMEPAD_Y)
typedef HRESULT(WINAPI *FnOff)(int);

int APIENTRY _tWinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	HINSTANCE hXInputDLL = LoadLibraryA("XInput1_3.dll");
	if (hXInputDLL == NULL)
		return 1;
	FnOff pOff = FnOff(GetProcAddress(hXInputDLL, reinterpret_cast<char*>(103)));
	if(pOff == NULL)
		return 1;
	for(;;) {
		Sleep(500);
		for (short i = 0; i < XUSER_MAX_COUNT; ++i) {
			XINPUT_STATE state;
			memset(&state, 0, sizeof(XINPUT_STATE));
			if(ERROR_SUCCESS==XInputGetState(i, &state) && state.Gamepad.wButtons==POWEROFF_COMBO) {
				Sleep(1000);
				if(ERROR_SUCCESS==XInputGetState(i, &state) && state.Gamepad.wButtons==POWEROFF_COMBO)
					pOff(i);
			}
		}
	}
	FreeLibrary(hXInputDLL);
	return 0;
}
