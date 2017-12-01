#pragma once
#include <tchar.h>
#include <windows.h>

#pragma region Declarations

#pragma region Form Declarations
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
HWND CreateForm(const TCHAR *formTitle, const TCHAR *className, int width, int height);
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
#pragma endregion

#pragma region Miscellaneous Declarations
bool SetNiceFont(HWND hwnd);
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
	case WM_COMMAND:

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

		ShowWindow(hwnd, SW_NORMAL);
		return hwnd;
	}
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
					(*textbox.TEXTCHANGE.event_proc) ();
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
		width,        // Button width
		height,        // Button height
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
/* Sets 'nice' font to the given hwnd */
bool SetNiceFont(HWND hwnd)
{
	//use 'regular' system GUI font instead of the ugly default 'universal' one
	return SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), true);
}
#pragma endregion
