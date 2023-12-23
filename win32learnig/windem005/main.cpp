//
// Created by wangly on 2023/12/21.
//


#include <windows.h>
#include "main.h"


/**
 * @brief 程序入口
 * @param hInstance 当前程序实例句柄
 * @param hPrevInstance 当前程序上一个实例句柄
 * @param lpCmdLine 命令行参数字符串
 * @param nCmdShow 窗口的显示方式
 * @return
 */
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //系统默认的按钮--默认窗口类
//    HWND hWnd = CreateWindow("Button", "MyWindow", WS_OVERLAPPEDWINDOW,
//                             CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
//                             NULL, NULL, hInstance, NULL);
    HWND hWnd = CreateWindow("Edit", "MyWindow", WS_OVERLAPPEDWINDOW,
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
