#define _CRT_SECURE_NO_WARNINGS
//#define DEBUG
#include <algorithm>
#include <ctype.h>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
template <typename T>
void swap(T &a, T &b)
{
    T t = a;
    a   = b;
    b   = t;
}
const int MAX_N = 10007;
int       n, m, a, b, j, k;
int       main(void)
{
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif  // DEBUG
    int i = 0;
    int tmp[30];
    while(std::cin >> tmp[i++])
        ;
    i--;
    std::sort(tmp, tmp + i);
    for(int j = 0; j < i; j++)
    {
        std::cout << tmp[j] << std::endl;
    }

#ifdef DEBUG
    system("pause");
    system("pause");
#endif  // DEBUG

    return 0;
}
