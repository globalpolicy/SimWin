#include <windows.h>
#include <tchar.h>
#include "simwin.h"

void BtnOkClick()
{
    MessageBox(0,_T("Ok"),_T(":D"),0);
}

void BtnCancelClick()
{
    MessageBox(0,_T("Cancel"),_T(";)"),0);
}

int main()
{
    HWND hwnd = CreateForm(_T("Simwin Form"),_T("Class1"),500,300);
    HWND hwndbtnOk = AddButton(hwnd, _T("Ok"), 50, 10, 100, 20);
    AddButtonEvent(hwndbtnOk,LCLICK,&BtnOkClick);
    HWND hwndbtnCancel = AddButton(hwnd, _T("Cancel"), 50, 30, 50, 20);
    AddButtonEvent(hwndbtnCancel,LCLICK,&BtnCancelClick);
    Engage();
}
