#ifndef _COMPARE_IMPL_HPP_
#define _COMPARE_IMPL_HPP_
#include "Compare.hpp"
Compare::Compare(const string &_A, const string &_B, const bool *_cmds)
{
    _M_need_merge = 0;
    _M_folder[0] = new Folder(_A);
    _M_folder[1] = new Folder(_B);
    for (int i = 0; i < _M_cnt_cmds; i++)
        _M_cmds[i] = _cmds[i];
    _M_link();
}
Compare::Compare(const string &_A, const string &_B, const string &_C)
{
    _M_merge2where = _C;
    _M_need_merge = 1;
    _M_folder[0] = new Folder(_A);
    _M_folder[1] = new Folder(_B);
    for (int i = 0; i < _M_cnt_cmds; i++)
        _M_cmds[i] = 0;
    _M_link();
    _M_merge();
}
void Compare::_M_link()
{
    _M_results.clear();                                           //清空
    if (_M_folder[0]->_M_only_file && _M_folder[1]->_M_only_file) //如果都是单一文件，则无视文件名强制比较
        _M_results.push_back(new LCS(_M_folder[0]->_M_base_dir + _M_folder[0]->_M_ext_dirs[0],
                                     _M_folder[1]->_M_base_dir + _M_folder[1]->_M_ext_dirs[0], _M_cmds));
    else
    {
        //取两者交集进行LCS比较
        vector<string> diff_A_B;
        std::set_intersection(_M_folder[0]->_M_ext_dirs.begin(), _M_folder[0]->_M_ext_dirs.end(),
                              _M_folder[1]->_M_ext_dirs.begin(), _M_folder[1]->_M_ext_dirs.end(),
                              std::inserter(_M_in_A_in_B, _M_in_A_in_B.begin()));

        for (const string &ext_file : _M_in_A_in_B)
            _M_results.push_back(new LCS(_M_folder[0]->_M_base_dir + ext_file,
                                         _M_folder[1]->_M_base_dir + ext_file, _M_cmds));
        //在A但是不在B中，直接给出结果
        std::set_difference(_M_folder[0]->_M_ext_dirs.begin(), _M_folder[0]->_M_ext_dirs.end(),
                            _M_folder[1]->_M_ext_dirs.begin(), _M_folder[1]->_M_ext_dirs.end(),
                            std::inserter(diff_A_B, diff_A_B.begin())); //STL直接求差集
        for (const string &ext_file : diff_A_B)
            cout << "File in A but not in B: " << _M_folder[0]->_M_base_dir << ext_file << endl;
        //在B但不在A中，直接给出结果
        diff_A_B.clear();
        std::set_difference(_M_folder[1]->_M_ext_dirs.begin(), _M_folder[1]->_M_ext_dirs.end(),
                            _M_folder[0]->_M_ext_dirs.begin(), _M_folder[0]->_M_ext_dirs.end(),
                            std::inserter(diff_A_B, diff_A_B.begin())); //STL直接求差集
        for (const string &ext_file : diff_A_B)
            cout << "File not in A but in B: " << _M_folder[1]->_M_base_dir << ext_file << endl;
    }
}
void Compare::_M_merge()
{
    if (_M_folder[0]->_M_only_file && _M_folder[1]->_M_only_file)
        for (LCS *result : _M_results)
            result->merge(_M_merge2where);
    else
    {
        size_type siz = _M_results.size();
        if (_M_merge2where.back() != '/' || _M_merge2where.back() != '\\')
            _M_merge2where.append("\\");
        for (size_type i = 0; i < siz; i++)
            _M_results[i]->merge(_M_merge2where + _M_in_A_in_B[i]);
    }
}
#endif