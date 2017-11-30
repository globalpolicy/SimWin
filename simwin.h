#include <tchar.h>
#include <windows.h>


#define MAX_BUTTONS 50
int buttonsCount=0;
typedef enum
{
    LCLICK
} ButtonEventsEnum;
typedef struct
{
    void (*event_proc) ();
} ButtonEvent;
typedef struct
{
    WNDPROC ButtonDefaultCallback;
    HWND ButtonHwnd;
    ButtonEvent LCLICK;
} Button;
Button Buttons[MAX_BUTTONS];
WNDPROC FindBtnDefaultCallBack(HWND btnHwnd, Button buttons[]); //helper function declaration




/* Callback for button */
LRESULT CALLBACK ButtonProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{

    switch(Msg) 
    {
        // Handle all messages we want to customize:
        case WM_LBUTTONDOWN:
        {
            for(int i=0;i<buttonsCount;i++)
            {
                Button button = Buttons[i];
                if(button.ButtonHwnd==hwnd)
                {
                    if (button.LCLICK.event_proc)
                        (*button.LCLICK.event_proc) ();
                }
            }
            return 0;	// If an application processes this message, it should return zero as per microsoft's documentation on WM_LBUTTONDOWN message
        }
    }

    WNDPROC BtnDefaultCallBack = FindBtnDefaultCallBack(hwnd, Buttons);
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
    
    Buttons[buttonsCount]={(WNDPROC)GetWindowLongPtr(btnHwnd, GWLP_WNDPROC), btnHwnd, NULL};
    LONG_PTR retval = SetWindowLongPtr(btnHwnd, GWLP_WNDPROC, (LONG_PTR) &ButtonProc);
    buttonsCount++;
    return btnHwnd;
}

bool AddButtonEvent(HWND btnHwnd, ButtonEventsEnum btnEvent, void (*Procedure) ())
{
    for(int i=0;i<buttonsCount;i++)
    {
        Button button = Buttons[i];
        if(btnHwnd == button.ButtonHwnd)
        {
            switch(btnEvent)
            {
                case LCLICK:
                    Buttons[i].LCLICK.event_proc = Procedure;
                    return true;
            }
        }
    }
}

/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        case WM_COMMAND:

        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

HWND CreateForm(const TCHAR *formTitle, const TCHAR *className, int width, int height)
{
    HINSTANCE hThisInstance=GetModuleHandle(NULL);
    const TCHAR *szClassName=className;


    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND+1;

    /* Register the window class, and if it fails quit the program */
    if (RegisterClassEx (&wincl))
    {
        HWND hwnd=CreateWindowEx (
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

        ShowWindow(hwnd,SW_NORMAL);
        return hwnd;
    }
}

void Engage(void)
{
    MSG message;
    BOOL bRet;
    while((bRet=GetMessage(&message,NULL,0,0))!=0)
    {
        if(bRet!=-1)
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }
}

/* Helper functions */
/* Takes HWND of button and returns corresponding WNDPROC */
WNDPROC FindBtnDefCallBack(HWND btnHwnd, Button buttons[])
{
    for(int i=0;i<buttonsCount;i++)
    {
        if(buttons[i].ButtonHwnd == btnHwnd)
        {
            return buttons[i].ButtonDefaultCallback;
        }
    }
}
