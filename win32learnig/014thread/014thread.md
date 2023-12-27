# 1 线程基础

- Windows线程是可以执行的代码的实例。系统是以线程为单位调度程序。一个程序当中可以有多个线程，实现多任务的处理。
- Windows线程的特点：
  1）线程都具有1个ID
  2）每个线程都具有自己的内存栈
  3）同一进程中的线程使用同一个地址空间。
- 线程的调度:
  将CPU的执行时间划分成时间片，依次根据时间片执行不同的线程。
  线程轮询：线程A -> 线程B -> 线程A......

# 2 创建线程

- 创建线程

```c
HANDLE CreateThread(
LPSECURITY_ATTRIBUTES lpThreadAttributes,//安全属性
SIZE_T dwStackSize, //线程栈的大小 按1M对齐
LPTHREAD_START_ROUTINE lpStartAddress, //线程处理函数的函数地址
LPVOID lpParameter, //传递给线程处理函数的参数
DWORD dwCreationFlags,//线程的创建方式，
LPDWORD lpThreadId //创建成功，返回线程的ID
); 创建成功，返回线程句柄
```

- 定义线程处理函数

```c
DWORD WINAPI ThreadProc(
LPVOID lpParameter //创建线程时，传递给线程的参数
);
```

# 3 销毁线程

- 挂起

```c
DWORD SuspendThread(
HANDLE hThread   // handle to thread
);
```

- 唤醒

```c
DWORD ResumeThread(
HANDLE hThread   // handle to thread
);
```

- 结束指定线程

```c
  BOOL TerminateThread(
HANDLE hThread, // handle to thread
DWORD dwExitCode // exit code
);
```

- 结束函数所在的线程

```c
  VOID ExitThread(
DWORD dwExitCode // exit code for this thread
);
```

# 4 线程相关操作

- 获取当前线程的ID

```c
GetCurrentThreadId
```

- 获取当前线程的句柄

```c
GetCurrentThread
```

- 等候单个句柄有信号

```c
VOID WaitForSingleObject(
HANDLE handle,  //句柄BUFF的地址
DWORD dwMilliseconds      // 等候时间 INFINITE
);
```

- 同时等候多个句柄有信号

```c
DWORD WaitForMultipleObjects(
DWORD nCount, //句柄数量
CONST HANDLE *lpHandles, //句柄BUFF的地址
BOOL bWaitAll,//等候方式
DWORD dwMilliseconds // 等候时间 INFINITE
);
```

- bWaitAll - 等候方式  
  TRUE - 表示所有句柄都有信号，才结束等候  
  FASLE- 表示句柄中只要有1个有信号，就结束等候。

# 5 线程同步

## 原子锁

- 相关问题  
  多个线程对同一个数据进行原子操作，会产生结果丢失。比如执行++运算时。

- 错误代码分析：  
  当线程A执行g_value++时，如果线程切换时间正好是在线程A将值保存到g_value之前，线程B继续执行g_value++，那么当线程A再次被切换回来之后，会将原来线程A保存的值保存到g_value上，线程B进行的加法操作被覆盖。

- 使用原子锁函数
  InterlockedIncrement  
  InterlockedDecrement  
  InterlockedCompareExchange  
  InterlockedExchange  
  ...
- 原子锁的实现： 直接对数据所在的内存操作，并且在任何一个瞬间只能有一个线程访问。

## 互斥

- 相关的问题  
  多线程下代码或资源的共享使用。
- 互斥的使用

1 创建互斥

```c
HANDLE CreateMutex(
LPSECURITY_ATTRIBUTES lpMutexAttributes, //安全属性
BOOL bInitialOwner,//初始的拥有者 TRUE/FALSE
LPCTSTR lpName //命名
); 创建成功返回互斥句柄
```

2 等候互斥

WaitFor.... 互斥的等候遵循谁先等候谁先获取。

3 释放互斥

```c
BOOL ReleaseMutex(
HANDLE hMutex // handle to mutex
);
```

4 关闭互斥句柄

CloseHandle

## 事件

- 相关问题
  程序之间的通知的问题。
- 事件的使用

1 创建事件

```c
HANDLE CreateEvent(
LPSECURITY_ATTRIBUTES lpEventAttributes, //安全属性
BOOL bManualReset,                       
//事件重置（复位）方式，TRUE手动，FALSE自动
BOOL bInitialState, //事件初始状态，TRUE有信号
LPCTSTR lpName //事件命名
); 创建成功返回 事件句柄
```

2 等候事件

```c
WaitForSingleObject / WaitForMultipleObjects
```

3 触发事件（将事件设置成有信号状态）

```c
BOOL SetEvent(
HANDLE hEvent // handle to event
);
```

4 复位事件（将事件设置成无信号状态）

```c
BOOL ResetEvent(
HANDLE hEvent // handle to event
);
```

5 关闭事件 CloseHandle

- 小心事件的死锁。

## 信号量

- 相关的问题

  类似于事件，解决通知的相关问题。但提供一个计数器，可以设置次数。

- 信号量的使用

  1 创建 信号量

```c
  HANDLE CreateSemaphore(
LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, //安全属性
LONG lInitialCount, //初始化信号量数量
LONG lMaximumCount, //信号量的最大值
LPCTSTR lpName //命名
); 创建成功返回信号量句柄
```

2 等候信号量

```c
WaitFor... 每等候通过一次，信号量的信号减1，直到为0阻塞
```

3 给信号量指定计数值

```c
BOOL ReleaseSemaphore(
HANDLE hSemaphore, //信号量句柄
LONG lReleaseCount, //释放数量
LPLONG lpPreviousCount   
//释放前原来信号量的数量，可以为NULL
);
```

4 关闭句柄 CloseHandle
















