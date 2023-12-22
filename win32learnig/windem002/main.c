//
// Created by wangly on 2023/12/21.
//


#include <windows.h>
#include "main.h"
#include <stdio.h>

/**
 * @brief 程序入口
 * @param hInstance 当前程序实例句柄
 * @param hPrevInstance 当前程序上一个实例句柄
 * @param lpCmdLine 命令行参数字符串
 * @param nCmdShow 窗口的显示方式
 * @return
 */
//int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//    MessageBox(NULL, "hello world", "hello world", MB_YESNOCANCEL);
//    return 0;
//}
int main() {
    printf("hello world\n");
    MessageBox(NULL, "hello world", "hello world", MB_YESNOCANCEL);
    return 0;
}