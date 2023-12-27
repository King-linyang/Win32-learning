//
// Created by wangly on 2023/12/21.
//


#include <windows.h>
#include "main.h"
#include <cstdio>

DWORD CALLBACK MyThread(PVOID pParam) {
    char *pBuf = (char *) pParam;
    while (1) {
        printf("%s\n", pBuf);
        Sleep(1000);
    }
    return 0;
}

DWORD CALLBACK MyThread2(PVOID pParam) {
    char *pBuf = (char *) pParam;
    while (1) {
        printf("%s\n", pBuf);
        Sleep(1000);
    }
    return 0;
}

int main() {
    printf("Hello, World!\n");
    DWORD nId = 0;
    char *pBuf = "*********";
    HANDLE hThread = CreateThread(NULL, 0, MyThread, pBuf, 0, &nId);
    char *pBuf2 = "--------";
    HANDLE hThread2 = CreateThread(NULL, 0, MyThread2, pBuf2, 0, &nId);
    return 0;
}
