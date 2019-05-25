// differ.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "hpp/File_for_diff.hpp"
#include "hpp/LCS.hpp"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv)
{
    string a_filedir, b_filedir;

    if (argc > 2)
    {
        a_filedir = argv[1];
        b_filedir = argv[2];
    }
    else if (argc == 2)
    {
        a_filedir = argv[1];
        cout << "enter the dir of b_filedir" << endl;
        getline(cin, b_filedir);
    }
    else
    {
        cout << "enter the dir of a_filedir" << endl;
        getline(cin, a_filedir);
        cout << "enter the dir of b_filedir" << endl;
        getline(cin, b_filedir);
    }

    cout << a_filedir << endl
         << b_filedir << endl;
    File_for_diff A(a_filedir);
    File_for_diff B(b_filedir);
    LCS lcs(&A, &B);
    lcs.print_same_line();
    lcs.print_diff();
    return 0;
}
