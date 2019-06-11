/*
 * File name: Folder.hpp
 * Description: 文件夹类，用于捕捉所有文件夹下的非隐藏文件
 * Author: 王锦润
 * Version: 1
 * Date: 2019.5.27
 * History: 此程序被纳入git，可以直接使用git查询。
 */
//防卫式声明，必须要有
//就算没有重复包含也建议有，这是代码习惯
#ifndef _FOLDER_HPP_
#define _FOLDER_HPP_
//friend成员函数导致必须要包含
#include <io.h>
#include <string>
#include <vector>
//减少std::的使用
using std::string;
using std::vector;

class Folder
{
private:
    /*
     * base_dir与ext_dirs的区别
     * 在只有一个文件时, 文件夹为base_dir, 文件名为ext_dir
     * 在有多个文件时，公共祖先为base_dir, ext_dir = 完整路径 - base_dir
     * 由于输入只可能为路径或者单个文件，因此公共祖先就是该路径或者文件所在文件夹
     */
    string _M_base_dir;
    vector<string> _M_ext_dirs;
    //判定是否为单个文件，这样可以防止单文件对比单文件的不匹配
    bool _M_only_file;
    //私有化更新，防止外部随意调用
    void _M_update_base(const string &filedir);
    void _M_update_ext(const string &dir);
    Folder() {}

public:
    Folder(const string &filedir); //此处会同时调用两个私有化函数
    void print_everything();       //验证用
    bool is_only_file() const { return _M_only_file; }
    friend class Compare;
};
#include "Folder.impl.hpp" //实现hpp
#endif