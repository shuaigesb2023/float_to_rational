这是一个用于将输入字符串转化为分数的代码
支持循环小数，返回值以一个pair返回，其中first成员为分子，second成员为分母

在ftr.cpp中含有一个模板化的函数，可以将自己写的整数类型作为返回值
但此类型需要支持成员之间的+ * / % = ==运算

在mian.cpp中包含了函数的初版代码，含有详细的注释和输入示例
使用unsigned long long作为分子分母的类型

在example.cpp中含有对ftr.cpp使用的示例代码
包含自定义类所需要的运算符的重载方式

本项目可以将ftr.cpp下载并使用include展开使用
所用到的库
ftr.cpp ： 
vector 使用了vector成员
utility 使用了pairc成员
string 使用了string成员

main.cpp：
与ftr.cpp相同
stdio 使用ptintf输出

example.cpp：
iostream 使用cout输出
