/*
 * File name: Folder.impl.hpp
 * Description: 文件夹类，用于捕捉所有文件夹下的非隐藏文件
 * Author: 王锦润
 * Version: 1
 * Date: 2019.5.27
 * History: 此程序被纳入git，可以直接使用git查询。
 */
//防卫式声明，必须要有
//就算没有重复包含也建议有，这是代码习惯
#ifndef _FOLDER_IMPL_HPP_
#define _FOLDER_IMPL_HPP_
#include "Folder.hpp"
#include <iostream>
using std::cout;
using std::endl;
/*
 * Function: 构造函数
 * Description: 构建文件夹，并搜索所有在文件夹下的文件
 * Input: 文件路径
 * Calls: _M_update_base, _M_update_ext
 */
Folder::Folder(const string &filedir)
{
    _M_only_file = 0;                            //首先清空唯一文件属性
    _M_update_base(filedir);                     //然后尝试更新文件夹路径
    if (_M_only_file == 0 && _M_base_dir.size()) //如果更新成功，更新所有文件
        _M_update_ext("");
}
/*
 * Function: print_everything
 * Description: 打印所有的文件路径
 */
void Folder::print_everything()
{
    cout << _M_only_file << endl;
    cout << _M_base_dir << endl;
    for (string ext_dir : _M_ext_dirs)
        cout << ext_dir << endl;
}
/*
 * Function: _M_update_base
 * Description: 检验文件/文件夹，如果为单个文件则同时更新basedir和extdir，如果不是则只更新basedir
 * Input: 文件路径filedir
 */
void Folder::_M_update_base(const string &filedir)
{
    //首先清空文件属性
    _M_base_dir.clear();
    _M_ext_dirs.clear();
    _finddata_t fileinfo;                                       //C的结构体，用于访问文件系统
    long hfile = 0;                                             //文件句柄
    if ((hfile = _findfirst(filedir.c_str(), &fileinfo)) != -1) //如果文件存在
    {
        //如果是文件
        if (fileinfo.attrib & _A_ARCH)
        {
            size_t pos = std::max(filedir.find_last_of('/') + 1, filedir.find_last_of('\\') + 1);
            _M_base_dir = filedir.substr(0, pos);       //basedir更新
            _M_ext_dirs.push_back(filedir.substr(pos)); //更新extdir
            _M_only_file = 1;
        }
        else if (fileinfo.attrib & _A_SUBDIR)
        {
            _M_base_dir = filedir; //更新文件夹
            if (_M_base_dir.back() != '/' && _M_base_dir.back() != '\\')
                _M_base_dir.push_back('\\'); //如果没有则自动补全
        }
    }
    //如果访问不到则啥都不做
    else
        cout << "Wrong file or folder" << endl;
}
/*
 * Function: _M_update_base
 * Description: 检验文件/文件夹，如果为单个文件则同时更新basedir和extdir，如果不是则只更新basedir
 * Input: 文件路径filedir
 */
void Folder::_M_update_ext(const string &dir)
{
    _finddata_t fileinfo;
    long hfile = 0;
    string p;
    if ((hfile = _findfirst(p.assign(_M_base_dir).append(dir).append("*").c_str(), &fileinfo)) != -1) //如果找到内容
    {
        //按照文件更新
        do
        {
            //如果是非隐藏文件夹则递归更新
            if ((fileinfo.attrib & _A_SUBDIR) && (fileinfo.attrib & _A_HIDDEN) == 0)
            {
                //.和..是两个必备文件夹，..会递归到上层，需要避开
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    _M_update_ext(p.assign(dir).append(fileinfo.name).append("\\"));
            }
            //如果是文件则加入文件
            else if ((fileinfo.attrib & _A_HIDDEN) == 0)
                _M_ext_dirs.push_back(p.assign(dir).append(fileinfo.name));
        } while (_findnext(hfile, &fileinfo) == 0); //句柄的用处
    }
}
#endif