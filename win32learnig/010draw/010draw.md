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

# GDI绘图对象-画笔

- 画笔的作用  
  线的颜色、线型、线粗。  
  HPEN - 画笔句柄
- 画笔的使用  
  1 创建画笔  
  HPEN CreatePen(  
  int fnPenStyle, //画笔的样式  
  int nWidth, //画笔的粗细  
  COLORREF crColor //画笔的颜色  
  );创建成功返回句柄

  PS_SOILD - 实心线，可以支持多个像素宽其他线型只能是一个像素宽。

  2 将画笔应用到DC中  
  HGDIOBJ SelectObject(  
  HDC hdc,//绘图设备句柄  
  HGDIOBJ hgdiobj //GDI绘图对象句柄，画笔句柄  
  );返回原来的GDI绘图对象句柄  
  注意保存原来DC当中画笔。  
  3 绘图  
  4 取出DC中的画笔  
  将原来的画笔，使用SelectObject函数，放入到设备DC中，就会将我们创建的画笔取出。  
  5 释放画笔  
  BOOL DeleteObject(  
  HGDIOBJ hObject //GDI绘图对象句柄，画笔句柄  
  );  
  只能删除不被DC使用的画笔，所以在释放前，必须将画笔从DC中取出。

# GDI绘图对象-画刷

- 画刷相关  
  画刷 - 封闭图形的填充的颜色、图案  
  HBRUSH - 画刷句柄
- 画刷的使用  
  1 创建画刷  
  CreateSolidBrush - 创建实心画刷  
  CreateHatchBrush - 创建纹理画刷  
  2 将画刷应用到DC中  
  SelectObject  
  3 绘图  
  4 将画刷从DC中取出  
  SelectObject  
  5 删除画刷  
  DeleteObject

- 其他  
  可以使用 GetStockObject 函数获取系统维护的画刷、画笔等。  
  如果不使用画刷填充，需要使用NULL_BRUSH参数，获取不填充的画刷。  
  GetStockObject返回的画刷不需要DeleteObject。  










