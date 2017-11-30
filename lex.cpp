#include "main.hpp"
Symbol::Symbol(char c) {
    ch = c;
    static map<char,SymbolType> def = {
        {'.',dot},       {'=',assignment}, 
        {'&',bitwise},   {'|',bitwise},
        {'*',arifm},     {'/',arifm},      {'+',arifm},     {'-',arifm},
        {'}',separator}, {'(',separator},  {')',separator}, {'{',separator},
        {' ',separator}, {'\n',separator}, {';',separator},
        {'#',wrongSymb}, {'@',wrongSymb},  {'~',wrongSymb}, {'?',wrongSymb}
    };
    if(isdigit(ch))
        type = digit;
    else if(isalpha(ch))
        type = letter;
    else
        type = def.find(ch)->second;
}
ResWord::ResWord(string word, tokenType key){
    this->word = word;
    this->key = key;
}
list<ResWord> resWords[5];
hash<string> hashFunc;
void addHash(string word, tokenType key){
    resWords[hashFunc(word)%5].push_back(ResWord(word,key));
}
void initHashTable(){
    addHash("if",ifRes);
    addHash("else",elseRes);
    addHash("for",forRes);
    addHash("with",withRes);
    addHash("return",returnRes);
}
int findResWord(string word){
    int h = hashFunc(word)%5;
    for (auto it = resWords[h].begin(); it != resWords[h].end(); it++) {
        if(it->word == word)
            return it->key;
    }
    return 0;
}
StateAct::StateAct(){
   this->next = emptySt;
   this->act = endAct;
}
StateAct::StateAct(int next, Act act){
   this->next = next;
   this->act = act;
}
StateMachine::StateMachine(int stateNum,int symbNum, Act act){
    this->stateNum = stateNum;
    this->symbNum = symbNum;
    changeSt = new StateAct*[stateNum];
    for(int i = 0; i < stateNum; i++){
        changeSt[i] = new StateAct[symbNum];
        for (int j = 0; j < symbNum; j++)
            changeSt[i][j].act = act;
    }      
}
LexAttr::LexAttr(int numstr,string token,int tokType, char state){
    this->numstr = numstr;
    this->token = token;
    this->tokType = tokType;
    this->state = state;
}
void StateMachine::addThread(int oldState, int symb, int nextState, Act signal){
    changeSt[oldState][symb] = StateAct(nextState, signal);
}
StateMachine lexMachine(countStates,countSymbolType, endAct);
void initLexMachine(){
    lexMachine.addThread(emptySt, digit, numberSt, idle);
    lexMachine.addThread(emptySt, letter, wordSt, idle);
    lexMachine.addThread(emptySt, bitwise, bitwiseSt, idle);
    lexMachine.addThread(emptySt, assignment, assignmentSt, idle);
    lexMachine.addThread(emptySt, arifm, arifmSt, idle);
    lexMachine.addThread(emptySt, separator, separatorSt, idle);
    lexMachine.addThread(emptySt, wrongSymb, wrongSt, idle);
    lexMachine.addThread(emptySt, dot, dotSt, idle);
    lexMachine.addThread(numberSt, digit, numberSt, idle);
    lexMachine.addThread(numberSt, dot, dotSt, idle);
    lexMachine.addThread(dotSt, digit, numberSt, idle);
    lexMachine.addThread(arifmSt, assignment, assignmentSt, idle);
    lexMachine.addThread(wordSt, digit, wordSt , idle);
    lexMachine.addThread(wordSt, letter, wordSt , idle);
    lexMachine.addThread(bitwiseSt, bitwise, logicSt, idle);
}
void printLexTable(vector<LexAttr> &recLexs){
    ofstream fout("lexTable.txt");
    string msg, sepMsg1, sepMsg2;
    vector<LexAttr>::iterator it;
    vector<LexAttr>::iterator preIt;
    fout << "################################\n####      LEXER  TABLE      ####\n################################\n" << endl;
    fout << "CLASS|STR|  TYPE LEX  | LEXEME\n--------------------------------" << endl;
    for (it = recLexs.begin(); it != recLexs.end(); it++){
        switch(it->tokType){
        case ifRes:
            msg = "Res Word  ";
        break;
        case elseRes:
            msg = "Res Word  ";
        break;
        case forRes:
            msg = "Res Word  ";
        break;
        case withRes:
            msg = "Res Word  ";
        break;
        case returnRes:
            msg = "Res Word  ";
        break;
        case endType:
        break;
        case spaceType:
        break;
        case idType:
            msg = "Identifier";
        break;
        case leftParent:
            msg = "Separator ";
        break;
        case rightParent:
            msg = "Separator ";
        break;
        case leftBrace:
            msg = "Separator ";
        break;
        case rightBrace:
            msg = "Separator ";
        break;
        case semiCol:
            msg = "Separator ";
        break;
        case numbType:
            msg = "Number    ";
        break;
        case assignType:
            msg = "Assignment";
        break;
        case logicType:
            msg = "Logic     ";
        break;
        case bit1:
            msg = "Bitwise1   ";
        break;
        case bit2:
            msg = "Bitwise2   ";
        break;
        case arifmType:
            msg = "Arifm     ";
        break;
        case wrongType:
            msg = "Wrong     ";
        break;
        }
        preIt = (it!=recLexs.begin()) ? it - 1 : it;
        if (preIt->numstr != it->numstr)
            fout << "--------------------------------"<< endl;
        sepMsg1 = (it->state < 10) ? "  | " : " | ";
        sepMsg2 = (it->numstr < 10) ? "  | " : " | ";
        fout << "#" << (int)it->state << sepMsg1 << it->numstr << sepMsg2 << msg << " | " << it->token << endl;
    }
    fout.close();
}
int classifier(string str, char state, vector<LexAttr> &recLexs){
    switch(state) {
        case wordSt : {
            int key = findResWord(str);
            if(key > 0){
                recLexs.push_back(LexAttr(lexMachine.numstr, str, key, key));
                return key;
            } else {
                recLexs.push_back(LexAttr(lexMachine.numstr, str, idType, wordSt));
                return idType;
            }
        }
        break;
        case separatorSt: {
            if(str == " "){
                return spaceType;
            }
            if (str == "\n"){
                lexMachine.numstr++;
                return endType;
            }
            if(str == "("){
                recLexs.push_back(LexAttr(lexMachine.numstr, str, leftParent, separatorSt));
                return leftParent;
            }
            if(str == ")"){
                recLexs.push_back(LexAttr(lexMachine.numstr, str, rightParent, separatorSt));
                return rightParent;
            }
            if(str == "{"){
                recLexs.push_back(LexAttr(lexMachine.numstr, str, leftBrace, separatorSt));
                return leftBrace;
            }
            if(str == "}"){
                recLexs.push_back(LexAttr(lexMachine.numstr, str, rightBrace, separatorSt));
                return rightBrace;
            }
            if(str == ";"){
                recLexs.push_back(LexAttr(lexMachine.numstr, str, semiCol, separatorSt));
                return semiCol;
            }
        }
        break;
        case numberSt: {
            recLexs.push_back(LexAttr(lexMachine.numstr, str, numbType, numberSt));
            return numbType;
        }
        break;
        case assignmentSt:{
            recLexs.push_back(LexAttr(lexMachine.numstr, str, assignType, assignmentSt));
            return assignType;
        }
        break;
        case logicSt: {
            recLexs.push_back(LexAttr(lexMachine.numstr, str, logicType, logicSt));
            return logicType;
        }
        break;
        case bitwiseSt: {
            if(str == "&"){
                recLexs.push_back(LexAttr(lexMachine.numstr, str, bit1, bitwiseSt));
                return bit1;
            }
            if(str == "|"){
                recLexs.push_back(LexAttr(lexMachine.numstr, str, bit2, bitwiseSt));
                return bit2;
            }
            
        }
        break;
        case arifmSt: {
            recLexs.push_back(LexAttr(lexMachine.numstr, str, arifmType, arifmSt));
            return arifmType;
        }
        break;
        case dotSt: { 
            recLexs.push_back(LexAttr(lexMachine.numstr, str, wrongType, dotSt));
            return wrongType;
        }
        break;
        case wrongSt: {
            recLexs.push_back(LexAttr(lexMachine.numstr, str, wrongType, wrongSt));
            return wrongType;
        }
        break;
    }
    return wrongType;
}
void lexan(ifstream& in, char ch, vector<LexAttr> &recLexs){
    initLexMachine();
    initHashTable();
    while(in >> noskipws >> ch){
        Symbol smb(ch);
        transletter(smb, recLexs);
    }
}
int transletter(Symbol& symb, vector<LexAttr> &recLexs){
    static char currState;
    static string buff;
    StateAct  stateAct = lexMachine.changeSt[currState][symb.type];
    switch(stateAct.act){
        case idle:
        break;
        case endAct: {
            classifier(buff,currState, recLexs);
            buff.clear();
            currState = stateAct.next;
            transletter(symb, recLexs);
            return 0;
        }
        break;
        default: {
          stateAct.act = stateAct.act;
          return stateAct.next;
      }
    }
    buff += symb.ch;
    currState = stateAct.next;
    return 0;
}
