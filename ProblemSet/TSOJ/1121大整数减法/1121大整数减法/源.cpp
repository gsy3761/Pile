#define _CRT_SECURE_NO_WARNINGS  // shut up MS
//#define DEBUG
#include <algorithm>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
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
#ifdef DEBUG
#    include <Windows.h>  //sleep()
#    include <stdlib.h>   //system("pause")
#endif                    // DEBUG

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
namespace bit
{
using Pos        = short;
using Digt       = int;
using singleDigt = short;
using IntStore   = std::vector<singleDigt>;
const Pos BIN    = 2;
const Pos OCT    = 8;
const Pos DEC    = 10;
const Pos HXE    = 16;
char      itoc(int);
int       ctoi(char);
class BigInt
{
public:
    BigInt(Pos pos, long long def);
    ~BigInt();
    std::string          string(void) const;
    BigInt               operator+(const BigInt &b) const;
    BigInt               operator+=(const BigInt &b);
    BigInt               operator-(const BigInt &b) const;
    BigInt               operator*(const unsigned int &) const;
    BigInt               operator*(const BigInt &b) const;
    BigInt               operator/(const BigInt &b) const;
    bool                 operator<(const BigInt &b) const;
    bool                 operator==(const BigInt &b) const;
    friend std::ostream &operator<<(std::ostream &os, const BigInt &in);
    friend std::istream &operator>>(std::istream &os, BigInt &in);

private:
    IntStore    ReverseInt;
    Pos         pos;
    bool        postive;
    BigInt      move(Digt);
    bool        absSmaller(const BigInt &) const;
    inline void correctPostive(void);
    inline bool isZero(void) const;
};
BigInt::BigInt(Pos pos, long long def = 0): pos(pos)
{
    int i = 0;
    if(def == 0)
    {
        postive = false;
        // reverseInt = std::string(std::to_string(0));
        // ReverseInt.push_back(0);
    }
    else
    {
        if(def > 0)
        {
            postive = true;
        }
        else
        {
            postive = false;
            def     = -def;
        }
        Digt i = 0;
        while(def != 0)
        {
            ReverseInt.push_back(def % pos);
            def /= pos;
            i++;
        }
    }
}
BigInt::~BigInt()
{
    ReverseInt.clear();
}
std::string BigInt::string(void) const
{
    std::string ans;
    // correctPostive();
    if(isZero())
        return "0";
    Digt j = postive ? 0 : 1;
    if(!postive)
    {
        ans.push_back('-');
    }
    for(auto i = ReverseInt.rbegin(); i != ReverseInt.rend(); ++i, ++j)
    {
        ans.push_back(itoc(*i));
    }
    // ans.reserve();
    return ans;
}
BigInt BigInt::operator+(const BigInt &b) const
{
    if(pos != b.pos)
        throw std::invalid_argument("posation mismatch when +");
    if(postive == b.postive)
    {
        BigInt ans(pos);
        Digt   i     = 0;
        int    extra = 0;
        while(i < (Digt) ReverseInt.size() || i < (Digt) b.ReverseInt.size() || extra != 0)
        {
            if(i < (Digt) ReverseInt.size())
            {
                extra += ReverseInt[i];
            }
            if(i < (Digt) b.ReverseInt.size())
            {
                extra += b.ReverseInt[i];
            }
            ans.ReverseInt.push_back(extra % (singleDigt) pos);
            extra /= (singleDigt) pos;
            i++;
        }
        ans.postive = postive;
        ans.correctPostive();
        return ans;
    }
    else
    {
        BigInt b2(b);
        b2.postive = !b2.postive;
        return *this - b2;
    }

    // return BigInt(10);
}
BigInt BigInt::operator+=(const BigInt &b)
{
    *this = *this + b;
    return *this;
}
BigInt BigInt::operator-(const BigInt &b) const
{
    if(pos != b.pos)
        throw std::invalid_argument("posation mismatch when -");
    BigInt ans(pos);
    if(absSmaller(b))
    {
        ans         = b - *this;
        ans.postive = !ans.postive;
    }
    else
    {
        if(postive == b.postive)
        {
            Digt i     = 0;
            int  extra = 0;
            while(i < (Digt) ReverseInt.size() || i < (Digt) b.ReverseInt.size() || extra != 0)
            {
                if(i < (Digt) ReverseInt.size())
                {
                    extra += ReverseInt[i];
                }
                if(i < (Digt) b.ReverseInt.size())
                {
                    extra -= b.ReverseInt[i];
                }
                ans.ReverseInt.push_back((extra % (singleDigt) pos + (singleDigt) pos) %
                                         (singleDigt) pos);
                extra = (extra - ans.ReverseInt.back()) / (singleDigt) pos;
                i++;
            }
            ans.postive = postive;
            return ans;
        }
        else
        {
            BigInt b2(b);
            b2.postive = !b2.postive;
            return *this + b2;
        }
    }
    ans.correctPostive();
    return ans;
}
BigInt BigInt::operator*(const unsigned int &b) const
{
    BigInt       ans(pos);
    unsigned int extra = 0;
    Digt         i     = 0;
    while(i < (Digt) ReverseInt.size() || extra != 0)
    {
        if(i < (Digt) ReverseInt.size())
        {
            extra += ReverseInt[i] * b;
        }
        ans.ReverseInt.push_back(extra % pos);
        extra /= pos;
        i++;
    }
    ans.postive = postive;
    ans.correctPostive();
    return ans;
}
BigInt BigInt::operator*(const BigInt &b) const
{
    if(pos != b.pos)
        throw std::invalid_argument("posation mismatch when *");
    BigInt ans(pos);
    Digt   i = 0;
    while(i < (Digt) b.ReverseInt.size())
    {
        ans += ((*this) * b.ReverseInt[i]).move(i);
        i++;
    }
    ans.postive = (postive == b.postive);
    ans.correctPostive();
    return ans;
}
BigInt BigInt::operator/(const BigInt &b) const
{
    if(pos != b.pos)
        throw std::invalid_argument("posation mismatch when /");
    if(b.isZero())
        throw std::invalid_argument("1/0");
    return BigInt(10);
}
bool BigInt::operator<(const BigInt &b) const
{
    if(pos != b.pos)
        throw std::invalid_argument("posation mismatch when <");
    if(isZero() && b.isZero())
    {
        return false;
    }
    else
    {
        if(postive == b.postive)
        {
            return (!postive) ^ absSmaller(b);
        }
        else
        {
            return !postive;
        }
    }
}
bool BigInt::operator==(const BigInt &b) const
{
    if(pos != b.pos)
        throw std::invalid_argument("posation mismatch when ==");
    if(isZero() && b.isZero())
    {
        return true;
    }
    else
    {
        if(postive == b.postive && ReverseInt.size() == b.ReverseInt.size())
        {
            for(Digt i = 0; i < (Digt) ReverseInt.size(); i++)
            {
                if(ReverseInt[i] != b.ReverseInt[i])
                    return false;
            }
            return true;
        }
        else
        {
            return false;
        }
    }
}
BigInt BigInt::move(Digt dis = 0)
{
    IntStore newStore;
    Digt     i = 0;
    if(dis < 0)
        i = -dis;
    else
        for(Digt j = 0; j < dis; j++)
        {
            newStore.push_back(0);
        }
    while(i < (Digt) ReverseInt.size())
    {
        newStore.push_back(ReverseInt[i]);
        i++;
    }
    ReverseInt = newStore;
    return *this;
}
bool BigInt::absSmaller(const BigInt &b) const
{
    if(ReverseInt.size() == b.ReverseInt.size())
    {
        for(Digt i = ReverseInt.size() - 1; i != Digt(-1); --i)
        {
            if(ReverseInt[i] < b.ReverseInt[i])
                return true;
            if(b.ReverseInt[i] < ReverseInt[i])
                return false;
        }
        return false;
    }
    else
    {
        return ReverseInt.size() < b.ReverseInt.size();
    }
}
void BigInt::correctPostive(void)
{
    if(isZero())
    {
        postive = false;
        ReverseInt.clear();
    }
}
inline bool BigInt::isZero(void) const
{
    if(ReverseInt.size() == 0)
    {
        return true;
    }
    else
    {
        for(auto i: ReverseInt)
        {
            if(i != 0)
            {
                return false;
            }
        }
        return true;
    }
    // return ReverseInt.size() == 0 || ReverseInt.size() == 1 && ReverseInt[0] == 0;
}
char itoc(int in)
{
    if(in < 10)
    {
        return in + '0';
    }
    else
    {
        return in + 'A';
    }
    return 0;
}
int ctoi(char in)
{
    if(isdigit(in))
    {
        return in - '0';
    }
    else
    {
        if(isalpha(in))
        {
            return toupper(in) - 'A';
        }
        else
        {
            throw std::invalid_argument("unable to transfer Char");
        }
    }
}
std::ostream &operator<<(std::ostream &os, const BigInt &out)
{
    os << out.string();
    return os;
}
std::istream &operator>>(std::istream &is, BigInt &in)
{
    if(!isalnum(is.peek()) && is.peek() != '-' && is.peek() != '+')
    {
        is.get();
    }
    if(is.peek() == '-' || is.peek() == '+')
    {
        in.postive = (is.get() == '+');
    }
    else
    {
        in.postive = true;
    }
    in.ReverseInt.clear();
    while(isalnum(is.peek()))
    {
        in.ReverseInt.push_back(ctoi(is.get()));
    }
    std::reverse(in.ReverseInt.begin(), in.ReverseInt.end());
    in.correctPostive();
    return is;
}
}  // namespace bit
#define BIGINT

int n, m, a, b, j, k;
int main(void)
{
#ifdef DEBUG
    std::fstream fin;
    fin.open("./in.txt", std::ios::in);
    std::cin.rdbuf(fin.rdbuf());
#endif  // DEBUG
    bit::BigInt a(10), b(10);
    while(std::cin >> a >> b)
    {
        std::cout << a - b << std::endl;
    }
#ifdef DEBUG
    system("pause");
    system("pause");
    Sleep(-1);
#endif  // DEBUG

    return 0;
}
