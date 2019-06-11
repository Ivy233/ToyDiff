/*
 * File name: diff.cpp
 * Description: Folder.hpp, LCS.hpp的接口
 * Author: 王锦润
 * Version: 1
 * Date: 2019.5.27
 * History: 此程序被纳入git，可以直接使用git查询。
 */
#include "hpp/Compare.hpp"
#include <bits/stdc++.h>
using namespace std;
//存储结果
const string _C_format = "--format";                         //代码格式化
const string _C_ignore_space = "--ignore-space";             //行前与行后空格
const string _C_ignore_all_space = "--ignore-all-space";     //所有空格(包括代码内的)
const string _C_ignore_blank_lines = "--ignore-blank-lines"; //空行
const string _C_ignore_tabs = "--ignore-tabs";               //所有tab
int main(int argc, char **argv)
{
    /*
     * 0: _cmd_format
     * 1: _cmd_ignore_space
     * 2: _cmd_ignore_all_space
     * 3: _cmd_ignore_blank_lines
     * 4: _cmd_ignore_tabs
    */
    bool _cmds[_M_cnt_cmds] = {0};
    vector<string> _argvs;
    string _file_dir[3];
    int _file_cnt = 0;

    // 整理所有命令行参数
    for (int i = 1; i < argc; i++)
    {
        _file_dir[0] = argv[i];
        _argvs.push_back(_file_dir[0]);
    }
    for (const string &_argv : _argvs)
    {
        if (_argv == _C_format)
            _cmds[0] = 1;
        else if (_argv == _C_ignore_space)
            _cmds[1] = 1;
        else if (_argv == _C_ignore_all_space)
            _cmds[2] = 1;
        else if (_argv == _C_ignore_blank_lines)
            _cmds[3] = 1;
        else if (_argv == _C_ignore_tabs)
            _cmds[4] = 1;
        else if (_file_cnt < 3 && _argv[0] != '-')
            _file_dir[_file_cnt++] = _argv;
    }
    //如果参数不足则额外输入
    while (_file_cnt < 2)
    {
        cout << "input filedir[" << _file_cnt << "]: " << endl;
        cin >> _file_dir[_file_cnt++];
    }
    cout << _file_dir[0] << endl
         << _file_dir[1] << endl;

    Compare cmp;
    if (_file_cnt == 2)
        cmp = Compare(_file_dir[0], _file_dir[1], _cmds);
    else if (_file_cnt == 3)
        cmp = Compare(_file_dir[0], _file_dir[1], _file_dir[2]);
    cmp.print();
    return 0;
}