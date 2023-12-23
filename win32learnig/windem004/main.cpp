//
// Created by wangly on 2023/12/21.
//

//#define UNICODE

#include <windows.h>
#include "main.h"
#include <cstdio>

void C_char() {
    const char *psText = "Hello World";
    printf("%s\n", psText);
}

void W_char() {
    //宽字节字符串指针
    //在Windows中，使用宽字节字符串来表示Unicode编码的字符串。
    const wchar_t *psText = L"Hello World";
    printf("%ls\n", psText);
    printf("字符个数：：%d\n", wcslen(psText));
}

/**
 #ifdef UNICODE
 typedef wchar_t TCHAR;
  #define _TEXT(quote) L##quote
 #else
  typedef char TCHAR;
  #define _TEXT(quote) quote
 #endif
 */
void T_char() {
    //TCHAR
    const TCHAR *psText = __TEXT("Hello World");
    //看是否定义了 UNICODE 宏
    //const char *psText = "Hello World"; | const wchar_t *psText = L"Hello World";
#ifdef UNICODE
    wprintf(L"%s\n", psText);
#else
    printf("单:%s\n", psText);
#endif
}

void printUnicede() {
    const wchar_t *psText = L"你好，世界";
    //    wprintf(L"%s\n", psText);
    //STD_OUTPUT_HANDLE 标准输出句柄
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteConsole(hOutput, psText, wcslen(psText), NULL, NULL);
}

int main() {
//    C_char();
//    W_char();
//    T_char();
    printUnicede();
    return 0;
}

