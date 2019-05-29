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
const string _C_basicformat = "-basicformat";
const string _C_format = "-format";
int main(int argc, char **argv)
{
    int format = 0;
    vector<string> vec_argv;
    vector<LCS> results;
    string filedir[2];
    int filecnt = 0;

    // 整理所有命令行参数
    for (int i = 1; i < argc; i++)
    {
        filedir[0] = argv[i];
        vec_argv.push_back(filedir[0]);
    }
    // 检测特定命令行参数是否存在
    if (find(vec_argv.begin(), vec_argv.end(), _C_basicformat) != vec_argv.end())
        format = 1;
    else if (find(vec_argv.begin(), vec_argv.end(), _C_format) != vec_argv.end())
        format = 2;
    else
        format = 0;
    // 考虑剩下的命令行参数
    for (const string &tmp_argv : vec_argv)
    {
        // 控制参数一般以-开头
        if (tmp_argv[0] != '-')
            filedir[filecnt++] = tmp_argv;
        // 到比较上限则跳出
        if (filecnt == 2)
            break;
    }
    //如果参数不足则额外输入
    while (filecnt < 2)
    {
        cout << "input filedir[" << filecnt << "]: " << endl;
        cin >> filedir[filecnt++];
    }
    cout << format << endl
         << filedir[0] << endl
         << filedir[1] << endl;
    Folder A(filedir[0]), B(filedir[1]);
    link(A, B, results, format);
    for (LCS result : results)
        result.print_diff();
    return 0;
}
