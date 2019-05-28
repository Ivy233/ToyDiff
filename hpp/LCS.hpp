#ifndef _LCS_HPP_
#define _LCS_HPP_
//#define debug
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;
class LCS
{
public:
    using size_type = size_t;
    using value_type = unsigned long long;

private:
    struct LCS_base
    {
        size_type _M_res, _M_prev_x, _M_prev_y;
        LCS_base(value_type _res = 0, size_type _prev_x = 0, size_type _prev_y = 0)
        {
            _M_res = _res;
            _M_prev_x = _prev_x;
            _M_prev_y = _prev_y;
        }
    };
    static const std::hash<string> _M_diff_hasher;

    string _M_filedir[2];
    vector<value_type> _M_hashline[2];
    //LCS
    vector<pair<size_type, size_type>> _M_same_line;

    void _M_update();
    void _M_read_file(const int &file_switch);

public:
    LCS(const string &_filedir1, const string &_filedir2)
    {
        _M_filedir[0] = _filedir1;
        _M_filedir[1] = _filedir2;
        _M_read_file(0);
        _M_read_file(1);
        _M_update();
    }
    void print_same()
    {
        for (pair<size_type, size_type> line : _M_same_line)
            cout << line.first << " " << line.second << endl;
    }

    void print_diff();
    void swapfile();
    void modifyfile(const string &newfiledir, const int &whichfile);
};
#include "LCS.impl.hpp"
#endif