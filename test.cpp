#include "stdafx.h"
#include "simwin.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

HWND formhwnd = nullptr;
HWND btnhwnd = nullptr;
HWND textboxhwnd = nullptr;

void clicked()
{
	MessageBox(0, _T("Clicked!"), _T(":D"), 0);
}

void textchanged()
{
	MessageBox(0, GetTextboxText(textboxhwnd), _T("You typed"), MB_ICONINFORMATION);
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
			AddButtonEvent(btnhwnd, BUTTONEVENT_LCLICK, &clicked);
		}
		textboxhwnd = AddTextbox(formhwnd, _T("Default text"), 50, 200, 200, 150, false, true, true);
		if (textboxhwnd) {
			AddTextboxEvent(textboxhwnd, TEXTBOXEVENT_TEXTCHANGE, &textchanged);
		}
		Engage();
	}

}
