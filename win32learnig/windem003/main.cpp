//
// Created by wangly on 2023/12/21.
//


#include <windows.h>
#include "main.h"

//窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    return DefWindowProc(hWnd, message, wParam, lParam);
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

    // 注册窗口类
    WNDCLASS wndClass = {0};
    wndClass.cbClsExtra = 0;//缓冲区
    wndClass.cbWndExtra = 0;//缓冲区
    wndClass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);//背景颜色
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);//光标
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//图标
    wndClass.hInstance = hInstance;//实例句柄
    wndClass.lpfnWndProc = WndProc;//窗口处理函数
    wndClass.lpszClassName = "MyWindowClass";//窗口类名
    wndClass.lpszMenuName = NULL;//菜单名 NULL:表示不要菜单
    wndClass.style = CS_HREDRAW | CS_VREDRAW;//窗口水平和垂直方向是否可变(重新画)

    RegisterClass(&wndClass);//注册窗口类

    //创建窗口
    HWND hWnd = CreateWindow("MyWindowClass", "MyWindow", WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                             NULL, NULL, hInstance, NULL);
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