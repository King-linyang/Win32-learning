# 图标资源

- 添加资源
  注意图标的大小，一个图标文件中，可以有多个不同大小的图标。

- 加载

```c
HICON LoadIcon(
HINSTANCE hInstance, // handle to application instance
LPCTSTR lpIconName   // name string or resource identifier
); 成功返回HICON句柄
```

- 设置
  注册窗口类

# 光标资源

- 添加光标的资源
  光标的大小默认是32X32像素，每个光标有HotSpot，是当前鼠标的热点
- 加载资源

```c
HCURSOR LoadCursor(
HINSTANCE hInstance, // handle to application instance
LPCTSTR lpCursorName // name or resource identifier
); hInstance - 可以为NULL，获取系统默认的Cursor

```

- 设置资源
  在注册窗口时，设置光标
  使用SetCursor设置光标

HCURSOR SetCursor(
HCURSOR hCursor // handle to cursor
);
SetCursor 在 WM_SETCURSOR 消息中进行设置

- WM_SETCURSOR 消息参数
  wPARAM - 当前使用的光标句柄
  lPARAM - LOWORD 当前区域的代码（Hit-Test code )
  HTCLIENT / HTCAPTION…
  HIWORD - 当前鼠标消息ID

# 加速键资源

- 添加 资源添加加速键表，增加命令ID对应的加速键。
- 使用
  加载加速键表
  HACCEL LoadAccelerators(
  HINSTANCE hInstance, // handle to module
  LPCTSTR lpTableName // accelerator table name
  ); 返回加速键表句柄
  翻译加速键
  int TranslateAccelerator(
  HWND hWnd,//处理消息的窗口句柄
  HACCEL hAccTable, //加速键句柄
  LPMSG lpMsg //消息
  ); 如果是加速键，返回非零。
- 在WM_COMMAND中相应消息，消息参数
  wPARAM ： HIWORD 为1表示加速键，为0表示菜单。
  LOWORD 为命令ID。
  lParam：为0














