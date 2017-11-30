#include "main.hpp"

int main()
{
    char ch;
    ifstream fin("program.txt");
    if(!fin.is_open()){
        cout<<"error while opening input the file\n";
        exit(0);
    }
    vector<LexAttr> recLexs;
    lexan(fin, ch, recLexs);
    printLexTable(recLexs);
    parser(recLexs);
    printParsTable(recLexs);
    fin.close();
    return 0;
}
