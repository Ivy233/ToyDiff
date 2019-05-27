#ifndef _LCS_HPP_
#define _LCS_HPP_
//#define debug
#include "File_for_diff.hpp"
class LCS
{
public:
    using size_type = File_for_diff::size_type;
    using value_type = File_for_diff::value_type;

private:
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

    File_for_diff *A, *B;
    std::vector<std::pair<size_type, size_type>> _M_same_line;

private:
    void update()
    {
        _M_same_line.clear();
        //LCS过程
        size_type size_A = A->size(), size_B = B->size();
        std::vector<std::vector<LCS_base>> _M_lcs;
        _M_lcs = std::vector<std::vector<LCS_base>>(size_A + 1, std::vector<LCS_base>(size_B + 1, 0));
        for (size_type i = 1; i <= size_A; i++)
            for (size_type j = 1; j <= size_B; j++)
            {
                if (A->at(i - 1) == B->at(j - 1))
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

public:
    LCS(File_for_diff *_A, File_for_diff *_B) : A(_A), B(_B) { update(); }
    void print_same_line()
    {
        for (std::pair<size_type, size_type> line : _M_same_line)
            std::cout << line.first << " " << line.second << std::endl;
    }

    void print_diff()
    {
        for (size_type i = 1, Al, Ar, Bl, Br; i < _M_same_line.size(); i++)
        {
            Ar = _M_same_line[i].first, Br = _M_same_line[i].second;
            Al = _M_same_line[i - 1].first, Bl = _M_same_line[i - 1].second;
            if (Ar - Al > 1 && Br - Bl != 1)
            {
                std::cout << "modify ";
                if (Ar - Al > 2)
                    std::cout << "line in A:" << Al + 1 << " ~ " << Ar - 1;
                else
                    std::cout << "line in A:" << Al + 1;
                std::cout << " <======> ";
                if (Br - Bl > 2)
                    std::cout << "line in B:" << Bl + 1 << " ~ " << Br - 1 << std::endl;
                else
                    std::cout << "line in B:" << Bl + 1 << std::endl;
            }
            else if (Ar - Al > 1 && Br - Bl == 1)
            {
                std::cout << "delete ";
                if (Ar - Al > 2)
                    std::cout << "line in A:" << Al + 1 << " ~ " << Ar - 1 << std::endl;
                else
                    std::cout << "line in A:" << Al + 1 << std::endl;
            }
            else if (Ar - Al == 1 && Br - Bl > 1)
            {
                std::cout << "add ";
                if (Br - Bl > 2)
                    std::cout << "line in B:" << Bl + 1 << " ~ " << Br - 1 << std::endl;
                else
                    std::cout << "line in B:" << Bl + 1 << std::endl;
            }
        }
    }
    void swapfile()
    {
        std::swap(A, B);
        update();
    }
    void modifyfile(const std::string &newfiledir, const int &whichfile)
    {
        switch (whichfile)
        {
        case 1:
            A->change(newfiledir);
            update();
            break;
        case 2:
            B->change(newfiledir);
            update();
            break;
        default:
            std::cout << "whichone?" << std::endl;
        }
    }
    void modifyfile(const char *newfiledir, const int &whichfile)
    {
        switch (whichfile)
        {
        case 1:
            A->change(newfiledir);
            update();
            break;
        case 2:
            B->change(newfiledir);
            update();
            break;
        default:
            std::cout << "whichone?" << std::endl;
        }
    }
};
#endif