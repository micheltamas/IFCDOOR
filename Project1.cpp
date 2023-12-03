// Project1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Project1.h"
#include "Important.h"
#include "Ifcread.h"
#include "CommCtrl.h"
#include "WinUser.h"
#include "libloaderapi.h"
#include <mciapi.h>

#pragma comment (lib, "User32.lib")
#pragma comment(lib, "comctl32.lib")



#define MAX_LOADSTRING 100

#ifdef UNICODE
#define CreateEvent  CreateEventW
#else
#define CreateEvent  CreateEventA
#endif // !UNICODE

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
OPENFILENAMEW ofn;
HWND mTable;
IFCDOORRELOBJECTS IFCS;
const int ColNumbers = 7;

wchar_t szFile[1000]; // buffer for file name


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
 
    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
///*

HWND CreateListView(HWND hwndParent)
{
    INITCOMMONCONTROLSEX icex;   // Structure for control initialization.
    icex.dwICC = ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icex);

    RECT rcClient;                       // The parent window's client area.

    GetClientRect(hwndParent, &rcClient);

    // Create the list-view window in report view with label editing enabled.
    HWND hWndListView = CreateWindow(WC_LISTVIEW,
        L"",
        WS_CHILD | LVS_REPORT , //| LVS_EDITLABELS
        0, 0,
        rcClient.right - rcClient.left,
        rcClient.bottom - rcClient.top,
        hwndParent,
        (HMENU)IDM_CODE_SAMPLES,
        hInst,
        NULL);
    
    return (hWndListView);
}
//*/
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//


static void _LvUpdate_New(HWND hWnd, HWND mTable, IFCDOORRELOBJECTS * IFCS)
{
    ListView_DeleteAllItems(mTable);
    tvIFCDOORSTOLISTW* iDoors = &IFCS->IFCDOORSTOLIST;

    std::string sTitle = "Number of IFCDOOR objects = " + std::to_string(IFCS->IFCDOORS.size());
    TONEWWSTR(szTitle, sTitle);
    szTitle = szTitle + L"; Filename= " + IFCS->FileName;

    for (int i = 0; i < iDoors->size(); i++)
    {
        IFCDOORSTOLISTW iDoor = (*iDoors)[i];
        int Pos = 0;
        LVITEM lvi;
 
      
        lvi.mask = LVIF_TEXT;
        WSTR wNR= std::to_wstring(i + 1);
        lvi.pszText = const_cast<LPWSTR>(wNR.c_str());
        lvi.iItem = SendMessage(mTable, LVM_GETITEMCOUNT, 0, 0);
        lvi.iSubItem = Pos++;
        int index = SendMessage(mTable, LVM_INSERTITEM, 0, (LPARAM)&lvi);

        lvi.mask = LVIF_TEXT;
        lvi.pszText = const_cast<LPWSTR>(iDoor.ws_p00_IFCDOORSTYLEName.c_str());
        lvi.iItem = index;
        lvi.iSubItem = Pos++;
        SendMessage(mTable, LVM_SETITEM, 0, (LPARAM)&lvi);
        
        lvi.mask = LVIF_TEXT;
        lvi.pszText = const_cast<LPWSTR>(iDoor.ws_p07_MATERIALMaterials.c_str());
        lvi.iItem = index;
        lvi.iSubItem = Pos++;
        SendMessage(mTable, LVM_SETITEM, 0, (LPARAM)&lvi);

        lvi.mask = LVIF_TEXT;
        lvi.pszText = const_cast<LPWSTR>(iDoor.ws_p02_IFCDOORName.c_str());
        lvi.iItem = index;
        lvi.iSubItem = Pos++;
        SendMessage(mTable, LVM_SETITEM, 0, (LPARAM)&lvi);

        lvi.mask = LVIF_TEXT;
        lvi.pszText = const_cast<LPWSTR>(iDoor.ws_p03_IFCDOORHeight.c_str());
        lvi.iItem = index;
        lvi.iSubItem = Pos++;
        SendMessage(mTable, LVM_SETITEM, 0, (LPARAM)&lvi);

        lvi.mask = LVIF_TEXT;
        lvi.pszText = const_cast<LPWSTR>(iDoor.ws_p04_IFCDOORWidth.c_str());
        lvi.iItem = index;
        lvi.iSubItem = Pos++;
        SendMessage(mTable, LVM_SETITEM, 0, (LPARAM)&lvi);

        lvi.mask = LVIF_TEXT;
        lvi.pszText = const_cast<LPWSTR>(iDoor.ws_p05_IfcDoorStyleOperationEnum.c_str());
        lvi.iItem = index;
        lvi.iSubItem = Pos++;
        SendMessage(mTable, LVM_SETITEM, 0, (LPARAM)&lvi);
    }
    SetWindowText(hWnd, szTitle.c_str());
    UpdateWindow(mTable);
    ShowWindow(mTable, 1);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

    case WM_CREATE:
        {
        
            mTable = CreateListView(hWnd);

            LV_COLUMN   lvColumn;
            
            TCHAR       szString[ColNumbers][30] = { TEXT("#"),TEXT("IFCDOORSTYLE NAME"),TEXT("IFCDOORSTYLE MATERIALS"), TEXT("IFCDOOR NAME"), TEXT("Heigth [mm]"), TEXT("Width [mm]"), TEXT("Operation") };
            int Wdth[11] = { 40,220,250,250,80,80,150};
            ListView_DeleteAllItems(mTable);

            lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
            lvColumn.fmt = LVCFMT_LEFT;
            lvColumn.cx = 120;

            for (int i = 0; i < ColNumbers; i++)
            {
                lvColumn.pszText = szString[i];
                lvColumn.cx = Wdth[i];
                lvColumn.fmt = i > ColNumbers+  1 ? LVCFMT_RIGHT : LVCFMT_LEFT;
                ListView_InsertColumn(mTable, i, &lvColumn);
            }

        }
        break;
    case WM_SIZE:
        RECT A;
        GetClientRect(hWnd, &A);
        SetWindowPos(mTable, 0, 0, 0, A.right, A.bottom, SWP_NOZORDER | SWP_NOACTIVATE);
        
        break;
    
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_FILE_OPEN:
                ZeroMemory(&ofn, sizeof(OPENFILENAMEW));
                ofn.lStructSize = sizeof(OPENFILENAMEW);

                ofn.nFilterIndex = 1;
                ofn.hwndOwner = hWnd;
                ofn.lpstrFile = szFile;
                ofn.nMaxFile = sizeof(szFile);
                ofn.lpstrFilter = L"IFC Files(.ifc)\0*.ifc\0Text Files(.txt)\0.txt\0All Files(.)\0*.*\0";
                ofn.lpstrTitle = L"Select a File";
               
                ofn.lpstrInitialDir = NULL;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

                //ofn.Flags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

                if (GetOpenFileName(&ofn))
                {
                
                    ReadFromIFC(szFile, &IFCS);
                    _LvUpdate_New(hWnd, mTable, &IFCS);
                    return 0;
                };
                break;
            case IDM_EDIT_DEFAULT:
                //DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

