#include "SubtreeRealisation.h"

namespace Translate {

	using namespace IRTree;

	const IStmt* CExpConverter::ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const 
	{
		return new IRTree::CCJump( IRTree::TEJump::CJ_NE, expr, new IRTree::CConst( 0 ), t, f );
	};


	const IStmt* CConditionalWrapper::ToStm() const {
		//создаем ссылку в одно и тоже место
		Temp::CLabel* tempLabel = new Temp::CLabel();
		IRTree::CLabel* irLabel = new IRTree::CLabel( tempLabel );
		const IStmt* cond = ToConditional( tempLabel, tempLabel );
		IRTree::CSeq* seq = new IRTree::CSeq( cond, irLabel );
		return seq;
	}

	const IExpr* CConditionalWrapper::ToExp() const {
		//Временную переменную, куда запишем результат
		Temp::CTemp* temp = new Temp::CTemp();
		IRTree::CTemp* irTemp = new IRTree::CTemp( temp );
		//Запоминаем ответ, true или false
		IRTree::CMove* moveTrue = new IRTree::CMove( irTemp, new IRTree::CConst( 1 ) );
		IRTree::CMove* moveFalse = new IRTree::CMove( irTemp, new IRTree::CConst( 0 ) );
		Temp::CLabel* trueLabel = new Temp::CLabel();
		Temp::CLabel* falseLabel = new Temp::CLabel();
		IRTree::CLabel* trueIRLabel = new IRTree::CLabel( trueLabel );
		IRTree::CLabel* falseIRLabel = new IRTree::CLabel( falseLabel );
		IRTree::CSeq* seqTrue = new IRTree::CSeq( trueIRLabel, moveTrue );
		IRTree::CSeq* seqFalse = new IRTree::CSeq( falseIRLabel, moveFalse );
		const IStmt* cond = ToConditional( trueLabel, falseLabel );
		IRTree::CEseq* eseq = new IRTree::CEseq( cond, irTemp );
		return eseq;
	}
	
	const IStmt* CAndWrapper::ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) {
		Temp::CLabel* firstTrueLabel = new Temp::CLabel();
		IRTree::CConst* falseConst = new IRTree::CConst(0);
		//Если первый false, то дальше нет смысла прыгать
		IRTree::CCJump* firstTrueJump = new IRTree::CCJump( IRTree::CJ_NE, left, falseConst, firstTrueLabel, f );
		IRTree::CLabel* firstTrueIRLabel = new IRTree::CLabel( firstTrueLabel );
		//2ой проверяется и true и false
		IRTree::CCJump* secondTrueJump = new IRTree::CCJump( IRTree::CJ_NE, right, falseConst, t, f );
		IRTree::CSeq* firstFalseSeq = new IRTree::CSeq( firstTrueIRLabel, secondTrueJump );
		IRTree::CSeq* finalSeq = new IRTree::CSeq( firstTrueJump, firstFalseSeq );
		return finalSeq;
	}

	const IStmt* CLessWrapper::ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) {
		IRTree::CCJump* returnValue = new IRTree::CCJump( IRTree::TEJump::CJ_LT, left, right, t, f );
		return returnValue;
	}


};