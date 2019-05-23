# 字符串的转换路径问题
[完整代码]()

**题目：**

给定两个字符串，记为start和to，再给定一个字符串列表list，list中一定包含to，list中没有重复字符串。所有字符串都是小写。规定start每次只能改变一个字符，最终的目标是彻底变为to，但每次变成的新字符串必须在list中存在。请返回所有的最短的变换路径。

**举例：**

start="abc", end="cab", list={"cab", "acc", "cbc", "ccc", "cac", "cbb", "aab", "abb"}

转换路径的方法有很多种，但所有最短的转换路径如下：

abc -> abb -> aab -> cab

abc -> abb -> cbb -> cab

abc -> cbc -> cac -> cab

abc -> cbc -> cbb -> cab

