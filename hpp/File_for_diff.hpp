#ifndef _FILE_FOR_DIFF_HPP_
#define _FILE_FOR_DIFF_HPP_
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
class File_for_diff
{
public:
    using value_type = unsigned long long;
    using size_type = size_t;

private:
    static const std::hash<std::string> _M_diff_hasher;
    std::string _M_filedir;
    std::vector<value_type> _M_hashline;
    void _M_readfile()
    {
        _M_hashline.clear();
        std::ifstream _M_file;
        _M_file.open(_M_filedir, std::ios::in);
        if (_M_file.good())
        {
            std::string s;
            while (getline(_M_file, s))
                _M_hashline.push_back(_M_diff_hasher(s));
        }
        else if (_M_file.bad())
            std::cout << _M_filedir << ": IO error while reading" << std::endl;
        else if (_M_file.fail())
            std::cout << _M_filedir << ": Non-recoverable error has occurred" << std::endl;
        else
            std::cout << _M_filedir << ": Unknown error" << std::endl;
    }

public:
    void _M_debug() {}
    File_for_diff() { _M_filedir = ""; }
    File_for_diff(const char *filedir)
    {
        _M_filedir = filedir;
        _M_readfile();
    }
    File_for_diff(const std::string &filedir)
    {
        _M_filedir = filedir;
        _M_readfile();
    }
    bool operator==(const File_for_diff &b) const
    {
        return _M_hashline == b._M_hashline;
    }
    void change(const std::string &newfiledir)
    {
        _M_filedir = newfiledir;
        _M_readfile();
    }
    void change(const char *newfiledir)
    {
        _M_filedir = newfiledir;
        _M_readfile();
    }
    value_type operator[](const size_t &x) { return _M_hashline.at(x); }
    value_type at(const size_t &x) { return _M_hashline.at(x); }
    size_type size() { return _M_hashline.size(); }
};
#endif