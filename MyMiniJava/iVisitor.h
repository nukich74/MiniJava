#pragma once

class CProgram;
class CMainClass;

class CClassDecl;
class CExtendClassDecl;
class CVarDecl;
class CMethodDecl;

class CGroupStmt;
class CIfStmt;
class CWhileStmt;
class CSOPStmt;
class CAssignStmt;
class CAssignExprStmt;

class COpExpr;
class CExExpr;
class CMethodCallExpr;
class CIntExpr;
class CTrueExpr;
class CFalseExpr;
class CNameExpr;
class CThisExpr;
class CNewIntExpr;
class CNewIdExpr;
class CNotExpr;
class CBrExpr;
class CIdExpr;
class CLengthExpr;
class CUnaryMinusExpr;

class CTypeName;

class CExprList;
class CFormalList;
class CClassDeclList;
class CVarDeclList;
class CMethodDeclList;
class CStmtList;


class IVisitor {
public:
	virtual ~IVisitor() {};

	virtual void Visit( const CProgram& p ) = 0;
	virtual void Visit( const CMainClass& p ) = 0;
	virtual void Visit( const CClassDecl& p ) = 0;
	virtual void Visit( const CClassDeclList& p ) = 0;

	virtual void Visit( const CExtendClassDecl& p ) = 0;
	virtual void Visit( const CVarDecl& p ) = 0;

	virtual void Visit( const CMethodDecl& p ) = 0;
	virtual void Visit( const CGroupStmt& p ) = 0;
	virtual void Visit( const CIfStmt& p ) = 0;
	virtual void Visit( const CWhileStmt& p ) = 0;
	virtual void Visit( const CSOPStmt& p ) = 0;
	virtual void Visit( const CAssignStmt& p ) = 0;
	virtual void Visit( const CAssignExprStmt& p ) = 0;

	virtual void Visit( const COpExpr& p ) = 0;
	virtual void Visit( const CExExpr& p ) = 0;
	virtual void Visit( const CMethodCallExpr& p ) = 0;
	virtual void Visit( const CIntExpr& p ) = 0;
	virtual void Visit( const CTrueExpr& p ) = 0;
	virtual void Visit( const CFalseExpr& p ) = 0;
	virtual void Visit( const CThisExpr& p ) = 0;
	virtual void Visit( const CNewIntExpr& p ) = 0;
	virtual void Visit( const CNewIdExpr& p ) = 0;
	virtual void Visit( const CNotExpr& p ) = 0;
	virtual void Visit( const CBrExpr& p ) = 0;
	virtual void Visit( const CIdExpr& p ) = 0;
	virtual void Visit( const CLengthExpr& p ) = 0; 
	virtual void Visit( const CUnaryMinusExpr& p ) = 0;

	virtual void Visit( const CTypeName& p ) = 0;

	virtual void Visit( const CExprList& p ) = 0;
	virtual void Visit( const CFormalList& p ) = 0;
	virtual void Visit( const CVarDeclList& p ) = 0;
	virtual void Visit( const CMethodDeclList& p ) = 0;
	virtual void Visit( const CStmtList& p ) = 0;
};
