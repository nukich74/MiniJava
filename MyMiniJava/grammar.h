#pragma once

namespace Tree {

class IVisitor;

// Корневой интерфейс программы
class IProgram {
public:
	virtual ~IProgram() {}
	virtual void Accept( IVisitor* ) const = 0;
};

// Главный класс
class IMainClass {
public:
	virtual ~IMainClass() {}
	virtual void Accept( IVisitor* ) const = 0;
};

// Список классов
class IClassDeclList {
public:
	virtual ~IClassDeclList() {}
	virtual void Accept( IVisitor* ) const = 0;
};

// Описание класса
class IClassDecl {
public:
	virtual ~IClassDecl() {}
	virtual void Accept( IVisitor* ) const = 0;
};

// Список объявлений переменных
class IVarDeclList {
public:
	virtual ~IVarDeclList() {}
	virtual void Accept( IVisitor* ) const = 0;
};

// Объявление переменной
class IVarDecl {
public:
	virtual ~IVarDecl() {}
	virtual void Accept( IVisitor* ) const = 0;
};

// Список методов класса
class IMethodDeclList {
public:
	virtual ~IMethodDeclList() {}
	virtual void Accept( IVisitor* ) const = 0;
};

// Метод класса
class IMethodDecl {
public:
	virtual ~IMethodDecl() {}
	virtual void Accept( IVisitor* ) const = 0;
};

// Список параметров
class IFormalList {
public:
	virtual ~IFormalList() {}
	virtual void Accept( IVisitor* ) const = 0;
};

// Тип
class IType {
public:
	virtual ~IType() {}
	virtual std::string GetName() const = 0;
	virtual void Accept( IVisitor* ) const = 0;
};

// Последовательность команд
class IStmtList {
public:
	virtual ~IStmtList() {}
	virtual void Accept( IVisitor* ) const = 0;
};

// Одна команда (или блок)
class IStmt {
public:
	virtual ~IStmt() {}
	virtual void Accept( IVisitor* ) const = 0;
};

// Последовательность выражений (аргументы функции)
class IExprList {
public:
	virtual ~IExprList() {}
	virtual void Accept( IVisitor* ) const = 0;
};

// Арифметическое выражение
class IExpr {
public:
	virtual ~IExpr() {}
	virtual void Accept( IVisitor* ) const = 0;
};

}