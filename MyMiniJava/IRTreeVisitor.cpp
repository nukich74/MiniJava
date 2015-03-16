#pragma once

#include "IRTreeVisitor.h"
#include "syntaxTree.h"
#include <assert.h>
#include "IntermidRepresent.h"
#include "SubtreeRealisation.h"
#include <ConstantsAndComClasses.h>

namespace Translate {
//IVisitor
void CIRTreeVisitor::Visit( const CProgram& p )
{
	const IMainClass* mc;
	if( ( mc = p.GetMainClass() ) != 0 ) {
		mc->Accept( this );
	} else {
		throw new std::exception( "no main class???" );
	}
	const IClassDeclList* cdl;
	if( ( cdl = p.GetClassDeclList() ) != 0 ) {
		cdl->Accept( this );
	}
}

void CIRTreeVisitor::Visit( const CMainClass& p )
{
	//Запомниаем имя класса, чтобы потом имена методов нормально можно было
	className = p.GetName();
	currentFrame = new StackFrame::CFrame( className + "_MainClass", 0 );
	const IStmt* smt;
	if( ( smt = p.GetStmt() ) != 0 ) {
		smt->Accept( this );
	}
	currentFrame->funcRoot = smt;
	lastReturnedExp = 0;
	lastReturnedStm = 0;
	lastReturnedExpList = 0;
	this->functions.push_back( currentFrame );
	currentFrame = 0;
	className = "";
}

void CIRTreeVisitor::Visit( const CClassDecl& p )
{
	className = p.GetName();
	const IVarDeclList* vdl; 
	const IMethodDeclList* mdl;
	if( ( vdl = p.GetVarDeclList() ) != 0 ) {
		vdl->Accept( this );
	}
	//для каждого метода фрэйм
	if( ( mdl = p.GetMethodDeclList() ) != 0 ) {
		mdl->Accept( this );
	}
	className = "";

}

void CIRTreeVisitor::Visit( const CClassDeclList& p )
{
	//обход списка
	const IClassDecl* cd;
	const IClassDeclList* cdl;
	if( ( cd = p.GetCurrent() ) != 0 ) {
		cd->Accept( this );
	}
	if( ( cdl = p.GetList() ) != 0 ) {
		cdl->Accept( this );
	}
}


void CIRTreeVisitor::Visit( const CExtendClassDecl& p )
{
	//Реализовать поиск по базовому классу
	className = p.GetClassName();
	std::string baseClassName = p.GetBaseClassName();
	className = baseClassName + "." + className;
	const IVarDeclList* vdl;
	const IMethodDeclList* mdl;
	if( ( vdl = p.GetVarDeclList() ) != 0 ) {
		vdl->Accept( this );
	}
	if( ( mdl = p.GetMethodDeclList() ) != 0 ) {
		mdl->Accept( this );
	}
	className = "";
}

void CIRTreeVisitor::Visit( const CVarDecl& p )
{
	//смысла нет заходить, там все-равно не обрабатываем типы, для ир дерева не нужна инфа
	p.GetType()->Accept( this );
}

void CIRTreeVisitor::Visit( const CMethodDecl& p )
{
	IStmt* newFuncRoot;
	StackFrame::CFrame* newFrame = new StackFrame::CFrame( p.GetName(), 0 );
	currentFrame = newFrame;
	if( p.GetFormalList() != 0 ) {
		p.GetFormalList()->Accept( this );
	}
	int counter = 0;
	for( auto iter : typesAndVariables ) {
		currentFrame->AddFormal( iter.first, new StackFrame::CInFrame( counter ) );
		counter += 4;
	} 
	//newFrame->AddFormal( lastReturnedAccess );
	if( p.GetVarDeclList() != 0 ) {
		p.GetVarDeclList()->Accept( this );
	}
	if( p.GetStmList() != 0 ) {
		p.GetStmList()->Accept( this );
	}
	//last = returned TEmp
	if( lastReturnedExp != 0 ) {
		if( lastReturnedStm != 0 ) {
			lastReturnedStm = new IRTree::CSeq( lastReturnedStm, new IRTree::CMove( new IRTree::CTemp( currentFrame->GetReturnValuePointer() ), lastReturnedExp ) );
		} else {
			lastReturnedStm = new IRTree::CMove( new IRTree::CTemp( currentFrame->GetReturnValuePointer() ), lastReturnedExp );
		}
			
	}

	currentFrame->funcRoot = lastReturnedStm;
	functions.push_back( newFrame );
	currentFrame = 0;
	lastReturnedExp = 0;
	lastReturnedExpList = 0;
	lastReturnedStm = 0;
}

void CIRTreeVisitor::Visit( const CGroupStmt& p ) 
{
	if( p.GetStmtList() != 0 ) {
		p.GetStmtList()->Accept( this );
	}
}
	
void CIRTreeVisitor::Visit( const CIfStmt& p )
{
	if( p.GetExp() != 0 ) {
		p.GetExp()->Accept( this );
	}
	const IExpr* ifExpRes = lastReturnedExp;
	Temp::CLabel* trueTempLabel = new Temp::CLabel();
	Temp::CLabel* falseTempLabel = new Temp::CLabel();
	Temp::CLabel* endTempLabel = new Temp::CLabel();
	IRTree::CLabel* trueLabel = new IRTree::CLabel( trueTempLabel );
	IRTree::CLabel* falseLabel = new IRTree::CLabel( falseTempLabel );
	IRTree::CLabel* endLabel = new IRTree::CLabel( endTempLabel );
	p.GetStmFirst()->Accept( this );
	IStmt* trueStm = new IRTree::CSeq( trueLabel, lastReturnedStm, endLabel );
	lastReturnedExp = 0;
	lastReturnedStm = 0;
	IStmt* falseStm = 0;
	if( p.GetStmSecond() != 0 ) {
		p.GetStmSecond()->Accept( this );
		falseStm = new IRTree::CSeq( falseLabel, lastReturnedStm, endLabel );
		lastReturnedExp = nullptr;
		lastReturnedStm = nullptr;
	}
	CExpConverter conv( ifExpRes );
	lastReturnedStm = new IRTree::CSeq( conv.ToConditional( trueTempLabel, falseTempLabel ), trueStm, falseStm );
}

void CIRTreeVisitor::Visit( const CWhileStmt& p )
{
	Temp::CLabel* beforeConditionLabelTemp = new Temp::CLabel();
	Temp::CLabel* inLoopLabelTemp = new Temp::CLabel();
	Temp::CLabel* endLabelTemp = new Temp::CLabel();
	IRTree::CLabel* beforeConditionLabel = new IRTree::CLabel( new Temp::CLabel() );
	IRTree::CLabel* inLoopLabel = new IRTree::CLabel( new Temp::CLabel() );
	IRTree::CLabel* endLabel = new IRTree::CLabel( new Temp::CLabel() );
	p.GetExpr()->Accept( this );
	Translate::CExpConverter converter( lastReturnedExp );
	const IStmt* whileStmt = converter.ToConditional( inLoopLabelTemp, endLabelTemp );
	lastReturnedExp = 0;
	lastReturnedStm = 0;
	IStmt* conditionStm = new IRTree::CSeq( beforeConditionLabel, whileStmt, inLoopLabel );
	p.GetStmt()->Accept( this );
	IStmt* endStmt = new IRTree::CSeq( new IRTree::CJump( beforeConditionLabelTemp ), endLabel );
	lastReturnedStm = new IRTree::CSeq( conditionStm, lastReturnedStm, endStmt );
	lastReturnedExp = 0;
}

void CIRTreeVisitor::Visit( const CSOPStmt& p )
{
	p.GetExpr()->Accept( this );
	//в lastReturnedExp будет то, что нужно распечатать
	const IExpr* expToPrint = lastReturnedExp;
	lastReturnedExp = 0;
	lastReturnedStm = 0;
	// Функция из стандарта, с label ---, далее просто её вызов с параметрами
	Temp::CLabel* funcName = new Temp::CLabel( "System.out.println" );
	const IRTree::CName* funcNameTree = new IRTree::CName( funcName );
	const IRTree::CExprList* args = new IRTree::CExprList( expToPrint, 0 );
	const IExpr* funcCall = new IRTree::CCall( funcNameTree, args );
	lastReturnedStm = new IRTree::CExp( funcCall );
}

void CIRTreeVisitor::Visit( const CAssignStmt& p )
{
	const IExpr* leftExp = currentFrame->GetAccess( p.GetName() )->GetExp( currentFrame );
	assert( p.GetExpr() != 0 );
	p.GetExpr()->Accept( this );
	const IExpr* rightExp = lastReturnedExp;
	lastReturnedExp = 0;
	lastReturnedStm = new IRTree::CMove( leftExp, rightExp );
}

void CIRTreeVisitor::Visit( const CAssignExprStmt& p )
{
	const IExpr* leftExp = currentFrame->GetAccess( p.GetName() )->GetExp( currentFrame );
	assert( p.GetExprId() != 0 );
	p.GetExprId()->Accept( this );
	const IExpr* index = lastReturnedExp;
	//получаем адресс элемента массива
	leftExp = new IRTree::CMem( new IRTree::CBinop( IRTree::BinOp::BO_Plus, index, leftExp ) );
	p.GetExprValue()->Accept( this );
	const IExpr* rightExp = lastReturnedExp;
	lastReturnedExp = 0;
	lastReturnedStm = new IRTree::CMove( leftExp, rightExp );
}

void CIRTreeVisitor::Visit( const COpExpr& p )
{
	p.GetExprFirst()->Accept( this );
	const IExpr* first = lastReturnedExp;
	p.GetExprSecond()->Accept( this );
	const IExpr* second = lastReturnedExp;
	IRTree::BinOp binOp;
	switch( p.GetOp() ) {
		case '+':
			binOp = IRTree::BinOp::BO_Plus;
			break;
		case '-':
			binOp = IRTree::BinOp::BO_Minus;
			break;
		case '*':
			binOp = IRTree::BinOp::BO_Mult;
			break;
		case '/':
			binOp = IRTree::BinOp::BO_Div;
			break;
		case '<':
			binOp = IRTree::BinOp::BO_Less;
			break;
		case '&':
			binOp = IRTree::BinOp::BO_And;
			break;
		default:
			assert( false );
	}
	lastReturnedExp = new IRTree::CMem( new IRTree::CBinop( binOp, first, second ) ) ;
}

void CIRTreeVisitor::Visit( const CExExpr& p )
{
	assert( p.GetExp() != 0 && p.GetExpId() != 0 );
	p.GetExp()->Accept( this );
	const IExpr* mas = lastReturnedExp;
	lastReturnedExp = 0;
	p.GetExpId()->Accept( this );
	const IExpr* index = lastReturnedExp;
	//получаем адресс элемента массива
	lastReturnedExp = new IRTree::CMem( new IRTree::CBinop( IRTree::BinOp::BO_Plus, index, mas ) );

	//WTF????
}

void CIRTreeVisitor::Visit( const CMethodCallExpr& p )
{
	p.GetExp()->Accept( this );
	const IExpr* exprToBeCalled = lastReturnedExp;
	lastReturnedExp = 0;
	std::string methodName = p.GetName();
	Temp::CLabel* functionLabel = new Temp::CLabel( methodName );
	IRTree::CName* functionName = new IRTree::CName( functionLabel );
	const IExprList* args;
	if( p.GetExprList() != 0 ) {
		p.GetExprList()->Accept( this );
		args = lastReturnedExpList;
	} else {
		args = new IRTree::CExprList( 0, 0 );
	}
	Temp::CTemp* returned = new Temp::CTemp();
	const IRTree::CTemp* returnedTemp = new IRTree::CTemp( returned );
	//выполняем функцию, возращаем return
	lastReturnedExp = new IRTree::CEseq( new IRTree::CMove( returnedTemp, new IRTree::CCall( functionName, lastReturnedExpList ) ), returnedTemp );
	lastReturnedExpList = 0;
}

void CIRTreeVisitor::Visit( const CIntExpr& p )
{
	lastReturnedExp = new IRTree::CConst( p.GetNum() );
}

void CIRTreeVisitor::Visit( const CTrueExpr& p )
{
	//у нас низкий уровень => нет никаких булов
	lastReturnedExp = new IRTree::CConst( 1 );
}

void CIRTreeVisitor::Visit( const CFalseExpr& p )
{
	//низкий уровень => нет булов
	lastReturnedExp = new IRTree::CConst( 0 ); 
}

void CIRTreeVisitor::Visit( const CThisExpr& p )
{
	//???????????????????????????????????????//
	lastReturnedExp = new IRTree::CTemp( currentFrame->GetStackPointer() );
}

void CIRTreeVisitor::Visit( const CNewIntExpr& p )
{
	//получаем размер
	assert( p.GetExpr() != 0 );
	p.GetExpr()->Accept( this );
	const IExpr* length = lastReturnedExp;
	//выделяем память
	Temp::CLabel* mallocLabel = new Temp::CLabel( "malloc" );
	const IRTree::CName* mallocName = new IRTree::CName( mallocLabel );
	const IRTree::CCall* mallocCall = new IRTree::CCall( mallocName, ( new IRTree::CExprList( length, 0 ) ) );
	Temp::CTemp* resultTemp = new Temp::CTemp();
	const IRTree::CTemp* tempTemp = new IRTree::CTemp( resultTemp );
	// Проставляем память нулями
	const IRTree::CCall* memSetCall = nullptr;
	const IRTree::CSeq* mallocMoveMemset = new IRTree::CSeq( new IRTree::CMove( tempTemp, mallocCall ), 
		new IRTree::CMove( tempTemp, length ) , new IRTree::CExp( memSetCall ) );
	lastReturnedExp = new IRTree::CEseq( mallocMoveMemset, tempTemp );
}

void CIRTreeVisitor::Visit( const CNewIdExpr& p )
{
	Temp::CLabel* mallocLabel = new Temp::CLabel( "malloc" );
	// По хорошему здесь надо посчитать сколько всего полей у класса и выделить столько машинных слов
	const IRTree::CName* mallocName = new IRTree::CName( mallocLabel );
	const IRTree::CCall* mallocCall = new IRTree::CCall( mallocName, (new IRTree::CExprList( new IRTree::CConst( 200 ), 0 ) ) );
	Temp::CTemp* resultTemp = new Temp::CTemp();
	const IRTree::CTemp* tempTemp = new IRTree::CTemp( resultTemp );
	// Проставляем память нулями
	const IRTree::CCall* memSetCall = nullptr;
	const IRTree::CSeq* mallocMoveMemset = new IRTree::CSeq( new IRTree::CMove( tempTemp, mallocCall ), new IRTree::CExp( memSetCall ) );
	lastReturnedExp = new IRTree::CEseq( mallocMoveMemset, tempTemp );
}

void CIRTreeVisitor::Visit( const CNotExpr& p )
{
	//-(exp - 1)
	p.GetExpr()->Accept( this );
	lastReturnedExp = new IRTree::CBinop( IRTree::BinOp::BO_Minus, 
		new IRTree::CConst( 0 ),
		new IRTree::CBinop( IRTree::BinOp::BO_Minus, lastReturnedExp, new IRTree::CConst( 1 ) )  );
}

void CIRTreeVisitor::Visit( const CBrExpr& p )
{
	p.GetExpr()->Accept( this );
	//теперь в lastReturnedExp записан результат выполнения операции экспр в скобке, полагаю его не вижу подходящего класса для оборачивания и есть ли в нем смысл?
}


//не используется
void CIRTreeVisitor::Visit( const CNameExpr& p )
{
	throw new std::exception( "CNAMEEXPR DOESN'T USED" );
	//lastReturnedStm = new IRTree::CLabel( new Temp::CLabel( p.GetName() ) );
}

void CIRTreeVisitor::Visit( const CIdExpr& p )
{
	//получить по имени переменную из фрэйма
	lastReturnedStm = new IRTree::CLabel( new Temp::CLabel( p.GetId() ) );
}

void CIRTreeVisitor::Visit( const CLengthExpr& p )
{
	p.GetExp()->Accept( this );
	const IExpr* varExp = lastReturnedExp;
	lastReturnedExp = nullptr;
	const IExpr* lengthCommandRW = new IRTree::CBinop( IRTree::BinOp::BO_Plus, varExp, new IRTree::CConst( 0 ) );
	// Создаем временную переменную
	const Temp::CTemp* lengthTemp = new Temp::CTemp();
	const IRTree::CTemp* tempVar = new IRTree::CTemp( lengthTemp );
	// Копируем значение туда
	const IRTree::CMove* movingCommand = new IRTree::CMove( tempVar, lengthCommandRW );
	// Возвращаем адрес переменной
	lastReturnedExp = new IRTree::CEseq( movingCommand, tempVar );
}

void CIRTreeVisitor::Visit( const CUnaryMinusExpr& p )
{
	p.GetExpr()->Accept( this );
	//0-expr
	lastReturnedExp = new IRTree::CBinop( IRTree::BinOp::BO_Minus, new IRTree::CConst(0), lastReturnedExp );
}

void CIRTreeVisitor::Visit( const CTypeName& p )
{
	//нет мыслей
}

void CIRTreeVisitor::Visit( const CExprList& p )
{	
	p.GetCurrent()->Accept( this );

	//идем вглубь листа, пока не дойдем до нуля
	if( p.GetList() != 0 ) {
		p.GetList()->Accept( this );
	}
	lastReturnedExpList = new IRTree::CExprList( lastReturnedExp, lastReturnedExpList );
}

void CIRTreeVisitor::Visit( const CFormalList& p )
{
	p.GetType()->Accept( this );
	typesAndVariables[p.GetName()] = p.GetType();
	if( p.GetFormalList() != 0 ) {
		p.GetFormalList()->Accept( this );
	}
	
}

void CIRTreeVisitor::Visit( const CVarDeclList& p )
{
	assert( p.GetCurrent() != 0 );
	p.GetCurrent()->Accept( this );
	if( p.GetList() != 0 ) {
		p.GetList()->Accept( this );
	}
}

void CIRTreeVisitor::Visit( const CMethodDeclList& p )
{
	assert( p.GetCurrent() != 0 );
	p.Accept( this );
	if( p.GetList() != 0 ) {
		p.GetList()->Accept( this );
	}
}

void CIRTreeVisitor::Visit( const CStmtList& p )
{
	//ну тут просто все приводим к Stmt и по очереди Accept
	const IStmt* addToList = 0;
	p.GetStmt()->Accept( this );
	if( lastReturnedStm == 0 ) {
		Translate::CExpConverter expConv( lastReturnedExp );
		addToList = expConv.ToStm();
	}
	//lastReturnedStmtList = new IRTree::CStmtList( lastReturnedStm, lastReturnedStmtList );
	lastReturnedExp = 0;
	lastReturnedStm = 0;
	if( p.GetList() != 0 ) {
		p.GetList()->Accept( this );
	}
	lastReturnedStm = new IRTree::CSeq( addToList, lastReturnedStm );
}

};