![img.png](img.png)
![img_1.png](img_1.png)

![img_2.png](img_2.png)
dw定义字  
db定义字符串    底层是存储ascii  

![img_3.png](img_3.png)

![img_4.png](img_4.png)
```asm
assume cs:codesg,ds:datasg
datasg segment
    db 'Basic'
    db 'iNfor'
datasg ends

codesg segment
start:
    mov ax,datasg
    mov ds,ax
    mov bx,0
    mov cx,5

s:
    mov al,[bx]
    and al,11011111B
    mov [bx],al
    inc bx
    loop s

    mov bx,5
    mov cx,11
s0: mov al,[bx]
    or al,00100000B
    mov [bx],al
    inc bx
    loop s0
    
    mov ax,4c00h
    int 21h
codesg ends
end start
codesg ends
end start

```
![img_5.png](img_5.png)
![img_6.png](img_6.png)


![img_7.png](img_7.png)

![img_8.png](img_8.png)

![img_9.png](img_9.png)
```asm
assume cs:codesg,ds:datasg
datasg segment
    db 'welcome to cloud'
    db '................'
datasg ends
codesg segment
start
    mov ax,datasg
    mov ds,ax
    mov si,0
    mov di,16
    
    mov cx,8
s:  mov ax,[si]
    mov [di],ax
    add si,2
    add di,2
    loop s

    mov ax,4c00h
    int 21h
codesg ends
end start
```
![img_10.png](img_10.png)

![img_11.png](img_11.png)

