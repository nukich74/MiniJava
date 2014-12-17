#pragma once
#include "iVisitor.h"
#include <iostream>
#include <vector>
#include <string>
#include "grammar.h"
#include "CodeInfo.h"

class CProgram : public IProgram {
public:
	CProgram( const CCodeInfo& _info, const IMainClass *_mainClass, const IClassDeclList *_classDeclList) : 
		mainClass( _mainClass ), classDeclList( _classDeclList ), info( _info ) {}
	
	const IMainClass* GetMainClass() const { return mainClass; }
	const IClassDeclList* GetClassDeclList() const { return classDeclList; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }

private:
	CCodeInfo info;
	const IMainClass *mainClass;
	const IClassDeclList *classDeclList;
};


// class id { 
//	 public static void main ( String [] id ) { 
//		 statement }
// }
class CMainClass : public IMainClass {
public:
	CMainClass( const CCodeInfo& _info, const std::string& _className, const std::string& _argsName, const IStmt* _stmt ) :
		className( _className ), argsName( _argsName ), stmt( _stmt ), info( _info ) {}	
	// имя главного класса
	std::string GetNameFirst() const { return className; }
	// имя массива параметров у main() - функции
	std::string GetArgsName() const { return argsName; }
	// выражение (TODO: не массив ли выражений?)
	const IStmt* GetStmt() const { return stmt; }
	
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;	
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
	CClassDecl( const CCodeInfo& _info, const std::string& _className, const IVarDeclList* _variables, const IMethodDeclList* _methods ) :
		className( _className ), variables( _variables ), methods( _methods ), info( _info ) {}

	// имя класса
	std::string GetName() const { return className; }
	// список переменных класса
	const IVarDeclList* GetVarDeclList() const { return variables; }
	// список методов класса
	const IMethodDeclList* GetMethodDeclList() const { return methods; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }

private:
	CCodeInfo info;
	std::string className;
	const IVarDeclList* variables;
	const IMethodDeclList* methods;
};


//class id extends id { VarDecl* MethodDecl* }
class CExtendClassDecl : public IClassDecl {
public:
	CExtendClassDecl( const CCodeInfo& _info, const std::string& _className, const std::string& _baseClassName, const IVarDeclList* _variables, const IMethodDeclList *_methods ) :
		className( _className ), baseClassName( _baseClassName ), variables( _variables ), methods( _methods ), info( _info ) {}

	std::string GetClassName() const { return className; }
	std::string GetBaseClassName() const { return baseClassName; }
	const IVarDeclList* GetVarDeclList() const { return variables; }
	const IMethodDeclList* GetMethodDeclList() const { return methods; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }

private:
	CCodeInfo info;
	std::string className;
	std::string baseClassName;
	const IVarDeclList* variables;
	const IMethodDeclList* methods;
};


//Type name;
class CVarDecl : public IVarDecl {
public:
	CVarDecl( const CCodeInfo& _info, const IType* _type, const std::string& _name ) : type( _type ), name( _name ), info( _info ) {}

	// тип переменной
	const IType* GetType() const { return type; }
	// имя переменной
	const std::string GetName() const { return name; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	const IType* type;
	std::string name;
};


// public Type name ( FormalList ) { 
//		VarDeclList
//		Statement 
//      return Expr ;
// }
class CMethodDecl : public IMethodDecl {
public:
	CMethodDecl( const CCodeInfo& _info, const IType* _type, const std::string& _name, const IFormalList* _formals, 
		const IVarDeclList* _variables, const IStmtList* _statements, const IExpr* _returnExpr ) :
	type( _type ), name( _name ), formals( _formals ), variables( _variables ), statements( _statements ), returnExpr( _returnExpr ), info( _info ) {}

	// тип возвращаемого значения
	const IType* GetType() const { return type; }
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
	CCodeInfo info;
	const IType* type;
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
	CGroupStmt( const CCodeInfo& _info, const IStmtList* _statements ) : statements( _statements ), info( _info ) {}
	
	const IStmtList* GetStmtList() const { return statements; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	const IStmtList* statements;
};


// if ( Expr ) 
//	 Statement 
// else 
//	 Statement
class CIfStmt : public IStmt {
public:
	CIfStmt( const CCodeInfo& _info, const IExpr *_condition, const IStmt *_trueStatement, const IStmt *_falseStatement ) : 
		condition( _condition ), trueStatement( _trueStatement ), falseStatement( _falseStatement ), info( _info ) {}
	
	const IExpr* GetExp() const { return condition; }
	const IStmt* GetStmFirst() const { return trueStatement; }
	const IStmt* GetStmSecond() const { return falseStatement; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	const IExpr *condition;
	const IStmt *trueStatement;
	const IStmt *falseStatement;
};

// while ( Exp ) 
//   Statement
class CWhileStmt : public IStmt {
public:
	CWhileStmt( const CCodeInfo& _info, const IExpr *_condition, const IStmt*_statement ) : condition( _condition ), statement( _statement ), info( _info ) {}
	CWhileStmt() {}
	const IExpr* GetExpr() const { return condition; }
	const IStmt* GetStmt() const { return statement; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	const IExpr *condition;
	const IStmt *statement;
};


//System.out.println( Expr ) ;
class CSOPStmt : public IStmt {
public:
	CSOPStmt( const CCodeInfo& _info, const IExpr *_printedExpr ) : printedExpr( _printedExpr ), info( _info ) {}
	CSOPStmt() {}

	const IExpr* GetExpr() const { return printedExpr; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	const IExpr *printedExpr;
};


//name = Expr ;
class CAssignStmt : public IStmt {
public:
	CAssignStmt( const CCodeInfo& _info, const std::string& _name, const IExpr *_value ) : name( _name ), value( _value ), info( _info ) {}
	
	std::string GetName() const { return name; }
	const IExpr* GetExpr() const { return value; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	std::string name;
	const IExpr* value;
};


//name [ Expr ]= Expr
class CAssignExprStmt : public IStmt {
public:
	CAssignExprStmt( const CCodeInfo& _info, const std::string& _name, const IExpr *_id, const IExpr *_value ) : name( _name ), id( _id ), value( _value ), info( _info ) {}
	
	std::string GetName() const { return name; }
	const IExpr* GetExprId() const { return id; }
	const IExpr* GetExprValue() const { return value; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
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
	COpExpr( const CCodeInfo& _info, const IExpr *_lExpr, BinOp _op, const IExpr *_rExpr ) : lExpr( _lExpr ), op( _op ), rExpr( _rExpr ), info( _info ) {}
	
	const IExpr* GetExprFirst() const { return lExpr; }
	BinOp GetOp() const { return op; }
	const IExpr* GetExprSecond() const { return rExpr; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	const IExpr *lExpr;
	BinOp op;
	const IExpr *rExpr;
};


//Expr [ Expr ]
class CExExpr :public IExpr {
public:
	CExExpr( const CCodeInfo& _info, const IExpr *_idExpr, const IExpr *_expr ) : idExpr( _idExpr ), expr( _expr ), info( _info ) {}
	
	const IExpr* GetExpId() const { return idExpr; }
	const IExpr* GetExp() const { return expr; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	const IExpr *idExpr;
	const IExpr *expr;
};


//Expr . name ( ExprList )
class CMethodCallExpr :public IExpr {
public:
	CMethodCallExpr( const CCodeInfo& _info, const IExpr *_expr, const std::string& _methodName, const IExprList *_args ) : 
		expr( _expr ), methodName( _methodName ), args( _args ), info( _info ) {}
	
	const IExpr* GetExp() const { return expr; }
	std::string GetName() const { return methodName; }
	const IExprList* GetExprList() const { return args; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	const IExpr *expr;
	std::string methodName;
	const IExprList *args;
};


class CIntExpr : public IExpr {
public:
	CIntExpr( const CCodeInfo& _info, const int _number ) : number( _number ), info( _info ) {}
	
	int GetNum() const { return number; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	int number; 
};


//true
class CTrueExpr : public IExpr {
public:
	CTrueExpr( const CCodeInfo& _info ) : info( _info ) {}
	CCodeInfo info;
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
};


//false
class CFalseExpr : public IExpr {
public:
	CFalseExpr( const CCodeInfo& _info ) : info( _info ) {}
	CCodeInfo info;	
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
};


//name (имя переменной/метода/класса/...)
class CNameExpr : public IExpr {
public:
	CNameExpr( const CCodeInfo& _info, const std::string& _name ) : name( _name ), info( _info ) {}
	
	std::string GetName() const { return name; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	std::string name;
};


//this
class CThisExpr : public IExpr {
public:
	CThisExpr( const CCodeInfo& _info ) : info( _info ) {}
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
	CCodeInfo info;
};


//new int [ Expr]
class CNewIntExpr : public IExpr {
public:
	CNewIntExpr( const CCodeInfo& _info, const IExpr *_expr ) : expr( _expr ), info( _info ) {}
	
	const IExpr* GetExpr() const { return expr; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	const IExpr *expr;
};


//new name ()
class CNewIdExpr : public IExpr {
public:
	CNewIdExpr( const CCodeInfo& _info, const std::string _className ) : className( _className ), info( _info ) {}
	
	std::string GetName() const { return className; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	std::string className;
};


//! Expr
class CNotExpr : public IExpr {
public:
	CNotExpr( const CCodeInfo& _info, const IExpr *_expr ) : expr( _expr ), info( _info ) {}
	
	const IExpr* GetExpr() const { return expr; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	const IExpr *expr;
};


//( Expr )
class CBrExpr : public IExpr {
public:
	CBrExpr( const CCodeInfo& _info, const IExpr *_expr ) : expr( _expr ), info( _info ) {}
		const IExpr* GetExpr() const { return expr; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	const IExpr *expr;
};

//id wrapper
class CIdExpr :public IExpr {
public:
	CIdExpr( const CCodeInfo& _info, const std::string _name ) : name( _name ), info( _info ) {}
	std::string GetId() const { return name; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	std::string name;
};

//expr.Length
class CLengthExpr : public IExpr {
public:
	CLengthExpr( const CCodeInfo& _info, const IExpr *_source ) : source( _source ), info( _info ) {}
	const IExpr* GetExp() const { return source; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	const IExpr *source;
};

class CUnaryMinusExpr : public IExpr {
public:
	CUnaryMinusExpr( const CCodeInfo& _info, const IExpr* _expr ) : expr( _expr ) { }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
	const IExpr* GetExpr() const { return expr; }
private:
	CCodeInfo info;
	const IExpr* expr;
};

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


// name (имя класса)
class CTypeName : public IType {
public:
	CTypeName( const CCodeInfo& _info, const std::string& _name ) : name( _name ), info( _info ) {}
	std::string GetName() const { return name; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	std::string name;
};


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


class CExprList : public IExprList {
public:
	CExprList( const CCodeInfo& _info, const IExpr* expr, const IExprList* list ) : exprList( list ), curExpr( expr ) , info( _info ) {}
	
	const IExprList* GetList() const { return exprList; }
	const IExpr* GetCurrent() const { return curExpr; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	const IExprList* exprList;
	const IExpr* curExpr;
};


//Type Name FormalList
class CFormalList : public IFormalList {
public:
	CFormalList( const CCodeInfo& _info, const IType* _type, const std::string _name, const IFormalList* _formals ) :
		type( _type ), name( _name ), formals( _formals ), info( _info ) {}
	
	const IType* GetType() const { return type; }
	std::string GetName() const { return name; }
	const IFormalList* GetFormalList() const { return formals; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	const IType* type;
	std::string name;
	const IFormalList* formals;
};


class CClassDeclList : public IClassDeclList {
public:
	CClassDeclList( const CCodeInfo& _info, const IClassDecl *_current, const IClassDeclList *_list ) : curClassDecl( _current ), list( _list ), info( _info ) {}
	CClassDeclList() {}
	const IClassDecl* GetCurrent() const { return curClassDecl; }
	const IClassDeclList* GetList() const { return list; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	const IClassDecl* curClassDecl;
	const IClassDeclList* list;
};


class CVarDeclList : public IVarDeclList {
public:
	CVarDeclList( const CCodeInfo& _info, const IVarDecl* _curDecl, const IVarDeclList* _list ) : curDecl( _curDecl ), list( _list ), info( _info ) {}
	const IVarDecl* GetCurrent() const { return curDecl; }
	const IVarDeclList* GetList() const { return list; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	const IVarDecl* curDecl;
	const IVarDeclList* list;
};


class CMethodDeclList : public IMethodDeclList {
public:
	CMethodDeclList( const CCodeInfo& _info, const IMethodDecl *_method, const IMethodDeclList *_list ) : method( _method ), list( _list ), info( _info ) {}
	const IMethodDecl* GetCurrent() const { return method; }
	const IMethodDeclList* GetList() const { return list; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	const IMethodDecl* method;
	const IMethodDeclList* list;
};

class CStmtList : public IStmtList {
public:
	CStmtList( const CCodeInfo& _info, const IStmt* cStmt, const IStmtList* _stmtList ) : stmtList( _stmtList ), curStmt( cStmt ), info( _info ) {}
	
	const IStmtList* GetList() const { return stmtList; }
	const IStmt* GetStmt() const { return curStmt; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	CCodeInfo info;
	const IStmt* curStmt;
	const IStmtList* stmtList;
};
