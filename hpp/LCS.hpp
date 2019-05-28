#ifndef _LCS_HPP_
#define _LCS_HPP_
#include <functional>
#include <string>
#include <vector>
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

private:
    string _M_filedir[2];
    vector<value_type> _M_hashline[2];
    vector<pair<size_type, size_type>> _M_same_line;
    int _M_format;
    void _M_update();
    void _M_read_file(const int &file_switch);

public:
    LCS(const string &_filedir1, const string &_filedir2, const int &_format);
    void print_same();
    void print_diff();
    void swapfile();
    void modifyfile(const string &newfiledir, const int &whichfile);
};
#include "LCS.impl.hpp"
#endif