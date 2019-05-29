/*
 * File name: LCS.impl.hpp
 * Description: 文件夹类，用于捕捉所有文件夹下的非隐藏文件
 * Author: 王锦润
 * Version: 1
 * Date: 2019.5.27
 * History: 此程序被纳入git，可以直接使用git查询。
 */
//防卫式声明，必须要有
//就算没有重复包含也建议有，这是代码习惯
#ifndef _LCS_IMPL_HPP_
#define _LCS_IMPL_HPP_
#include "LCS.hpp"
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;
/*
 * Function: 构造函数
 * Description: 构建文件夹，并搜索所有在文件夹下的文件
 * Input: 两个文件路径，格式化方式
 * Calls: _M_readfile, _M_update
 */
LCS::LCS(const string &_filedir1, const string &_filedir2, const int &_format)
{
    _M_format = _format;
    _M_filedir[0] = _filedir1;
    _M_filedir[1] = _filedir2;
    _M_read_file(0);
    _M_read_file(1);
    _M_update();
}
/*
 * Function: _M_read_file
 * Description: 读取文件，可能会格式化文件
 * Input: 读取文件号0-1
 */
void LCS::_M_read_file(const int &whichfile)
{
    //hashline清空
    _M_hashline[whichfile].clear();
    //如果需要文件格式化
    if (_M_format == 2)
    {
        //得到后缀名
        string ext = _M_filedir[whichfile].substr(_M_filedir[whichfile].find('.'));
        //如果是clang-format可识别后缀
        if (ext == ".cpp" || ext == ".hpp" || ext == ".c" || ext == ".h" || ext == ".cc")
        {
            string p("clang-format -i -style=llvm ");
            p.append(_M_filedir[whichfile]);
            system(p.c_str()); //命令行格式化
        }
        //其他也可以加
    }
    //读取文件
    std::ifstream _M_file;
    _M_file.open(_M_filedir[whichfile], std::ios::in);
    if (_M_file.good())
    {
        string s;
        while (getline(_M_file, s)) //按行读取
        {
            if (_M_format == 1) //如果需要基本格式化
            {
                if (s.empty()) //空行滤过
                    continue;
                s.erase(0, s.find_first_not_of(" ")); //行前空格滤过
                s.erase(s.find_last_not_of(" ") + 1); //行后空格滤过
            }
            _M_hashline[whichfile].push_back(_M_diff_hasher(s)); //按行hash加入结果
        }
    }
}
/*
 * Function: _M_update
 * Description: 更新LCS结果，这里是LCS算法的核心
 */
void LCS::_M_update()
{
    //清空结果以等待重新产生
    _M_same_line.clear();
    //LCS初始化
    size_type size_A = _M_hashline[0].size(), size_B = _M_hashline[1].size();       //求出两个数组的大小
    vector<vector<LCS_base>> _M_lcs;                                                //这里可能开成static会更好
    _M_lcs = vector<vector<LCS_base>>(size_A + 1, vector<LCS_base>(size_B + 1, 0)); //初始化数组
    //LCS过程，其实是DP
    for (size_type i = 1; i <= size_A; i++)
        for (size_type j = 1; j <= size_B; j++)
        {
            //如果相同则贪心的从[i-1][j-1]更新
            if (_M_hashline[0].at(i - 1) == _M_hashline[1].at(j - 1))
                _M_lcs[i][j] = LCS_base(_M_lcs[i - 1][j - 1]._M_res + 1, i - 1, j - 1);
            //否则选择[i][j-1],[i-1][j]中较大的一个
            else if (_M_lcs[i][j - 1]._M_res > _M_lcs[i - 1][j]._M_res)
                _M_lcs[i][j] = LCS_base(_M_lcs[i][j - 1]._M_res, i, j - 1);
            else
                _M_lcs[i][j] = LCS_base(_M_lcs[i - 1][j]._M_res, i - 1, j);
        }
    //哨兵两个，用于把LCS转化成合适的值
    _M_same_line.push_back(std::make_pair(size_A + 1, size_B + 1));
    //LCS回溯，查找可能更新的值
    for (size_type x = size_A, y = size_B; x && y;) //这里不能再循环内部更新，因为更新x后会影响y的更新
    {
        size_type xx = _M_lcs[x][y]._M_prev_x, yy = _M_lcs[x][y]._M_prev_y;
        if (x - xx == 1 && y - yy == 1)
            _M_same_line.push_back(std::make_pair(x, y));
        x = xx, y = yy;
    }
    //哨兵
    _M_same_line.push_back(std::make_pair(0, 0));
    //由于是从后往前回溯，因此需要反转
    std::reverse(_M_same_line.begin(), _M_same_line.end());
}
/*
 * Function: print_diff
 * Description: 输出不同之处
 */
void LCS::print_diff()
{
    //标记是否有差异出现
    bool flag = 0;
    cout << "Compare " << _M_filedir[0] << " with " << _M_filedir[1] << ":" << endl;
    for (size_type i = 1, Al, Ar, Bl, Br; i < _M_same_line.size(); i++)
    {
        Ar = _M_same_line[i].first, Br = _M_same_line[i].second;
        Al = _M_same_line[i - 1].first, Bl = _M_same_line[i - 1].second;
        //修改
        if (Ar - Al > 1 && Br - Bl != 1)
        {
            flag = 1;
            cout << "\tmodify ";
            //超过一行
            if (Ar - Al > 2)
                cout << "line in A:" << Al + 1 << " ~ " << Ar - 1;
            //只有一行
            else
                cout << "line in A:" << Al + 1;
            cout << " <======> ";
            if (Br - Bl > 2)
                cout << "line in B:" << Bl + 1 << " ~ " << Br - 1 << endl;
            else
                cout << "line in B:" << Bl + 1 << endl;
        }
        //删除
        else if (Ar - Al > 1 && Br - Bl == 1)
        {
            flag = 1;
            cout << "\tdelete ";
            if (Ar - Al > 2)
                cout << "line in A:" << Al + 1 << " ~ " << Ar - 1 << endl;
            else
                cout << "line in A:" << Al + 1 << endl;
        } //添加
        else if (Ar - Al == 1 && Br - Bl > 1)
        {
            flag = 1;
            cout << "\tadd ";
            if (Br - Bl > 2)
                cout << "line in B:" << Bl + 1 << " ~ " << Br - 1 << endl;
            else
                cout << "line in B:" << Bl + 1 << endl;
        }
    }
    if (flag == 0)
        cout << "\tNothing different." << endl
             << endl;
}
/*
 * Function: print_same
 * Description: 输出相同之处
 */
void LCS::print_same()
{
    for (pair<size_type, size_type> line : _M_same_line)
        cout << line.first << " " << line.second << endl;
}
/*
 * Function: swapfile
 * Description: 交换两个文件
 */
void LCS::swapfile()
{
    swap(_M_filedir[0], _M_filedir[1]);   //交换文件路径
    swap(_M_hashline[0], _M_hashline[1]); //交换行hash结果
    for (pair<size_type, size_type> &line : _M_same_line)
        std::swap(line.first, line.second); //交换LCS结果
}
/*
 * Function: modifyfile
 * Description: 修改文件信息
 * Input: 新的文件路径，修改哪个文件
 */
void LCS::modifyfile(const string &_newfiledir, const int &whichfile)
{
    _M_filedir[whichfile] = _newfiledir;
    _M_read_file(whichfile); //重新读取文件
    _M_update();             //重新LCS
}
#endif