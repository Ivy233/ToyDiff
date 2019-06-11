#ifndef _COMPARE_HPP_
#define _COMPARE_HPP_
#include "Folder.hpp"
#include "LCS.hpp"
#include <string>
#include <vector>
#define _M_cnt_cmds 6
class Compare
{
private:
    string _M_merge2where; //合并位置
    bool _M_need_merge;    //是否需要合并

    bool _M_cmds[_M_cnt_cmds]; //cmd命令
    Folder *_M_folder[2];      //文件夹

    vector<LCS *> _M_results;    //结果的存放位置
    vector<string> _M_in_A_in_B; //同时在A和B中的

private:
    void _M_link();  //寻找匹配的文件，放入LCS*的数组
    void _M_merge(); //合并（如果需要的话）

public:
    using size_type = LCS::size_type;

    Compare() {}
    Compare(const string &_A, const string &_B, const bool *_cmds); //不合并的时候接受的参数
    Compare(const string &_A, const string &_B, const string &_C);  //合并时接受的参数

    void print() //输出
    {
        for (LCS *const result : _M_results)
            result->print_diff();
    }
};
#include "Compare.impl.hpp"
#endif