#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <list>
#include <vector>
#include <stack>
using namespace std;

enum States {
    endSt,        wrongSt,     empSt, numbSt,  logicSt,   // && ||
    assignmentSt, separatorSt, dotSt, arifmSt, bitwiseSt, // & |
    wordSt,       countStates
};
enum SymbolType {
    digit,      // 0..9
    letter,     // a..z A..Z _
    bitwise,    // & |
    assignment, // =
    arifm,      // * / + -
    separator,  // ; ( ) { } \n
    wrongSymb,  // #
    dot,  countSymbolType
};
struct Symbol {
    Symbol(char ch);
    char ch;
    SymbolType type;
};
enum tokenType {
    spaceT,  idT,      numbT,  assignT,
    logicT,  bitwiseT, arifmT, wrongT,  endT,
    //Res Words
    ifR,    elseR,   forR,  withR,  returnR, inR,
    //Bitwise Opretators
    bit1, //&
    bit2, //|
    //Arifm Opretators
    log1, //&&
    log2, //||
    //Separators
    semiCol,   // ;
    leftPar,   // (
    rightPar,  // )
    leftBrace,    // {
    rightBrace,   // }
    //countTokenTypes,
    //Non Terms:  (For Parser)
    EMP,  EQ, ID,
    EX,   AEX,
    BoEX, BoEX1,
    BaEX, BaEX1,
    LoEX, LoEX1,
    LaEX, LaEX1,

    W,  W1, W2, W3,
    R,  R1, R2, R3,
    F,  F1, F2, F3,

    IF, IF1,  IF2,  IF3,  IF4,
    IE, IE1,

    B,  B1, B2,
    S,  SL, SL1,
    WR, PR, countNT
};
struct ResWord {
    ResWord(string word, tokenType key);
    string word;
    tokenType key;
};
enum Act{
    idle,       endAct,
    shift,   reduce,
    wrong
};
struct LexAttr{
    LexAttr(int numstr,string token, int tokType, char state);
    int numstr, tokType;
    string token;
    char state;
};
struct StateAct {
    StateAct();
    StateAct(int next, Act act);
    int next;
    Act act;
};
struct StateMachine {
    StateMachine(int stateNum,int symbNum, Act act);
    void addThread(int oldState, int symb, int nextState, Act signal);
    int stateNum, symbNum, currState = 0, numstr = 1;
    StateAct** changeSt;
};
//For Lexer
void lexan(ifstream& in, char ch, vector<LexAttr> &recLexs);
void initLexMachine();
void initHashTable();
void addHash(string word, tokenType key);
void printLexTable(vector<LexAttr> &recLexs);
int transletter(Symbol& symb, vector<LexAttr> &recLexs);
int findResWord(string word);
int getSepType(char c);
int classifier(string str, char state, vector<LexAttr> &recLexs);
//For Parser
int parseNt(int last, int nt, int& act);
void reduceNext(stack<int>& buf, int next,ofstream& fout);
int reduceLast(stack<int>&buf, int nextAct, int last, ofstream& fout);
void addShifts(int nt);
void initParsMachine();
string printNameNt(int nt);
int parser(vector<LexAttr> &recLexs);
int nT(int type);
int parseLex(LexAttr lex, stack<int>& buf, ofstream& fout);
