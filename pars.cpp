#include "main.hpp"

StateMachine parsMachine(getNt(countNonTerms),countNonTerms, wrongAct);
void initParsMachine(){
	parsMachine.addThread(getNt(emptyNt), idType, getNt(idNt), reduceAct);
	//Equality Expression
	parsMachine.addThread(getNt(emptyNt), idNt, getNt(eqExNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), numbType, getNt(eqExNt), reduceAct);

	//Bitwise And Expession
	parsMachine.addThread(getNt(emptyNt), eqExNt, getNt(bitAndExNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), bitAndExNt, getNt(bitAndExNt), reduceAct);
	parsMachine.addThread(getNt(bitAndExNt), bit1, getNt(bitAndEx1Nt), reduceAct);
	addDefaultShifts(bitAndEx1Nt);
	parsMachine.addThread(getNt(bitAndEx1Nt), eqExNt, getNt(bitAndExNt), reduceAct);
	
	//Bitwise Or Expession
	parsMachine.addThread(getNt(emptyNt), bitAndExNt, getNt(bitOrExNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), bitOrExNt, getNt(bitOrExNt), reduceAct);
	parsMachine.addThread(getNt(bitOrExNt), bit2, getNt(bitOrEx1Nt), reduceAct);
	addDefaultShifts(bitOrEx1Nt);
	parsMachine.addThread(getNt(bitOrEx1Nt), bitAndExNt, getNt(bitOrExNt), reduceAct);

	//Logic And Expession
	parsMachine.addThread(getNt(emptyNt), bitOrExNt, getNt(logAndExNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), logAndExNt, getNt(logAndExNt), reduceAct);
	parsMachine.addThread(getNt(logAndExNt), log1, getNt(logAndEx1Nt), reduceAct);
	addDefaultShifts(logAndEx1Nt);
	parsMachine.addThread(getNt(logAndEx1Nt), bitOrExNt, getNt(logAndExNt), reduceAct);

	//Logic Or Expession
	parsMachine.addThread(getNt(emptyNt), logAndExNt, getNt(logOrExNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), logOrExNt, getNt(logOrExNt), reduceAct);
	parsMachine.addThread(getNt(logOrExNt), log2, getNt(logOrEx1Nt), reduceAct);
	addDefaultShifts(logOrEx1Nt);
	parsMachine.addThread(getNt(logOrEx1Nt), logAndExNt, getNt(logOrExNt), reduceAct);

	//Assignment Expression
	parsMachine.addThread(getNt(emptyNt), logOrExNt, getNt(assignExNt), reduceAct);
	parsMachine.addThread(getNt(idNt), assignType, getNt(assignExNt), reduceAct);
	addDefaultShifts(assignExNt);
	parsMachine.addThread(getNt(assignExNt), assignExNt, getNt(assignExNt), reduceAct);

	//Expression
	parsMachine.addThread(getNt(emptyNt), assignExNt, getNt(exprNt), reduceAct);

	//With
	parsMachine.addThread(getNt(emptyNt), withRes, getNt(withNt), reduceAct);
	parsMachine.addThread(getNt(withNt), leftParent, getNt(with1Nt), reduceAct);
	addDefaultShifts(with1Nt);
	parsMachine.addThread(getNt(with1Nt), exprNt, getNt(with2Nt), reduceAct);
	parsMachine.addThread(getNt(with2Nt), rightParent, getNt(with3Nt), reduceAct);
	addDefaultShifts(with3Nt);
	parsMachine.addThread(getNt(with3Nt), statemNt, getNt(with4Nt), reduceAct);
	parsMachine.addThread(getNt(with4Nt), semiCol, getNt(withNt), reduceAct);
	addDefaultShifts(withNt);
	parsMachine.addThread(getNt(withNt), statemNt, getNt(withNt), reduceAct);

	//Return
	parsMachine.addThread(getNt(emptyNt), returnRes, getNt(returnNt), reduceAct);
	parsMachine.addThread(getNt(returnNt), semiCol, getNt(returnNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), returnNt, getNt(return1Nt), reduceAct);
	addDefaultShifts(return1Nt);
	parsMachine.addThread(getNt(return1Nt), exprNt, getNt(return2Nt), reduceAct);
	parsMachine.addThread(getNt(return2Nt), semiCol, getNt(returnNt), reduceAct);
	addDefaultShifts(returnNt);
	parsMachine.addThread(getNt(returnNt), statemNt, getNt(returnNt), reduceAct);

	//For
	parsMachine.addThread(getNt(emptyNt), forRes, getNt(forNt), reduceAct);
	parsMachine.addThread(getNt(forNt), leftParent, getNt(for1Nt), reduceAct);
	addDefaultShifts(for1Nt);
	parsMachine.addThread(getNt(for1Nt), exprNt, getNt(for2Nt), reduceAct);
	parsMachine.addThread(getNt(for2Nt), semiCol, getNt(for2Nt), reduceAct);

	parsMachine.addThread(getNt(for1Nt), idNt, getNt(for2Nt), reduceAct);
	addDefaultShifts(for2Nt);
	parsMachine.addThread(getNt(for2Nt), exprNt, getNt(for3Nt), reduceAct);
	parsMachine.addThread(getNt(for3Nt), semiCol, getNt(for3Nt), reduceAct);

	parsMachine.addThread(getNt(for2Nt), inRes, getNt(for3Nt), reduceAct);
	addDefaultShifts(for3Nt);
	parsMachine.addThread(getNt(for3Nt), exprNt, getNt(for3Nt), reduceAct);
	parsMachine.addThread(getNt(for3Nt), rightParent, getNt(forNt), reduceAct);
	addDefaultShifts(forNt);
	parsMachine.addThread(getNt(forNt), statemNt, getNt(forNt), reduceAct);

	//Statement
	parsMachine.addThread(getNt(emptyNt), exprNt, getNt(statemNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), withNt, getNt(statemNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), returnNt, getNt(statemNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), forNt, getNt(statemNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), ifElseNt, getNt(statemNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), ifNt, getNt(statemNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), blockNt, getNt(statemNt), reduceAct);

	//Statement List
	parsMachine.addThread(getNt(emptyNt), statemNt, getNt(statemListNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), statemListNt, getNt(statemList1Nt), reduceAct);
	addDefaultShifts(statemList1Nt);
	parsMachine.addThread(getNt(statemList1Nt), statemNt, getNt(statemListNt), reduceAct);
	parsMachine.addThread(getNt(statemListNt), endType, getNt(progNt), reduceAct);
}
void addDefaultShifts(int nt){
	parsMachine.addThread(getNt(nt), numbType, getNt(emptyNt), shiftAct);
	parsMachine.addThread(getNt(nt), idType, getNt(emptyNt), shiftAct);
	parsMachine.addThread(getNt(nt), returnRes, getNt(emptyNt), shiftAct);
	parsMachine.addThread(getNt(nt), withRes, getNt(emptyNt), shiftAct);
	parsMachine.addThread(getNt(nt), forRes, getNt(emptyNt), shiftAct);
}
void addStatementShifts(int nt){

}
void addExprShifts(int nt){

}

void printParsTable(vector<LexAttr> &recLexs){
	/*string msg;
	vector<LexAttr>::iterator it;
	ofstream fout("parserTable.txt");
	fout << "#################################\n####      PARSER  TABLE      ####\n#################################\n" << endl;
  out << "CLASS|STR|  TYPE LEX  | LEXEME\n--------------------------------" << endl;
  fout.close();*/
}
string getNameNt(int nt){
	switch(nt + emptyNt){
		case emptyNt:
			return "emptyNt";
		case eqExNt:
			return "eqExNt";
		case idNt:
			return "idNt";

		case bitAndExNt:
			return "bitAndExNt";
		case bitAndEx1Nt:
			return "bitAndEx1Nt";

		case bitOrExNt:
			return "bitOrExNt";
		case bitOrEx1Nt:
			return "bitOrEx1Nt";


		case logOrExNt:
			return "logOrExNt";
		case logOrEx1Nt:
			return "logOrEx1Nt";


		case logAndExNt:
			return "logAndExNt";
		case logAndEx1Nt:
			return "logAndEx1Nt";


		case assignOpNt:
			return "assignOpNt";
		case assignExNt:
			return "assignExNt";

		case exprNt:
			return "exprNt";

		case forNt:
			return "forNt";
		case for1Nt:
			return "for1Nt";
		case for2Nt:
			return "for2Nt";

		case withNt:
			return "withNt";
		case with1Nt:
			return "with1Nt";
		case with2Nt:
			return "with2Nt";
		case with3Nt:
			return "with3Nt";
		case with4Nt:
			return "with4Nt";

		case returnNt:
			return "returnNt";

		case statemNt:
			return "statemNt";
		case statemListNt:
			return "statemListNt";
		case statemList1Nt:
			return "statemList1Nt";
		case progNt:
			return "progNt";
		default:
			return to_string(nt);
	}
}
int parseLex(LexAttr lex, stack<int>& buf, ofstream& fout){
	int act, nextAct, tokenType = lex.tokType, last = buf.top(), next = parseNt(last, tokenType, act);
	switch(act) {
		case reduceAct: {
				reduceNext(buf, next, fout);
				reduceLast(buf, nextAct, last, fout);
		}
		break;
		case shiftAct: {
			next = parseNt(getNt(emptyNt), tokenType, nextAct);
			if(nextAct == reduceAct) {
				//fout<<"push (next)\t"<<getNameNt(next)<<endl;
				buf.push(next);
			} else
				return -1;
		}
		break;
		case wrongAct: {
			if(reduceLast(buf, nextAct, last, fout))
				return parseLex(lex, buf, fout);
			next = parseNt(getNt(emptyNt), last + emptyNt, nextAct);
      if(nextAct == reduceAct) {
      	reduceNext(buf, next, fout);
      	return parseLex(lex, buf, fout);
      } else {
      	return -1;
      }
    }
	}
	return 0;
}
void reduceNext(stack<int>& buf, int next, ofstream& fout){
    fout<<"pop (top)\t"<<getNameNt(buf.top())<<"\t push (next)\t"<<getNameNt(next)<<endl;
    buf.pop();
    buf.push(next);
}

int reduceLast(stack<int> &buf, int nextAct, int last, ofstream& fout){
	if(buf.size()>=2) {
        last = buf.top();
        buf.pop();
        int preLast = buf.top();
				int newNext = parseNt(preLast ,last + emptyNt, nextAct);
        if(nextAct == reduceAct) {
            //fout<<"pop (preLast)\t"<<getNameNt(preLast)<<"\t pop (last)\t"<<getNameNt(last)<<",\t push \t"<<getNameNt(newNext)<<endl;
            buf.pop();
            buf.push(newNext);
            return 1;
        } else {
            buf.push(last);
        }
    }
    return 0;
}
int parseNt(int last, int nt, int& act){
  StateAct  stateAct = parsMachine.changeSt[last][nt];
  act = stateAct.act;
  return stateAct.next;
}
int getNt(int type){
	return type - emptyNt;
}
int parser(vector<LexAttr> &recLexs){
	stack<int> buf;
	string token;
	vector<LexAttr>::iterator it;
	initParsMachine();
	buf.push(getNt(emptyNt));
	recLexs.push_back(LexAttr(0,"",endType, endSt));

	ofstream fout("parserTable.txt");
	fout << "#################################\n####      PARSER  TABLE      ####\n#################################\n" << endl;

	cout << "###################\n#####  Parser #####\n###################" << endl;
  for(it = recLexs.begin();it!=recLexs.end();it++) {
		if(parseLex(*it, buf, fout)<0) {
			cout << "Syntax error:\t(Line	" << it->numstr << ")\tInvalid token:\t" << it->token << endl;
			//break;
		}
  }
	if (buf.size() == 1 && buf.top() == getNt(progNt))
		cout << "Not find Syntax error's" << endl;
	else
		cout << "###################\nSyntax error:\tBuffer size: " << buf.size() <<"\tTop element from buffer: "<< getNameNt(buf.top()) << endl;
	cout << "###################" << endl;
	return 0;
}