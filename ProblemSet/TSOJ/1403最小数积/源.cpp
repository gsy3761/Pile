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
int       main(void)
{
#ifdef InFile
    std::fstream fin;
    fin.open("./in.txt", std::ios::in);
    std::cin.rdbuf(fin.rdbuf());
#endif  // InFile

    while(std::cin >> n)
    {
        std::vector<LL> vec[2];
        for(int i = 0; i < 2; i++)
        {
            for(int j = 0; j < n; j++)
            {
                LL k;
                std::cin >> k;
                vec[i].push_back(k);
            }
            std::sort(vec[i].begin(), vec[i].end());
        }
        std::reverse(vec[0].begin(), vec[0].end());
        LL ans = 0;
        for(int i = 0; i < n; i++)
        {
            ans += vec[0][i] * vec[1][i];
        }
        std::cout << ans << std::endl;
    }
#ifdef InFile
    system("pause");
    Sleep(-1);
#endif  // InFile
    return 0;
}
