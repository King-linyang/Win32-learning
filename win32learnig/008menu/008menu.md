# 菜单分类

- 窗口的顶层菜单
- 弹出式菜单
- 系统菜单

HMENU类型表示菜单，ID表示菜单项。

# 资源相关

资源脚本文件：*.rc文件

编译器：RC.EXE

CL.EXE
.c/.cpp--------------->.obj| LINK.EXE
RC.EXE |------------------->.exe
.rc-------------------->.res|

# 菜单资源的使用

- 添加菜单资源
- 加载菜单资源  
  1> 注册窗口类时设置菜单  
  2> 创建窗口传参设置菜单  
  3> 在主窗口WM_CREATE消息中利用 SetMenu函数设置菜单

```c
加载菜单资源
HMENU LoadMenu(
    HINSTANCE hInstance,  // handle to module
    LPCTSTR lpMenuName    // menu name or resource identifier
);
```

## 命令消息（WM_COMMAND）处理

附带信息：

- wPARAM：  
  HIWORD - 对于菜单为0  
  LOWORD - 菜单项的ID  
  lPARAM - 对于菜单为0

# 上下文菜单

显示上下文菜单

```c
BOOL TrackPopupMenu(
HMENU hMenu, //菜单句柄
UINT uFlags, //显示方式
int x,//水平位置，屏幕坐标系
int y,//垂直位置，屏幕坐标系
int nReserved, //保留，必须0
HWND hWnd, //处理菜单消息的窗口句柄
CONST RECT *prcRect //NULL，忽略
); TrackPopupMenu是阻塞函数
```

# 上下文菜单

- WM_RBUTTONUP
  鼠标右键弹起消息为窗口坐标系坐标，要使用需将其转换成屏幕坐标系坐标 ClientToScreen

- WM_CONTEXTMENU
  wParam ：右键点击的窗口句柄
  lPARAM ：LOWORD X坐标，屏幕坐标系
  HIWORD Y坐标，屏幕坐标系

  WM_CONTEXTMENU消息是在WM_RBUTTONUP消息之后产生。







