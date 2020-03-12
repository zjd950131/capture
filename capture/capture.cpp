// capture.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "capture.h"

#define MAX_LOADSTRING 100
//按钮ID
#define IDB_ONE     3301  
#define IDB_TWO     3302
// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CAPTURE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CAPTURE));

    MSG msg;

    // 主消息循环:
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
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CAPTURE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

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

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HWND hwndButtonCintinue;
    HWND hwndButtonExit;
    switch (message)
    {
    case WM_CREATE:
    {
        hwndButtonCintinue = CreateWindow(TEXT("button"),//必须为：button    
            TEXT("取色"),//按钮上显示的字符    
            WS_CHILD | WS_VISIBLE,
            100, 240, 100, 50,  //按钮在界面上出现的位置
            hWnd, (HMENU)IDB_ONE,  //设置按钮IDIDC_BUTTON_CONTINUE = 131自己定义ID
            ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        hwndButtonExit = CreateWindow(TEXT("button"),//必须为：button    
            TEXT("退出"),//按钮上显示的字符    
            WS_CHILD | WS_VISIBLE,
            400, 240, 100, 50,  //按钮在界面上出现的位置
            hWnd, (HMENU)IDB_TWO,  //设置按钮ID IDC_BUTTON_EXIT =132自己定义ID
            ((LPCREATESTRUCT)lParam)->hInstance, NULL);
    }
    return 0;

    case WM_COMMAND:
        {
        switch (LOWORD(wParam))
        {
        case IDB_ONE:
            //MessageBox(hwnd, L"您点击了第一个按钮。", L"提示", MB_OK | MB_ICONINFORMATION);  
            SendMessage((HWND)lParam, WM_SETTEXT, (WPARAM)NULL, (LPARAM)L"第一个按鈕已点击");
            break;

        case IDB_TWO:
            //MessageBox(hwnd, L"您点击了第二个按钮。", L"提示", MB_OK | MB_ICONINFORMATION);  
            SendMessage((HWND)lParam, WM_SETTEXT, (WPARAM)NULL, (LPARAM)L"第二个按鈕已点击");
            break;


        default:
            break;
        }

        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
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

