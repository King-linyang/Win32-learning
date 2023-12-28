//
// Created by wangly on 2023/12/21.
//


#include <windows.h>
#include "main.h"
#include <cstdio>

//互斥句柄
HANDLE g_hMutex = nullptr;
//事件句柄
HANDLE g_hEvent = nullptr;
//信号量句柄
HANDLE g_hSemaphore = nullptr;

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

DWORD CALLBACK MyThread3(PVOID pParam) {
    char *pBuf = (char *) pParam;
    while (1) {
//        printf("%s\n", pBuf);
        WaitForSingleObject(g_hMutex, INFINITE);//等互斥，时间无线大,等到之后互斥句柄就变得无信号了
        for (int i = 0; i < strlen(pBuf); i++) {
            printf("%c", pBuf[i]);
            Sleep(125);
        }
        printf("\n");
        ReleaseMutex(g_hMutex);//释放互斥，互斥句柄变得有信号了
    }
}

DWORD CALLBACK MyThread4(PVOID pParam) {
    char *pBuf = (char *) pParam;
    while (1) {
//        printf("%s\n", pBuf);
        WaitForSingleObject(g_hMutex, INFINITE);//等互斥，时间无线大,等到之后互斥句柄就变得无信号了
        for (int i = 0; i < strlen(pBuf); i++) {
            printf("%c", pBuf[i]);
            Sleep(125);
        }
        printf("\n");
        ReleaseMutex(g_hMutex);//释放互斥，互斥句柄变得有信号了
    }
}

void createThread() {
    DWORD nId = 0;
    char *pBuf = "*********";
    HANDLE hThread = CreateThread(NULL, 0, MyThread, pBuf, 0, &nId);
    char *pBuf2 = "--------";
    HANDLE hThread2 = CreateThread(NULL, 0, MyThread2, pBuf2, 0, &nId);
}

long g_value = 0;

DWORD CALLBACK TestAdd1(PVOID pParam) {
    for (int i = 0; i < 100000; i++) {
//        g_value++;
//使用原子锁
        InterlockedIncrement(&g_value);
    }
    return 0;
}

DWORD CALLBACK TestAdd2(PVOID pParam) {
    for (int i = 0; i < 100000; i++) {
//        g_value++;
        InterlockedIncrement(&g_value);
    }
    return 0;
}

DWORD CALLBACK print5(PVOID pParam) {
    while (1) {
        WaitForSingleObject(g_hEvent, INFINITE);//等事件句柄有信号，时间无线大,
        ResetEvent(g_hEvent);//设置事件句柄无信号
        printf("**************\n");
    }
}

DWORD CALLBACK ctrl6(PVOID pParam) {
    while (1) {
        Sleep(10);
        SetEvent(g_hEvent);//设置事件句柄有信号
    }
}

DWORD CALLBACK fun8(LPVOID pParam) {
    while (1) {
        WaitForSingleObject(g_hSemaphore, INFINITE);//等待信号量
        printf("**************\n");
//        ReleaseSemaphore(g_hSemaphore, 1, NULL);// 释放信号量
    }
}

int main() {
    //创建线程
//    createThread();
    printf("Hello, World!\n");

//    printf("线程同步---------------------------原子锁\n");
//    //线程同步---------------------------原子锁
//    DWORD nId = 0;
//    char *pBuf = "*********";
//    HANDLE hThread[2];
//    hThread[0] = CreateThread(NULL, 0, TestAdd1, pBuf, 0, &nId);
//    char *pBuf2 = "--------";
//    hThread[1] = CreateThread(NULL, 0, TestAdd2, pBuf2, 0, &nId);
//    //阻塞主线程
//    WaitForMultipleObjects(2, hThread, true, INFINITE);
//    printf("g_value = %ld\n", g_value);
//    //线程同步---------------------------原子锁
//    printf("线程同步---------------------------原子锁\n");

//    printf("线程同步---------------------------互斥\n");
//    //创建互斥锁
//    g_hMutex = CreateMutex(NULL, FALSE, NULL);//FALSE 表示创建互斥的主线程不拥有互斥--这里就表示任何线程都不用有
//    DWORD nId1 = 0;
//    char *pBuf3 = "*********";
//    HANDLE hThread3 = CreateThread(NULL, 0, MyThread3, pBuf3, 0, &nId1);
//    char *pBuf4 = "--------";
//    HANDLE hThread4 = CreateThread(NULL, 0, MyThread4, pBuf4, 0, &nId1);
//    getchar();
//    CloseHandle(g_hMutex);
//    printf("线程同步---------------------------互斥\n");

//    printf("线程同步---------------------------事件\n");
//    //创建事件--TRUE创建之初有信号/传FALSE表示事件自动复位--不需要 ResetEvent(g_hEvent);//设置事件句柄无信号
//    g_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
//    DWORD nId2 = 0;
//    HANDLE hThread3[2] = {0};
//    hThread3[0] = CreateThread(NULL, 0, print5, NULL, 0, &nId2);//打印
//    hThread3[1] = CreateThread(NULL, 0, ctrl6, NULL, 0, &nId2);//控制打印
//    WaitForMultipleObjects(2, hThread3, TRUE, INFINITE);
//    CloseHandle(g_hEvent);
//    printf("线程同步---------------------------事件\n");

    printf("线程同步---------------------------信号量\n");
    g_hSemaphore = CreateSemaphore(NULL, 3, 10, NULL);//3 表示信号量初值 10 表示最大值
    DWORD nId = 0;
    HANDLE hThread = CreateThread(NULL, 0, fun8, NULL, 0, &nId);

//    getchar();
//    ReleaseSemaphore(g_hSemaphore, 5, NULL);//重新指定信号量计数值5
//    ReleaseSemaphore(g_hSemaphore, 50, NULL);//非法值--最大是10


    WaitForSingleObject(hThread, INFINITE);//等待线程执行完
    CloseHandle(hThread);//关闭线程
    CloseHandle(g_hSemaphore);//关闭信号
    printf("线程同步---------------------------信号量\n");

    return 0;
}
