# 关键字
## var
用于声明变量  
```
var a = 1;
```
后续可以对此变量进行操作  
```
a = 10;
a = 5 + 3 * 7 - 5;
```
如果没有声明就使用的话，会弹出错误  
```
b = 7;
```
```console
Error: " b " has not been declared
```
重复声明也会报错  
```
set a = 9;
```
```console
Error: " a " has been declared
```  
  
**MLS中不用声明类型**  
一切交给Mindustry处理就可以了  