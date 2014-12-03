#pragma once
#include "iVisitor.h"
#include <iostream>
#include <vector>
#include <string>
#include "grammar.h"

class CProgram : public IProgram {
public:
	CProgram( const IMainClass *_mainClass, const IClassDeclList *_classDeclList) : 
		mainClass( _mainClass ), classDeclList( _classDeclList ) {}
	
	const IMainClass* GetMainClass() const { return mainClass; }
	const IClassDeclList* GetClassDeclList() const { return classDeclList; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }

private:
	const IMainClass *mainClass;
	const IClassDeclList *classDeclList;
};


// class id { 
//	 public static void main ( String [] id ) { 
//		 statement }
// }
class CMainClass : public IMainClass {
public:
	CMainClass( const std::string& _className, const std::string& _argsName, const IStmt* _stmt ) :
		className( _className ), argsName( _argsName ), stmt( _stmt ) {}	
	// имя главного класса
	std::string GetNameFirst() const { return className; }
	// имя массива параметров у main() - функции
	std::string GetArgsName() const { return argsName; }
	// выражение (TODO: не массив ли выражений?)
	const IStmt* GetStmt() const { return stmt; }
	
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	std::string className;
	std::string argsName;
	const IStmt* stmt;
};


// class id { 
//	 VarDeclList 
//	 MethodDeclList 
// }
class CClassDecl : public IClassDecl {
public:
	CClassDecl( const std::string& _className, const IVarDeclList* _variables, const IMethodDeclList* _methods ) :
		className( _className ), variables( _variables ), methods( _methods ) {}

	// имя класса
	std::string GetName() const { return className; }
	// список переменных класса
	const IVarDeclList* GetVarDeclList() const { return variables; }
	// список методов класса
	const IMethodDeclList* GetMethodDeclList() const { return methods; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }

private:
	std::string className;
	const IVarDeclList* variables;
	const IMethodDeclList* methods;
};


//class id extends id { VarDecl* MethodDecl* }
class CExtendClassDecl : public IClassDecl {
public:
	CExtendClassDecl( const std::string& _className, const std::string& _baseClassName, const IVarDeclList* _variables, const IMethodDeclList *_methods ) :
		className( _className ), baseClassName( _baseClassName ), variables( _variables ), methods( _methods ) {}

	std::string GetClassName() const { return className; }
	std::string GetBaseClassName() const { return baseClassName; }
	const IVarDeclList* GetVarDeclList() const { return variables; }
	const IMethodDeclList* GetMethodDeclList() const { return methods; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }

private:
	std::string className;
	std::string baseClassName;
	const IVarDeclList *variables;
	const IMethodDeclList *methods;
};


//Type name;
class CVarDecl : public IVarDecl {
public:
	CVarDecl( const std::string& _type, const std::string& _name ) : type( _type ), name( _name ) {}

	// тип переменной
	const std::string GetType() const { return type; }
	// имя переменной
	const std::string GetName() const { return name; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	std::string type;
	std::string name;
};


// public Type name ( FormalList ) { 
//		VarDeclList
//		Statement 
//      return Expr ;
// }
class CMethodDecl : public IMethodDecl {
public:
	CMethodDecl( const std::string& _type, const std::string& _name, const IFormalList* _formals, 
		const IVarDeclList* _variables, const IStmtList* _statements, const IExpr* _returnExpr ) :
	type( _type ), name( _name ), formals( _formals ), variables( _variables ), statements( _statements ), returnExpr( _returnExpr ) {}
	~CMethodDecl() {}

	// тип возвращаемого значения
	std::string GetType() const { return type; }
	// имя метода
	std::string GetName() const { return name; }
	// список переменных
	const IFormalList* GetFormalList() const { return formals; }
	// переменные, объявленные в методе
	const IVarDeclList* GetVarDeclList() const { return variables; }
	const IStmtList* GetStmList() const { return statements; }
	const IExpr* GetExp() const { return returnExpr; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	std::string type;
	std::string name;
	const IFormalList* formals;
	const IVarDeclList* variables;
	const IStmtList* statements;
	const IExpr* returnExpr;
};

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


//{ Statement }
class CGroupStmt : public IStmt {
public:
	CGroupStmt( const IStmtList *_statements ) : statements( _statements ) {}
	
	const IStmtList* GetStmtList() const { return statements; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IStmtList *statements;
};


// if ( Expr ) 
//	 Statement 
// else 
//	 Statement
class CIfStmt : public IStmt {
public:
	CIfStmt( const IExpr *_condition, const IStmt *_trueStatement, const IStmt *_falseStatement ) : 
		condition( _condition ), trueStatement( _trueStatement ), falseStatement( _falseStatement ) {};
	
	const IExpr* GetExp() const { return condition; }
	const IStmt* GetStmFirst() const { return trueStatement; }
	const IStmt* GetStmSecond() const { return falseStatement; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExpr *condition;
	const IStmt *trueStatement;
	const IStmt *falseStatement;
};

// while ( Exp ) 
//   Statement
class CWhileStmt : public IStmt {
public:
	CWhileStmt( const IExpr *_condition, const IStmt*_statement ) : condition( _condition ), statement( _statement ) {};
	CWhileStmt() {}
	const IExpr* GetExpr() const { return condition; }
	const IStmt* GetStmt() const { return statement; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExpr *condition;
	const IStmt *statement;
};


//System.out.println( Expr ) ;
class CSOPStmt : public IStmt {
public:
	CSOPStmt( const IExpr *_printedExpr ) : printedExpr( _printedExpr ) {};
	CSOPStmt() {}

	const IExpr* GetExpr() const { return printedExpr; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExpr *printedExpr;
};


//name = Expr ;
class CAssignStmt : public IStmt {
public:
	CAssignStmt( const std::string& _name, const IExpr *_value ) : name( _name ), value( _value ) {};
	
	std::string GetName() const { return name; }
	const IExpr* GetExpr() const { return value; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	std::string name;
	const IExpr* value;
};


//name [ Expr ]= Expr
class CAssignExprStmt : public IStmt {
public:
	CAssignExprStmt( const std::string& _name, const IExpr *_id, const IExpr *_value ) : name( _name ), id( _id ), value( _value ) {};
	
	std::string GetName() const { return name; }
	const IExpr* GetExprId() const { return id; }
	const IExpr* GetExprValue() const { return value; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	std::string name;
	const IExpr *id;
	const IExpr *value;
};


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


enum BinOp {
	BO_Plus,
	BO_Minus,
	BO_Mult,
	BO_Div,
	BO_And,
	BO_Less
};


//Expr op Expr
class COpExpr :public IExpr {
public:
	COpExpr( const IExpr *_lExpr, BinOp _op, const IExpr *_rExpr ) : lExpr( _lExpr ), op( _op ), rExpr( _rExpr ) {}
	
	const IExpr* GetExprFirst() const { return lExpr; }
	BinOp GetOp() const { return op; }
	const IExpr* GetExprSecond() const { return rExpr; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExpr *lExpr;
	BinOp op;
	const IExpr *rExpr;
};


//Expr [ Expr ]
class CExExpr :public IExpr {
public:
	CExExpr( const IExpr *_idExpr, const IExpr *_expr ) : idExpr( _idExpr ), expr( _expr ) {};
	
	const IExpr* GetExpId() const { return idExpr; }
	const IExpr* GetExp() const { return expr; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExpr *idExpr;
	const IExpr *expr;
};


//Expr . name ( ExprList )
class CMethodExpr :public IExpr {
public:
	CMethodExpr( const IExpr *_expr, const std::string& _methodName, const IExprList *_args ) : 
		expr( _expr ), methodName( _methodName ), args( _args ) {};
	
	const IExpr* GetExp() const { return expr; }
	std::string GetName() const { return methodName; }
	const IExprList* GetExprList() const { return args; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExpr *expr;
	std::string methodName;
	const IExprList *args;
};


class CIntExpr : public IExpr {
public:
	CIntExpr( const int _number ) : number( _number ) {}
	
	int GetNum() const { return number; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	int number; 
};


//true
class CTrueExpr : public IExpr {
public:
	CTrueExpr() {}
	
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
};


//false
class CFalseExpr : public IExpr {
public:
	CFalseExpr() {}
	
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
};


//name (имя переменной/метода/класса/...)
class CNameExpr : public IExpr {
public:
	CNameExpr( const std::string& _name ) : name( _name ) {}
	
	std::string GetName() const { return name; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	std::string name;
};


//this
class CThisExpr : public IExpr {
public:
	CThisExpr() {}
		void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
};


//new int [ Expr]
class CNewIntExpr : public IExpr {
public:
	CNewIntExpr( const IExpr *_expr ) : expr( _expr ) {}
	
	const IExpr* GetExpr() const { return expr; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExpr *expr;
};


//new name ()
class CNewIdExpr : public IExpr {
public:
	CNewIdExpr( const std::string _className ) : className( _className ) {}
	
	std::string GetName() const { return className; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	std::string className;
};


//! Expr
class CNotExpr : public IExpr {
public:
	CNotExpr( const IExpr *_expr ) : expr( _expr ) {};
	
	const IExpr* GetExpr() const { return expr; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExpr *expr;
};


//( Expr )
class CBrExpr : public IExpr {
public:
	CBrExpr( const IExpr *_expr ) : expr( _expr ) {};
		const IExpr* GetExpr() const { return expr; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExpr *expr;
};


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


// name (имя класса)
class CTypeName : IType {
public:
	CTypeName( const std::string& _name ) : name( _name ) {};
	
	std::string GetName() const { return name; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	std::string name;
};


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


class CExprList : public IExprList {
public:
	CExprList( const IExpr* expr, const IExprList* list ) : exprList( list ), curExpr( expr )  {};
	
	const IExprList* GetList() const { return exprList; }
	const IExpr* GetCurrent() const { return curExpr; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExprList* exprList;
	const IExpr* curExpr;
};


//Type Name FormalList
class CFormalList : IFormalList {
public:
	CFormalList( const std::string& _type, const std::string _name, const IFormalList* _formals ) :
		type( _type ), name( _name ), formals( _formals ) {};
	
	std::string GetType() const { return type; }
	std::string GetName() const { return name; }
	const IFormalList* GetFormalList() const { return formals; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	std::string type;
	std::string name;
	const IFormalList* formals;
};


class CClassDeclList : public IClassDeclList {
public:
	CClassDeclList( const IClassDecl *_current, const IClassDeclList *_list ) : curClassDecl( _current ), list( _list ) {};
	CClassDeclList() {}
	const IClassDecl* GetCurrent() const { return curClassDecl; }
	const IClassDeclList* GetList() const { return list; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IClassDecl* curClassDecl;
	const IClassDeclList* list;
};


class CVarDeclList : public IVarDeclList {
public:
	CVarDeclList( const IVarDecl* _curDecl, const IVarDeclList* _list ) : curDecl( _curDecl ), list( _list ) {};
	~CVarDeclList() {}
	const IVarDecl* GetCurrent() const { return curDecl; }
	const IVarDeclList* GetList() const { return list; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IVarDecl* curDecl;
	const IVarDeclList* list;
};


class CMethodDeclList : public IMethodDeclList {
public:
	CMethodDeclList( const IMethodDecl *_method, const IMethodDeclList *_list ) : method( _method ), list( _list ) {};
	~CMethodDeclList() {}
	const IMethodDecl* GetCurrent() const { return method; }
	const IMethodDeclList* GetList() const { return list; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IMethodDecl* method;
	const IMethodDeclList* list;
};

class CStmtList : public IStmtList {
public:
	CStmtList( const IStmt* cStmt, const IStmtList* _stmtList ) : stmtList( _stmtList ), curStmt( cStmt ) {};
	
	const IStmtList* GetList() const { return stmtList; }
	const IStmt* GetStmt() const { return curStmt; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IStmt* curStmt;
	const IStmtList* stmtList;
};
