#define _CRT_SECURE_NO_WARNINGS  // shut up MS//NOT fo CPP//scanf VS. scanf_s
//#define DEBUG
//#define InFile
#include <algorithm>
#include <ctype.h>
#include <fstream>   //file
#include <iostream>  //stream
#include <math.h>
#include <sstream>  //stringstream
#include <stdio.h>
#include <string.h>
#include <string>
// STL
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
// STL
#ifdef InFile
#    include <Windows.h>  //sleep()
#    include <stdlib.h>   //system("pause")
#endif                    // InFile
#ifdef DEBUG
#    define Check(X) std::cout << "Express \"" << #    X << "\" is " << (X) << std::endl
#else
#    define Check(X) ;
#endif
// template <typename T> void swap(T &a, T &b)
//{
//	T t = a;
//	a = b;
//	b = t;
//}
using namespace std;
using LL        = long long;
using ULL       = unsigned long long;
const int MAX_N = 10007;
int       n, m, a, b, j, k;
ULL       square(ULL max, ULL min)
{
    ULL ans = 0;
    for(ULL i = 1; i <= min; i++)
    {
        ans += (max - i + 1) * (min - i + 1);
    }
    return ans;
}
int main(void)
{
#ifdef InFile
    std::fstream fin;
    fin.open("./in.txt", std::ios::in);
    std::cin.rdbuf(fin.rdbuf());
#endif  // InFile

    while(std::cin >> n >> m)
    {
        ULL Max = std::max(n, m);
        ULL Min = std::min(n, m);
        std::cout << square(Max, Min) << ' '
                  << (Min * (Min + 1) / 2) * (Max * (Max + 1) / 2) - square(Max, Min) << std::endl;
    }
#ifdef InFile
    system("pause");
    Sleep(-1);
#endif  // InFile
    return 0;
}
