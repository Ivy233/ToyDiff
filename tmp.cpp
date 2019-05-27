#include <io.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
void getFiles_all(const string &path, vector<string> &files)
{
    long hFile = 0;
    _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            if (fileinfo.attrib & _A_SUBDIR)
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                {
                    files.push_back(p.assign(path).append("\\").append(fileinfo.name));
                    getFiles_all(p.assign(path).append("\\").append(fileinfo.name), files);
                }
            }
            else
                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
        } while (_findnext(hFile, &fileinfo) == 0);
    }
    else
        files.push_back(path);
}
int main()
{
    string basic_path;
    cin >> basic_path;
    vector<string> files;
    getFiles_all(basic_path, files);
    for (auto file : files)
        cout << file << endl;
    return 0;
}