![img_39.png](img_39.png)
![img_40.png](img_40.png)
![img_41.png](img_41.png)
![img_42.png](img_42.png)

![img_43.png](img_43.png)
![img_44.png](img_44.png)
![img_45.png](img_45.png)

```asm
assume cs:codesg
codesg segment
    mov ax, 0123h
    mov bx, 0456h
    add ax, bx
    add ax, ax
    
    mov ax, 4c00H
    int 21h

codesg ends

end
```
![img_46.png](img_46.png)
C:\Users\wangly\Downloads\MASM 6.x>MASM.EXE 1.asm
C:\Users\wangly\Downloads\MASM 6.x>LINK.EXE 1.obj

![img_47.png](img_47.png)

debug
![img_48.png](img_48.png)
![img_49.png](img_49.png)
-t 执行一步
-p 结束

