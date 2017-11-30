parsMachine.addThread(getNt(statementNt), endType, getNt(statementListNt), reduceAct);
  parsMachine.addThread(getNt(statementListNt), statementNt, getNt(statementListNt), reduceAct);
  addStatementShifts(statementListNt);
  parsMachine.addThread(getNt(emptyNt), statementNt, getNt(statementListNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), ifNt, getNt(statementNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), ifElseNt, getNt(statementNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), forNt, getNt(statementNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), exprNt, getNt(statementNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), blockNt, getNt(statementNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), returnNt, getNt(statementNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), withNt, getNt(statementNt), reduceAct);

	//Block: begin
	parsMachine.addThread(getNt(emptyNt), leftBrace, getNt(block1Nt), reduceAct);
	addStatementShifts(block1Nt);
	parsMachine.addThread(getNt(block1Nt), getNt(statementListNt), getNt(block2Nt), reduceAct);
	parsMachine.addThread(getNt(block2Nt), rightBrace, getNt(block2Nt), reduceAct);
	addStatementShifts(blockNt);
	
	//Block: end

	//If: begin
	parsMachine.addThread(getNt(emptyNt), ifRes, getNt(if1Nt), reduceAct);
	parsMachine.addThread(getNt(if1Nt), leftParent, getNt(if2Nt), reduceAct);
	addExprShifts(if2Nt);
	parsMachine.addThread(getNt(if2Nt), getNt(exprNt), getNt(if3Nt), reduceAct);
	parsMachine.addThread(getNt(if3Nt), rightParent, getNt(if4Nt), reduceAct);
	addStatementShifts(if4Nt);
	parsMachine.addThread(getNt(if4Nt), getNt(statementNt), getNt(ifNt), reduceAct);
	//If: end
	parsMachine.addThread(getNt(if4Nt), elseRes, getNt(ifElse1Nt), reduceAct);
	addStatementShifts(ifElse1Nt);
	parsMachine.addThread(getNt(ifElse1Nt), getNt(statementNt), getNt(ifElseNt), reduceAct);
	//IfElse: end

	//For: begin
	parsMachine.addThread(getNt(emptyNt), forRes, getNt(for1Nt), reduceAct);
	parsMachine.addThread(getNt(for1Nt), leftParent, getNt(for2Nt), reduceAct);
	parsMachine.addThread(getNt(for2Nt), getNt(exprNt), getNt(for3Nt), reduceAct);
	parsMachine.addThread(getNt(for3Nt), semiCol, getNt(for4Nt), reduceAct);
	//;
	parsMachine.addThread(getNt(for4Nt), getNt(exprNt), getNt(for5Nt), reduceAct);
	parsMachine.addThread(getNt(for5Nt), semiCol, getNt(for6Nt), reduceAct);
	//;
	parsMachine.addThread(getNt(for6Nt), getNt(exprNt), getNt(for7Nt), reduceAct);
	parsMachine.addThread(getNt(for7Nt), rightParent, getNt(forNt), reduceAct);
	//For: end

	//Return: begin
	parsMachine.addThread(getNt(emptyNt), returnRes, getNt(return1Nt), reduceAct);
	addExprShifts(return1Nt);
	parsMachine.addThread(getNt(return1Nt), getNt(exprNt), getNt(return1Nt), reduceAct);
	parsMachine.addThread(getNt(return2Nt), semiCol, getNt(return1Nt), reduceAct);
	parsMachine.addThread(getNt(return1Nt), getNt(return2Nt), getNt(returnNt), reduceAct);
	addStatementShifts(returnNt);
	//Return: end

	//With: begin
	parsMachine.addThread(getNt(emptyNt), withRes, getNt(with1Nt), reduceAct);
	parsMachine.addThread(getNt(with1Nt), leftParent, getNt(with2Nt), reduceAct);
	parsMachine.addThread(getNt(with2Nt), getNt(exprNt), getNt(with3Nt), reduceAct);
	parsMachine.addThread(getNt(with3Nt), rightParent, getNt(with4Nt), reduceAct);
	parsMachine.addThread(getNt(with4Nt), getNt(statementNt), getNt(with5Nt), reduceAct);
	parsMachine.addThread(getNt(with5Nt), semiCol, getNt(withNt), reduceAct);
	//With: end

	parsMachine.addThread(getNt(emptyNt), getNt(assignNt), getNt(exprNt), reduceAct);

	//AssignExp: begin
	parsMachine.addThread(getNt(emptyNt), getNt(logicOrExprNt), getNt(assignNt), reduceAct);

	parsMachine.addThread(getNt(emptyNt), idType, getNt(assign1Nt), reduceAct);
	parsMachine.addThread(getNt(assign1Nt), getNt(assgnOpNt), getNt(assign2Nt), reduceAct);
	parsMachine.addThread(getNt(assign2Nt), getNt(assignNt), getNt(assignNt), reduceAct);
	//AssignExp: end

	parsMachine.addThread(getNt(emptyNt), assignType, getNt(assgnOpNt), reduceAct);

	//LogOrExp: begin
	parsMachine.addThread(getNt(emptyNt), getNt(logicAndExprNt), getNt(logicOrExprNt), reduceAct); //!?

	parsMachine.addThread(getNt(emptyNt), getNt(logicOrExprNt), getNt(logicOrExpr1Nt), reduceAct);
	parsMachine.addThread(getNt(logicOrExpr1Nt), logicType, getNt(logicOrExpr2Nt), reduceAct);
	parsMachine.addThread(getNt(logicOrExpr2Nt), getNt(logicAndExprNt), getNt(logicOrExprNt), reduceAct);
	//LogOrExp: end

	//LogAndExp: begin !!!!!!
	parsMachine.addThread(getNt(emptyNt), bitwOrExprNt, getNt(logicAndExprNt), reduceAct);

	parsMachine.addThread(getNt(emptyNt), logicAndExprNt, getNt(logicAndExpr1Nt), reduceAct);
	parsMachine.addThread(getNt(logicAndExpr1Nt), logicType, getNt(logicAndExpr2Nt), reduceAct);
	parsMachine.addThread(getNt(logicAndExpr2Nt), bitwOrExprNt, getNt(logicAndExprNt), reduceAct);
	//LogAndExp: end

	//BitwOrExp: begin
	parsMachine.addThread(getNt(emptyNt), bitwAndExprNt, getNt(bitwOrExprNt), reduceAct); //!?

	parsMachine.addThread(getNt(emptyNt), bitwOrExprNt, getNt(bitwOrExpr1Nt), reduceAct);
	parsMachine.addThread(getNt(bitwOrExpr1Nt), bitwiseType, getNt(bitwOrExpr2Nt), reduceAct);
	parsMachine.addThread(getNt(logicOrExpr2Nt), bitwAndExprNt, getNt(bitwOrExprNt), reduceAct);
	//BitwOrExp: end

	//BitwAndExp: begin
	parsMachine.addThread(getNt(emptyNt), equalExprNt, getNt(bitwAndExprNt), reduceAct);

	parsMachine.addThread(getNt(emptyNt), getNt(bitwAndExprNt), getNt(bitwAndExpr1Nt), reduceAct);
	parsMachine.addThread(getNt(bitwAndExpr1Nt), bitwiseType, getNt(bitwAndExpr2Nt), reduceAct);
	parsMachine.addThread(getNt(bitwAndExpr2Nt), getNt(equalExprNt), getNt(bitwAndExprNt), reduceAct);
	//BitwAndExp: end

	//EqualExpr: begin
	parsMachine.addThread(getNt(emptyNt), idType, getNt(equalExprNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), numbType, getNt(equalExprNt), reduceAct);
	addStatementShifts(equalExprNt);
	//EqualExpr: end


	string getNameNt(int nt){
	switch(nt + emptyNt){
		case emptyNt:
			return "emptyNt";
		case exprNt:
			return "exprNt";
		case equalExprNt:
			return "equalExprNt";

		case logicOrExprNt:
			return "logicOrExprNt";
		case logicOrExpr1Nt:
			return "logicOrExpr1Nt";
		case logicOrExpr2Nt:
			return "logicOrExpr2Nt";

		case logicAndExprNt:
			return "logicAndExprNt";
		case logicAndExpr1Nt:
			return "logicAndExpr1Nt";
		case logicAndExpr2Nt:
			return "logicAndExpr2Nt";

		case bitwOrExprNt:
			return "bitwiseOrExprNt";
		case bitwOrExpr1Nt:
			return "bitwiseOrExpr1Nt";
		case bitwOrExpr2Nt:
			return "bitwiseOrExpr2Nt";

		case bitwAndExprNt:
			return "bitwiseAndExprNt";
		case bitwAndExpr1Nt:
			return "bitwiseAndExpr1Nt";
		case bitwAndExpr2Nt:
			return "bitwiseAndExpr2Nt";

		case ifNt:
			return "ifNt";
		case if1Nt:
			return "if1Nt";
		case if2Nt:
			return "if2Nt";
		case if3Nt:
			return "if3Nt";
		case if4Nt:
			return "if4Nt";
		case ifElseNt:
			return "ifElseNt";
		case ifElse1Nt:
			return "ifElse1Nt";

		case withNt:
			return "withNt";
		case with1Nt:
			return "with1Nt";
		case with2Nt:
			return "with2Nt";

		case returnNt:
			return "returnNt";
		case return1Nt:
			return "return1Nt";
		case return2Nt:
			return "return2Nt";
		case return3Nt:
			return "return2Nt";

		case forNt:
			return "forNt";
		case blockNt:
			return "blockNt";
		case block1Nt:
			return "block1Nt";
		case block2Nt:
			return "block2Nt";
		case statementNt:
			return "statementNt";
		case statementListNt:
			return "statementListNt";
		case wrongNt:
			return "wrongNt";
		default:
			return to_string(nt);
	}
}
//NORM

	//Equality Expression
	parsMachine.addThread(getNt(emptyNt), idType, getNt(bitAndExNt), reduceAct);
	parsMachine.addThread(getNt(emptyNt), numbType, getNt(bitAndExNt), reduceAct);
	//Bitwise And Expession
	parsMachine.addThread(getNt(bitAndExNt), bit1, getNt(bitAndEx1Nt), reduceAct);
	parsMachine.addThread(getNt(bitAndEx1Nt), idType, getNt(bitOrExNt), reduceAct);
	parsMachine.addThread(getNt(bitAndEx1Nt), numbType, getNt(bitOrExNt), reduceAct);
	//Bitwise Or Expession
	parsMachine.addThread(getNt(bitOrExNt), bitAndExNt, getNt(bitOrExNt), reduceAct);
	parsMachine.addThread(getNt(bitOrExNt), bit2, getNt(bitOrEx1Nt), reduceAct);
	addDefaultShifts(bitOrEx1Nt);
	parsMachine.addThread(getNt(bitOrEx1Nt), bitAndExNt, getNt(bitOrExNt), reduceAct);
	//Logic And Expession
