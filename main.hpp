#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<list>
#include<vector>
#include<stack>
using namespace std;

enum States {
  endSt,        wrongSt,     emptySt, numberSt, logicSt,   // && ||   
  assignmentSt, separatorSt, dotSt,   arifmSt,  bitwiseSt, // & |
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
  dot, countSymbolType
};
struct Symbol {
  Symbol(char ch);
  char ch;
  SymbolType type;
};
enum tokenType {
  spaceType,  idType,      numbType,  assignType,
  logicType,  bitwiseType, arifmType, wrongType,  endType,
  //Res Words
  ifRes,    elseRes,   forRes,  withRes,  returnRes, inRes,
  //Bitwise Opretators
  bit1, //&
  bit2, //|
  //Arifm Opretators
  log1, //&&
  log2, //||
  //Separators
  semiCol,      // ;
  leftParent,   // (
  rightParent,  // )
  leftBrace,    // {
  rightBrace,   // }
  //countTokenTypes,
  //Non Terms:  (For Parser)
  emptyNt,    exprNt,       eqExNt,   idNt, 
  logOrExNt,  logOrEx1Nt,
  logAndExNt, logAndEx1Nt,
  bitOrExNt,  bitOrEx1Nt,
  bitAndExNt, bitAndEx1Nt,
  assignOpNt, assignExNt,   assgnOpNt,

  withNt,     with1Nt,      with2Nt,  with3Nt,
  returnNt,   return1Nt,    return2Nt,
  forNt,      for1Nt,       for2Nt,   for3Nt,

  ifNt,       if1Nt,        if2Nt,
  ifElseNt,   ifElse1Nt,
  
  blockNt,    block1Nt,     block2Nt,
  statemNt,   statemListNt, statemList1Nt,
  wrongNt,    progNt,       countNonTerms
};
struct ResWord {
  ResWord(string word, tokenType key);
  string word;
  tokenType key;
};
enum Act{
  idle,       endAct,
  shiftAct,   reduceAct,
  wrongAct
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
void addDefaultShifts(int nt);
void initParsMachine();
string getNameNt(int nt);
int parser(vector<LexAttr> &recLexs);
int getNt(int type);
int parseLex(LexAttr lex, stack<int>& buf, ofstream& fout);