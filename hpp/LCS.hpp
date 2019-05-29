/*
 * File name: LCS.hpp
 * Description: 比较类，用于比较两个文件
 * Author: 王锦润
 * Version: 1
 * Date: 2019.5.27
 * History: 此程序被纳入git，可以直接使用git查询。
 */
//防卫式声明，必须要有
//就算没有重复包含也建议有，这是代码习惯
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
    //简单的声明
public:
    using size_type = size_t;
    using value_type = unsigned long long;

private:
    //子类，方便存储结果
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
    //static 哈希方法，仿函数方式调用hash
    static const std::hash<string> _M_diff_hasher;

private:
    string _M_filedir[2];                            //两个文件的路径
    vector<value_type> _M_hashline[2];               //读取结果，行hash
    vector<pair<size_type, size_type>> _M_same_line; //比较结果
    int _M_format;                                   //比较之前的格式化方式
    void _M_update();                                //LCS更新
    void _M_read_file(const int &file_switch);       //读取文件

public:
    LCS(const string &_filedir1, const string &_filedir2, const int &_format);
    void print_same();                                               //输出相同的行，调试功能
    void print_diff();                                               //输出不同的行，有功能
    void swapfile();                                                 //交换文件，这会交换LCS结果
    void modifyfile(const string &newfiledir, const int &whichfile); //更改文件路径，这会重新计算LCS
};
#include "LCS.impl.hpp"
#endif