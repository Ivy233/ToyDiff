#ifndef _LCS_IMPL_HPP_
#define _LCS_IMPL_HPP_
#include "LCS.hpp"
void LCS::_M_read_file(const int &whichfile)
{
    _M_hashline[whichfile].clear();
    std::ifstream _M_file;
    _M_file.open(_M_filedir[whichfile], std::ios::in);
    if (_M_file.good())
    {
        string s;
        while (getline(_M_file, s))
            _M_hashline[whichfile].push_back(_M_diff_hasher(s));
    }
}
void LCS::_M_update()
{
    _M_same_line.clear();
    //LCS过程
    size_type size_A = _M_hashline[0].size(), size_B = _M_hashline[1].size();
    vector<vector<LCS_base>> _M_lcs;
    _M_lcs = vector<vector<LCS_base>>(size_A + 1, vector<LCS_base>(size_B + 1, 0));
    for (size_type i = 1; i <= size_A; i++)
        for (size_type j = 1; j <= size_B; j++)
        {
            if (_M_hashline[0].at(i - 1) == _M_hashline[1].at(j - 1))
                _M_lcs[i][j] = LCS_base(_M_lcs[i - 1][j - 1]._M_res + 1, i - 1, j - 1);
            else if (_M_lcs[i][j - 1]._M_res > _M_lcs[i - 1][j]._M_res)
                _M_lcs[i][j] = LCS_base(_M_lcs[i][j - 1]._M_res, i, j - 1);
            else
                _M_lcs[i][j] = LCS_base(_M_lcs[i - 1][j]._M_res, i - 1, j);
        }
    //哨兵两个，用于把LCS转化成合适的值
    _M_same_line.push_back(std::make_pair(size_A + 1, size_B + 1));
    for (size_type x = size_A, y = size_B; x && y;)
    {
        size_type xx = _M_lcs[x][y]._M_prev_x, yy = _M_lcs[x][y]._M_prev_y;
        if (x - xx == 1 && y - yy == 1)
            _M_same_line.push_back(std::make_pair(x, y));
        x = xx, y = yy;
    }
    _M_same_line.push_back(std::make_pair(0, 0));
    std::reverse(_M_same_line.begin(), _M_same_line.end());
}
void LCS::print_diff()
{
    for (size_type i = 1, Al, Ar, Bl, Br; i < _M_same_line.size(); i++)
    {
        Ar = _M_same_line[i].first, Br = _M_same_line[i].second;
        Al = _M_same_line[i - 1].first, Bl = _M_same_line[i - 1].second;
        if (Ar - Al > 1 && Br - Bl != 1)
        {
            cout << "modify ";
            if (Ar - Al > 2)
                cout << "line in A:" << Al + 1 << " ~ " << Ar - 1;
            else
                cout << "line in A:" << Al + 1;
            cout << " <======> ";
            if (Br - Bl > 2)
                cout << "line in B:" << Bl + 1 << " ~ " << Br - 1 << endl;
            else
                cout << "line in B:" << Bl + 1 << endl;
        }
        else if (Ar - Al > 1 && Br - Bl == 1)
        {
            cout << "delete ";
            if (Ar - Al > 2)
                cout << "line in A:" << Al + 1 << " ~ " << Ar - 1 << endl;
            else
                cout << "line in A:" << Al + 1 << endl;
        }
        else if (Ar - Al == 1 && Br - Bl > 1)
        {
            cout << "add ";
            if (Br - Bl > 2)
                cout << "line in B:" << Bl + 1 << " ~ " << Br - 1 << endl;
            else
                cout << "line in B:" << Bl + 1 << endl;
        }
    }
}
void LCS::swapfile()
{
    swap(_M_filedir[0], _M_filedir[1]);
    swap(_M_hashline[0], _M_hashline[1]);
    for (pair<size_type, size_type> &line : _M_same_line)
        std::swap(line.first, line.second);
}
void LCS::modifyfile(const string &_newfiledir, const int &whichfile)
{
    _M_filedir[whichfile] = _newfiledir;
    _M_read_file(whichfile);
    _M_update();
}
#endif