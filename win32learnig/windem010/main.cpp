//
// Created by wangly on 2023/12/21.
//


#include <windows.h>
#include "main.h"
#include <cstdio>

HANDLE g_hOutPut = 0;//接受标准输出句柄
#define WM_MYNESS WM_USER+1001   //自定义消息

void drawPoint(HDC hdc) {
    SetPixel(hdc, 100, 100, RGB(255, 0, 0));
    for (int i = 0; i < 256; i++) {
        SetPixel(hdc, i, i, RGB(255, 0, 0));
    }
    LineTo(hdc, 400, 400);//画线
}

void myPaint(HWND hWnd) {
    //绘制窗口内容
    PAINTSTRUCT ps = {0};
    HDC hdc = BeginPaint(hWnd, &ps);
//    drawPoint(hdc);//绘制一个点

    //创建一个画笔,带颜色的
    HPEN hpen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));//实线
    HGDIOBJ oOldPen = SelectObject(hdc, hpen);//oOldPen原来的画笔
    MoveToEx(hdc, 100, 100, NULL);

    //创建画刷
//    HBRUSH hbrush = CreateSolidBrush(RGB(255, 0, 0));//填充画刷
//    HBRUSH hbrush = CreateHatchBrush(HS_CROSS, RGB(255, 0, 0));//纹理画刷
    HGDIOBJ hbrush = GetStockObject(NULL_BRUSH);//获取操作系统的画刷(这个是透明画刷),这个画刷不需要销毁
    HGDIOBJ oOldBrush = SelectObject(hdc, hbrush);//oOldBrush原来的画刷

    //画带颜色的图形
    Rectangle(hdc, 100, 100, 400, 400);
    Ellipse(hdc, 100, 100, 400, 400);

    SelectObject(hdc, oOldBrush);
//    DeleteObject(hbrush);

    SelectObject(hdc, oOldPen);
    DeleteObject(hdc);

    EndPaint(hWnd, &ps);
}

//窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_DESTROY:
            PostQuitMessage(0);//使GetMessage返回0
//            PostMessage(hWnd, WM_QUIT, 0, 0);
//            SendMessage(hWnd, WM_QUIT, 0, 0);
            break;
        case WM_PAINT:
            myPaint(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
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

    AllocConsole();//增加docs窗口
    g_hOutPut = GetStdHandle(STD_OUTPUT_HANDLE);//获取标准输出句柄
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