#ifndef _EXAMPLE_H
#define _EXAMPLE_H

#include <string>
#include <vector>
using namespace std;

// Enum для типов операций с нашими Int
enum ArithmOperationType
{
	PLUS, MINUS, MULTI, DELETE, UMINUS, POW	
};

enum LogicOperationType
{
	// вообще чтобы все выразить достаточно 3-х операции (2-ух:)))
	STRICT_LESS, STRICT_MORE, LESS, MORE, EQUALLY 
};


/*создаем класс интерфейс*/
class Expr {
    public:
	virtual int eval() = 0; // нужен этот метод обязательно
};


// класс арифметических операциии
// принимает два экспрешона (expression) и собственно операция на этими двумя выражениями
class ExprArith : public Expr {
    public:
	ExprArith(int op_, Expr *e1_, Expr *e2_) : op(op_), e1(e1_), e2(e2_) { }
	int eval();
    private:
	int op; /* '+', '-', '*', '/', UMINUS, POW */ // у операции должен быть тип OperationType
	Expr *e1, *e2;
};

// Класс котрый будет хранить Int значение (мы помечаем что это переменная а в дополнительной информации храним какая именно это переменная)
class ExprNumeral : public Expr {
    public:
	ExprNumeral(int val_) : val(val_) { }
	int eval() { return val; } // здесь мы его переопределяем
	void changeValue(int newVal)
	{ val = newVal; }
    private:
	int val;
};


// expression  - переменная (хранит имя переменной)
// наверное еще должна хранить объект класса ExprNumeral (где будет хранится значение этой переменной)
class ExprVariable : public Expr {
    public:
       ExprVariable(const char *name_) : name(name_) { }
       int eval();
    private:
       string name;
};




// класс логических операторов
// Для данного класса тоже надо создать enum
class LogExpr { /* A <> B */
    public:
	LogExpr(int op_, Expr *e1_, Expr *e2_) : op(op_), e1(e1_), e2(e2_) { }
	bool eval();
    private:
	int op; /* '<', '>', '=' */
	Expr *e1, *e2;
};


class ListExpr {
	public:
		ListExpr()
		{}
		void add(Expr* e)
		{
			list.push_back(e);
		}
		void run();
	private:
		vector<Expr*> list;
};


class ExprForVar : public Expr {
	public:
		ExprForVar(ListExpr* E_): E(E_)
		{}
		int eval();
	private:
		ListExpr* E;
};


// класс нетерминальных символов
// нужно для построения грамматики
// интерфейс от которого потом все будут наследоваться
class Stmt { 
    public:
	virtual void run() = 0;
};


class ListStmt {
    public:
	ListStmt()// пустой конструктор 
	{}
	void add(Stmt *s) // добавить команду
	{ 
		list.push_back(s);
	}
	void run();
    private:
	vector<Stmt*> list; // содержит вектор команд
};

// печать нетерминала
class StmtPrint : public Stmt {
    public:
	StmtPrint(Expr *e_, bool flag_) : e(e_), flag(flag_)
	{}
	void run();
    private:
	Expr *e;
	bool flag;
};


class StmtReturn : public Stmt {
 	public:
		StmtReturn(Expr *e_): e(e_)
		{}
		void run();
	private:
		Expr *e;
};


// неп=терминал для оператора if
class StmtIf : public Stmt {
    public:
	StmtIf(LogExpr *e_, ListStmt *L1_, ListStmt *L2_) : e(e_), L1(L1_), L2(L2_) 
	{ }
	void run();
    private:
	LogExpr *e; // логическая операция в данном операторе
	ListStmt *L1, *L2;
};

class StmtIfWithOneExpr : public Stmt {
	public:
		StmtIfWithOneExpr(LogExpr *e_, Stmt *L1_, Stmt *L2_): e(e_), L1(L1_), L2(L2_)
		{}
		void run();
	private:
		LogExpr *e;
		Stmt *L1;
		Stmt *L2;
}; 


class StmtWhile: public Stmt {
	public:
		StmtWhile(LogExpr *e_, ListStmt *L_):e(e_), L(L_)
		{}
		void run();
	private:
		LogExpr *e;
		ListStmt *L;
};


class StmtWhileForOneCommand: public Stmt {
	public:
		StmtWhileForOneCommand(LogExpr *e_, Stmt *L_):e(e_), L(L_)
		{}
		void run();
	private:
		LogExpr *e;
		Stmt *L;
};

//назначение
class StmtAssign : public Stmt {
    public:
	StmtAssign(const char *name_, Expr *e_) : name(name_), e(e_) { }
	void run();
    private:
	string name;
	Expr *e;
};



// для цикла for
class StmtFor: public Stmt {
	public:
        	StmtFor(const char *name_, Expr *e1_, Expr *e2_, ListStmt *L_): name(name_), e1(e1_), e2(e2_), L(L_)
		{}
		void run();
	private:
		string name;
		Expr *e1;
		Expr *e2;
		ListStmt *L;
};

class StmtForForOneCommand: public Stmt {
	public:
        	StmtForForOneCommand(const char *name_, Expr *e1_, Expr *e2_, Stmt *L_): name(name_), e1(e1_), e2(e2_), L(L_)
		{}
		void run();
	private:
		string name;
		Expr *e1;
		Expr *e2;
		Stmt *L;
};


class StmtReadln: public Stmt {
	public:
		StmtReadln(const char* name_):name(name_)
		{}
		void run();
	private:
		string name;
};


class StmtWriteln: public Stmt {
	public:
		StmtWriteln(const char* name_): name(name_)
		{}
		void run();
	private:
		string name;
}; 


class StmtWrite: public Stmt {
	public:
		StmtWrite(const char* name_): name(name_)
		{}
		void run();
	private:
		string name;
}; 

extern ListStmt *Program; 

// этот файл генерирует bison
#include "miniJavaInter.hpp"

struct id_tab 
{
	string name; //хранит имя переменной
	int value;// значение переменной
};

extern struct id_tab Table[]; // массив переменных

struct id_tab *get_id(string name);

void add_id(string name, int value);

int pow_int(int x, int n); // функция возведения в степень

int yylex();

void yyerror(string s); // функция выдачи ошибки

#endif /* _EXAMPLE_H */
