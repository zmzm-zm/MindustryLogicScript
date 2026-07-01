# 语法
## 关键字
### var
你可以使用var来声明一个变量  
并附上初始化值或不  
初始值可以是一个数，也可以是一个表达式  
但一个变量只能声明一次  
~~~mls
var a;  
var b = 10;  
var c = 4 + 1 / 2;  
var a = 3; ~ Error: " a " has been declared  
~ 想改变它的值，再次赋值即可  
a = 63;
~ 不进行初始化赋值时，自动初始化为-1027，请警惕这个值
~~~
### if
使用if来进行条件判断  
条件为**真-true**则执行当前if的代码块  
条件为**假-false**则不执行，或继续判断其他分支  
if分为三种  
- `if ($CONDITION) { $CODEBLOCK }`  
  这种会在检查条件`$CONDITION`后选择是否执行`$CODEBLOCK`  
- `elseif ($CONDITION) { $CODEBLOCK }`  
  这种必须接在**if**后边，作为另一个分支，**不可单数使用**，逻辑与上述一致  
- `else {$CODEBLOCK}`  
  这种必须接在**if**或**elseif**后边  
  但是没有条件，意为上方判断全不满足时，执行此代码块`$$CODEBLOCK`  
  不是必要分支  
~~~mls

~~~