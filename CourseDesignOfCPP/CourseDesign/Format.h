#pragma once
//#include<Windows.h>
#include <array>
#include <charconv>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>

template <class Key, class Val, class Map = std::map<Key, Val> >
std::string formatMap(const Map &map);

template <class T>
std::string format(const T &dat);

template <>
std::string format(const std::string &string);

template <>
std::string format(const char &c);

template <class Key, class Val, class Is = std::istream, class Map = std::map<Key, Val> >
Is &deFormatMap(Is &is, Map &map);

template <class T, class Is = std::istream>
Is &deFormat(Is &is, T &t);

template <class Is = std::istream>
Is &deFormat(Is &is, char &c);

// template<class Key,class Val,class Is = std::istream>
// Is& deFormat(Is& is, std::map<Key, Val>& map);

template <class Is = std::istream>
Is &deFormat(Is &is, std::string &str);

const std::map<char, std::string> TransformChar { { '\\', "\\\\" }, { '\n', "\\n" },
                                                  { '\'', "\\\'" }, { '\"', "\\\"" },
                                                  { '\r', "\\r" },  { '\f', "\\f" },
                                                  { '\v', "\\v" },  { '\t', "\\t" } };
const std::map<char, char>        RevTransformChar {
    { '\\', '\\' }, { 'n', '\n' }, { '\'', '\'' }, { '\"', '\"' },
    { 'r', '\r' },  { 'f', '\f' }, { 'v', '\v' },  { 't', '\t' },
};

template <class Key, class Val, class Map>
std::string formatMap(const Map &map)
{
    std::string res;
    res += "{";
    for(auto iter = map.begin(); iter != map.end(); iter++)
    {
        res += format(iter->first);
        res += ":";
        res += format(iter->second);
        res += ",";
    }
    res.pop_back();  // kill useless ','
    res += "}";
    return res;
}

template <class T>
std::string format(const T &dat)
{
    return std::to_string(dat);
    // std::to_chars(str, str + 107, dat);
    // return std::string(str);
}

template <>
std::string format(const std::string &string)
{
    std::string res;
    res += "\"";
    for(auto c: string)
    {
        if(TransformChar.find(c) != TransformChar.end())
        {
            res += TransformChar.find(c)->second;
        }
        else
        {
            res += c;
        }
    }
    res += "\"";
    return res;
}

template <>
std::string format(const char &c)
{
    if(TransformChar.find(c) != TransformChar.end())
    {
        return "\'" + TransformChar.find(c)->second + "\'";
    }
    else
    {
        return "\'" + std::string(1, c) + "\'";
    }
}

template <class Key, class Val, class Is, class Map>
Is &deFormatMap(Is &is, Map &map)
{
    if(is.peek() == '{')
    {
        is.get();
    }
    while(is.peek() != '}')
    {
        Key key;
        Val val;
        deFormat(is, key);
        if(is.peek() == ':')
        {
            is.get();
        }
        deFormat(is, val);
        if(is.peek() == ',')
        {
            is.get();
        }
        map.insert(std::pair<Key, Val>(key, val));
    }
    is.get();
    return is;
}

template <class T, class Is>
Is &deFormat(Is &is, T &t)
{
    is >> t;
    return is;
}

template <class Is>
Is &deFormat(Is &is, char &c)
{
    if(is.peek() == '\'')
    {
        is.get();
    }
    if(is.peek() == '\\')
    {
        is.get();
        if(RevTransformChar.find(is.peek()) != RevTransformChar.end())
        {
            c = RevTransformChar.find(is.peek())->second;
        }
        is.get();
    }
    else
    {
        c = is.get();
    }
    if(is.peek() == '\'')
    {
        is.get();
    }
    return is;
}

// template<class Key, class Val, class Is>
// Is& deFormat(Is& is, std::map<Key, Val>& map)
//{
//	deFormatMap<Key,Val,Is,std::map<Key,Val> >(is, map);
//	return is;
//}

template <class Is>
Is &deFormat(Is &is, std::string &str)
{
    if(is.peek() == '\"')
    {
        is.get();
    }
    while(is.peek() != '\"')
    {
        char c;
        c = is.get();
        str.push_back(c);
    }
    is.get();
    return is;
}

// int main(void)
//{
//	std::map<std::string, std::string> map;
//	std::stringstream ss("{\"name\":\"Rufus\",\"age\":\"15\"}");
//	deFormatMap<std::string, std::string>(ss, map);
//	std::cout << format<int, int>(map) << std::endl;
//}