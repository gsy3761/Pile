题目描述:
莫尔斯电码表示方式为：
```
    a/A .-
    b/B -...
    c/C -.-.
    d/D -..
    e/E .
    f/F ..-.
    g/G --.
    h/H ....
    i/I ..
    j/J .---
    k/K -.-
    l/L .-..
    m/M --
    n/N -.
    o/O ---
    p/P .--.
    q/Q --.-
    r/R .-.
    s/S ...
    t/T -
    u/U ..-
    v/V ...-
    w/W .--
    x/X -..-
    y/Y -.--
    z/Z --..
    0 .----
    1 ..---
    2 ...--
    3 ....-
    4 .....
    5 -....
    6 --...
    7 ---..
    8 ----.
    9 -----
```
其中字母部分不区分大小写。任务要求是将输入的字符串(测试数据中所有的字母字符均为大写字母，无须再做判断，且长度小于等于100)转换成莫尔斯电码，每个电码间用"==="分割开来

输入描述：
每行输入大写字母和数字构成的符号串，长度小于等于100，没有分隔符

输出描述：
对应的莫尔斯电码，每个莫尔斯码都用"==="隔开

样例输入:
ABCD123456EFG

样例输出:
.-===-...===-.-.===-..===..---===...--===....-===.....===-....===--...===.===..-.===--.