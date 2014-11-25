#pragma once
#include "iVisitor.h"
#include <iostream>
#include <vector>
#include <string>


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


class IExpr {
public:
	virtual ~IExpr() = 0 {};
	virtual void Accept( IVisitor *v )const = 0 {};
};



class IStmt {
public:
	virtual ~IStmt() = 0 {};
	virtual void Accept( IVisitor *v ) const = 0 {};
};

class IClassDecl {
public:
	virtual ~IClassDecl() = 0 {};
	virtual void Accept( IVisitor *v )const = 0 {};
};


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


class CProgram {
public:
	CProgram( const CMainClass *_mainClass, const CClassDeclList *_classDeclList) : 
		mainClass( _mainClass ), classDeclList( _classDeclList ) {}
	~CProgram() {}
	
	const CMainClass* GetMainClass() const { return mainClass; }
	const CClassDeclList* GetClassDeclList() const { return classDeclList; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }

private:
	const CMainClass *mainClass;
	const CClassDeclList *classDeclList;
};


// class id { 
//	 public static void main ( String [] id ) { 
//		 statement }
// }
class CMainClass {
public:
	CMainClass( const std::string _className, const std::string _argsName, const IStmt *_stmt ) :
		className( _className ), argsName( _argsName ), stmt( _stmt ) {}
	~CMainClass() {}
	
	// имя главного класс
	const std::string GetNameFirst() const { return className; }
	// имя массива параметров у main() - функции
	const std::string GetArgsName() const { return argsName; }
	// выражение (TODO: не массив ли выражений?)
	const IStmt* GetStmt() const { return stmt; }
	
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const std::string className;
	const std::string argsName;
	const IStmt *stmt;
};


// class id { 
//	 VarDeclList 
//	 MethodDeclList 
// }
class CClassDecl : public IClassDecl {
public:
	CClassDecl( const std::string _className, const CVarDeclList* _variables, const CMethodDeclList* _methods ) :
		className( _className ), variables( _variables ), methods( _methods ) {}
	~CClassDecl() {}

	// имя класса
	const std::string GetName() const { return className; }
	// список переменных класса
	const CVarDeclList* GetVarDeclList() const { return variables; }
	// список методов класса
	const CMethodDeclList* GetMethodDeclList() const { return methods; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }

private:

	const std::string className;
	const CVarDeclList *variables;
	const CMethodDeclList *methods;
};


//class id extends id { VarDecl* MethodDecl* }
class CExtendClassDecl : public IClassDecl {
public:
	CExtendClassDecl( const std::string _className, const std::string _baseClassName, const CVarDeclList *_variables, const CMethodDeclList *_methods ) :
		className( _className ), baseClassName( _baseClassName ), variables( _variables ), methods( _methods ) {}
	~CExtendClassDecl() {}

	const std::string GetClassName() const { return className; }
	const std::string GetBaseClassName() const { return baseClassName; }
	const CVarDeclList* GetVarDeclList() const { return variables; }
	const CMethodDeclList* GetMethodDeclList() const { return methods; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }

private:
	const std::string className;
	const std::string baseClassName;
	const CVarDeclList *variables;
	const CMethodDeclList *methods;
};


//Type name;
class CVarDecl {
public:
	CVarDecl( const std::string _type, const std::string _name ) : type( _type ), name( _name ) {}
	~CVarDecl() {}

	// тип переменной
	const std::string GetType() const { return type; }
	// имя переменной
	const std::string GetName() const { return name; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const std::string type;
	const std::string name;
};


// public Type name ( FormalList ) { 
//		VarDeclList
//		Statement 
//      return Expr ;
// }
class CMethodDecl {
public:
	CMethodDecl( const std::string _type, const std::string _name, const CFormalList *_formals, 
		const CVarDeclList *_variables, const CStmtList *_statements, const IExpr *_returnExpr ) :
	type( _type ), name( _name ), formals( _formals ), variables( _variables ), statements( _statements ), returnExpr( _returnExpr ) {}
	~CMethodDecl() {}

	// тип возвращаемого значения
	const std::string GetType() const { return type; }
	// имя метода
	const std::string GetName() const { return name; }
	// список переменных
	const CFormalList* GetFormalList() const { return formals; }
	// переменные, объявленные в методе
	const CVarDeclList* GetVarDeclList() const { return variables; }
	const CStmtList* GetStmList() const { return statements; }
	const IExpr* GetExp() const { return returnExpr; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const std::string type;
	const std::string name;
	const CFormalList *formals;
	const CVarDeclList *variables;
	const CStmtList *statements;
	const IExpr *returnExpr;
};


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


//{ Statement }
class CGroupStmt : public IStmt {
public:
	CGroupStmt( const CStmtList *_statements ) : statements( _statements ) {}
	~CGroupStmt() {}

	const CStmtList* GetStmtList() const { return statements; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const CStmtList *statements;
};


// if ( Expr ) 
//	 Statement 
// else 
//	 Statement
class CIfStmt : public IStmt {
public:
	CIfStmt( const IExpr *_condition, const IStmt *_trueStatement, const IStmt *_falseStatement ) : 
		condition( _condition ), trueStatement( _trueStatement ), falseStatement( _falseStatement ) {};
	~CIfStmt() {}

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
	CAssignStmt( const std::string _name, const IExpr *_value ) : name( _name ), value( _value ) {};
	~CAssignStmt() {}

	const std::string GetName() const { return name; }
	const IExpr* GetExpr() const { return value; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const std::string name;
	const IExpr* value;
};


//name [ Expr ]= Expr
class CAssignExprStmt : public IStmt {
public:
	CAssignExprStmt( const std::string _name, const IExpr *_id, const IExpr *_value ) : name( _name ), id( _id ), value( _value ) {};
	~CAssignExprStmt() {}

	const std::string GetName() const { return name; }
	const IExpr* GetExprId() const { return id; }
	const IExpr* GetExprValue() const { return value; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const std::string name;
	const IExpr *id;
	const IExpr *value;
};


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


enum CBinOp {
	Plus,
	Minus,
	Mult,
	Div,
	And,
	Less
};


//Expr op Expr
class COpExpr :public IExpr {
public:
	COpExpr( const IExpr *_lExpr, CBinOp _op, const IExpr *_rExpr ) : lExpr( _lExpr ), op( _op ), rExpr( _rExpr ) {}
	~COpExpr() {}

	const IExpr* GetExprFirst() const { return lExpr; }
	CBinOp GetOp() const { return op; }
	const IExpr* GetExprSecond() const { return rExpr; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExpr *lExpr;
	CBinOp op;
	const IExpr *rExpr;
};


//Expr [ Expr ]
class CExExpr :public IExpr {
public:
	CExExpr( const IExpr *_idExpr, const IExpr *_expr ) : idExpr( _idExpr ), expr( _expr ) {};
	~CExExpr() {}

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
	CMethodExpr( const IExpr *_expr, const std::string _methodName, const CExprList *_args ) : 
		expr( _expr ), methodName( _methodName ), args( _args ) {};
	~CMethodExpr() {}

	const IExpr* GetExp() const { return expr; }
	const std::string GetName() const { return methodName; }
	const CExprList* GetExprList() const { return args; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExpr *expr;
	const std::string methodName;
	const CExprList *args;
};


class CIntExpr : public IExpr {
public:
	CIntExpr( const int _number ) : number( _number ) {}
	~CIntExpr() {}

	const int GetNum() const { return number; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const int number; 
};


//true
class CTrueExpr :public IExpr {
public:
	CTrueExpr() {}
	~CTrueExpr() {}

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
};


//false
class CFalseExpr :public IExpr {
public:
	CFalseExpr() {}
	~CFalseExpr() {}

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
};


//name (имя переменной/метода/класса/...)
class CNameExpr :public IExpr {
public:
	CNameExpr( const std::string _name ) : name( _name ) {}
	~CNameExpr() {}

	const std::string GetName() const { return name; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const std::string name;
};


//this
class CThisExpr :public IExpr {
public:
	CThisExpr() {}
	~CThisExpr() {}
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
};


//new int [ Expr]
class CNewIntExpr :public IExpr {
public:
	CNewIntExpr( const IExpr *_expr ) : expr( _expr ) {}
	~CNewIntExpr() {}

	const IExpr* GetExpr() const { return expr; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExpr *expr;
};


//new name ()
class CNewIdExpr :public IExpr {
public:
	CNewIdExpr( const std::string _className ) : className( _className ) {}
	~CNewIdExpr() {}

	const std::string GetName() const { return className; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const std::string className;
};


//! Expr
class CNotExpr :public IExpr {
public:
	CNotExpr( const IExpr *_expr ) : expr( _expr ) {};
	~CNotExpr() {}

	const IExpr* GetExpr() const { return expr; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExpr *expr;
};


//( Expr )
class CBrExpr : public IExpr {
public:
	CBrExpr( const IExpr *_expr ) : expr( _expr ) {};
	~CBrExpr() {}
	const IExpr* GetExpr() const { return expr; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExpr *expr;
};


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


// name (имя класса)
class CTypeName {
public:
	CTypeName( const std::string _name ) : name( _name ) {};
	~CTypeName() {}

	const std::string GetName() const { return name; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const std::string name;
};


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


class CExprList {
public:
	CExprList( const std::vector<IExpr*> _exprList ) : exprList( _exprList ) {};
	~CExprList() {}

	const std::vector<IExpr*> GetExprList() const { return exprList; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	std::vector<IExpr*> exprList;
};


//Type Name FormalList
class CFormalList {
public:
	CFormalList( const std::string _type, const std::string _name, const CFormalList * _formals ) :
		type( _type ), name( _name ), formals( _formals ) {};
	~CFormalList() {}

	const std::string GetType() const { return type; }
	const std::string GetName() const { return name; }
	const CFormalList* GetFormalList() const { return formals; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const std::string type;
	const std::string name;
	const CFormalList *formals;
};


class CClassDeclList {
public:
	CClassDeclList( std::vector<IClassDecl*> _declList) : declList( _declList ) {};
	CClassDeclList() {}

	const std::vector<IClassDecl*> GetDeclList() const { return declList; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	std::vector<IClassDecl*> declList;
};


class CVarDeclList {
public:
	CVarDeclList( std::vector<CVarDecl*> _varDeclList ) : varDeclList( _varDeclList ) {};
	~CVarDeclList() {}

	const std::vector<CVarDecl*> GetVarDeclList() const { return varDeclList; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	std::vector<CVarDecl*> varDeclList;
};


class CMethodDeclList {
public:
	CMethodDeclList( std::vector<CMethodDecl*> _methodDeclList ) : methodDeclList( _methodDeclList ) {};
	~CMethodDeclList() {}

	const std::vector<CMethodDecl*> GetMethodDeclList() const { return methodDeclList; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	std::vector<CMethodDecl*> methodDeclList;
};


class CStmtList {
public:
	CStmtList( std::vector<IStmt*> _stmtList ) : stmtList( _stmtList ) {};
	~CStmtList() {}

	const std::vector<IStmt*> GetStmtList() const { return stmtList; }

	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	std::vector<IStmt*> stmtList;
};
