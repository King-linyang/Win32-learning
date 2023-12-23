//
// Created by wangly on 2023/12/21.
//


#include <windows.h>
#include "main.h"
#include <cstdio>

//HANDLE g_hOutPut = 0;//接受标准输出句柄

void OnCreate(HWND hWnd, LPARAM lParam) {
    CREATESTRUCT *pCreate = (CREATESTRUCT *) lParam;
    char *psDD = (char *) pCreate->lpCreateParams;
    MessageBox(hWnd, psDD, "Message", MB_OK);
}

void OnSize(HWND hWnd, LPARAM lParam) {
    short width = LOWORD(lParam);
    short height = HIWORD(lParam);
    printf("OnSize: 宽%d, 高%d\n", width, height);
}

//窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_DESTROY:
            PostQuitMessage(0);//使GetMessage返回0
            break;
        case WM_CREATE:
            OnCreate(hWnd, lParam);
            break;
        case WM_SIZE:
            OnSize(hWnd, lParam);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

/**
 * @brief 程序入口
 * @param hInstance 当前程序实例句柄
 * @param hPrevInstance 当前程序上一个实例句柄
 * @param lpCmdLine 命令行参数字符串
 * @param nCmdShow 窗口的显示方式
 * @return
 */
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//    MessageBox(NULL, "hello world", "hello world", MB_YESNOCANCEL);

//    AllocConsole();//增加docs窗口
//    g_hOutPut = GetStdHandle(STD_OUTPUT_HANDLE);//获取标准输出句柄
    // 注册窗口类
    WNDCLASS wndClass = {0};
    wndClass.cbClsExtra = 0;//缓冲区
    wndClass.cbWndExtra = 0;//缓冲区
    wndClass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);//背景颜色
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);//光标
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//图标
    wndClass.hInstance = hInstance;//实例句柄
    wndClass.lpfnWndProc = WndProc;//窗口处理函数
    wndClass.lpszClassName = "Main";//窗口类名
    wndClass.lpszMenuName = NULL;//菜单名 NULL:表示不要菜单
    wndClass.style = CS_HREDRAW | CS_VREDRAW;//窗口水平和垂直方向是否可变(重新画)

    RegisterClass(&wndClass);//注册窗口类

    //创建窗口
    const char *sss = "Hello data";
    HWND hWnd = CreateWindowEx(0, "Main", "MyWindow", WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                               NULL, NULL, hInstance, (LPVOID) sss);

    //子窗口
    // 注册窗口类
    WNDCLASS wndClassC = {0};
    wndClassC.cbClsExtra = 0;//缓冲区
    wndClassC.cbWndExtra = 0;//缓冲区
    wndClassC.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);//背景颜色
    wndClassC.hCursor = LoadCursor(NULL, IDC_ARROW);//光标
    wndClassC.hIcon = LoadIcon(NULL, IDI_APPLICATION);//图标
    wndClassC.hInstance = hInstance;//实例句柄
    wndClassC.lpfnWndProc = DefWindowProc;//窗口处理函数
    wndClassC.lpszClassName = "Child";//窗口类名
    wndClassC.lpszMenuName = NULL;//菜单名 NULL:表示不要菜单
    wndClassC.style = CS_HREDRAW | CS_VREDRAW;//窗口水平和垂直方向是否可变(重新画)

    RegisterClass(&wndClassC);//注册窗口类
    //创建子窗口
    HWND hWndC = CreateWindowEx(0, "Child", "MyWindow", WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
                                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                hWnd, NULL, hInstance, NULL);
    HWND hWndC1 = CreateWindowEx(0, "Child", "MyWindow", WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
                                 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                 hWnd, NULL, hInstance, NULL);


    ShowWindow(hWnd, SW_SHOW);//显示窗口
    UpdateWindow(hWnd);//更新窗口-重绘
    //消息循环
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);//翻译消息
        DispatchMessage(&msg);//分派消息
    }
    return 0;
}