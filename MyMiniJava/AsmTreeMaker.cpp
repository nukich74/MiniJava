// Borin Pavel
// 

#include <AsmTreeMaker.h>
#include <ConstantsAndComClasses.h>


namespace Assembler {

void CAsmTreeMaker::InitializeTree( const IRTree::CStmtList* cmdList  ) const
{
	const IRTree::CStmtList* next = cmdList;
	while( next != 0 ) {
		munchStm( next->GetCurrent() );
		next = dynamic_cast<const IRTree::CStmtList*>( next->GetNextStmts() );
	}
};

void CAsmTreeMaker::munchStm( const IRTree::IStmt* vertex ) const
{
	if( dynamic_cast<const IRTree::CSeq*>( vertex ) != 0 ) {
		munchStm( dynamic_cast<const IRTree::CSeq*>( vertex ) );
		return;
	}
	if( dynamic_cast<const IRTree::CMove*>( vertex ) != 0 ) {
		munchStm( dynamic_cast<const IRTree::CMove*>( vertex ) );
		return;
	}
	if( dynamic_cast<const IRTree::CLabel*>( vertex ) != 0 ) {
		munchStm( dynamic_cast<const IRTree::CLabel*>( vertex ) );
		return;
	}
	if( dynamic_cast<const IRTree::CJump*>( vertex ) != 0 ) {
		munchStm( dynamic_cast<const IRTree::CJump*>( vertex ) );
		return;
	}
	if( dynamic_cast<const IRTree::CExp*>( vertex ) != 0 ) {
		munchStm( dynamic_cast<const IRTree::CExp*>( vertex ) );
		return;
	}
	if( dynamic_cast<const IRTree::CCJump*>( vertex ) != 0 ) {
		munchStm( dynamic_cast<const IRTree::CCJump*>( vertex ) );
		return;
	}
	assert( false );
};

void CAsmTreeMaker::munchStm( const IRTree::CSeq* vertex ) const
{
	assert( vertex->last == 0 );
	munchStm( vertex->left );
	munchStm( vertex->right );
}

void CAsmTreeMaker::munchStm( const IRTree::CMove* vertex ) const
{
	using namespace IRTree;
	//Temp->Mem
	if( dynamic_cast<const CMem*>( vertex->dst ) ) {
		// NO MEM <- MEM in x86
		const CMem* memDst = dynamic_cast<const CMem*>( vertex->dst );

		if( dynamic_cast<const CBinop*>( memDst->expr ) ) {
			const CBinop* binOp = dynamic_cast<const CBinop*>( memDst->expr );
			
			// MEM[+(expr,const)] <- Temp
			if( binOp->oper == BinOp::BO_Plus ) {
				
				if( dynamic_cast<const CConst*>( binOp->left ) != 0 ) {
					const CConst* constant = dynamic_cast<const CConst*>( binOp->left );
					
					std::string cmd = "mov ['d0+";
					cmd += std::to_string( constant->value );
					cmd += "],'s0\n";
					const IAsmInstr* asmInst = new CMove( 
						cmd, new Temp::CTempList( munchExp( binOp->right ), nullptr ), 
						new Temp::CTempList( munchExp( vertex->src ), nullptr ), 0 );
					func.push_back( asmInst );
					return;

				} else if( dynamic_cast<const CConst*>( binOp->right ) != 0 ) {
					const CConst* constant = dynamic_cast<const CConst*>( binOp->right );
					
					std::string cmd = "mov ['d0+";
					cmd += std::to_string( constant->value );
					cmd += "], 's0\n";
					const IAsmInstr* asmInst = new CMove( 
						cmd, new Temp::CTempList( munchExp( binOp->left ), nullptr ), 
						new Temp::CTempList( munchExp( vertex->src ), nullptr ), 0 );
					func.push_back( asmInst );
					return;
				}
			}
		} 
		std::string cmd = "mov ['d0], 's0\n";
		const IAsmInstr* asmInst = new CMove( 
			cmd, new Temp::CTempList( munchExp( memDst->expr ), nullptr ), 
			new Temp::CTempList( munchExp( vertex->src ), nullptr ), 0 );
		func.push_back( asmInst );
		return;
	} else if( dynamic_cast<const CTemp*>( vertex->dst ) ) {
		// Temp <- Temp; Temp <- Mem
		const CTemp* tmp = dynamic_cast<const CTemp*>( vertex->dst );
			
		std::string cmd = "mov 'd0, 's0\n";
		const IAsmInstr* asmInst = new CMove( 
			cmd, new Temp::CTempList( tmp->temp, nullptr ), 
			new Temp::CTempList( munchExp( vertex->src ), nullptr ), 0 );
		func.push_back( asmInst );
		return;
	}
};

void CAsmTreeMaker::munchStm( const IRTree::CLabel* label ) const 
{
	// создание метки
	const IAsmInstr* asmInstr = new CLabel( new Temp::CLabelList( label->label, 0 ) );
	func.push_back( asmInstr );
};

void CAsmTreeMaker::munchStm( const IRTree::CJump* jump ) const
{
	const IAsmInstr* asmInstr = new COper( "jmp 'j0\n", 0, 0, new Temp::CLabelList( jump->label->label, 0 ) );
	func.push_back( asmInstr );
};

void CAsmTreeMaker::munchStm( const IRTree::CExp* expr ) const 
{
	munchExp( expr->exp );
};

void CAsmTreeMaker::munchStm( const IRTree::CCJump* cjump ) const 
{
	//assert( cjump->ifFalse == 0 );
	const Temp::CTemp* regLeft = munchExp( cjump->left );
	const Temp::CTemp* regRight = munchExp( cjump->right );
	Temp::CTempList* tmpList = new Temp::CTempList( regLeft, new Temp::CTempList( regRight, 0 ) );
	func.push_back( new COper( "cmp 's0, 's1\n", 0, tmpList ) );
	Temp::CLabelList* trueList = new Temp::CLabelList( cjump->ifTrue, 0 );
	switch( cjump->relop ) {
	case IRTree::CJ_EQ:
		func.push_back( new COper( "je 'l0", 0, 0, trueList ) );
		break;
	case IRTree::CJ_GE:
		func.push_back( new COper( "jge 'l0", 0, 0, trueList ) );
		break;
	case IRTree::CJ_GT:
		func.push_back( new COper( "jg 'l0", 0, 0, trueList ) );
		break;
	case IRTree::CJ_LE:
		func.push_back( new COper( "jle 'l0", 0, 0, trueList ) );
		break;
	case IRTree::CJ_LT:
		func.push_back( new COper( "jl 'l0", 0, 0, trueList ) );
		break;
	case IRTree::CJ_NE:
		func.push_back( new COper( "jne 'l0", 0, 0, trueList ) );
		break;
	case IRTree::CJ_UGE:
		func.push_back( new COper( "jl 'l0", 0, 0, trueList ) );
		break;
	case IRTree::CJ_UGT:
		func.push_back( new COper( "jle 'l0", 0, 0, trueList ) );
		break;
	case IRTree::CJ_ULE:
		func.push_back( new COper( "jg 'l0", 0, 0, trueList ) );
		break;
	case IRTree::CJ_ULT:
		func.push_back( new COper( "jge 'l0", 0, 0, trueList ) );
		break;
	default:
		assert( false );
	}
};

const Temp::CTemp* CAsmTreeMaker::munchExp( const IRTree::IExpr* expr ) const
{
	if( dynamic_cast<const IRTree::CConst*>( expr ) != 0 ) {
		return munchExp( dynamic_cast<const IRTree::CConst*>( expr ) );
	}
	if( dynamic_cast<const IRTree::CTemp*>( expr ) != 0 ) {
		return munchExp( dynamic_cast<const IRTree::CTemp*>( expr ) );
	}
	if( dynamic_cast<const IRTree::CBinop*>( expr ) != 0 ) {
		return munchExp( dynamic_cast<const IRTree::CBinop*>( expr ) );
	}
	if( dynamic_cast<const IRTree::CMem*>( expr ) != 0 ) {
		return munchExp( dynamic_cast<const IRTree::CMem*>( expr ) );
	}
	if( dynamic_cast<const IRTree::CCall*>( expr ) != 0 ) {
		return munchExp( dynamic_cast<const IRTree::CCall*>( expr ) );
	}
	assert( false );
	return 0;
};

const Temp::CTemp* CAsmTreeMaker::munchExp( const IRTree::CConst* expr ) const
{
	using namespace Temp;
	CTemp* newTemp = new CTemp();
	std::string asmCmd = "mov 'd0, ";
	asmCmd += std::to_string( expr->value );
	asmCmd += "\n";
	IAsmInstr* asmInstr = new CMove( asmCmd, new CTempList( newTemp, 0 ), 0 );
	func.push_back( asmInstr );
	return newTemp;
};


const Temp::CTemp* CAsmTreeMaker::munchExp( const IRTree::CTemp* expr ) const
{
	return expr->temp;
};

const Temp::CTemp* CAsmTreeMaker::munchExpBinopLess( const IRTree::CBinop* expr ) const
{
	using namespace Temp;
	const Temp::CTemp* tmp = new CTemp();


	func.push_back( new COper( "mov 'd0, 0\n", new CTempList( tmp, 0 ), 0, 0 ) );
	
	const CTemp* left = new CTemp();
	const CTemp* right = new CTemp();
	func.push_back( new CMove( "mov 'd0, 's0\n", new CTempList( left, 0 ), new CTempList( munchExp( expr->left ), 0 ) ) );
	func.push_back( new CMove( "mov 'd0, 's0\n", new CTempList( right, 0 ), new CTempList( munchExp( expr->right ), 0 ) ) );

	const CTempList* source = new CTempList( left, new CTempList( right, 0 ) );

	func.push_back( new COper( "cmp 's0, s1\n", 0, source ) );

	Temp::CLabel* label =  new Temp::CLabel();

	func.push_back( new COper( "jnl 'l0\n", 0, 0, new CLabelList( label, 0 ) ) );
	func.push_back( new COper( "mov 'd0, 1\n", new CTempList( tmp, 0 ), 0 ) );
	func.push_back( new CLabel( new CLabelList( label, 0 ) ) );

	return tmp;
}

const Temp::CTemp* CAsmTreeMaker::munchExp( const IRTree::CBinop* expr ) const
{
	std::string command;
	Temp::CTempList* usedRegisters = 0;
	switch( expr->oper ) {
		case IRTree::BO_Plus:
			command = "add";
			usedRegisters = new Temp::CTempList( stackFrame->GetEax(), 0 );
			break;
		case IRTree::BO_Minus:
			command = "sub";
			usedRegisters = new Temp::CTempList( stackFrame->GetEax(), 0 );
			break;
		case IRTree::BO_Mult:
			command = "mul";
			usedRegisters = new Temp::CTempList( stackFrame->GetEax(), new Temp::CTempList( stackFrame->GetEdx(), 0 ) );
			break;
		case IRTree::BO_Div:
			command = "div";
			usedRegisters = new Temp::CTempList( stackFrame->GetEax(), new Temp::CTempList( stackFrame->GetEdx(), 0 ) );
			break;
		case IRTree::BO_Less:
			return munchExpBinopLess( expr ); 

		default:
			assert( false );
	}
	if( dynamic_cast<const IRTree::CConst*>( expr->left ) != 0 && dynamic_cast<const IRTree::CConst*>( expr->right ) != 0 ) {
		// const + const
		int leftValue = dynamic_cast<const IRTree::CConst*>( expr->left )->value;
		int rightValue = dynamic_cast<const IRTree::CConst*>( expr->right )->value;
		Temp::CTemp* tmp = new Temp::CTemp();
		Temp::CTempList* tmplist = new Temp::CTempList( tmp, 0 );
		func.push_back( new CMove( "mov 'd0, " + std::to_string( leftValue ) + "\n", usedRegisters, 0 ) );
		if( expr->oper == IRTree::BO_Div ) {
			func.push_back( new CMove( "mov 'd0, 0\n", new Temp::CTempList( stackFrame->GetEdx(), 0 ), 0 ) );
		}
		func.push_back( new COper( command + " " + std::to_string( rightValue ) + "\n", usedRegisters, 0 ) );
		func.push_back( new CMove( "mov 'd0, 's0\n", tmplist, usedRegisters ) );
		return tmp;
	} else if( dynamic_cast<const IRTree::CConst*>( expr->left ) != 0 ) {
		// const + some
		int leftValue = dynamic_cast<const IRTree::CConst*>( expr->left )->value;
		Temp::CTemp* tmp1 = new Temp::CTemp();
		Temp::CTempList* tmpList1 = new Temp::CTempList( tmp1, 0 );
		func.push_back( new CMove( "mov 'd0, 's0\n", tmpList1,
			new Temp::CTempList( munchExp( expr->right ), 0 ) ) );
		Temp::CTemp* tmp2 = new Temp::CTemp();
		func.push_back( new CMove( "mov 'd0, " + std::to_string( leftValue ) + "\n", usedRegisters, 0 ) );
		if( expr->oper == IRTree::BO_Div ) {
			func.push_back( new CMove( "mov 'd0, 0\n", new Temp::CTempList( stackFrame->GetEdx(), 0 ), 0 ) );
		}
		func.push_back( new COper( command + " 's0\n", usedRegisters, tmpList1 ) );
		func.push_back( new CMove( "mov 'd0, 's0\n", new Temp::CTempList( tmp2, 0 ), usedRegisters ) );
		return tmp2;
	} else if( dynamic_cast<const IRTree::CConst*>( expr->right ) != 0 ) {
		// some + const
		int rightValue = dynamic_cast<const IRTree::CConst*>( expr->right )->value;
		Temp::CTemp* tmp1 = new Temp::CTemp();
		Temp::CTempList* tmpList1 = new Temp::CTempList( tmp1, 0 );
		func.push_back( new CMove( "mov 'd0, 's0\n", usedRegisters, new Temp::CTempList( munchExp( expr->left ), 0 ) ) );
		if( expr->oper == IRTree::BO_Div ) {
			func.push_back( new CMove( "mov 'd0, 0\n", new Temp::CTempList( stackFrame->GetEdx(), 0 ), 0 ) );
		}
		func.push_back( new COper( command + " " + std::to_string( rightValue ) + "\n", usedRegisters, 0 ) );
		func.push_back( new CMove( "mov 'd0, 's0\n", tmpList1, usedRegisters ) );
		return tmp1;
	} else {
		// some + some
		Temp::CTemp* tmp1 = new Temp::CTemp();
		Temp::CTempList* tmpList1 = new Temp::CTempList( tmp1, 0 );
		func.push_back( new CMove( "mov 'd0, 's0\n", usedRegisters, new Temp::CTempList( munchExp( expr->left ), 0 ) ) );
		Temp::CTemp* tmp2 = new Temp::CTemp();
		Temp::CTempList* tmpList2 = new Temp::CTempList( tmp2, 0 );
		func.push_back( new CMove( "mov 'd0, 's0\n", tmpList2, new Temp::CTempList( munchExp( expr->right ), 0 ) ) );
		if( expr->oper == IRTree::BO_Div ) {
			func.push_back( new CMove( "mov 'd0, 0\n", new Temp::CTempList( stackFrame->GetEdx(), 0 ), 0 ) );
		}
		func.push_back( new COper( command + " 's0\n",	usedRegisters, tmpList2 ) );
		func.push_back( new CMove( "mov 'd0, 's0\n", tmpList1, usedRegisters ) );
		return tmp1;
	}
};

const Temp::CTemp* CAsmTreeMaker::munchExp( const IRTree::CMem* expr ) const
{
	using namespace Temp;
	const CTemp* tmp = munchExp( expr->expr );
	// запомнили фрэймпоинтер
	CTemp* fpTmp = new CTemp();
	func.push_back( new CMove( "mov 'd0, 's0\n", new CTempList( fpTmp, 0 ), new CTempList( stackFrame->GetFramePointer(), 0 ) ) );
	CTemp* resTmp = new CTemp();
	func.push_back( new CMove( "mov 'd0, ['s0 + 's1]\n", new CTempList( resTmp, 0 ),
		new CTempList( fpTmp, new CTempList( tmp, 0 ) ) ) );

	return resTmp;
};

const Temp::CTemp* CAsmTreeMaker::munchExp( const IRTree::CCall* expr ) const
{
	const IRTree::CName* name = dynamic_cast<const IRTree::CName*>( expr->func );
	assert( name != 0 );
	const IRTree::CExprList* argList = dynamic_cast<const IRTree::CExprList*>( expr->args );
	const Temp::CTempList* argsList = munchArgs( argList );
	while( argsList != 0 ) {
		if( argsList->GetCurrent() != 0 ) {
			func.push_back( new COper( "push 's0\n", 0, new Temp::CTempList( argsList->GetCurrent(), 0 ) ) );
			argsList = argsList->GetNext();
		} else { 
			break;
		}
	}
	func.push_back( new COper( "call 'l0\n", 0, 0, new Temp::CLabelList( name->label, 0 ) ) );
	return new Temp::CTemp();
};

const Temp::CTempList* CAsmTreeMaker::munchArgs( const IRTree::CExprList* exprList ) const
{
	// стремное место, из-за тупого IExprList
	if( exprList == 0 ) {
		return 0;
	}
	Temp::CTempList* argsTempList = 0;
	while( exprList != 0 ) {
		Temp::CTemp* tmp = new Temp::CTemp();
		func.push_back( new CMove( "mov 'd0, 's0\n", new Temp::CTempList( tmp, 0 ),
			new Temp::CTempList( munchExp( exprList->GetCurrent() ), 0 ) ) );
		
		exprList = dynamic_cast<const IRTree::CExprList*>( exprList->GetNextExprs() );
		argsTempList = new Temp::CTempList( tmp, argsTempList );
	}
	return argsTempList;
};


}; // namespace Assembler