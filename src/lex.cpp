#include "main.h"
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
list<ResWord> resWords[6];
hash<string> hashFunc;
void addHash(string word, tokenType key){
    resWords[hashFunc(word)%6].push_back(ResWord(word,key));
}
void initHashTable(){
    addHash("if",ifR);
    addHash("else",elseR);
    addHash("for",forR);
    addHash("with",withR);
    addHash("return",returnR);
    addHash("in",inR);
}
int findResWord(string word){
    int h = hashFunc(word)%6;
    for (auto it = resWords[h].begin(); it != resWords[h].end(); it++) {
        if(it->word == word)
            return it->key;
    }
    return 0;
}
StateAct::StateAct(){
    this->next = empSt;
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
StateMachine lexM(countStates,countSymbolType, endAct);
void initLexM(){
    lexM.addThread(empSt, digit, numbSt, idle);
    lexM.addThread(empSt, letter, wordSt, idle);
    lexM.addThread(empSt, bitwise, bitwiseSt, idle);
    lexM.addThread(empSt, assignment, assignmentSt, idle);
    lexM.addThread(empSt, arifm, arifmSt, idle);
    lexM.addThread(empSt, separator, separatorSt, idle);
    lexM.addThread(empSt, wrongSymb, wrongSt, idle);
    lexM.addThread(empSt, dot, dotSt, idle);
    lexM.addThread(numbSt, digit, numbSt, idle);
    lexM.addThread(numbSt, dot, dotSt, idle);
    lexM.addThread(dotSt, digit, numbSt, idle);
    lexM.addThread(arifmSt, assignment, assignmentSt, idle);
    lexM.addThread(wordSt, digit, wordSt , idle);
    lexM.addThread(wordSt, letter, wordSt , idle);
    lexM.addThread(bitwiseSt, bitwise, logicSt, idle);
}
void printLexTable(vector<LexAttr> &recLexs){
    ofstream fout("lexTable.txt");
    string msg, sepMsg1, sepMsg2;
    vector<LexAttr>::iterator it, preIt;
    fout << "################################\n####      LEXER  TABLE      ####\n################################\n" << endl;
    fout << "CLASS|STR|  TYPE LEX  | LEXEME\n--------------------------------" << endl;
    for (it = recLexs.begin(); it != recLexs.end(); it++){
        switch(it->tokType){
        case ifR:
            msg = "Res Word  ";
            break;
        case elseR:
            msg = "Res Word  ";
            break;
        case forR:
            msg = "Res Word  ";
            break;
        case withR:
            msg = "Res Word  ";
            break;
        case returnR:
            msg = "Res Word  ";
            break;
        case inR:
            msg = "Res Word  ";
            break;
        case endT:
            break;
        case spaceT:
            break;
        case idT:
            msg = "Identifier";
            break;
        case leftPar:
            msg = "Separator ";
            break;
        case rightPar:
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
        case numbT:
            msg = "Number    ";
            break;
        case assignT:
            msg = "Assignment";
            break;
        case log1:
            msg = "Logic     ";
            break;
        case log2:
            msg = "Logic     ";
            break;
        case bit1:
            msg = "Bitwise   ";
            break;
        case bit2:
            msg = "Bitwise   ";
            break;
        case arifmT:
            msg = "Arifm     ";
            break;
        case wrongT:
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
            recLexs.push_back(LexAttr(lexM.numstr, str, key, key));
            return key;
        } else {
            recLexs.push_back(LexAttr(lexM.numstr, str, idT, wordSt));
            return idT;
        }
    }
        break;
    case separatorSt: {
        if(str == " "){
            return spaceT;
        }
        if (str == "\n"){
            lexM.numstr++;
            return endT;
        }
        if(str == "("){
            recLexs.push_back(LexAttr(lexM.numstr, str, leftPar, separatorSt));
            return leftPar;
        }
        if(str == ")"){
            recLexs.push_back(LexAttr(lexM.numstr, str, rightPar, separatorSt));
            return rightPar;
        }
        if(str == "{"){
            recLexs.push_back(LexAttr(lexM.numstr, str, leftBrace, separatorSt));
            return leftBrace;
        }
        if(str == "}"){
            recLexs.push_back(LexAttr(lexM.numstr, str, rightBrace, separatorSt));
            return rightBrace;
        }
        if(str == ";"){
            recLexs.push_back(LexAttr(lexM.numstr, str, semiCol, separatorSt));
            return semiCol;
        }
    }
        break;
    case numbSt: {
        recLexs.push_back(LexAttr(lexM.numstr, str, numbT, numbSt));
        return numbT;
    }
        break;
    case assignmentSt:{
        recLexs.push_back(LexAttr(lexM.numstr, str, assignT, assignmentSt));
        return assignT;
    }
        break;
    case logicSt: {
        if(str == "&&"){
            recLexs.push_back(LexAttr(lexM.numstr, str, log1, logicSt));
            return log1;
        }
        if(str == "||"){
            recLexs.push_back(LexAttr(lexM.numstr, str, log2, logicSt));
            return log2;
        }
    }
        break;
    case bitwiseSt: {
        if(str == "&"){
            recLexs.push_back(LexAttr(lexM.numstr, str, bit1, bitwiseSt));
            return bit1;
        }
        if(str == "|"){
            recLexs.push_back(LexAttr(lexM.numstr, str, bit2, bitwiseSt));
            return bit2;
        }

    }
        break;
    case arifmSt: {
        recLexs.push_back(LexAttr(lexM.numstr, str, arifmT, arifmSt));
        return arifmT;
    }
        break;
    case dotSt: {
        recLexs.push_back(LexAttr(lexM.numstr, str, wrongT, dotSt));
        return wrongT;
    }
        break;
    case wrongSt: {
        recLexs.push_back(LexAttr(lexM.numstr, str, wrongT, wrongSt));
        return wrongT;
    }
        break;
    }
    return wrongT;
}
void lexan(ifstream& in, char ch, vector<LexAttr> &recLexs){
    initLexM();
    initHashTable();
    while(in >> noskipws >> ch){
        Symbol smb(ch);
        transletter(smb, recLexs);
    }
}
int transletter(Symbol& symb, vector<LexAttr> &recLexs){
    static char currState;
    static string buff;
    StateAct  stateAct = lexM.changeSt[currState][symb.type];
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
        return stateAct.next;
    }
    }
    buff += symb.ch;
    currState = stateAct.next;
    return 0;
}
