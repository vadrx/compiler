#include "main.hpp"

StateMachine parsM(nT(countNT),countNT, wrong);
void initParsMachine(){
	parsM.addThread(nT(EMP), idT, nT(ID), reduce);
	//Equality Exression
	parsM.addThread(nT(EMP), ID, nT(EQ), reduce);
	parsM.addThread(nT(EMP), numbT, nT(EQ), reduce);

	//Bitwise And Expression
	parsM.addThread(nT(EMP), EQ, nT(BaEX), reduce);
	parsM.addThread(nT(EMP), BaEX, nT(BaEX), reduce);
	parsM.addThread(nT(BaEX), bit1, nT(BaEX1), reduce);
	addShifts(BaEX1);
	parsM.addThread(nT(BaEX1), EQ, nT(BaEX), reduce);
	//Bitwise Or Expression
	parsM.addThread(nT(EMP), BaEX, nT(BoEX), reduce);
	parsM.addThread(nT(EMP), BoEX, nT(BoEX), reduce);
	parsM.addThread(nT(BoEX), bit2, nT(BoEX1), reduce);
	addShifts(BoEX1);
	parsM.addThread(nT(BoEX1), BaEX, nT(BoEX), reduce);

	//Logic And Expression
	parsM.addThread(nT(EMP), BoEX, nT(LaEX), reduce);
	parsM.addThread(nT(EMP), LaEX, nT(LaEX), reduce);
	parsM.addThread(nT(LaEX), log1, nT(LaEX1), reduce);
	addShifts(LaEX1);
	parsM.addThread(nT(LaEX1), BoEX, nT(LaEX), reduce);
	//Logic Or Expression
	parsM.addThread(nT(EMP), LaEX, nT(LoEX), reduce);
	parsM.addThread(nT(EMP), LoEX, nT(LoEX), reduce);
	parsM.addThread(nT(LoEX), log2, nT(LoEX1), reduce);
	addShifts(LoEX1);
	parsM.addThread(nT(LoEX1), LaEX, nT(LoEX), reduce);

	//AssignmenT Expression
	parsM.addThread(nT(EMP), LoEX, nT(AEX), reduce);
	parsM.addThread(nT(ID), assignT, nT(AEX), reduce);
	//Exression
	parsM.addThread(nT(EMP), AEX, nT(EX), reduce);
	addShifts(EX);
	parsM.addThread(nT(EX), S, nT(EX), reduce);

	//With
	parsM.addThread(nT(EMP), withR, nT(W), reduce);
	parsM.addThread(nT(W), leftPar, nT(W1), reduce);
	addShifts(W1);
	parsM.addThread(nT(W1), EX, nT(W2), reduce);
	parsM.addThread(nT(W2), rightPar, nT(W2), reduce);
	addShifts(W2);
	parsM.addThread(nT(W2), S, nT(W3), reduce);
	parsM.addThread(nT(W3), semiCol, nT(W), reduce);
	addShifts(W);
	parsM.addThread(nT(W), S, nT(W), reduce);
	//Return
	parsM.addThread(nT(EMP), returnR, nT(R), reduce);
	parsM.addThread(nT(R), semiCol, nT(R), reduce);
	parsM.addThread(nT(EMP), R, nT(R1), reduce);
	addShifts(R1);
	parsM.addThread(nT(R1), EX, nT(R2), reduce);
	addShifts(R2);
	parsM.addThread(nT(R2), semiCol, nT(R), reduce);
	addShifts(R);
	parsM.addThread(nT(R), S, nT(R), reduce);

	//For
	parsM.addThread(nT(EMP), forR, nT(F), reduce);
	parsM.addThread(nT(F), leftPar, nT(F1), reduce);
	addShifts(F1);
	parsM.addThread(nT(F1), EX, nT(F2), reduce);
	parsM.addThread(nT(F2), semiCol, nT(F2), reduce);

	parsM.addThread(nT(F1), ID, nT(F2), reduce);
	addShifts(F2);
	parsM.addThread(nT(F2), EX, nT(F3), reduce);
	parsM.addThread(nT(F3), semiCol, nT(F3), reduce);

	parsM.addThread(nT(F2), inR, nT(F3), reduce);
	addShifts(F3);
	parsM.addThread(nT(F3), EX, nT(F3), reduce);
	parsM.addThread(nT(F3), rightPar, nT(F), reduce);
	addShifts(F);
	parsM.addThread(nT(F), S, nT(F), reduce);

	//If
	parsM.addThread(nT(EMP), ifR, nT(IF), reduce);
	parsM.addThread(nT(IF), leftPar, nT(IF1), reduce);
	addShifts(IF1);
	parsM.addThread(nT(IF1), EX, nT(IF2), reduce);
	parsM.addThread(nT(IF2), rightPar, nT(IF), reduce);
	addShifts(IF);
	parsM.addThread(nT(IF), S, nT(IF), reduce);
	// Else
	parsM.addThread(nT(IF), elseR, nT(IE), reduce);
	addShifts(IE);
	parsM.addThread(nT(IE), S, nT(IE), reduce);

	//Block
	parsM.addThread(nT(EMP), leftBrace, nT(B1), reduce);
	parsM.addThread(nT(EMP), B1, nT(B2), reduce);
	addShifts(B2);
	parsM.addThread(nT(B2), SL, nT(B1), reduce);
	parsM.addThread(nT(B1), rightBrace, nT(B), reduce);
	addShifts(B);
	parsM.addThread(nT(B), S, nT(B), reduce);
	//StatemenT
	parsM.addThread(nT(EMP), EX, nT(S), reduce);
	parsM.addThread(nT(EMP), W, nT(S), reduce);
	parsM.addThread(nT(EMP), R, nT(S), reduce);
	parsM.addThread(nT(EMP), F, nT(S), reduce);
	parsM.addThread(nT(EMP), IE, nT(S), reduce);
	parsM.addThread(nT(EMP), IF, nT(S), reduce);
	parsM.addThread(nT(EMP), B, nT(S), reduce);
	//StatemenT List
	parsM.addThread(nT(EMP), S, nT(SL), reduce);
	parsM.addThread(nT(EMP), SL, nT(SL1), reduce);
	addShifts(SL1);
	parsM.addThread(nT(SL1), S, nT(SL), reduce);
	parsM.addThread(nT(SL), endT, nT(PR), reduce);
}
void addShifts(int nt){
	parsM.addThread(nT(nt), numbT, nT(EMP), shift);
	parsM.addThread(nT(nt), idT, nT(EMP), shift);
	parsM.addThread(nT(nt), returnR, nT(EMP), shift);
	parsM.addThread(nT(nt), withR, nT(EMP), shift);
	parsM.addThread(nT(nt), forR, nT(EMP), shift);
	parsM.addThread(nT(nt), ifR, nT(EMP), shift);
	parsM.addThread(nT(nt), leftBrace, nT(EMP), shift);
}
string printNameNt(int nt){
	switch(nt + EMP){
		case EMP:
			return "EMP";
		case EX:
			return "EX";
		case EQ:
			return "EQ";
		case ID:
			return "ID";

		case BaEX:
			return "BaEX";
		case BaEX1:
			return "BaEX1";
		case BoEX:
			return "BoEX";
		case BoEX1:
			return "BoEX1";

		case LoEX:
			return "LoEX";
		case LoEX1:
			return "LoEX1";
		case LaEX:
			return "LaEX";
		case LaEX1:
			return "LaEX1";

		case AEX:
			return "AEX";

		case B:
			return "B";
		case B1:
			return "B1";
		case B2:
			return "B2";

		case F:
			return "F";
		case F1:
			return "F1";
		case F2:
			return "F2";
		case F3:
			return "F3";

		case W:
			return "W";
		case W1:
			return "W1";
		case W2:
			return "W2";
		case W3:
			return "W3";

		case IF:
			return "IF";
		case IF1:
			return "IF1";
		case IF2:
			return "IF2";
		case IE:
			return "IE";	
		case IE1:
			return "IE1";

		case R:
			return "R";
		case R1:
			return "R1";
		case R2:
			return "R2";

		case S:
			return "S";
		case SL:
			return "SL";
		case SL1:
			return "SL1";
		case PR:
			return "PR";
		default:
			return to_string(nt);
	}
}
int parseLex(LexAttr lex, stack<int>& buf, ofstream& fout){
	int act, nextAct, tokenT = lex.tokType;
	int last = buf.top(), next = parseNt(last, tokenT, act);
	switch(act) {
		case reduce: {
				reduceNext(buf, next, fout);
				reduceLast(buf, nextAct, last, fout);
		}
		break;
		case shift: {
			next = parseNt(nT(EMP), tokenT, nextAct);
			if(nextAct == reduce) {
				fout<<"leaf:\t"<<printNameNt(next)<<endl;
				buf.push(next);
			} else
				return -1;
		}
		break;
		case wrong: {
			if(reduceLast(buf, nextAct, last, fout))
				return parseLex(lex, buf, fout);
			next = parseNt(nT(EMP), last + EMP, nextAct);
      if(nextAct == reduce) {
      	reduceNext(buf, next, fout);
      	return parseLex(lex, buf, fout);
      } else
      	return -1;
    }
	}
	return 0;
}

void reduceNext(stack<int>& buf, int next, ofstream& fout){
    fout<<"node with 1 branch:\t"<<printNameNt(buf.top())<<"\t"<<printNameNt(next)<<endl;
    buf.pop();
    buf.push(next);
}
int reduceLast(stack<int> &buf, int nextAct, int last, ofstream& fout){
	if(buf.size()>=2) {
        last = buf.top();
        buf.pop();
        int preLast = buf.top(), newNext = parseNt(preLast ,last + EMP, nextAct);
        if(nextAct == reduce) {
            fout<<"node with 2 branch:\t"<<printNameNt(preLast)<<"\t"<<printNameNt(last)<<"\t"<<printNameNt(newNext)<<endl;
            buf.pop();
            buf.push(newNext);
            return 1;
        } else {
            buf.push(last);
        }
    }
    return 0;
}
int parseNt(int last, int nT, int& act){
  StateAct  stateAct = parsM.changeSt[last][nT];
  act = stateAct.act;
  return stateAct.next;
}
int nT(int nt){
	return nt - EMP;
}
int parser(vector<LexAttr> &recLexs){
	stack<int> buf;
	string token;
	initParsMachine();
	buf.push(nT(EMP));
	recLexs.push_back(LexAttr(0,"",endT, endSt));
	//Print Parser result in Log-File
	ofstream fout("parserTable.log");
	fout << "#######################################" << endl;
	fout << "#######      PRINTED  TREE      #######" << endl;
	fout << "#######################################\n" << endl;
	//Print Syntax Error's
	cout << "#######################################" << endl;
	cout << "#########       PARSER        #########" << endl;
	cout << "#######################################" << endl;
  for(vector<LexAttr>::iterator it = recLexs.begin(); it!=recLexs.end(); it++) {
		if(parseLex(*it, buf, fout)<0) {
			cout << "Syntax error:\t(Line	" <<it->numstr<< ") Invalid token: " <<it->token<<endl;
			if(printNameNt(buf.top())== "W2" || printNameNt(buf.top())== "F3" || printNameNt(buf.top())== "IF2") 
				cout << "May be expected ')'\n"; 
			if(printNameNt(buf.top())== "B2" || printNameNt(buf.top())== "PR") 
				cout << "May be expected '}'\n"; 
			break;
		}
  }
	if (buf.size() == 1 && buf.top() == nT(PR))
		cout << "Not find Syntax error's" << endl;
	else {
		cout << "#######################################" << endl;
		cout << "Syntax error:\tBuffer size:\t" << buf.size() << endl;
		cout << "Top element in buffer: "<< printNameNt(buf.top()) << endl;
		cout << "Check parserTable.log" << endl;
	}
	cout << "#######################################" << endl;
	fout.close();
	return 0;
}