# 介绍
这是[MLS](https://github.com/zmzm-zm/MindustryLogicScript)的**Wiki**网页，由markdown文件生成，部署在`GitHub Pages`上  
网页相关见[这里](#关于这个网页本身)
  
## 关于项目
### 想法和初衷  
我很喜欢玩[Mindustry](https://github.com/Anuken/Mindustry)这款游戏  
游戏内有一个部分叫做**逻辑**，即**Mindustry Logic**，简称为ML  
它允许你通过图形化编程来操控方块，炮塔，单位，甚至渲染游戏原生内容，修改游戏规则等等  
这听起来不错，但事实是  
- **臃肿的图形化编程导致可见的上下文极短**  
  无论PC还是PE，可见上下文不超过约15条命令  
  这导致需要频繁翻看，效率低下  
- **语言的低级以至于开发难度大大增加**  
  ML类似汇编语言，甚至不如汇编语言  
  开发效率远远比不上高级语言  
  举个例子吧，在C++等高级语言中，判断奇偶可能像这样  
  ```cpp  
  if(num & 0) cout << "even\n";
  else cout << "odd\n";
  ```  
  而且还可以封装为函数多次使用  
  像这样  
  ```cpp
  bool isOdd(int num) {
  	return num & 1;
  }
  ```
  看到了吧，极其简单  
  但在ML中呢?
  ```ml
  set a 3
  op mod isOdd a 2
  jump 5 notEqual isOdd 0
  set msg "Odd"
  jump 6 always x false
  set msg "Even"
  print msg
  printflush message1
  ```
  **先不要批判我这串ML写的好不好**，就算你能写的再好，你要也要手动处理jump  
  jump就相当编程里的if + goto，而会写代码的人，**绝对不会使用goto语句**  
  但goto语句在汇编语言中是必要的，这就会导致代码复杂度极速上升  
  ~~**更别说把他封装为函数了**~~  
  会涉及更多复杂的处理，标签出入栈，数组管理等  
  顺便一提，ML只甚至没有原声数组，需要你用内存元和边界变量手搓  
    
  所以，**开发一个高级语言很有必要**  
  而且不仅是模仿高级语法  
  更会配提供开发模板，语法糖等  
  你甚至可以写库  
  
## 关于**MLS**  
- [语言本身](./language/introduction.md)  
- [编译器](./compiler/introduction.md)