#include "IRTreeVisitor.h"
#include <iostream>
#include"grammar.h"
#include <string>
#include <cassert>

namespace IRTranslate {

	void CIRTreeVisitor::Visit( const CExpBinOpExp& exp )
	{
		// Забираем правый и левый операнды
		exp.LeftArg( )->Accept( *this );
		const IRTree::IExp* first = lastReturnedExp;
		exp.RightArg( )->Accept( *this );
		const IRTree::IExp* second = lastReturnedExp;
		IRTree::TBinop binOp;
		switch( exp.Operation( ) ) {
		case '+':
			binOp = IRTree::B_Plus;
			break;
		case '-':
			binOp = IRTree::B_Minus;
			break;
		case '*':
			binOp = IRTree::B_Mul;
			break;
		default:
			assert( false );
		}
		// Берем то что лежит по first, second и применяем бинарную операцию
		lastReturnedExp = new IRTree::CMem( new IRTree::CBinop( binOp, first, second ) );
	}

	void CIRTreeVisitor::Visit( const CUnMinExp& exp )
	{
		// Как в лекциях заменяем на (0 - exp)
		const IRTree::IExp* first = new IRTree::CConst( 0 );
		exp.Exp( )->Accept( *this );
		const IRTree::IExp* second = lastReturnedExp;
		// Аналогично binop
		lastReturnedExp = new IRTree::CMem( new IRTree::CBinop( IRTree::B_Minus, first, second ) );
	}

	void CIRTreeVisitor::Visit( const CExpWithIndex& exp )
	{
		exp.Exp( )->Accept( *this );
		const IRTree::IExp* varExp = lastReturnedExp;
		lastReturnedExp = nullptr;
		exp.Index( )->Accept( *this );
		const IRTree::IExp* indexExp = new IRTree::CBinop( IRTree::B_Plus, new IRTree::CMem( lastReturnedExp ), new IRTree::CConst( 1 ) );
		lastReturnedExp = nullptr;
		IRTree::IExp* offset = new IRTree::CBinop( IRTree::B_Mul, new IRTree::CConst( Frame::CFrame::WordSize( ) ), indexExp );
		// Возвращаем адрес переменной
		lastReturnedExp = new IRTree::CBinop( IRTree::B_Plus, varExp, offset );
	}

	void CIRTreeVisitor::Visit( const CExpDotLength& exp )
	{
		// Во время компиляции уже известен размер каждого массива, он должен проверяться на корректность при валидации
		exp.Exp( )->Accept( *this );
		const IRTree::IExp* varExp = lastReturnedExp;
		lastReturnedExp = nullptr;
		const IRTree::IExp* lengthCommandRW = new IRTree::CBinop( IRTree::B_Plus, varExp, new IRTree::CConst( 0 ) );
		// Создаем временную переменную
		const Temp::CTemp* lengthTemp = new Temp::CTemp( );
		const IRTree::CTemp* tempVar = new IRTree::CTemp( *lengthTemp );
		// Копируем значение туда
		const IRTree::CMove* movingCommand = new IRTree::CMove( tempVar, lengthCommandRW );
		// Возвращаем адрес переменной
		lastReturnedExp = new IRTree::CEseq( movingCommand, tempVar );
	}

	void CIRTreeVisitor::Visit( const CExpIdExpList& exp )
	{
#pragma message( "TODO Возможно здесь надо что-то делать" )
		assert( currentFrame == 0 );
		//currentFrame = new Frame::CFrame( exp.Id() )
		// Больше ничего, всю остальную информацию уже знаем из таблицы символов
	}

	void CIRTreeVisitor::Visit( const CExpIdVoidExpList& exp )
	{
#pragma message( "TODO Возможно здесь надо что-то делать" )
		// Заголовок функции без возвращаемого типа
		assert( currentFrame == 0 );
		//currentFrame = new Frame::CFrame( exp.Id() )
		// Больше ничего, всю остальную информацию уже знаем из таблицы символов
	}

	void CIRTreeVisitor::Visit( const CIntegerLiteral& exp )
	{
		lastReturnedExp = new IRTree::CConst( exp.Value( ) );
	}

	void CIRTreeVisitor::Visit( const CTrue& exp )
	{
		// True у нас константа 1
		lastReturnedExp = new IRTree::CConst( 1 );
	}

	void CIRTreeVisitor::Visit( const CFalse& exp )
	{
		// False у нас константа 0
		lastReturnedExp = new IRTree::CConst( 0 );
	}

	void CIRTreeVisitor::Visit( const CId& exp )
	{
		// Найдем нужную инфу во фрейме
		lastReturnedAccess = currentFrame->GetAccess( exp.Id( ) );
		lastReturnedExp = nullptr;
		lastReturnedStm = nullptr;
	}

	void CIRTreeVisitor::Visit( const CThis& exp )
	{
#pragma message( "TODO Здесь надо возвращать IRTree::IRName переменной" )
		std::cout << "this";
	}

	void CIRTreeVisitor::Visit( const CNewIntExpIndex& exp )
	{
#pragma message( "TODO Оператор new для int[] тут получаем количество необходимой памяти из lastReturnedExp выделяем и возвращаем Name" )
		exp.Exp( )->Accept( *this );
	}
	void CIRTreeVisitor::Visit( const CNewId& exp )
	{
#pragma message( "TODO Оператор new для любого типа тут нужен размер типа, выделяем и возвращаем Name" )
		std::cout << "new " << exp.TypeId( ) << "()";
	}

	void CIRTreeVisitor::Visit( const CNotExp& exp )
	{
		// Получаем lastReturnedExp и записываем туда конструкцию XOR c Const(0)
		exp.Exp( )->Accept( *this );
		lastReturnedExp = new IRTree::CBinop( IRTree::B_Xor,
			new IRTree::CConst( 0 ), new IRTree::CMem( lastReturnedExp ) );
	}

	void CIRTreeVisitor::Visit( const CExpInBrackets& exp )
	{
#pragma message( "TODO Здесь нужно чтобы тот кому выражение принадлежит забрал lastReturnedExp" )
		// Строится exp list
		exp.Exp( )->Accept( *this );
	}

	void CIRTreeVisitor::Visit( const CProgram& program )
	{
		// Здесь для IRTree ничего не нужно
		program.MainClass( )->Accept( *this );
		if( program.ClassDeclList( ) != 0 ) {
			program.ClassDeclList( )->Accept( *this );
		}

	}

	void CIRTreeVisitor::Visit( const CMainClass& mainClass )
	{
		// Запоминаем в каком мы классе
		className = mainClass.MainClassName( );
		// У main нет никаких переменных, потому что такая грамматика
		//	Программу можно будет начать если сделать временный объект какого нибудь класса
		//	например System.out.println( new Pr1() );
		currentFrame = new Frame::CFrame( className + ":main" );
		if( mainClass.StatementList( ) != 0 ) {
			mainClass.StatementList( )->Accept( *this );
		}
		currentFrame->Stm = lastReturnedStm;
		lastReturnedStm = nullptr;
		lastReturnedExp = nullptr;
		lastReturnedAccess = nullptr;
		Methods.push_back( currentFrame );
		// Очищаем инфу о текущем фрейме
		currentFrame = 0;
		className = "";
	}

	void CIRTreeVisitor::Visit( const CClassDeclList& classDeclList )
	{
		// Здесь для IRTree ничего не нужно
		for( const auto& clsDecl : classDeclList.ClassDeclList( ) ) {
			clsDecl->Accept( *this );
		}
	}

	void CIRTreeVisitor::Visit( const CClassDecl& classDecl )
	{
#pragma message( "TODO Возможно здесь надо что-то делать" )
		// Запоминаем в каком мы классе
		className = classDecl.ClassId( );
		if( classDecl.VarDeclList( ) != 0 ) {
			classDecl.VarDeclList( )->Accept( *this );
		}
		if( classDecl.MethodDeclList( ) != 0 ) {
			classDecl.MethodDeclList( )->Accept( *this );
		}
		lastReturnedAccess = nullptr;
		lastReturnedExp = nullptr;
		lastReturnedStm = nullptr;
		className = "";
	}

	void CIRTreeVisitor::Visit( const CVarDeclList& varDeclList )
	{
		// Здесь для IRTree ничего не нужно
		for( const auto& decl : varDeclList.VarDeclList( ) ) {
			decl->Accept( *this );
		}
	}

	void CIRTreeVisitor::Visit( const CVarDecl& varDecl )
	{
		varDecl.VarType( )->Accept( *this );
	}

	void CIRTreeVisitor::Visit( const CMethodDeclList& methodDeclList )
	{
		// Здесь для IRTree ничего не нужно
		for( const auto& decl : methodDeclList.MethodDeclList( ) ) {
			decl->Accept( *this );
		}
	}


	void CIRTreeVisitor::Visit( const CMethodDecl& methodDecl )
	{
		// Все это мы игнорируем, это есть у теблицы символоа
		methodDecl.ReturnedType( )->Accept( *this );
		if( methodDecl.FormalList( ) != 0 ) {
			methodDecl.FormalList( )->Accept( *this );
		}
		if( methodDecl.VarDeclList( ) != 0 ) {
			methodDecl.VarDeclList( )->Accept( *this );
		}
		// Строим фрейм
		currentFrame = new Frame::CFrame( className + ":" + methodDecl.MethodName( ) );
		// Добавляем поля класса к фрейму
		for( const auto& field : symbolsTable.Classes( ).at( className ).Fields ) {
			currentFrame->AddField( field.Name( ), new Frame::CInObject( currentFrame->ThisCounter ) );
			currentFrame->ThisCounter++;
		}

		// Добавил костыль, ибо не компилится - в ClassDecsriptor методы и переменные хранятся в массивах а не map.
		// Если не конструкция вам не по душе можете выделить в отдельный метод, либо развлечься иным способом.
		const std::vector<SymbolsTable::CVariableDescriptor>* params = nullptr;
		const std::vector<SymbolsTable::CVariableDescriptor>* locals = nullptr;
		for( auto& method : symbolsTable.Classes( ).at( className ).Methods ) {
			if( method.Name( ) == methodDecl.MethodName( ) ) {
				params = &method.Params;
				locals = &method.Locals;
				break;
			}
		}

		// Добавляем параметры функции фрейму
		for( const auto& field : *params ) {
			currentFrame->AddField( field.Name( ), new Frame::CInFrame( currentFrame->LocalCounter ) );
			currentFrame->LocalCounter++;
		}
		// Добавляем локальные переменные фрейму
		for( const auto& field : *locals ) {
			currentFrame->AddField( field.Name( ), new Frame::CInFrame( currentFrame->LocalCounter ) );
			currentFrame->LocalCounter++;
		}
		if( methodDecl.StatementList( ) != 0 ) {
			methodDecl.StatementList( )->Accept( *this );
		}
		if( methodDecl.ReturnedExp( ) != 0 ) {
			methodDecl.ReturnedExp( )->Accept( *this );
		}
		Methods.push_back( currentFrame );
		currentFrame = nullptr;
		lastReturnedStm = nullptr;
		lastReturnedExp = nullptr;
		lastReturnedAccess = nullptr;
	}

	void CIRTreeVisitor::Visit( const CFormalList& formalList )
	{
#pragma message( "TODO Возможно здесь надо что-то делать" )
		for( auto ptr = formalList.FormalList( ).begin( ); ptr != formalList.FormalList( ).end( ); ++ptr ) {
			if( ptr != formalList.FormalList( ).begin( ) ) {
				std::cout << ", ";
			}
			ptr->first->Accept( *this );
			std::cout << " ";
			std::cout << ptr->second;
		}
	}

	void CIRTreeVisitor::Visit( const CType& type )
	{
		// Здесь для IRTree ничего не нужно
		// Все у таблицы символов
	}

	void CIRTreeVisitor::Visit( const CStatementList& statementList )
	{
		// Предполагается что есть хоть какие то statement
		assert( statementList.StatmentList( ).size( ) > 0 );
		const IRTree::IStm* listOfStm = nullptr;
		// Выполняем первый
		statementList.StatmentList( ).front( )->Accept( *this );
		listOfStm = lastReturnedStm;
		lastReturnedStm = nullptr;
		lastReturnedExp = nullptr;
		lastReturnedAccess = nullptr;
		if( statementList.StatmentList( ).size( ) == 1 ) {
			lastReturnedStm = listOfStm;
			return;
		}
		else {
			auto iter = statementList.StatmentList( ).begin( );
			iter++;
			// начинаем после прервого!
			for( ; iter != statementList.StatmentList( ).end( ); iter++ ) {
				( *iter )->Accept( *this );
				const IRTree::IStm* statementToAdd = 0;
				if( lastReturnedStm == 0 ) {
					// Нам нужны только IStm потому юзаем конвертер
					Translate::CExpConverter converter( lastReturnedExp );
					statementToAdd = converter.ToStm( );
				}
				else {
					statementToAdd = lastReturnedStm;
				}
				listOfStm = new IRTree::CSeq( listOfStm, statementToAdd );
				lastReturnedStm = nullptr;
				lastReturnedExp = nullptr;
				lastReturnedAccess = nullptr;
			}
			lastReturnedStm = listOfStm;
		}
	}

	void CIRTreeVisitor::Visit( const CAssignStatement& assignStatement )
	{
#pragma message( "TODO Возможно здесь надо что-то делать" )
		std::cout << assignStatement.LeftId( );
		if( assignStatement.IndexExp( ) != 0 ) {
			std::cout << "[";
			assignStatement.IndexExp( )->Accept( *this );
			std::cout << "]";
		}
		std::cout << " = ";
		assignStatement.RightExp( )->Accept( *this );
		std::cout << ";";
	}

	void CIRTreeVisitor::Visit( const CPrintStatement& printStatement )
	{
		// Вычисляем то что надо напечатать
		printStatement.Exp( )->Accept( *this );
		const IRTree::IExp* exprForPrint = lastReturnedExp;
		lastReturnedExp = nullptr;
		lastReturnedStm = nullptr;
		lastReturnedAccess = nullptr;
		// Вызываем функцию
		Temp::CLabel* funcName = new Temp::CLabel( "System.out.println" );
		const IRTree::CName* funcNameTree = new IRTree::CName( funcName );
		const IRTree::CExpList* args = new IRTree::CExpList( exprForPrint, nullptr );
		const IRTree::IExp* funcCall = new IRTree::CCall( funcNameTree, *args );
		lastReturnedExp = funcCall;
	}

	void CIRTreeVisitor::Visit( const CCurlyBraceStatement& curlyBraceStatement )
	{
		// Здесь ничего делать не нужно, это обрамление из фигурных скобок для StatementList
		curlyBraceStatement.StatementList( )->Accept( *this );
	}

	void CIRTreeVisitor::Visit( const CIfStatement& ifStatement )
	{
		ifStatement.Exp( )->Accept( *this );
		const IRTree::IExp* ifExpr = lastReturnedExp;
		lastReturnedExp = nullptr;
		lastReturnedStm = nullptr;
		lastReturnedAccess = nullptr;
		Temp::CLabel* trueLabelTemp = new Temp::CLabel( );
		Temp::CLabel* falseLabelTemp = new Temp::CLabel( );
		Temp::CLabel* endLabelTemp = new Temp::CLabel( );
		IRTree::CLabel* trueLabel = new IRTree::CLabel( trueLabelTemp );
		IRTree::CLabel* falseLabel = new IRTree::CLabel( falseLabelTemp );
		IRTree::CLabel* endLabel = new IRTree::CLabel( endLabelTemp );
		ifStatement.IfStatement( )->Accept( *this );
		IRTree::IStm* trueStm = new IRTree::CSeq( trueLabel, lastReturnedStm, endLabel );
		lastReturnedExp = nullptr;
		lastReturnedStm = nullptr;
		lastReturnedAccess = nullptr;
		IRTree::IStm* falseStm = 0;
		if( ifStatement.ElseStatement( ) != 0 ) {
			ifStatement.ElseStatement( )->Accept( *this );
			falseStm = new IRTree::CSeq( falseLabel, lastReturnedStm, endLabel );
			lastReturnedExp = nullptr;
			lastReturnedStm = nullptr;
			lastReturnedAccess = nullptr;
		}
		Translate::CExpConverter converter( ifExpr );
		// Предполагается что ToConditional правильно обрабатывает если второй аргумент 0
		lastReturnedStm = converter.ToConditional( trueLabelTemp, falseLabelTemp );
	}

	void CIRTreeVisitor::Visit( const CWhileStatement& whileStatement )
	{
		Temp::CLabel* beforeConditionLabelTemp = new Temp::CLabel( );
		Temp::CLabel* inLoopLabelTemp = new Temp::CLabel( );
		Temp::CLabel* endLabelTemp = new Temp::CLabel( );
		IRTree::CLabel* beforeConditionLabel = new IRTree::CLabel( new Temp::CLabel( ) );
		IRTree::CLabel* inLoopLabel = new IRTree::CLabel( new Temp::CLabel( ) );
		IRTree::CLabel* endLabel = new IRTree::CLabel( new Temp::CLabel( ) );
		whileStatement.Exp( )->Accept( *this );
		Translate::CExpConverter converter( lastReturnedExp );
		const IRTree::IStm* whileStm = converter.ToConditional( inLoopLabelTemp, endLabelTemp );
		lastReturnedExp = nullptr;
		lastReturnedStm = nullptr;
		lastReturnedAccess = nullptr;
		IRTree::IStm* conditionStm = new IRTree::CSeq( beforeConditionLabel, whileStm, inLoopLabel );
		whileStatement.Statement( )->Accept( *this );
		lastReturnedStm = new IRTree::CSeq( conditionStm, lastReturnedStm,
			new IRTree::CJump( beforeConditionLabelTemp ), endLabel );
		lastReturnedExp = nullptr;
		lastReturnedAccess = nullptr;
	}

	void CIRTreeVisitor::Visit( const CExpList& expList )
	{
#pragma message( "Не ясно что делать" )
		for( const auto& decl : expList.ExpList( ) ) {
			decl->Accept( *this );
			std::cout << std::endl;
		}
	}

} // namespace Translate