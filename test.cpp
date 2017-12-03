#include "stdafx.h"
#include "simwin.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

HWND formhwnd = nullptr;
HWND btnhwnd = nullptr;
HWND textboxhwnd = nullptr;
HWND checkboxhwnd = nullptr;
HWND btntogglecheckhwnd = nullptr;

void checkandmsg()
{
	if(GetCheckboxState(checkboxhwnd) == CHECKBOXSTATE_CHECKED)
		MessageBox(0, _T("Checked!"), _T(":D"), 0);
	else if(GetCheckboxState(checkboxhwnd) == CHECKBOXSTATE_UNCHECKED)
		MessageBox(0, _T("Unchecked!"), _T(":("), 0);
	else
		MessageBox(0, _T("Indeterminate!"), _T(":|"), 0);

}

void textchanged()
{
	MessageBox(0, GetTextboxText(textboxhwnd), _T("You typed"), MB_ICONINFORMATION);
}

void togglechecked()
{
	if (GetCheckboxState(checkboxhwnd) == CHECKBOXSTATE_CHECKED)
		SetCheckboxState(checkboxhwnd, CHECKBOXSTATE_UNCHECKED);
	else if (GetCheckboxState(checkboxhwnd) == CHECKBOXSTATE_UNCHECKED)
		SetCheckboxState(checkboxhwnd, CHECKBOXSTATE_CHECKED);
}

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	formhwnd = CreateForm(_T("Title"), _T("SimwinForm"), 300, 500);
	if (formhwnd) {
		btnhwnd = AddButton(formhwnd, _T("Ok"), 50, 100, 80, 30);
		if (btnhwnd) {
			AddButtonEvent(btnhwnd, BUTTONEVENT_LCLICK, &checkandmsg);
		}
		textboxhwnd = AddTextbox(formhwnd, _T("Default text"), 50, 200, 200, 150, false, true, true);
		if (textboxhwnd) {
			AddTextboxEvent(textboxhwnd, TEXTBOXEVENT_TEXTCHANGE, &textchanged);
		}
		checkboxhwnd = AddCheckbox(formhwnd, _T("Checkbox1"), 50, 350, 70, 30);
		if (checkboxhwnd){
			AddCheckboxEvent(checkboxhwnd, CHECKBOXEVENT_STATECHANGE, &checkandmsg);
		}
		btntogglecheckhwnd = AddButton(formhwnd, _T("Toggle Checkbox"), 50, 380, 100, 30);
		if (btntogglecheckhwnd) {
			AddButtonEvent(btntogglecheckhwnd, BUTTONEVENT_LCLICK, &togglechecked);
		}
		Engage();
	}

}

