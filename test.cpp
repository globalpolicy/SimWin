#include "stdafx.h"
#include "simwin.h"
#include <stdio.h>

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

HWND formhwnd = nullptr;
HWND btnhwnd = nullptr;
HWND textboxhwnd = nullptr;
HWND checkboxhwnd = nullptr;
HWND btntogglecheckhwnd = nullptr;
HWND form2hwnd = nullptr;
HWND form2btnhwnd = nullptr;
HWND form2textboxhwnd = nullptr;

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

void form2minimized()
{
	MessageBox(0, _T("Minimized!"), _T("Info"), 0);
}

void form2resized()
{
	FormSize formsize = GetFormSize(form2hwnd);
	TCHAR showthis[50];
	swprintf_s(showthis, 30, _T("Height = %d\r\nWidth = %d"), formsize.Height, formsize.Width);
	SetTextboxText(form2textboxhwnd, showthis);
}

void form2maximized()
{
	long textboxlength = wcslen(GetTextboxText(form2textboxhwnd));
	TCHAR *showthis = (TCHAR*)calloc(textboxlength + 20, sizeof(TCHAR));
	swprintf_s(showthis, textboxlength + 20, _T("%s\r\n%s"), GetTextboxText(form2textboxhwnd), _T("Maximized!"));
	SetTextboxText(form2textboxhwnd, showthis);
}

void onclickform2btn()
{
	if (GetFormSize(form2hwnd).Height > 550)
	{
		SetFormSize(form2hwnd, { 300,550 });
	}
	else
	{
		SetFormSize(form2hwnd, { 400,600 });
	}

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
	}
	form2hwnd = CreateForm(_T("Another title"), _T("SimwinForm2"), 500, 550);
	if (form2hwnd)
	{
		form2textboxhwnd = AddTextbox(form2hwnd, _T("Info here"), 50, 20, 200, 400, false, true, true);
		if (form2textboxhwnd)
		{
			AddFormEvent(form2hwnd, FORMEVENT_MINIMIZED, &form2minimized);
			AddFormEvent(form2hwnd, FORMEVENT_MAXIMIZED, &form2maximized);
			AddFormEvent(form2hwnd, FORMEVENT_RESIZE, &form2resized);
			form2btnhwnd = AddButton(form2hwnd, _T("Toggle size"), 50, 450, 70, 30);
			if (form2btnhwnd)
			{
				AddButtonEvent(form2btnhwnd, BUTTONEVENT_LCLICK, &onclickform2btn);
			}
		}


	}
	Engage();
}

