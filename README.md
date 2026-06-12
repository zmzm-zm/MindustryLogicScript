# Mindustry Logic Script  
**See an English version at [`this`](./README_EN.md)** 
**README最后修改日期26.6.9** 
本仓库提供了一个编译器  
用于将mls脚本语言转化为Mindustry Logic，即像素工厂逻辑  
具体信息见[`本仓库Wiki`](https://zmzm-zm.github.io/MindustryLogicScript)  
## 关于mls  
- **mls不是市面上任何一种语言**  
可能会有重名，雷同等，纯属意外  
具体语法可以见[`本仓库Wiki`](https://zmzm-zm.github.io/MindustryLogicScript)  
- **mls不是一门编程语言**  
它是为了简化Mindustry Logic并提供更高级的特性  
在被转化为Mindustry Logic后在游戏上运行  
所以它并不能被编译器编译为汇编代码  
但他有一些基础的逻辑，控制语句等等  
并且提供各种语法糖和功能模板，给常见逻辑和功能封装了函数  
- **mls是一个无类型的语言**  
因为具体类型检查等都由游戏运行时决定  
而且Mindustry Logic本身就弱类型  
所以即使你写`"Hello World" / 3`也不会编译错误  
**不过这个功能在考虑之内**  
会检查不可能正确的运算，如`"Hello World" / 3`  
> 目前仍在开发中，只有极少数功能可用  

## 如何使用
- 在本仓库的[release页面](https://github.com/zmzm-zm/MindustryLogicScript/releases)下载编译器  
	> 如果没有，那就是连初版都还没做出来  

- 设置环境变量，使命令可以被找到  
- 输入编译命令，例如  
	```console
	mls output input1.mls input2.msl 
	```
	第一个参数为输出文件的名字  
	第二个即以后的为输入文件  
	**目前仅支持单文件**，不会对第二个以后的文件进行处理  
- 输出的`output.ml`即为结果  
	复制粘贴到游戏即可使用
	> 到目前输出仍为原生Mindustry Logic  
	后续会加入蓝图功能