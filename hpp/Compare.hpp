/*
 * File name: Compare.hpp
 * Description: 顶层类，整合LCS和Folder，减少相互的底层调用，使结构更容易控制
 * Author: 王锦润
 * Version: 2
 * Date: 2019.6.11
 * History: 此程序被纳入git，可以直接使用git查询。
 */
//防卫式声明，必须要有
//就算没有重复包含也建议有，这是代码习惯
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
    string _M_dir_merge;                 //合并位置
    bool _M_need_merge;                  //是否需要合并
    bool _M_cmds[_M_cnt_cmds];           //cmd命令
    Folder *_M_folder[2];                //文件夹
    vector<LCS *> _M_results;            //结果的存放位置
    vector<string> _M_file_intersection; //同时在A和B中的，方便合并，注意和差集的区别

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