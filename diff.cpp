/*
 * File name: diff.cpp
 * Description: Folder.hpp, LCS.hpp的接口
 * Author: 王锦润
 * Version: 1
 * Date: 2019.5.27
 * History: 此程序被纳入git，可以直接使用git查询。
 */
#include "hpp/Folder.hpp"
#include "hpp/LCS.hpp"
#include <bits/stdc++.h>
using namespace std;
//存储结果
vector<LCS> results;
int main(int argc, char **argv)
{
    string filedir[2];
    int format = 0;
    if (argc == 4) //如果多余四个则认为第四个为format参数
    {
        filedir[0] = argv[1];
        filedir[1] = argv[2];
        if (strcmp(argv[3], "-basicformat") == 0)
            format = 1;
        else if (strcmp(argv[3], "-format") == 0)
            format = 2;
    }
    else if (argc == 3) //三个命令行参数
    {
        filedir[0] = argv[1];
        filedir[1] = argv[2];
    }
    else if (argc == 2) //两个命令行参数
    {
        filedir[0] = argv[1];
        cout << "enter the dir of filedir[1]" << endl;
        getline(cin, filedir[1]);
    }
    else //啥文件都没有
    {
        cout << "enter the dir of filedir[0]" << endl;
        getline(cin, filedir[0]);
        cout << "enter the dir of filedir[1]" << endl;
        getline(cin, filedir[1]);
    }
    Folder A(filedir[0]), B(filedir[1]);
    link(A, B, results, format);
    for (LCS result : results)
        result.print_diff();
    return 0;
}
