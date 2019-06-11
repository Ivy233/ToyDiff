/*
 * File name: Compare.impl.hpp
 * Description: 顶层类实现
 * Author: 王锦润
 * Version: 2
 * Date: 2019.6.11
 * History: 此程序被纳入git，可以直接使用git查询。
 */
//防卫式声明，必须要有
//就算没有重复包含也建议有，这是代码习惯
#ifndef _COMPARE_IMPL_HPP_
#define _COMPARE_IMPL_HPP_
#include "Compare.hpp"
/*
 * Function: 构造函数
 * Description: 构建文件夹，匹配并获得差异
 * Input: 两个文件(夹)路径，cmd输入
 * Calls: _M_link
 */
Compare::Compare(const string &_A, const string &_B, const bool *_cmds)
{
    _M_need_merge = 0;
    _M_folder[0] = new Folder(_A);
    _M_folder[1] = new Folder(_B);
    for (int i = 0; i < _M_cnt_cmds; i++)
        _M_cmds[i] = _cmds[i]; //复制一份cmd，一个类对象一个cmd命令，方便后续窗口化管理
    _M_link();
}
/*
 * Function: 构造函数
 * Description: 构建文件夹，匹配并获得差异，最后合并，忽视最初输入的cmd选项
 * Input: 两个文件(夹)路径，cmd输入
 * Calls: _M_link,_M_merge
 */
Compare::Compare(const string &_A, const string &_B, const string &_C)
{
    _M_dir_merge = _C;
    _M_need_merge = 1;
    _M_folder[0] = new Folder(_A);
    _M_folder[1] = new Folder(_B);
    for (int i = 0; i < _M_cnt_cmds; i++)
        _M_cmds[i] = 0;
    _M_link();
    _M_merge();
}
/*
 * Function: _M_link
 * Description: 匹配文件夹，对每一对匹配成功的进行LCS
 */
void Compare::_M_link()
{
    _M_results.clear();                                           //清空
    if (_M_folder[0]->_M_only_file && _M_folder[1]->_M_only_file) //如果都是单一文件，则无视文件名强制比较
        _M_results.push_back(new LCS(
            _M_folder[0]->_M_base_dir + _M_folder[0]->_M_ext_dirs[0],
            _M_folder[1]->_M_base_dir + _M_folder[1]->_M_ext_dirs[0],
            _M_cmds));
    else
    {
        //取两者交集进行LCS比较
        vector<string> diff_A_B;
        //STL求交集
        std::set_intersection(
            _M_folder[0]->_M_ext_dirs.begin(), _M_folder[0]->_M_ext_dirs.end(),
            _M_folder[1]->_M_ext_dirs.begin(), _M_folder[1]->_M_ext_dirs.end(),
            std::inserter(_M_file_intersection, _M_file_intersection.begin()));
        for (const string &ext_file : _M_file_intersection)
            _M_results.push_back(new LCS(
                _M_folder[0]->_M_base_dir + ext_file,
                _M_folder[1]->_M_base_dir + ext_file, _M_cmds));

        //在A但是不在B中，直接给出结果
        std::set_difference(
            _M_folder[0]->_M_ext_dirs.begin(), _M_folder[0]->_M_ext_dirs.end(),
            _M_folder[1]->_M_ext_dirs.begin(), _M_folder[1]->_M_ext_dirs.end(),
            std::inserter(diff_A_B, diff_A_B.begin())); //STL直接求差集
        for (const string &ext_file : diff_A_B)
            cout << "File in A but not in B: " << _M_folder[0]->_M_base_dir << ext_file << endl;

        //在B但不在A中，直接给出结果
        diff_A_B.clear(); //复用空间
        std::set_difference(
            _M_folder[1]->_M_ext_dirs.begin(), _M_folder[1]->_M_ext_dirs.end(),
            _M_folder[0]->_M_ext_dirs.begin(), _M_folder[0]->_M_ext_dirs.end(),
            std::inserter(diff_A_B, diff_A_B.begin())); //STL直接求差集
        for (const string &ext_file : diff_A_B)
            cout << "File not in A but in B: " << _M_folder[1]->_M_base_dir << ext_file << endl;
    }
}
/*
 * Function: _M_merge
 * Description: 合并文件夹内部匹配的内容
 */
void Compare::_M_merge()
{
    //单个文件则直接输出
    if (_M_folder[0]->_M_only_file && _M_folder[1]->_M_only_file)
        for (LCS *result : _M_results)
            result->merge(_M_dir_merge);
    //很多文件则依照公共路径一起输出
    else
    {
        size_type siz = _M_results.size(); //公共集的大小
        if (_M_dir_merge.back() != '/' || _M_dir_merge.back() != '\\')
            _M_dir_merge.append("\\"); //防止最后路径d:\tmp\section之类
        for (size_type i = 0; i < siz; i++)
            _M_results[i]->merge(_M_dir_merge + _M_file_intersection[i]); //合并
    }
}
#endif