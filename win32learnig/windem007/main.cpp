//
// Created by wangly on 2023/12/21.
//


#include <windows.h>
#include "main.h"
#include <cstdio>

HANDLE g_hOutPut = 0;//接受标准输出句柄
#define WM_MYNESS WM_USER+1001   //自定义消息


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

void ProMyMess(HWND hWnd, LPARAM lParam, LPARAM i) {
    char test[256] = {0};
    sprintf(test, "处理自定义消息: %ld\n", lParam);
    MessageBox(hWnd, test, "处理自定义消息", MB_OK);
}

void myPaint(HWND hWnd) {
    printf("myPaint绘图消息\n");

    PAINTSTRUCT ps = {0};
    HDC hdc = BeginPaint(hWnd, &ps);
    TextOut(hdc, 10, 10, "Hello World", 11);
    EndPaint(hWnd, &ps);
    //绘图代码只能在绘图消息中进行处理
}

void myKeyDown(HWND pHwnd, WPARAM param) {
    char test[256] = {0};
    sprintf(test, "键盘按下--键码: %u\n", param);
    WriteConsole(g_hOutPut, test, strlen(test), nullptr, nullptr);
}
void onChar(HWND pHwnd, WPARAM param){
    char test[256] = {0}; test[256] = {0};
    sprintf(test, "字符输入--字符: %u\n", param);
    WriteConsole(g_hOutPut, test, strlen(test), nullptr, nullptr);
}
//窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CHAR:
            onChar(hWnd, wParam);
            break;
        case WM_PAINT:
            myPaint(hWnd);
            break;
        case WM_LBUTTONDOWN:
            myPaint(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);//使GetMessage返回0
//            PostMessage(hWnd, WM_QUIT, 0, 0);
//            SendMessage(hWnd, WM_QUIT, 0, 0);
            break;
        case WM_KEYDOWN:
            myKeyDown(hWnd, wParam);
            break;
        case WM_CREATE:
            OnCreate(hWnd, lParam);
            PostMessage(hWnd, WM_MYNESS, 1, 2);
            break;
        case WM_MYNESS:
            ProMyMess(hWnd, wParam, lParam);
            break;
        case WM_SIZE:
            OnSize(hWnd, lParam);
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
//    while (GetMessage(&msg, NULL, 0, 0)) {
//        TranslateMessage(&msg);//翻译消息
//        DispatchMessage(&msg);//分派消息
//    }
    while (1) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            //有消息
            //获取消息
            if (GetMessage(&msg, NULL, 0, 0)) {
                TranslateMessage(&msg);//翻译消息
                DispatchMessage(&msg);//分派消息
            } else {
                return 0;
            }
        } else {
            //没有消息--空闲处理
//            printf("没有消息\n");
        }
    }
    return 0;
}