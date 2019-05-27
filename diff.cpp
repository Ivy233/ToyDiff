// differ.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "hpp/File_for_diff.hpp"
#include "hpp/LCS.hpp"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv)
{
    string filedir[2];
    int format = 0;
    if (argc == 4)
    {
        if (strcmp(argv[1], "-nothing") == 0)
            format = 0;
        else if (strcmp(argv[1], "-format") == 0)
            format = 1;
        else if (strcmp(argv[1], "-basicformat") == 0)
            format = 2;
        filedir[0] = argv[2];
        filedir[1] = argv[3];
    }
    else if (argc == 3)
    {
        filedir[0] = argv[1];
        filedir[1] = argv[2];
    }
    else if (argc == 2)
    {
        filedir[0] = argv[1];
        cout << "enter the dir of filedir[1]" << endl;
        getline(cin, filedir[1]);
    }
    else
    {
        cout << "enter the dir of filedir[0]" << endl;
        getline(cin, filedir[0]);
        cout << "enter the dir of filedir[1]" << endl;
        getline(cin, filedir[1]);
    }

    cout << format << endl
         << filedir[0] << endl
         << filedir[1] << endl;
    File_for_diff A(filedir[0]);
    File_for_diff B(filedir[1]);
    LCS lcs(&A, &B);
    lcs.print_same_line();
    lcs.print_diff();
    lcs.modifyfile("D:\\tmp\\bbb.txt", 2);
    lcs.print_same_line();
    lcs.print_diff();
    return 0;
}
