# 字符串的统计字符串
[完整代码]()

**题目：**

给定一个字符串str， 返回str的统计字符串。

**举例：**

"aaabbcaadfe"的统计字符串为"a_3_b_2_c_1_a_2_d_1_f_1_e_1"

**补充问题：**

给定一个字符串的统计字符串cstr， 再给定一个整数Index, 返回cstr所代表的原始字符串上的第index个字符。例如， "a_1_b_100"所代表的原始字符串上第0个字符是'a'， 第50个字符是'b'。

**解答**
>对于原问题：
> 1. 若str为空，那么就返回空。
> 2. 若str不为空，那么就准备一个string res用于保存答案，一个int count用于表示当前字符是数量。res初始时为str[0]， count初始时为1。然后还需要一个整型i表示处理到哪个字符了，别越界，i初始从1开始，因为str[0]已经放在res中了。
> 3. 只要i不越界就进行下面的循环。比较str[i]与str[i-1]若两者相等就令count++，若两者不相等，就要放res中添加新东西了，res = res + '_' + char(count) + '_' + str[i]，同时让count重新等于1。注意到统计字符串最后没有下划线，我们若按照res = res + '_' + char(count) + '_' + str[i]处理，在循环中最后会加入最后元素，但是不会加入它的个数，最后的元素的个数将在循环外加入res = res + '_' + char(count)。

> 对于补充题目：
> 1. 需要一个bool stage，stage为true表示现在处在遇到字符的阶段，stage为false表示现在处在遇到连续字符统计的阶段。一个char cur，表示上一次遇到字符阶段时遇到的是cur字符。一个int num表示上一次遇到连续字符统计阶段是字符出现的数量。一个int sum表示目前遍历到的cstr的位置相当于原字符串的什么位置。初始stage=true, cur, num=0, sum=0.
> 2. 从左到右遍历cstr。
>   * 若遇到'_'则变换stage=!stage，
>   * 若当前stage=true，则将num加到sum上，检查sum有无大于等于index，若大于等于了    说明找到了要找的字符，返回这个字符cur。若没有，则需要继续。将cur替换为当前位置的字符，同时num=0，用于统计新的cur的个数。            
>   * 若stage=false，说明正处在字符统计阶段，计算num。
>   * 若遍历完cstr了还没有返回，再检查最后一个字符。因为每次sum是在遇到新的字符的时候才将num加到sum中的，所以对于最后一个字符还没有把它的num加到sum中，最后把这个num加到sum中，若sum>=index则返回cur，否则就是原str中没有要找的字符，返回0.