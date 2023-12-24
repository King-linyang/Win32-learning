# 绘图基础

- 绘图设备 DC（Device Context），绘图上下文/绘图描述表
- HDC - DC句柄，表示绘图设备
- GDI - Windows graphics device interface （Win32提供的绘图API）
- 颜色
  计算机使用红、绿、蓝，
  R - 0～255
  G - 0～255
  B - 0～255
  每一个点颜色是3个字节24位保存 0-2^24-1
  16位：5，5，6
  32位：8，8，8， 8绘图或透明度

- 颜色的使用
  COLORREF - 实际DWORD
  例如：COLORREF nColor = 0;

- 赋值使用RGB宏
  例如 : nColor = RGB( 0, 0, 255);

- 获取RGB值，
  GetRValue/GetGValue/GetBValue
  例如 : BYTE nRed = GetRValue( nColor );

## SetPixel 设置指定点的颜色

```c
COLORREF SetPixel(
HDC hdc,//DC句柄
int X,//X坐标
int Y,//Y坐标
COLORREF crColor //设置的颜色
); 返回点原来的颜色
```

- 线的使用(直线、弧线)
  MoveToEx – 指名窗口当前点
  LineTo - 从窗口当前点到指定点绘制一条直线
  当前点：上一次绘图时的最后一点，初始为（0，0）点。

- 封闭图形：能够用画刷填充的图形
  Rectangle / Ellipse 










