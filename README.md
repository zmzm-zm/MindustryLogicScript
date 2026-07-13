# Mindustry Logic Script  
**See an English version at [this](./README_EN.md)**  
**README最后修改日期26.7.13**  
本仓库提供了一个编译器  
用于将mls脚本语言转化为**Mindustry Logic**，即像素工厂逻辑  
集体信息见[Wiki](#Wiki)  
## 关于mls  
- **mls不是市面上任何一种语言**  
可能会有重名，雷同等，纯属意外  
具体语法可以见[本仓库Wiki](https://zmzm-zm.github.io/MindustryLogicScript)  
- **mls不是一门编程语言**  
它是为了简化Mindustry Logic并提供更高级的特性  
在被转化为Mindustry Logic后在游戏上运行  
所以它并不能被编译器编译为汇编代码  
但他有一些基础的逻辑，控制语句等等  
并且提供各种语法糖和功能模板，给常见逻辑和功能封装了函数  
- **mls是一个弱类型的语言**  
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
	mls output input1.mls input2.mls 
	```
	第一个参数为输出文件的名字  
	第二个即以后的为输入文件  
	**目前仅支持单文件**，不会对第二个以后的文件进行处理  
- 输出的`output.ml`即为结果  
	复制粘贴到游戏即可使用
	> 到目前输出仍为原生Mindustry Logic  
	后续会加入蓝图功能  
## Wiki
### 声明
本项目Wiki页面代码在AI辅助下完成，即使用了大语言模型进行代码生成，因为我并不会前端  
但是所有功能性代码均经过人工测试和审核，所有文档内容，即*.md文件均由人工编写  
**我想说的是**，如果你喜欢这个风格的网页，可以直接[拿走使用](#使用)  
**但是必须标明出处**，即使它大部分由AI生成，但是调试，测试，精雕等我仍然付出了心血  
具体信息见[本仓库Wiki](https://zmzm-zm.github.io/MindustryLogicScript)  
如果[打不开Wiki网页](#本地浏览Wiki)
### 本地浏览Wiki
如果你打不开Wiki网页  
可以本地浏览，具体操作如下  
> 需要使用Linux命令行

1. 获取文件
	- 浏览器页面下载  
	![浏览器页面下载](./sources/download_in_page.png)
	- [Release页面下载](https://github.com/zmzm-zm/MindustryLogicScript/releases)  
	- git工具下载  
	```console
	git clone https://github.com/zmzm-zm/MindustryLogicScript
	```
2. 进入wiki文件夹  
	```console
	cd MindustryLogicScript/wiki
	```
3. 创建本地服务器  
	- 使用python3  
	```console
	python3 -m http.server 8080
	```
	没有python请先下载
	```console
	sudo apt install python
	```
	- 使用nodejs
	```console
	http-server
	```
	需下载
	```
	sudo apt install nodejs npm
	npm install -g http-server
	```
4. 访问
	- 使用python3  
	在浏览器网址输入`http://localhost:8000/index.html`
	- 使用nodejs  
	在浏览器网址输入`http://127.0.0.1:8080/index.html`
### 使用
如果你要拿走这个Wiki  
这里是使用方法  
建议使用node.js  
在Wiki根目录下运行服务器  
提前下载nodejs和http-server
~~~console
~/wiki $ http-server
~~~
如果你修改或增加了md文件，请运行[generate-manifest.js](./wiki/generate-manifest.js)  
文件内有详细说明  
运行及其示例输出:
~~~console
~/wiki $ node generate-manifest.js
[generate-manifest] 已生成 manifest.json
  根目录文件: 1 个
  分组:       2 个
  总文档数:   4 篇
~~~
> 不过它只支持一层目录，即docs下最多再有一层目录，因为我不确定多层目录如何显示，我也没有这个需求，你想要的话可以尝试编写相关逻辑

#### 可能的疑难杂症
- 你更改了网页逻辑却没有效果？  
	如果你是Edge，尝试`ctrl+shift+R`进行强制刷新，或者清除浏览器对此Wiki文件的缓存  
	其他浏览器我不确定是不是`ctrl+shift+R`，但清除浏览器对此Wiki文件的缓存理应有效  
	~~这个离谱的Bug浪费了我一个下午的时间，你能想象加了一堆`console.log()但控制台没有任何输出的场景吗`~~  