#include "main.h"
int main(int argc, char *argv[])
{
    char ch;
    ifstream fin(argv[1]);
    if(!fin.is_open()){
        cout<<"error while opening input the file\n";
        exit(0);
    }
    vector<LexAttr> recLexs;
    lexan(fin, ch, recLexs);
    printLexTable(recLexs);
    parser(recLexs);
    fin.close();
    return 0;
    return 0;
}
