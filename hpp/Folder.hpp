#ifndef _FOLDER_HPP_
#define _FOLDER_HPP_
#include "LCS.hpp"
#include <io.h>
#include <string>
#include <vector>
using std::string;
using std::vector;

class Folder
{
private:
    string _M_base_dir;
    vector<string> _M_ext_dirs;
    bool _M_only_file;
    void _M_update_base(const string &filedir);
    void _M_update_ext(const string &dir);

public:
    Folder(const string &filedir);
    void print_everything();
    bool is_only_file() const { return _M_only_file; }
    friend void link(const Folder &A, const Folder &B, vector<LCS> &results, const int &_format);
};
#include "Folder.impl.hpp"
#endif