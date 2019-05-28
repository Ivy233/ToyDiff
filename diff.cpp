#include "hpp/Folder.hpp"
#include "hpp/LCS.hpp"
#include <bits/stdc++.h>
using namespace std;
vector<LCS> results;
int main(int argc, char **argv)
{
    string filedir[2];
    int format = 0;
    if (argc == 4)
    {
        filedir[0] = argv[1];
        filedir[1] = argv[2];
        if (strcmp(argv[3], "-basicformat") == 0)
            format = 1;
        else if (strcmp(argv[3], "-format") == 0)
            format = 2;
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
    Folder A(filedir[0]), B(filedir[1]);
    link(A, B, results, format);
    for (LCS result : results)
        result.print_diff();
    return 0;
}
