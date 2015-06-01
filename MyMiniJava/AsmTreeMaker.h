// Borin Pavel
// AsmCodeGeneration

#pragma once

#include <list>
#include <string.h>
#include <IntermidRepresent.h>
#include <Temp.h>
#include <StackFrame.h>
#include <AssemblerInstr.h>


namespace Assembler {

class CAsmTreeMaker {
public:
	CAsmTreeMaker( const StackFrame::CFrame* _stackFrame ) : 
		stackFrame( _stackFrame ), isInitialized( false ) {};
	
	// функция интерпретирования промежуточного представления функции
	void InitializeTree( const IRTree::CStmtList* cmdList ) const;
	bool IsInitialized() const { return isInitialized; };

	const std::list<const IAsmInstr*> GetAsmInstr() const { return func; };
	const StackFrame::CFrame* GetFrame() const { return stackFrame; };

private:
	mutable std::list<const IAsmInstr*> func;
	bool isInitialized;
	const StackFrame::CFrame* stackFrame;

	void munchStm( const IRTree::IStmt* vertex ) const;

	void munchStm( const IRTree::CCJump* vertex ) const;
	void munchStm( const IRTree::CJump* vertex ) const;
	void munchStm( const IRTree::CLabel* vertex ) const;
	void munchStm( const IRTree::CSeq* vertex ) const;
	void munchStm( const IRTree::CMove* vertex ) const;
	void munchStm( const IRTree::CExp* vertex ) const;

	const Temp::CTemp* munchExp( const IRTree::IExpr* expr ) const;

	const Temp::CTemp* munchExp( const IRTree::CConst* expr ) const;
	const Temp::CTemp* munchExp( const IRTree::CTemp* expr ) const;
	const Temp::CTemp* munchExp( const IRTree::CBinop* expr ) const;
	const Temp::CTemp* munchExp( const IRTree::CMem* expr ) const;
	const Temp::CTemp* munchExp( const IRTree::CCall* expr ) const;

	const Temp::CTemp* munchExpBinopLess( const IRTree::CBinop* expr ) const;

	const Temp::CTempList* munchArgs( const IRTree::CExprList* exprList ) const;
};


};