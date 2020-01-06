﻿#define _CRT_SECURE_NO_WARNINGS  // shut up MS//NOT fo CPP//scanf VS. scanf_s
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
using LL                       = long long;
using ULL                      = unsigned long long;
const int                MAX_N = 10007;
int                      n, m, a, b, j, k;
std::vector<std::string> table[] {
    { "5012588880247200305", "2404507230489008702", "8460060030487808287", "3036544020484800301",
      "2288524860609456784", "4052524050367808222", "5648048010007200900", "9668589660483600426",
      "4296068010364208580", "5404560030129456004", "4808048850007200005", "6060005640728256249",
      "7624022490721056965", "7444080090720000002", "2616068880724656424", "7892528850843008402",
      "4200000840243600307", "3632587200008256963", "7052521680607200301", "8040067290242400429",
      "7412580810843600420", "9488521620604656185", "1444086450482256366", "4028521680729008280",
      "8468047260244656728", "9660007260241808226", "6064569630964656548", "7264565640241056724",
      "6632528850246608102", "5040063270008256961", "2432584080368400425", "8672524020602400427",
      "8048040030849008886", "9636004890603008284", "2228044050128400125", "8824564890960000663",
      "3420004860844656301", "5072522490243600841", "1448048880369008100", "3604083210247808165",
      "5076008820363600187", "3608528850368400786", "7448588820244656189", "5820003270484208285",
      "1080548010360000180", "8400007260723456184", "1236060090122256720", "4864020840848400841",
      "8252524800364656066", "6696543240244208163", "4628043270487056787", "8228528820603008286",
      "5672520000485856186", "8884029690848256121", "1200542490485856008", "3420060030244208700",
      "2408588820001056602", "3812046480008256607", "3692045610006608523", "4832520840485856906",
      "4080006450364656789", "4088049660240000845", "9660000870364656064", "4412527200484208287",
      "6488524890120000428", "4624081650123600784", "4864083210844208465", "2256002460842256008",
      "1448580870009008288", "3248588070247808345", "1860544890607200485", "8256549600247200129",
      "3696000030840608647", "6216546420721056967", "1260007200127200961", "8856064890244656187",
      "4800068820846608404", "8404501680367808948", "2464504830723600361", "9068584050968400006",
      "3068044830487056064", "5460000840840000607", "9424562400006608523", "3816064890001056600",
      "9812523240364656789", "9664025670247200127", "7832580840721056609", "2220064020967808524",
      "5856543270604656902", "9248526450969456969" },
    { "72645656402410567240", "82525248003646560660", "74440800907200000020",
      "96685896604836004260", "60645696309646565480", "78925288508430084020",
      "48325208404858569060", "40285216807290082800", "54045600301294560040",
      "56725200004858561860", "56480480100072009000", "84000072607234561840",
      "22885248606094567840", "26160688807246564240", "14485808700090082880",
      "24085888200010566020", "90685840509684000060", "38160648900010566000",
      "46240816501236007840", "14480488803690081000", "30680448304870560640",
      "96360048906030082840", "48000688208466084040", "84680472602446567280",
      "34200600302442087000", "22200640209678085240", "36085288503684007860",
      "96600008703646560640", "40525240503678082220", "42960680103642085800",
      "66325288502466081020", "22560024608422560080", "12005424904858560080",
      "80480400308490088860", "84045016803678089480", "14440864504822563660",
      "74125808108436004200", "58565432706046569020", "64885248901200004280",
      "12360600901222567200", "96600072602418082260", "82285288206030082860",
      "24045072304890087020", "10805480103600001800" },
    { "906858405096840000609",
      "966000087036465606405",
      "240858882000105660207",
      "567252000048585618606",
      "663252885024660810201",
      "342006003024420870009",
      "402852168072900828009",
      "306804483048705606405",
      "144408645048225636603",
      "360852885036840078603",
      "741258081084360042000",
      "564804801000720090006",
      "123606009012225672009",
      "963600489060300828408",
      "144858087000900828807",
      "966858966048360042609",
      "846804726024465672807",
      "726456564024105672408" },
    { "1444086450482256366038",
      "3608528850368400786036",
      "8468047260244656728072",
      "3420060030244208700096",
      "1236060090122256720090",
      "7412580810843600420006",
      "4028521680729008280092",
      "5672520000485856186064",
      "2408588820001056602074",
      "9668589660483600426096",
      "7264565640241056724082",
      "9068584050968400006092" },
    { "36085288503684007860367",
      "72645656402410567240820",
      "24085888200010566020746",
      "14440864504822563660381",
      "40285216807290082800921",
      "12360600901222567200901" },
    { "360852885036840078603672", "144408645048225636603816", "402852168072900828009216" }
};
int main(void)
{
#ifdef InFile
    std::fstream fin;
    fin.open("./in.txt", std::ios::in);
    std::cin.rdbuf(fin.rdbuf());
#endif  // InFile
    while(std::cin >> n)
    {
        if(n <= 18)
        {
            std::vector<ULL> buffer { 0 };
            for(int i = 1; i <= n; i++)
            {
                std::vector<ULL> temp;
                for(auto u: buffer)
                {
                    for(size_t j = 0; j < 10; j++)
                    {
                        if(!(i != 1 && u == 0) && (u * 10 + j) % i == 0)
                        {
                            temp.push_back((u * 10 + j));
                        }
                    }
                }
                buffer.swap(temp);
            }
            std::sort(buffer.begin(), buffer.end());
            for(auto u: buffer)
            {
                if(u)
                {
                    std::cout << u << std::endl;
                }
            }
        }
        else
        {
            sort(table[n - 19].begin(), table[n - 19].end());
            for(auto u: table[n - 19])
            {
                std::cout << u << std::endl;
            }
        }
    }
#ifdef InFile
    system("pause");
    Sleep(-1);
#endif  // InFile
    return 0;
}
