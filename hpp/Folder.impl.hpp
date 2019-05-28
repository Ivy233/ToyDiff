#ifndef _FOLDER_IMPL_HPP_
#define _FOLDER_IMPL_HPP_
#include "Folder.hpp"
#include <iostream>
using std::cout;
using std::endl;
Folder::Folder(const string &filedir)
{
    _M_only_file = 0;
    _M_update_base(filedir);
    if (_M_only_file == 0 && _M_base_dir.size())
        _M_update_ext("");
}
void Folder::print_everything()
{
    cout << _M_only_file << endl;
    cout << _M_base_dir << endl;
    for (string ext_dir : _M_ext_dirs)
        cout << ext_dir << endl;
}
void Folder::_M_update_base(const string &filedir)
{
    _M_base_dir.clear();
    _M_ext_dirs.clear();
    _finddata_t fileinfo;
    long hfile = 0;
    if ((hfile = _findfirst(filedir.c_str(), &fileinfo)) != -1)
    {
        if (fileinfo.attrib & _A_ARCH)
        {
            size_t pos = std::max(filedir.find_last_of('/') + 1, filedir.find_last_of('\\') + 1);
            _M_base_dir = filedir.substr(0, pos);
            _M_ext_dirs.push_back(filedir.substr(pos));
            _M_only_file = 1;
        }
        else if (fileinfo.attrib & _A_SUBDIR)
        {
            _M_base_dir = filedir;
            if (_M_base_dir.back() != '/' && _M_base_dir.back() != '\\')
                _M_base_dir.push_back('\\');
        }
    }
    else
        cout << "Wrong file or folder" << endl;
}
void Folder::_M_update_ext(const string &dir)
{
    _finddata_t fileinfo;
    long hfile = 0;
    string p;
    if ((hfile = _findfirst(p.assign(_M_base_dir).append(dir).append("*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            if ((fileinfo.attrib & _A_SUBDIR) && (fileinfo.attrib & _A_HIDDEN) == 0)
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    _M_update_ext(p.assign(dir).append(fileinfo.name).append("\\"));
            }
            else if ((fileinfo.attrib & _A_HIDDEN) == 0)
                _M_ext_dirs.push_back(p.assign(dir).append(fileinfo.name));
        } while (_findnext(hfile, &fileinfo) == 0);
    }
}
void link(const Folder &A, const Folder &B, vector<LCS> &results, const int &_format)
{
    results.clear();
    if (A._M_only_file && B._M_only_file)
        results.push_back(LCS(A._M_base_dir + A._M_ext_dirs[0], B._M_base_dir + B._M_ext_dirs[0], _format));
    else
    {
        for (string ext_dir : A._M_ext_dirs)
        {
            size_t pos = std::find(B._M_ext_dirs.begin(), B._M_ext_dirs.end(), ext_dir) - B._M_ext_dirs.begin();
            if (pos != B._M_ext_dirs.size())
                results.push_back(LCS(A._M_base_dir + ext_dir, B._M_base_dir + B._M_ext_dirs[pos], _format));
            else
                cout << "File in A: " << ext_dir << " not found." << endl;
        }
    }
}
#endif