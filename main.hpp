#include<iostream>
#include<fstream>
#include<cctype>
#include<map>
#include<string>
#include<list>
#include<vector>
#include<stack>
using namespace std;

enum States {
  endSt,        wrongSt,     emptySt, numberSt, logicSt,   // && ||   
  assignmentSt, separatorSt, dotSt,   arifmSt,  bitwiseSt, // & |
  wordSt, countStates
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
  ifRes,    elseRes,   forRes,  withRes,  returnRes,
  //Bitwise Opretators
  bit1, //&
  bit2, //|
  //Separators
  semiCol,      // ;
  leftParent,   // (
  rightParent,  // )
  leftBrace,    // {
  rightBrace,   // }
  //countTokenTypes, (21)

  //Non Terms:  (For Parser)
  emptyNt,    exprNt, eqExNt, //numbNt, idNt,
  logOrExNt,  logOrEx1Nt,   logOrEx2Nt,
  logAndExNt, logAndEx1Nt,  logAndEx2Nt,
  bitOrExNt,  bitOrEx1Nt,  bitOrEx2Nt,
  bitAndExNt, bitAndEx1Nt, bitAndEx2Nt,
  withNt,   with1Nt,   with2Nt,     with3Nt,  with4Nt, with5Nt,
  returnNt, return1Nt, return2Nt, return3Nt,
  forNt,    for1Nt,    for2Nt, for3Nt, for4Nt, for5Nt, for6Nt, for7Nt,
  ifElseNt, ifElse1Nt,
  ifNt,     if1Nt, if2Nt, if3Nt, if4Nt,  
  assignNt, assign1Nt, assign2Nt,
  blockNt,  block1Nt, block2Nt,
  statemNt, statemListNt,   
  wrongNt,  assgnOpNt, 
  progNt,
  countNonTerms
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
int reduceLast(stack<int>buf, int nextAct, int last, ofstream& fout);
void addStatementShifts(int nt);
void addExprShifts(int nt);
void addDefaultShifts(int nt);
void initParsMachine();
void printParsTable(vector<LexAttr> &recLexs);
string getNameNt(int nt);
int parser(vector<LexAttr> &recLexs);
int getNt(int type);
int parseLex(LexAttr lex, stack<int>& buf, ofstream& fout);
