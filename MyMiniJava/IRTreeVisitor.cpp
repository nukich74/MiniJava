// Borin Pavel

#include "IRTreeVisitor.h"
#include "syntaxTree.h"
#include <assert.h>
#include "IntermidRepresent.h"
#include "SubtreeRealisation.h"
#include <ConstantsAndComClasses.h>

namespace Translate {

using namespace IRTree;

//IVisitor
void CIRTreeVisitor::Visit( const Tree::CProgram& p )
{
	const Tree::IMainClass* mc;
	if( ( mc = p.GetMainClass() ) != 0 ) {
		mc->Accept( this );
	} else {
		throw new std::exception( "no main class???" );
	}
	const Tree::IClassDeclList* cdl;
	if( ( cdl = p.GetClassDeclList() ) != 0 ) {
		cdl->Accept( this );
	}
}

void CIRTreeVisitor::Visit( const Tree::CMainClass& p )
{
	//Запомниаем имя класса, чтобы потом имена методов нормально можно было
	className = p.GetName();
	currentFrame = new StackFrame::CFrame( className + "_MainClass", 0 );
	const Tree::IStmt* smt;
	if( ( smt = p.GetStmt() ) != 0 ) {
		smt->Accept( this );
	}
	currentFrame->funcRoot = lastReturnedStm;
	lastReturnedExp = 0;
	lastReturnedStm = 0;
	lastReturnedExpList = 0;
	this->functions.push_back( currentFrame );
	currentFrame = 0;
	className = "";
}

void CIRTreeVisitor::Visit( const Tree::CClassDecl& p )
{
	className = p.GetName();
	isItInClass = true;
	const Tree::IVarDeclList* vdl; 
	const Tree::IMethodDeclList* mdl;
	if( ( vdl = p.GetVarDeclList() ) != 0 ) {
		isItInClass = true;
		vdl->Accept( this );
	}
	isItInClass = false;
	//для каждого метода фрэйм
	if( ( mdl = p.GetMethodDeclList() ) != 0 ) {
		mdl->Accept( this );
	}
	className = "";

}

void CIRTreeVisitor::Visit( const Tree::CClassDeclList& p )
{
	//обход списка
	const Tree::IClassDecl* cd;
	const Tree::IClassDeclList* cdl;
	if( ( cd = p.GetCurrent() ) != 0 ) {
		cd->Accept( this );
	}
	if( ( cdl = p.GetList() ) != 0 ) {
		cdl->Accept( this );
	}
}


void CIRTreeVisitor::Visit( const Tree::CExtendClassDecl& p )
{
	//Реализовать поиск по базовому классу
	className = p.GetClassName();
	std::string baseClassName = p.GetBaseClassName();
	className = baseClassName + "." + className;
	const Tree::IVarDeclList* vdl;
	const Tree::IMethodDeclList* mdl;
	if( ( vdl = p.GetVarDeclList() ) != 0 ) {
		vdl->Accept( this );
	}
	if( ( mdl = p.GetMethodDeclList() ) != 0 ) {
		mdl->Accept( this );
	}
	className = "";
}

void CIRTreeVisitor::Visit( const Tree::CVarDecl& p )
{
	//смысла нет заходить, там все-равно не обрабатываем типы, для ир дерева не нужна инфа
	p.GetType()->Accept( this );
	if( !isItInClass ) { 
		currentFrame->AddFormal( p.GetName(), new StackFrame::CInFrame( varCounter ) );
		varCounter += 1;
	} else {
		// это опреление переменной в классе
		// должны были обработать
		//assert( false );

	}
}

void CIRTreeVisitor::Visit( const Tree::CMethodDecl& p )
{
	isItInClass = false;
	IStmt* newFuncRoot;
	StackFrame::CFrame* newFrame = new StackFrame::CFrame( p.GetName(), 0 );
	currentFrame = newFrame;
	varCounter = 3;
	currentFrame->AddFormal( "this", new StackFrame::CInFrame( varCounter ) );
	varCounter += 1;

	if( p.GetFormalList() != 0 ) {
		p.GetFormalList()->Accept( this );
	}
	varCounter = 0;
	
	for( auto iter : typesAndVariables ) {
		currentFrame->AddLocal( iter.first, new StackFrame::CInFrame( varCounter ) );
		varCounter -= 1;
	} 
	
	if( p.GetVarDeclList() != 0 ) {
		p.GetVarDeclList()->Accept( this );
	}

	if( p.GetStmList() != 0 ) {
		p.GetStmList()->Accept( this );
	}
	//last = returned TEmp
	assert( lastReturnedExp == 0 );
	const IStmt* root = lastReturnedStm;
	lastReturnedStm = 0;
	p.GetExp()->Accept( this );
	if( lastReturnedExp != 0 ) {
		if( lastReturnedStm != 0 ) {
			lastReturnedStm = new IRTree::CSeq( lastReturnedStm, new IRTree::CMove( new IRTree::CTemp( currentFrame->GetReturnValuePointer() ), lastReturnedExp ) );
		} else {
			lastReturnedStm = new IRTree::CMove( new IRTree::CTemp( currentFrame->GetReturnValuePointer() ), lastReturnedExp );
		}
	}

	lastReturnedStm = new IRTree::CSeq( root, lastReturnedStm );
	currentFrame->funcRoot = lastReturnedStm;
	functions.push_back( newFrame );
	currentFrame = 0;
	lastReturnedExp = 0;
	lastReturnedExpList = 0;
	lastReturnedStm = 0;
}

void CIRTreeVisitor::Visit( const Tree::CGroupStmt& p ) 
{
	if( p.GetStmtList() != 0 ) {
		p.GetStmtList()->Accept( this );
	}
}
	
void CIRTreeVisitor::Visit( const Tree::CIfStmt& p )
{
#pragma message( "DO IF( DSA || DQWD )" )
	/*if( p.GetExp() != 0 ) {
		p.GetExp()->Accept( this );
	}*/
	//const IExpr* ifExpRes = lastReturnedExp;

	const IRTree::IExpr* left = 0;
	const IRTree::IExpr* right = 0;
	TEJump op = CJ_NE;

	if( dynamic_cast<const Tree::COpExpr*>( p.GetExp() ) ) {
		const Tree::COpExpr* opExpr = dynamic_cast<const Tree::COpExpr*>( p.GetExp() );
		if( opExpr->GetOp() == Tree::BinOp::BO_Less ) {
			opExpr->GetExprFirst()->Accept( this );
			left = lastReturnedExp;
			opExpr->GetExprSecond()->Accept( this );
			right = lastReturnedExp;
			op = CJ_LT;
		}
		if( opExpr->GetOp() == Tree::BinOp::BO_And ) {
			Temp::CLabel* trueTempLabel = new Temp::CLabel();
			Temp::CLabel* falseTempLabel = new Temp::CLabel();
			Temp::CLabel* endTempLabel = new Temp::CLabel();
			IRTree::CLabel* trueLabel = new IRTree::CLabel( trueTempLabel );
			IRTree::CLabel* falseLabel = new IRTree::CLabel( falseTempLabel );
			IRTree::CLabel* endLabel = new IRTree::CLabel( endTempLabel );

			IRTree::CSeq* finalSeq = 0;


			opExpr->GetExprFirst()->Accept( this );
			left = lastReturnedExp;

			Temp::CLabel* firstTrueLabel = new Temp::CLabel();
			IRTree::CConst* falseConst = new IRTree::CConst(0);
			//Если первый false, то дальше нет смысла прыгать
			IRTree::CCJump* firstTrueJump = new IRTree::CCJump( IRTree::CJ_NE, left, falseConst, firstTrueLabel, falseTempLabel );
			const IRTree::CLabel* firstTrueIRLabel = new IRTree::CLabel( firstTrueLabel );
			
			const IRTree::IStmt* nextPart = 0;
			while( dynamic_cast<const Tree::COpExpr*>( opExpr->GetExprSecond() ) ) {

				IRTree::CCJump* secondTrueJump = new IRTree::CCJump( IRTree::CJ_NE, right, falseConst, trueTempLabel, falseTempLabel );
				IRTree::CSeq* firstFalseSeq = new IRTree::CSeq( firstTrueIRLabel, secondTrueJump );

				nextPart = new IRTree::CSeq( firstFalseSeq, nextPart );

				opExpr = dynamic_cast<const Tree::COpExpr*>( opExpr->GetExprSecond() );
				
			}
			
			finalSeq = new IRTree::CSeq( firstTrueJump, nextPart );
			
			lastReturnedStm = finalSeq;
			return;
		}
	} else {
		// когда нет условий, просто сверить с нулем
		p.GetExp()->Accept( this );
		left = lastReturnedExp;
		right = new IRTree::CConst( 0 );
		op = CJ_NE;
	}


	Temp::CLabel* trueTempLabel = new Temp::CLabel();
	Temp::CLabel* falseTempLabel = new Temp::CLabel();
	Temp::CLabel* endTempLabel = new Temp::CLabel();
	IRTree::CLabel* trueLabel = new IRTree::CLabel( trueTempLabel );
	IRTree::CLabel* falseLabel = new IRTree::CLabel( falseTempLabel );
	IRTree::CLabel* endLabel = new IRTree::CLabel( endTempLabel );
	p.GetStmFirst()->Accept( this );
	IStmt* trueStm = new IRTree::CSeq( trueLabel, lastReturnedStm, new IRTree::CJump( endLabel ) );
	lastReturnedExp = 0;
	lastReturnedStm = 0;
	IStmt* falseStm = 0;
	if( p.GetStmSecond() != 0 ) {
		p.GetStmSecond()->Accept( this );
		falseStm = new IRTree::CSeq( falseLabel, lastReturnedStm, new IRTree::CJump( endLabel ) );
		lastReturnedExp = nullptr;
		lastReturnedStm = nullptr;
	}
	//CExpConverter conv( ifExpRes );
	//lastReturnedStm = new IRTree::CSeq( conv.ToConditional( trueTempLabel, falseTempLabel ), trueStm, falseStm );
	const IStmt* cond = new IRTree::CCJump( op, left, right, trueTempLabel, falseTempLabel );
	lastReturnedStm = new IRTree::CSeq( cond, trueStm, falseStm );
	lastReturnedStm = new IRTree::CSeq( lastReturnedStm, endLabel );
}

void CIRTreeVisitor::Visit( const Tree::CWhileStmt& p )
{
	Temp::CLabel* beforeConditionLabelTemp = new Temp::CLabel();
	Temp::CLabel* inLoopLabelTemp = new Temp::CLabel();
	Temp::CLabel* endLabelTemp = new Temp::CLabel();
	IRTree::CLabel* beforeConditionLabel = new IRTree::CLabel( beforeConditionLabelTemp );
	IRTree::CLabel* inLoopLabel = new IRTree::CLabel( inLoopLabelTemp );
	IRTree::CLabel* endLabel = new IRTree::CLabel( endLabelTemp );
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

void CIRTreeVisitor::Visit( const Tree::CSOPStmt& p )
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

void CIRTreeVisitor::Visit( const Tree::CAssignStmt& p )
{
	const IExpr* leftExp = 0;
	const StackFrame::IAccess* var = currentFrame->GetAccess( p.GetName() );
	if( var != 0 ) {
		leftExp = currentFrame->GetAccess( p.GetName() )->GetExp( currentFrame );	
	} else {
		// тогда берем this
		leftExp = currentFrame->GetAccess( "this" )->GetExp( currentFrame );

		// теперь нужно найти эту переменную в symbolTable
		const SymbolsTable::CClassInfo* clInfo = (*symbolTable).at( className );
		const std::vector<SymbolsTable::CVariableInfo*> classVars = clInfo->GetLocals();
		
		for( int i = 0; i < classVars.size(); ++i ) {
			if( classVars[i]->GetName() == p.GetName() ) {
				// обращаемся по соответствующему адрессу
				leftExp = new CMem( new CBinop( BO_Plus, leftExp, new CConst( i * 4 ) ) );
			}
		}
	}

	p.GetExpr()->Accept( this );
	const IExpr* rightExp = lastReturnedExp;
	lastReturnedExp = 0;
	lastReturnedStm = new IRTree::CMove( leftExp, rightExp );
}

void CIRTreeVisitor::Visit( const Tree::CAssignExprStmt& p )
{
	const IExpr* leftExp = 0;
	const StackFrame::IAccess* var = currentFrame->GetAccess( p.GetName() );
	if( var != 0 ) {
		leftExp = currentFrame->GetAccess( p.GetName() )->GetExp( currentFrame );	
	} else {
		// тогда берем this
		leftExp = currentFrame->GetAccess( "this" )->GetExp( currentFrame );

		// теперь нужно найти эту переменную в symbolTable
		const SymbolsTable::CClassInfo* clInfo = (*symbolTable).at( className );
		const std::vector<SymbolsTable::CVariableInfo*> classVars = clInfo->GetLocals();
		
		for( int i = 0; i < classVars.size(); ++i ) {
			if( classVars[i]->GetName() == p.GetName() ) {
				// обращаемся по соответствующему адрессу
				leftExp = new CMem( new CBinop( BO_Plus, leftExp, new CConst( i * 4 ) ) );
			}
		}
	}
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

void CIRTreeVisitor::Visit( const Tree::COpExpr& p )
{
	p.GetExprFirst()->Accept( this );
	const IExpr* first = lastReturnedExp;
	p.GetExprSecond()->Accept( this );
	const IExpr* second = lastReturnedExp;
	IRTree::BinOp binOp;
	switch( p.GetOp() ) {
	    case Tree::BinOp::BO_Plus:
			binOp = IRTree::BinOp::BO_Plus;
			break;
		case Tree::BinOp::BO_Minus:
			binOp = IRTree::BinOp::BO_Minus;
			break;
		case Tree::BinOp::BO_Mult:
			binOp = IRTree::BinOp::BO_Mult;
			break;
		case Tree::BinOp::BO_Div:
			binOp = IRTree::BinOp::BO_Div;
			break;
		case Tree::BinOp::BO_Less:
			binOp = IRTree::BinOp::BO_Less;
			break;
		case Tree::BinOp::BO_And:
			binOp = IRTree::BinOp::BO_And;
			break;
		default:
			assert( false );
	}
	lastReturnedExp = new IRTree::CBinop( binOp, first, second );
}

void CIRTreeVisitor::Visit( const Tree::CExExpr& p )
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

void CIRTreeVisitor::Visit( const Tree::CMethodCallExpr& p )
{
	p.GetExp()->Accept( this );
	const IExpr* exprToBeCalled = lastReturnedExp;
	lastReturnedExp = 0;
	std::string methodName = p.GetName();
	Temp::CLabel* functionLabel = new Temp::CLabel( methodName );
	IRTree::CName* functionName = new IRTree::CName( functionLabel );
	const IExprList* args = 0;

	assert( exprToBeCalled != 0 );
	if( p.GetExprList() != 0 ) {
		p.GetExprList()->Accept( this );
		args = new IRTree::CExprList( exprToBeCalled, lastReturnedExpList );
	}
	Temp::CTemp* returned = new Temp::CTemp();
	const IRTree::CTemp* returnedTemp = new IRTree::CTemp( returned );
	//выполняем функцию, возращаем return
	lastReturnedExp = new IRTree::CEseq( new IRTree::CMove( returnedTemp, 
		new IRTree::CCall( functionName, args ) ), returnedTemp );
	lastReturnedExpList = 0;
}

void CIRTreeVisitor::Visit( const Tree::CIntExpr& p )
{
	lastReturnedExp = new IRTree::CConst( p.GetNum() );
}

void CIRTreeVisitor::Visit( const Tree::CTrueExpr& p )
{
	//у нас низкий уровень => нет никаких булов
	lastReturnedExp = new IRTree::CConst( 1 );
}

void CIRTreeVisitor::Visit( const Tree::CFalseExpr& p )
{
	//низкий уровень => нет булов
	lastReturnedExp = new IRTree::CConst( 0 ); 
}

void CIRTreeVisitor::Visit( const Tree::CThisExpr& p )
{
	// просто берем указатель на класс
	lastReturnedExp = currentFrame->GetAccess( "this" )->GetExp( currentFrame );
}

void CIRTreeVisitor::Visit( const Tree::CNewIntExpr& p )
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

void CIRTreeVisitor::Visit( const Tree::CNewIdExpr& p )
{
	Temp::CLabel* mallocLabel = new Temp::CLabel( "malloc" );
	// По хорошему здесь надо посчитать сколько всего полей у класса и выделить столько машинных слов
	// теперь нужно найти эту переменную в symbolTable
	const SymbolsTable::CClassInfo* clInfo = (*symbolTable).at( className );
	const std::vector<SymbolsTable::CVariableInfo*> classVars = clInfo->GetLocals();
	int length = classVars.size();

	const IRTree::CName* mallocName = new IRTree::CName( mallocLabel );
	const IRTree::CCall* mallocCall = new IRTree::CCall( mallocName, ( new IRTree::CExprList( new IRTree::CConst( length * currentFrame->WordSize() ), 0 ) ) );
	Temp::CTemp* resultTemp = new Temp::CTemp();
	const IRTree::CTemp* tempTemp = new IRTree::CTemp( resultTemp );
	// Проставляем память нулями
	const IRTree::CCall* memSetCall = nullptr;
	//const IRTree::CSeq* mallocMoveMemset = new IRTree::CSeq( new IRTree::CMove( tempTemp, mallocCall ), new IRTree::CExp( memSetCall ) );
	//lastReturnedExp = new IRTree::CEseq( mallocMoveMemset, tempTemp );
	lastReturnedExp = new IRTree::CEseq( new IRTree::CMove( tempTemp, mallocCall ), tempTemp );
}

void CIRTreeVisitor::Visit( const Tree::CNotExpr& p )
{
	//-(exp - 1)
	p.GetExpr()->Accept( this );
	lastReturnedExp = new IRTree::CBinop( IRTree::BinOp::BO_Minus, 
		new IRTree::CConst( 0 ),
		new IRTree::CBinop( IRTree::BinOp::BO_Minus, lastReturnedExp, new IRTree::CConst( 1 ) )  );
}

void CIRTreeVisitor::Visit( const Tree::CBrExpr& p )
{
	p.GetExpr()->Accept( this );
	//теперь в lastReturnedExp записан результат выполнения операции экспр в скобке, полагаю его не вижу подходящего класса для оборачивания и есть ли в нем смысл?
}


//не используется
void CIRTreeVisitor::Visit( const Tree::CNameExpr& p )
{
	throw new std::exception( "CNAMEEXPR DOESN'T USED" );
	//lastReturnedStm = new IRTree::CLabel( new Temp::CLabel( p.GetName() ) );
}

void CIRTreeVisitor::Visit( const Tree::CIdExpr& p )
{
	//получить по имени переменную из фрэйма
	//lastReturnedExp = new IRTree::CName( new Temp::CLabel( p.GetId() ) );
	//lastReturnedExp = currentFrame->GetAccess( p.GetId() )->GetExp( currentFrame );

	const IExpr* leftExp = 0;
	const StackFrame::IAccess* var = currentFrame->GetAccess( p.GetId() );
	if( var != 0 ) {
		lastReturnedExp = currentFrame->GetAccess( p.GetId() )->GetExp( currentFrame );	
	} else {
		// тогда берем this
		lastReturnedExp = currentFrame->GetAccess( "this" )->GetExp( currentFrame );

		// теперь нужно найти эту переменную в symbolTable
		const SymbolsTable::CClassInfo* clInfo = (*symbolTable).at( className );
		const std::vector<SymbolsTable::CVariableInfo*> classVars = clInfo->GetLocals();
		
		for( int i = 0; i < classVars.size(); ++i ) {
			if( classVars[i]->GetName() == p.GetId() ) {
				// обращаемся по соответствующему адрессу
				lastReturnedExp = new CMem( new CBinop( BO_Plus, lastReturnedExp, new CConst( i * 4 ) ) );
			}
		}
	}
}

void CIRTreeVisitor::Visit( const Tree::CLengthExpr& p )
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

void CIRTreeVisitor::Visit( const Tree::CUnaryMinusExpr& p )
{
	p.GetExpr()->Accept( this );
	//0-expr
	lastReturnedExp = new IRTree::CBinop( IRTree::BinOp::BO_Minus, new IRTree::CConst(0), lastReturnedExp );
}

void CIRTreeVisitor::Visit( const Tree::CTypeName& p )
{
	//нет мыслей
}

void CIRTreeVisitor::Visit( const Tree::CExprList& p )
{	
	p.GetCurrent()->Accept( this );

	const IExpr* tempExpr = lastReturnedExp;
	lastReturnedExp = 0;
	//идем вглубь листа, пока не дойдем до нуля
	if( p.GetList() != 0 ) {
		p.GetList()->Accept( this );
	}
	lastReturnedExpList = new IRTree::CExprList( tempExpr, lastReturnedExpList );
}

void CIRTreeVisitor::Visit( const Tree::CFormalList& p )
{
	p.GetType()->Accept( this );
	typesAndVariables[p.GetName()] = p.GetType();
	if( p.GetFormalList() != 0 ) {
		p.GetFormalList()->Accept( this );
	}
	
}

void CIRTreeVisitor::Visit( const Tree::CVarDeclList& p )
{
	assert( p.GetCurrent() != 0 );
	p.GetCurrent()->Accept( this );
	if( p.GetList() != 0 ) {
		p.GetList()->Accept( this );
	}
}

void CIRTreeVisitor::Visit( const Tree::CMethodDeclList& p )
{
	assert( p.GetCurrent() != 0 );
	p.GetCurrent()->Accept( this );
	if( p.GetList() != 0 ) {
		p.GetList()->Accept( this );
	}
}

void CIRTreeVisitor::Visit( const Tree::CStmtList& p )
{
	//ну тут просто все приводим к Stmt и по очереди Accept
	const IStmt* tempStmt = 0;
	p.GetStmt()->Accept( this );
	if( lastReturnedStm == 0 ) {
		Translate::CExpConverter expConv( lastReturnedExp );
		tempStmt = expConv.ToStm();
	} else {
		tempStmt = lastReturnedStm;
	}
	//lastReturnedStmtList = new IRTree::CStmtList( lastReturnedStm, lastReturnedStmtList );
	lastReturnedExp = 0;
	lastReturnedStm = 0;
	if( p.GetList() != 0 ) {
		p.GetList()->Accept( this );
	}
	lastReturnedStm = new IRTree::CSeq( tempStmt, lastReturnedStm );
}

};