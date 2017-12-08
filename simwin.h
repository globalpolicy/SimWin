#pragma once
#include <tchar.h>
#include <windows.h>
#include <shellapi.h>

#pragma region Declarations

#pragma region Form Declarations
#define MAX_FORMS 50
int formsCount = 0;
typedef enum
{
	FORMEVENT_RESIZE,
	FORMEVENT_MINIMIZED,
	FORMEVENT_MAXIMIZED
} FormEventsEnum;
typedef struct
{
	void(*event_proc) ();
} FormEvent;
typedef struct
{
	WNDPROC FormDefaultCallback;
	HWND FormHwnd;
	FormEvent RESIZE;
	FormEvent MINIMIZED;
	FormEvent MAXIMIZED;
} Form;
typedef struct
{
	LONG Width;
	LONG Height;
} FormSize;
Form Forms[MAX_FORMS];
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
HWND CreateForm(const TCHAR *formTitle, const TCHAR *className, int width, int height);
bool AddFormEvent(HWND formHwnd, FormEventsEnum formEvent, void(*Procedure) ());
FormSize GetFormSize(HWND formHwnd);
bool SetFormSize(HWND formHwnd, FormSize toSet);
void Engage(void);
#pragma endregion

#pragma region Button Declarations
#define MAX_BUTTONS 50
int buttonsCount = 0;
typedef enum
{
	BUTTONEVENT_LCLICK
} ButtonEventsEnum;
typedef struct
{
	void(*event_proc) ();
} ButtonEvent;
typedef struct
{
	WNDPROC ButtonDefaultCallback;
	HWND ButtonHwnd;
	ButtonEvent LCLICK;
} Button;
Button Buttons[MAX_BUTTONS];
WNDPROC FindBtnDefaultCallBack(HWND btnHwnd, Button buttons[]); //helper function declaration
LRESULT CALLBACK ButtonProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);
HWND AddButton(HWND parentFormhwnd, const TCHAR *btnCaption, int x, int y, int width, int height);
bool AddButtonEvent(HWND btnHwnd, ButtonEventsEnum btnEvent, void(*Procedure) ());
#pragma endregion

#pragma region Textbox Declarations
#define MAX_TEXTBOXES 50
int textboxesCount = 0;
typedef enum
{
	TEXTBOXEVENT_TEXTCHANGE
} TextboxEventsEnum;
typedef struct
{
	void(*event_proc) ();
} TextboxEvent;
typedef struct
{
	WNDPROC TextboxDefaultCallback;
	HWND TextboxHwnd;
	TextboxEvent TEXTCHANGE;
} Textbox;
Textbox Textboxes[MAX_TEXTBOXES];
WNDPROC FindTextboxDefaultCallBack(HWND textboxHwnd, Textbox textboxes[]);
LRESULT CALLBACK TextboxProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);
HWND AddTextbox(HWND parentFormhwnd, const TCHAR *defText, int x, int y, int width, int height, bool horscroll, bool verscroll, bool multiline);
bool AddTextboxEvent(HWND textboxHwnd, TextboxEventsEnum textboxEvent, void(*Procedure)());
LPTSTR GetTextboxText(HWND textboxHwnd);
bool SetTextboxText(HWND textboxHwnd, TCHAR *text);
#pragma endregion

#pragma region Checkbox Declarations
#define MAX_CHECKBOXES 50
int checkboxesCount = 0;
typedef enum
{
	CHECKBOXEVENT_STATECHANGE
} CheckboxEventsEnum;
typedef enum
{
	CHECKBOXSTATE_CHECKED,
	CHECKBOXSTATE_UNCHECKED,
	CHECKBOXSTATE_INDETERMINATE
} CheckboxStatesEnum;
typedef struct
{
	void(*event_proc) ();
} CheckboxEvent;
typedef struct
{
	WNDPROC CheckboxDefaultCallback;
	HWND CheckboxHwnd;
	CheckboxEvent STATECHANGE;
} Checkbox;
Checkbox Checkboxes[MAX_CHECKBOXES];
WNDPROC FindCheckboxDefaultCallBack(HWND checkboxHwnd, Checkbox checkboxes[]);
LRESULT CALLBACK CheckboxProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);
HWND AddCheckbox(HWND parentFormhwnd, const TCHAR *checkText, int x, int y, int width, int height);
bool AddCheckboxEvent(HWND checkboxHwnd, CheckboxEventsEnum textboxEvent, void(*Procedure)());
CheckboxStatesEnum GetCheckboxState(HWND checkboxHwnd);
void SetCheckboxState(HWND checkboxHwnd, CheckboxStatesEnum state);
#pragma endregion

#pragma region Menu Declarations
#define MAX_MENUITEMS 50
int menuItemsCount = 0;
typedef enum
{
	MENUITEMEVENT_CLICK
} MenuItemEventsEnum;
typedef struct
{
	void(*event_proc) ();
} MenuItemEvent;
typedef struct
{
	int MenuItemId;
	MenuItemEvent CLICK;
} MenuItem;
MenuItem MenuItems[MAX_MENUITEMS];
HMENU AddMainPopupMenu(HWND parentFormhwnd, const TCHAR *menuText);
HMENU AddPopupMenu(HMENU hParentMenu, const TCHAR *menuText);
int AddFinalMenuItem(HMENU hParentMenu, const TCHAR *menuText);
int AddMainMenuItem(HWND parentFormhwnd, const TCHAR *menuText);
bool IsMenuItemChecked(HWND parentFormhwnd, int menuItemID);
void SetMenuItemCheckStatus(HWND parentFormhwnd, int menuItemID, bool checked);
bool AddMenuItemEvent(int menuItemID, MenuItemEventsEnum menuItemEvent, void(*Procedure) ());
#pragma endregion

#pragma region Tray Declarations
#define WM_TRAYMSG WM_USER + 1 // custom defined message for tray events
#define MAX_TRAYICONS 50
int trayIconsCount = 0;
typedef enum
{
	TRAYICONEVENT_LCLICK,
	TRAYICONEVENT_RCLICK,
	TRAYICONEVENT_DBLCLICK
} TrayIconEventsEnum;
typedef struct
{
	void(*event_proc) ();
} TrayIconEvent;
typedef struct
{
	int uniqueID;
	HWND parentFormHwnd;
	TCHAR *toolTipText;
	HMENU trayIconPopupMenu;
	TrayIconEvent LCLICK;
	TrayIconEvent RCLICK;
	TrayIconEvent DBLCLICK;
} TrayIcon; // note : LCLICK and DBLCLICK event handlers are made mutually exclusive - one must be null
typedef enum
{
	TRAYICONBALLOONTYPE_NONE,
	TRAYICONBALLOONTYPE_INFO,
	TRAYICONBALLOONTYPE_WARNING,
	TRAYICONBALLOONTYPE_ERROR
} TrayIconBalloonTypesEnum;
TrayIcon TrayIcons[MAX_TRAYICONS];
#define MAX_TRAYICONMENUITEMS 50
int trayIconMenuItemsCount = 0;
typedef enum
{
	TRAYICONMENUITEMEVENT_CLICK
} TrayIconMenuItemEventsEnum;
typedef struct
{
	void(*event_proc) ();
} TrayIconMenuItemEvent;
typedef struct
{
	int TrayIconMenuItemId;
	HMENU parentMenu;
	TrayIconMenuItemEvent CLICK;
} TrayIconMenuItem;
TrayIconMenuItem TrayIconMenuItems[MAX_TRAYICONMENUITEMS];
int CreateTrayIcon(HWND parentFormhwnd, TCHAR *tooltipText);
bool AddTrayIconEvent(int trayIconID, TrayIconEventsEnum trayIconEvent, void(*Procedure) ());
bool ShowTrayIcon(int trayIconID);
bool HideTrayIcon(int trayIconID);
bool ShowBalloonMessage(int trayIconID, TCHAR *title, TCHAR *msg, TrayIconBalloonTypesEnum balloonInfoType, bool playSound);
bool HideBalloonMessage(int trayIconID);
HMENU CreateTrayIconMainPopupMenu(int trayIconID);
HMENU AddTrayIconPopupMenu(HMENU hParentPopupMenu, TCHAR *menuTxt);
int AddTrayIconPopupMenuItem(HMENU hParentPopupMenu, TCHAR *menuTxt);
bool AddTrayIconPopupMenuItemEvent(int trayIconPopupMenuItemID, TrayIconMenuItemEventsEnum trayIconMenuItemEvent, void(*Procedure) ());
bool ShowTrayIconPopupMenu(int trayIconID);
bool IsTrayIconPopupMenuItemChecked(int trayIconPopupMenuItemID);
void SetTrayIconPopupMenuItemCheckStatus(int trayIconPopupMenuItemID, bool checked);
#pragma endregion


#pragma region Miscellaneous Declarations
bool SetNiceFont(HWND hwnd);
bool StartThread(void(*Procedure)());
void Cleanup();
#pragma endregion

#pragma endregion

#pragma region Definitions

#pragma region Definitions related to Forms

/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)                  /* handle the messages */
	{
	case WM_DESTROY:
		PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
		break;
	case WM_SIZING:
		for (int i = 0; i<formsCount; i++)
		{
			Form form = Forms[i];
			if (form.FormHwnd == hwnd)
			{
				if (form.RESIZE.event_proc) 
					(*form.RESIZE.event_proc) ();	
			}
		}
		break;
	case WM_SIZE:
		for (int i = 0; i<formsCount; i++)
		{
			Form form = Forms[i];
			if (form.FormHwnd == hwnd)
			{
				if (wParam == SIZE_MINIMIZED)
				{
					if (form.MINIMIZED.event_proc)
						(*form.MINIMIZED.event_proc) ();
				}
				else if (wParam == SIZE_MAXIMIZED)
				{
					if (form.MAXIMIZED.event_proc)
						(*form.MAXIMIZED.event_proc) ();
				}
			}
		}
		break;
	case WM_COMMAND:
		for (int i = 0; i < menuItemsCount; i++)
		{
			MenuItem menuitem = MenuItems[i];
			if (menuitem.MenuItemId == LOWORD(wParam))
			{
				if (menuitem.CLICK.event_proc)
					(*menuitem.CLICK.event_proc) ();
			}
		}
		for (int i = 0; i < trayIconMenuItemsCount; i++)
		{
			TrayIconMenuItem trayIconMenuItem = TrayIconMenuItems[i];
			if (trayIconMenuItem.TrayIconMenuItemId == LOWORD(wParam))
			{
				if (trayIconMenuItem.CLICK.event_proc)
					(*trayIconMenuItem.CLICK.event_proc) ();
			}
		}
		break;
	case WM_TRAYMSG:
		for (int i=0;i<trayIconsCount;i++)
		{
			TrayIcon trayIcon = TrayIcons[i];
			if(wParam==trayIcon.uniqueID)
			{
				switch(lParam)
				{
				case WM_LBUTTONDBLCLK:
					if (trayIcon.DBLCLICK.event_proc)
						(*trayIcon.DBLCLICK.event_proc) ();
					break;
				case WM_LBUTTONUP:
					if (trayIcon.LCLICK.event_proc)
						(*trayIcon.LCLICK.event_proc) ();
					break;
				case WM_RBUTTONUP:
					if (trayIcon.RCLICK.event_proc)
						(*trayIcon.RCLICK.event_proc) ();
					break;
				}
			}

		}
		break;
	default:                      /* for messages that we don't deal with */
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

HWND CreateForm(const TCHAR *formTitle, const TCHAR *className, int width, int height)
{
	HINSTANCE hThisInstance = GetModuleHandle(NULL);
	const TCHAR *szClassName = className;


	WNDCLASSEX wincl;        /* Data structure for the windowclass */

							 /* The Window structure */
	wincl.hInstance = hThisInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
	wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
	wincl.cbSize = sizeof(WNDCLASSEX);

	/* Use default icon and mouse-pointer */
	wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;                 /* No menu */
	wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
	wincl.cbWndExtra = 0;                      /* structure or the window instance */
											   /* Use Windows's default colour as the background of the window */
	wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND + 1;

	/* Register the window class, and if it fails quit the program */
	if (RegisterClassEx(&wincl))
	{
		HWND hwnd = CreateWindowEx(
			0,                   /* Extended possibilites for variation */
			szClassName,         /* Classname */
			formTitle,       /* Title Text */
			WS_OVERLAPPEDWINDOW, /* default window */
			CW_USEDEFAULT,       /* Windows decides the position */
			CW_USEDEFAULT,       /* where the window ends up on the screen */
			width,                 /* The programs width */
			height,                 /* and height in pixels */
			HWND_DESKTOP,        /* The window is a child-window to desktop */
			NULL,                /* No menu */
			hThisInstance,       /* Program Instance handler */
			NULL                 /* No Window Creation data */
		);

		Forms[formsCount] = { WindowProcedure, hwnd, NULL, NULL };
		formsCount++;
		ShowWindow(hwnd, SW_NORMAL);
		return hwnd;
	}
}

bool AddFormEvent(HWND formHwnd, FormEventsEnum formEvent, void(*Procedure) ())
{
	for (int i = 0; i<formsCount; i++)
	{
		Form form = Forms[i];
		if (formHwnd == form.FormHwnd)
		{
			switch (formEvent)
			{
			case FORMEVENT_RESIZE:
				Forms[i].RESIZE.event_proc = Procedure;
				return true;
			case FORMEVENT_MINIMIZED:
				Forms[i].MINIMIZED.event_proc = Procedure;
				return true;
			case FORMEVENT_MAXIMIZED:
				Forms[i].MAXIMIZED.event_proc = Procedure;
				return true;
			}
		}
	}
}

FormSize GetFormSize(HWND formHwnd)
{
	RECT *rect = (RECT*)malloc(sizeof(RECT));
	FormSize formsize = { 0,0 };
	if (GetWindowRect(formHwnd, rect))
	{
		formsize.Height = rect->bottom - rect->top;
		formsize.Width = rect->right - rect->left;
	}
	return formsize;
}

bool SetFormSize(HWND formHwnd, FormSize toSet)
{
	return SetWindowPos(formHwnd, NULL, NULL, NULL, toSet.Width, toSet.Height, SWP_NOMOVE);
}

/* Message loop for main window */
void Engage(void)
{
	MSG message;
	BOOL bRet;
	while ((bRet = GetMessage(&message, NULL, 0, 0)) != 0)
	{
		if (bRet != -1)
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
	Cleanup(); // call cleanup functions
}

#pragma endregion

#pragma region Definitions related to Buttons
/* Callback for button */
LRESULT CALLBACK ButtonProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
		// Handle all messages we want to customize:
	case WM_LBUTTONUP:
		for (int i = 0; i<buttonsCount; i++)
		{
			Button button = Buttons[i];
			if (button.ButtonHwnd == hwnd)
			{
				if (button.LCLICK.event_proc)
					(*button.LCLICK.event_proc) ();
			}
		}
	}
	WNDPROC BtnDefaultCallBack = nullptr;
	BtnDefaultCallBack = FindBtnDefaultCallBack(hwnd, Buttons);
	return CallWindowProc(BtnDefaultCallBack, hwnd, Msg, wParam, lParam);
}

HWND AddButton(HWND parentFormhwnd, const TCHAR *btnCaption, int x, int y, int width, int height)
{
	HWND btnHwnd = CreateWindow(
		_T("BUTTON"),  // Predefined class 
		btnCaption,      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_FLAT,  // Styles 
		x,         // x position 
		y,         // y position 
		width,        // Button width
		height,        // Button height
		parentFormhwnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLongPtr(parentFormhwnd, GWLP_HINSTANCE),
		NULL);      // Pointer not needed.

	SetNiceFont(btnHwnd);
	Buttons[buttonsCount] = { (WNDPROC)GetWindowLongPtr(btnHwnd, GWLP_WNDPROC), btnHwnd, NULL };
	LONG_PTR retval = SetWindowLongPtr(btnHwnd, GWLP_WNDPROC, (LONG_PTR)&ButtonProc);
	buttonsCount++;
	return btnHwnd;
}

bool AddButtonEvent(HWND btnHwnd, ButtonEventsEnum btnEvent, void(*Procedure) ())
{
	for (int i = 0; i<buttonsCount; i++)
	{
		Button button = Buttons[i];
		if (btnHwnd == button.ButtonHwnd)
		{
			switch (btnEvent)
			{
			case BUTTONEVENT_LCLICK:
				Buttons[i].LCLICK.event_proc = Procedure;
				return true;
			}
		}
	}
}
#pragma endregion

#pragma region Definitions related to Textboxes
/*Callback for textbox*/
LRESULT CALLBACK TextboxProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
		// Handle all messages we want to customize:
	case WM_CHAR:
		for (int i = 0; i<textboxesCount; i++)
		{
			Textbox textbox = Textboxes[i];
			if (textbox.TextboxHwnd == hwnd)
			{
				if (textbox.TEXTCHANGE.event_proc)
					StartThread(textbox.TEXTCHANGE.event_proc);
			}
		}
	}
	WNDPROC TextboxDefaultCallBack = nullptr;
	TextboxDefaultCallBack = FindTextboxDefaultCallBack(hwnd, Textboxes);
	return CallWindowProc(TextboxDefaultCallBack, hwnd, Msg, wParam, lParam);
}

HWND AddTextbox(HWND parentFormhwnd, const TCHAR *defText, int x, int y, int width, int height, bool horscroll, bool verscroll, bool multiline)
{
	HWND textboxHwnd = CreateWindow(
		_T("EDIT"),  // Predefined class 
		defText,      // Default text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_EX_CLIENTEDGE | (multiline ? ES_MULTILINE : 0x0L) | (horscroll ? WS_HSCROLL : 0x0L) | (verscroll ? WS_VSCROLL : 0x0L),  // Styles 
		x,         // x position 
		y,         // y position 
		width,        // Textbox width
		height,        // Textbox height
		parentFormhwnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLongPtr(parentFormhwnd, GWLP_HINSTANCE),
		NULL);      // Pointer not needed.

	SetNiceFont(textboxHwnd);
	Textboxes[textboxesCount] = { (WNDPROC)GetWindowLongPtr(textboxHwnd, GWLP_WNDPROC), textboxHwnd, NULL };
	LONG_PTR retval = SetWindowLongPtr(textboxHwnd, GWLP_WNDPROC, (LONG_PTR)&TextboxProc);
	textboxesCount++;
	return textboxHwnd;
}

bool AddTextboxEvent(HWND textboxHwnd, TextboxEventsEnum textboxEvent, void(*Procedure)())
{
	for (int i = 0; i<textboxesCount; i++)
	{
		Textbox textbox = Textboxes[i];
		if (textboxHwnd == textbox.TextboxHwnd)
		{
			switch (textboxEvent)
			{
			case TEXTBOXEVENT_TEXTCHANGE:
				Textboxes[i].TEXTCHANGE.event_proc = Procedure;
				return true;
			}
		}
	}
}

LPTSTR GetTextboxText(HWND textboxHwnd)
{
	TCHAR* text;
	int textlength = GetWindowTextLength(textboxHwnd);
	text = (TCHAR*) calloc(textlength, sizeof(TCHAR));
	GetWindowText(textboxHwnd, text, textlength+1);
	return text;
}

bool SetTextboxText(HWND textboxHwnd, TCHAR *text)
{
	return SendMessage(textboxHwnd, WM_SETTEXT, NULL, (LPARAM)text);
}
#pragma endregion

#pragma region Definitions related to Checkboxes
/*Callback for checkbox*/
LRESULT CALLBACK CheckboxProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
		// Handle all messages we want to customize:
	case WM_LBUTTONUP:
		for (int i = 0; i<checkboxesCount; i++)
		{
			Checkbox checkbox = Checkboxes[i];
			if (checkbox.CheckboxHwnd == hwnd)
			{
				if (checkbox.STATECHANGE.event_proc)
					StartThread(checkbox.STATECHANGE.event_proc);
			}
		}
	}
	WNDPROC CheckboxDefaultCallBack = nullptr;
	CheckboxDefaultCallBack = FindCheckboxDefaultCallBack(hwnd, Checkboxes);
	return CallWindowProc(CheckboxDefaultCallBack, hwnd, Msg, wParam, lParam);
}

HWND AddCheckbox(HWND parentFormhwnd, const TCHAR *checkText, int x, int y, int width, int height)
{
	HWND checkboxHwnd = CreateWindow(
		_T("BUTTON"),  // Predefined class 
		checkText,      // Checkbox text 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_VISIBLE | WS_CHILD ,  // Styles 
		x,         // x position 
		y,         // y position 
		width,        // Button width
		height,        // Button height
		parentFormhwnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLongPtr(parentFormhwnd, GWLP_HINSTANCE),
		NULL);      // Pointer not needed.

	SetNiceFont(checkboxHwnd);
	Checkboxes[checkboxesCount] = { (WNDPROC)GetWindowLongPtr(checkboxHwnd, GWLP_WNDPROC), checkboxHwnd, NULL };
	LONG_PTR retval = SetWindowLongPtr(checkboxHwnd, GWLP_WNDPROC, (LONG_PTR)&CheckboxProc);
	checkboxesCount++;
	return checkboxHwnd;
}

bool AddCheckboxEvent(HWND checkboxHwnd, CheckboxEventsEnum checkboxEvent, void(*Procedure)())
{
	for (int i = 0; i<checkboxesCount; i++)
	{
		Checkbox checkbox = Checkboxes[i];
		if (checkboxHwnd == checkbox.CheckboxHwnd)
		{
			switch (checkboxEvent)
			{
			case CHECKBOXEVENT_STATECHANGE:
				Checkboxes[i].STATECHANGE.event_proc = Procedure;
				return true;
			}
		}
	}
}

CheckboxStatesEnum GetCheckboxState(HWND checkboxHwnd)
{
	UINT checkState = SendMessage(checkboxHwnd, BM_GETCHECK, NULL, NULL);
	switch (checkState)
	{
	case BST_CHECKED:
		return CHECKBOXSTATE_CHECKED;
	case BST_UNCHECKED:
		return CHECKBOXSTATE_UNCHECKED;
	default:
		return CHECKBOXSTATE_INDETERMINATE;
	}
}

void SetCheckboxState(HWND checkboxHwnd, CheckboxStatesEnum state)
{
	switch (state)
	{
	case CHECKBOXSTATE_CHECKED:
		SendMessage(checkboxHwnd, BM_SETCHECK, BST_CHECKED, NULL);
		break;
	case CHECKBOXSTATE_UNCHECKED:
		SendMessage(checkboxHwnd, BM_SETCHECK, BST_UNCHECKED, NULL);
		break;
	case CHECKBOXSTATE_INDETERMINATE:
		SendMessage(checkboxHwnd, BM_SETCHECK, BST_INDETERMINATE, NULL);
		break;
	}
}
#pragma endregion

#pragma region Definitions related to Menus
/* Adds/creates a root branching/popup menu much like the standard "File" menu to a given form hwnd and returns its handle */
HMENU AddMainPopupMenu(HWND parentFormhwnd, const TCHAR *menuText)
{
	HMENU hMenu = (GetMenu(parentFormhwnd)) ? (GetMenu(parentFormhwnd)) : (CreateMenu());	// a window will have only one menu, so either retrieve it, or create one if non-existent
	HMENU hSubMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, menuText);
	SetMenu(parentFormhwnd, hMenu);
	return hSubMenu;
}
/* Adds an intermediate branching/popup menu, like the "Open" menu of the File->Open->... menu structure and returns its handle */
HMENU AddPopupMenu(HMENU hParentMenu, const TCHAR *menuText)
{
	HMENU hSubMenu = CreatePopupMenu();
	AppendMenu(hParentMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, menuText);
	return hSubMenu;
}
/* Adds a clickable/actionable menu item to a parent popup menu, like the "Project" of File->New->Project menu structure and returns its unique ID */
// a "menu item" is the last endpoint of a menu route; it can produce WM_COMMAND message when clicked
int AddFinalMenuItem(HMENU hParentMenu, const TCHAR *menuText)
{
	AppendMenu(hParentMenu, MF_STRING, menuItemsCount, menuText);
	MenuItems[menuItemsCount] = { menuItemsCount, NULL };
	menuItemsCount++;
	return (menuItemsCount - 1);
}
/* Adds/creates a clickable/actionable menu item directly on a given form hwnd, like maybe a "Exit" menu upon clicking which, the app exits */
// a "menu item" is the last endpoint of a menu route; it can produce WM_COMMAND message when clicked
int AddMainMenuItem(HWND parentFormhwnd, const TCHAR *menuText)
{
	HMENU hMenu = (GetMenu(parentFormhwnd)) ? (GetMenu(parentFormhwnd)) : (CreateMenu());	// a window will have only one menu, so either retrieve it, or create one if non-existent
	AppendMenu(hMenu, MF_STRING, menuItemsCount, menuText);
	MenuItems[menuItemsCount] = { menuItemsCount, NULL };
	menuItemsCount++;
	SetMenu(parentFormhwnd, hMenu);
	return (menuItemsCount - 1);
}
bool IsMenuItemChecked(HWND parentFormhwnd, int menuItemID)
{
	MENUITEMINFO *menuiteminfo = (MENUITEMINFO*)malloc(sizeof(MENUITEMINFO));
	menuiteminfo->cbSize = sizeof(MENUITEMINFO);
	menuiteminfo->fMask = MIIM_STATE;
	if (GetMenuItemInfo(GetMenu(parentFormhwnd), menuItemID, false, menuiteminfo))
	{
		if (menuiteminfo->fState == MFS_CHECKED)
			return true;
		else if (menuiteminfo->fState == MFS_UNCHECKED)
			return false;
	}
	return false;
}
void SetMenuItemCheckStatus(HWND parentFormhwnd, int menuItemID, bool checked)
{
	CheckMenuItem(GetMenu(parentFormhwnd), menuItemID, MF_BYCOMMAND | (checked)?(MF_CHECKED):(MF_UNCHECKED));
}
bool AddMenuItemEvent(int menuItemID, MenuItemEventsEnum menuItemEvent, void(*Procedure) ())
{
	for (int i = 0; i<menuItemsCount; i++)
	{
		MenuItem menuitem = MenuItems[i];
		if (menuItemID == menuitem.MenuItemId)
		{
			switch (menuItemEvent)
			{
			case MENUITEMEVENT_CLICK:
				MenuItems[i].CLICK.event_proc = Procedure;
				return true;
			}
		}
	}
}
#pragma endregion

#pragma region Definitions related to Tray
/* Creates a new TrayIcon with given tooltip text and returns its unique ID; returns -1 on fail. Note that it doesn't actually display the tray icon */
int CreateTrayIcon(HWND parentFormhwnd, TCHAR *tooltipText)
{
	TrayIcons[trayIconsCount] = { trayIconsCount,parentFormhwnd, tooltipText, NULL, NULL,NULL,NULL };
	trayIconsCount++;
	return (trayIconsCount - 1);
}

/* Assigns an event handler to a tray icon specified by trayIconID
 * Note : LCLICK and DBLCLICK events are made mutually exclusive - one must be null; whichever is assigned later overrides the one assigned before
 */
bool AddTrayIconEvent(int trayIconID, TrayIconEventsEnum trayIconEvent, void (*Procedure) ())
{
	for (int i = 0; i < trayIconsCount; i++)
	{
		TrayIcon trayIcon = TrayIcons[i];
		if (trayIcon.uniqueID == trayIconID)
		{
			switch (trayIconEvent)
			{
			case TRAYICONEVENT_LCLICK:
				TrayIcons[i].LCLICK.event_proc = Procedure;
				TrayIcons[i].DBLCLICK.event_proc = nullptr; // nullify the event handler for double click event
				return true;
			case TRAYICONEVENT_RCLICK:
				TrayIcons[i].RCLICK.event_proc = Procedure;
				return true;
			case TRAYICONEVENT_DBLCLICK:
				TrayIcons[i].DBLCLICK.event_proc = Procedure;
				TrayIcons[i].LCLICK.event_proc = nullptr; // nullify the event handler for single left click event
				return true;
			}
		}
	}
}

/* Displays the tray icon specified by trayIconID in the system notification area */
bool ShowTrayIcon(int trayIconID)
{
	NOTIFYICONDATA *ndata;
	ndata = (NOTIFYICONDATA*)malloc(sizeof(NOTIFYICONDATA));
	ndata->cbSize = sizeof(NOTIFYICONDATA);
	ndata->uVersion = NOTIFYICON_VERSION;
	ndata->uFlags = NIF_TIP | NIF_ICON | NIF_MESSAGE;
	ndata->uCallbackMessage = WM_TRAYMSG;
	ndata->hIcon = LoadIcon(NULL, IDI_APPLICATION);
	for (int i = 0; i < trayIconsCount; i++)
	{
		TrayIcon trayIcon = TrayIcons[i];
		if (trayIcon.uniqueID == trayIconID)
		{
			ndata->uID = trayIcon.uniqueID;
			ndata->hWnd = trayIcon.parentFormHwnd;
			wcscpy_s(ndata->szTip, trayIcon.toolTipText);
			return Shell_NotifyIcon(NIM_ADD, ndata);
		}
	}
}

/* Removes tray icon from notification area */
bool HideTrayIcon(int trayIconID)
{
	NOTIFYICONDATA *nData = (NOTIFYICONDATA*)malloc(sizeof(NOTIFYICONDATA));
	nData->cbSize = sizeof(NOTIFYICONDATA);
	for (int i = 0; i < trayIconsCount; i++)
	{
		TrayIcon trayIcon = TrayIcons[i];
		if (trayIconID == trayIcon.uniqueID)
		{
			nData->uID = trayIcon.uniqueID;
			nData->hWnd = trayIcon.parentFormHwnd;
			return Shell_NotifyIcon(NIM_DELETE, nData);
		}
	}
}

bool ShowBalloonMessage(int trayIconID, TCHAR *title, TCHAR *msg, TrayIconBalloonTypesEnum balloonInfoType, bool playSound)
{
	NOTIFYICONDATA *nData = (NOTIFYICONDATA*)malloc(sizeof(NOTIFYICONDATA));
	nData->cbSize = sizeof(NOTIFYICONDATA);
	for (int i = 0; i < trayIconsCount; i++)
	{
		TrayIcon trayIcon = TrayIcons[i];
		if (trayIcon.uniqueID == trayIconID)
		{
			nData->uID = trayIcon.uniqueID;
			nData->hWnd = trayIcon.parentFormHwnd;
			nData->uFlags = NIF_INFO;
			switch (balloonInfoType)
			{
			case TRAYICONBALLOONTYPE_NONE:
				nData->dwInfoFlags = NIIF_NONE;
				break;
			case TRAYICONBALLOONTYPE_INFO:
				nData->dwInfoFlags = NIIF_INFO;
				break;
			case TRAYICONBALLOONTYPE_WARNING:
				nData->dwInfoFlags = NIIF_WARNING;
				break;
			case TRAYICONBALLOONTYPE_ERROR:
				nData->dwInfoFlags = NIIF_ERROR;
				break;
			}
			nData->dwInfoFlags |= (playSound) ? (NULL) : (NIIF_NOSOUND);
			wcscpy_s(nData->szInfoTitle, title);
			wcscpy_s(nData->szInfo, msg);
			return Shell_NotifyIcon(NIM_MODIFY, nData);
		}
	}
}

bool HideBalloonMessage(int trayIconID)
{
	NOTIFYICONDATA *nData = (NOTIFYICONDATA*)malloc(sizeof(NOTIFYICONDATA));
	nData->cbSize = sizeof(NOTIFYICONDATA);
	for (int i = 0; i < trayIconsCount; i++)
	{
		TrayIcon trayIcon = TrayIcons[i];
		if (trayIcon.uniqueID == trayIconID)
		{
			nData->uID = trayIcon.uniqueID;
			nData->hWnd = trayIcon.parentFormHwnd;
			nData->uFlags = NIF_INFO;
			wcscpy_s(nData->szInfo, _T(""));
			return Shell_NotifyIcon(NIM_MODIFY, nData);
		}
	}
}

/* Creates the main popup menu for tray and returns its handle for further operation */
HMENU CreateTrayIconMainPopupMenu(int trayIconID)
{
	HMENU hSubMenu = CreatePopupMenu();
	if (hSubMenu)
	{
		for (int i = 0; i < trayIconsCount; i++)
		{
			TrayIcon trayIcon = TrayIcons[i];
			if (trayIcon.uniqueID == trayIconID)
			{
				TrayIcons[i].trayIconPopupMenu = hSubMenu;
				return hSubMenu;
			}
		}
	}
}

/* Adds a popup menu with the provided name to the given parent menu */
HMENU AddTrayIconPopupMenu(HMENU hParentPopupMenu, TCHAR *menuTxt)
{
	HMENU hSubMenu = CreatePopupMenu();
	if (AppendMenu(hParentPopupMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, menuTxt))
		return hSubMenu;
}

/* Adds a popup menu item to the given parent popup menu and returns its unique menuID */
int AddTrayIconPopupMenuItem(HMENU hParentPopupMenu, TCHAR *menuTxt)
{
	if (AppendMenu(hParentPopupMenu, MF_STRING, trayIconMenuItemsCount + MAX_MENUITEMS, menuTxt))
	{
		TrayIconMenuItems[trayIconMenuItemsCount] = { trayIconMenuItemsCount + MAX_MENUITEMS,hParentPopupMenu,NULL };
		trayIconMenuItemsCount++;
		return trayIconMenuItemsCount - 1 + MAX_MENUITEMS;
	}
}

bool AddTrayIconPopupMenuItemEvent(int trayIconPopupMenuItemID, TrayIconMenuItemEventsEnum trayIconMenuItemEvent, void(*Procedure) ())
{
	for (int i = 0; i < trayIconMenuItemsCount; i++)
	{
		TrayIconMenuItem trayIconMenuItem = TrayIconMenuItems[i];
		if (trayIconMenuItem.TrayIconMenuItemId == trayIconPopupMenuItemID)
		{
			switch (trayIconMenuItemEvent)
			{
			case TRAYICONMENUITEMEVENT_CLICK:
				TrayIconMenuItems[i].CLICK.event_proc = Procedure;
				return true;
			}
		}
	}
}

/* Displays the popup menu corresponding to the provided trayIconID */
bool ShowTrayIconPopupMenu(int trayIconID)
{
	for (int i = 0; i < trayIconsCount; i++)
	{
		TrayIcon trayIcon = TrayIcons[i];
		if (trayIcon.uniqueID == trayIconID)
		{
			LPPOINT point = (LPPOINT)malloc(sizeof(POINT));
			if (GetCursorPos(point))
			{
				SetForegroundWindow(trayIcon.parentFormHwnd);
				return TrackPopupMenu(trayIcon.trayIconPopupMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, point->x, point->y, 0, trayIcon.parentFormHwnd, NULL);
			}
		}
	}
}

/* Checks if the popup menu item specified by trayIconPopupMenuItemID is ticked */
bool IsTrayIconPopupMenuItemChecked(int trayIconPopupMenuItemID)
{
	MENUITEMINFO *menuiteminfo = (MENUITEMINFO*)malloc(sizeof(MENUITEMINFO));
	menuiteminfo->cbSize = sizeof(MENUITEMINFO);
	menuiteminfo->fMask = MIIM_STATE;
	for (int i = 0; i < trayIconMenuItemsCount; i++)
	{
		TrayIconMenuItem trayIconMenuItem = TrayIconMenuItems[i];
		if (trayIconMenuItem.TrayIconMenuItemId == trayIconPopupMenuItemID)
		{
			if (GetMenuItemInfo(trayIconMenuItem.parentMenu, trayIconPopupMenuItemID, false, menuiteminfo))
			{
				if (menuiteminfo->fState == MFS_CHECKED)
					return true;
				else if (menuiteminfo->fState == MFS_UNCHECKED)
					return false;
			}
		}
	}
	return false;
}

/* Sets the checked status of the popup menu item specified by trayIconPopupMenuItemID */
void SetTrayIconPopupMenuItemCheckStatus(int trayIconPopupMenuItemID, bool checked)
{
	for (int i = 0; i < trayIconMenuItemsCount; i++)
	{
		TrayIconMenuItem trayIconMenuItem = TrayIconMenuItems[i];
		if (trayIconMenuItem.TrayIconMenuItemId == trayIconPopupMenuItemID)
		{
			CheckMenuItem(trayIconMenuItem.parentMenu, trayIconPopupMenuItemID, MF_BYCOMMAND | (checked) ? (MF_CHECKED) : (MF_UNCHECKED));
		}
	}	
}
#pragma endregion

#pragma endregion


#pragma region Helper functions
/* Takes HWND of button and returns corresponding WNDPROC */
WNDPROC FindBtnDefaultCallBack(HWND btnHwnd, Button buttons[])
{
	for (int i = 0; i<buttonsCount; i++)
	{
		if (buttons[i].ButtonHwnd == btnHwnd)
		{
			return buttons[i].ButtonDefaultCallback;
		}
	}
}
/* Takes HWND of textbox and returns coresponding WNDPROC */
WNDPROC FindTextboxDefaultCallBack(HWND textboxHwnd, Textbox textboxes[])
{
	for (int i = 0; i<textboxesCount; i++)
	{
		if (textboxes[i].TextboxHwnd == textboxHwnd)
		{
			return textboxes[i].TextboxDefaultCallback;
		}
	}
}
/* Takes HWND of checkbox and returns coresponding WNDPROC */
WNDPROC FindCheckboxDefaultCallBack(HWND checkboxHwnd, Checkbox checkboxes[])
{
	for (int i = 0; i<checkboxesCount; i++)
	{
		if (checkboxes[i].CheckboxHwnd == checkboxHwnd)
		{
			return checkboxes[i].CheckboxDefaultCallback;
		}
	}
}
/* Sets 'nice' font to the given hwnd */
bool SetNiceFont(HWND hwnd)
{
	//use 'regular' system GUI font instead of the ugly default 'universal' one
	return SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), true);
}
/* Function for cleaning up before quiting */
void Cleanup()
{
	NOTIFYICONDATA *nData = (NOTIFYICONDATA*)malloc(sizeof(NOTIFYICONDATA));
	nData->cbSize = sizeof(NOTIFYICONDATA);
	for (int i = 0; i < trayIconsCount; i++)
	{
		nData->uID = TrayIcons[i].uniqueID;
		nData->hWnd = TrayIcons[i].parentFormHwnd;
		Shell_NotifyIcon(NIM_DELETE, nData); // remove tray icons
	}
}
#pragma region Thread functions for creating a new thread
void DelayAndRunProc(void(*Procedure)())	// Only to be called by StartThread() function
{
	Sleep(10);
	LPSECURITY_ATTRIBUTES sec = (LPSECURITY_ATTRIBUTES)malloc(sizeof(SECURITY_ATTRIBUTES));
	sec->nLength = sizeof(SECURITY_ATTRIBUTES);
	sec->lpSecurityDescriptor = NULL;
	sec->bInheritHandle = NULL;
	CreateThread(sec, NULL, (LPTHREAD_START_ROUTINE)Procedure, nullptr, NULL, NULL);
}
/* Starts a new thread */
bool StartThread(void(*Procedure)())
{
	LPSECURITY_ATTRIBUTES sec = (LPSECURITY_ATTRIBUTES)malloc(sizeof(SECURITY_ATTRIBUTES));
	sec->nLength = sizeof(SECURITY_ATTRIBUTES);
	sec->lpSecurityDescriptor = NULL;
	sec->bInheritHandle = NULL;
	return CreateThread(sec, NULL, (LPTHREAD_START_ROUTINE)&DelayAndRunProc, Procedure, NULL, NULL);
}
#pragma endregion
#pragma endregion

#pragma region Credits
/*
https://codingmisadventures.wordpress.com/2009/02/20/creating-a-system-tray-icon-using-visual-c-and-win32/
https://www.codeproject.com/Articles/4768/Basic-use-of-Shell-NotifyIcon-in-Win
*/
#pragma endregion
