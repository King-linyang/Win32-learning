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

# 位图绘制

- 位图相关  
  光栅图形 - 记录图像中每一点的颜色等信息。  
  矢量图形 - 记录图像算法、绘图指令等。  
  HBITMAP - 位图句柄
- 位图的使用  
  1 在资源中添加位图资源  
  2 从资源中加载位图LoadBitmap  
  3 创建一个与当前DC相匹配的DC（内存DC）  
  HDC CreateCompatibleDC(  
  HDC hdc //当前DC句柄，可以为NULL（使用屏幕DC）  
  ); 返回创建好的DC句柄  
  4 将位图放入匹配的DC中 SelectObject  
  5 成像（1:1）  
  BOOL BitBlt(  
  HDC hdcDest, //目的DC  
  int nXDest, // 目的左上X坐标  
  int nYDest, // 目的左上Y坐标  
  int nWidth, // 目的宽度  
  int nHeight, // 目的高度  
  HDC hdcSrc, //源DC  
  int nXSrc, // 源左上X坐标  
  int nYSrc, // 源左上Y坐标  
  DWORD dwRop //成像方法 SRCCOPY  
  );  
  缩放成像  
  BOOL StretchBlt(  
  HDC hdcDest, // handle to destination DC  
  int nXOriginDest, // x-coord of destination upper-left corner  
  int nYOriginDest, // y-coord of destination upper-left corner  
  int nWidthDest, // width of destination rectangle  
  int nHeightDest, // height of destination rectangle  
  HDC hdcSrc, // handle to source DC  
  int nXOriginSrc, // x-coord of source upper-left corner  
  int nYOriginSrc, // y-coord of source upper-left corner  
  int nWidthSrc, // 源DC宽  
  int nHeightSrc, // 源DC高  
  DWORD dwRop // raster operation code  
  );  
  6 取出位图  
  SelectObject  
  7 释放位图  
  DeleteObject  
  8 释放匹配的DC  
  DeleteDC

# 字体

- 字体相关
  Window常用的字体为 TrueType格式的字体文件
  字体名 - 标识字体类型
  HFONT - 字体句柄

- 字体的使用
  1 创建字体
  HFONT CreateFont(
  int nHeight, //字体高度
  int nWidth, //字体宽度
  int nEscapement, //字符串倾斜角度
  int nOrientation,//字符旋转角度
  int fnWeight, //字体的粗细
  DWORD fdwItalic, //斜体
  DWORD fdwUnderline, //字符下划线
  DWORD fdwStrikeOut, //删除线
  DWORD fdwCharSet, //字符集  
  DWORD fdwOutputPrecision,//输出精度
  DWORD fdwClipPrecision,//剪切精度
  DWORD fdwQuality,//输出质量
  DWORD fdwPitchAndFamily,//匹配字体
  LPCTSTR lpszFace //字体名称
  );
  2 应用字体到DC
  SelectObject
  3 绘制文字
  DrawText/TextOut
  4 取出字体
  SelectObject
  5 删除字体
  DeleteObject


