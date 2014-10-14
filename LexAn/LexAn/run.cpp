#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "miniJava.h"


// ВОЗМОЖНАЯ ОШИБКА в ПРАВИЛЕ ВЫВОДА if с одиночным действием, связанная с ; (там есть и после writeln должна быть)

// реализация методов из example.h

// Выражение - арифметическая операция
int ExprArith::eval()
{
	// Есть два указателя на другие выражение и опареция между ними
	int v1, v2;
	v1 = e1->eval(); 
	if(e2) // если операция не унарная (т.е. аргумента действительно 2)
	{ 
		v2 = e2->eval();
	}
	switch(op)  // смотрим нашу операцию
	{
		case '+': 
			return v1 + v2;
		case '-': 
			return v1 - v2;
		case '*': 
			return v1 * v2;
		case '/': 
			  if (v2 == 0) //делить на 0 нельзя
			  {
				  cerr << "Runtime error: division by zero\n"; 
				  exit(1);
			  }
			  return v1 / v2;
		case UMINUS: 
			return -v1;
		case POW: 
			return pow_int(v1,v2);
	}

	return 0;
}


// хранит имя переменной
int ExprVariable::eval()
{
	struct id_tab *tab;  // указатель на структуру id_tab
	if ((tab = get_id(name))) 
	{
		return tab->value;
	} 
	else 
	{
		add_id(name, 0);
		//cerr << "Runtime error: " << name << " not defined\n";
		//exit(1);
	}
}


int ExprForVar::eval()
{
	E->run();	
}

// тут только 3 операции, остальные можно выразить через них
// выводим значение данного выражения
bool LogExpr::eval()
{
	int v1, v2;
	v1 = e1->eval(); // получаем сравниваемые элементы
	v2 = e2->eval(); // получаем сравниваемы элемент 2
	switch(op) 
	{
		case '<': return v1 < v2;
		case '>': return v1 > v2;
		case '=': return v1 == v2;
		case 'n': return v1 != v2; 
	}

	return false; // если что-то другое
}

void ListExpr::run() // поочередно вносим переменные в нашу таблицу
{
	vector<Expr*>::iterator i;
	for(i = list.begin(); i < list.end(); i++)
		(*i)->eval();
}

void ListStmt::run()
{
	// по очередно запускает команды на исполнение
	vector<Stmt*>::iterator i;
	for (i = list.begin(); i < list.end(); i++)
		(*i)->run();
}

// печать неперминала (соответсвующее ему выражение)
void StmtPrint::run()
{
	cout << e->eval();
	if (flag)
		cout << endl;
}

void StmtReturn::run()
{
	if(e)
		cout << e->eval();
	exit(0);
}

// для оператора if
void StmtIf::run()
{
	// имеет значение логической операции
	bool v = e->eval();
	
	// в зависимости от неее выполняет ту или иную последовательность команд(в нем уже есть эти последовательности команд)
	if (v) 
		L1->run();
	else
	{ 
		if (L2)
			L2->run();
	}
}

void StmtIfWithOneExpr::run()
{
	// имеет значение логической операции
	bool v = e->eval();
	
	// в зависимости от неее выполняет ту или иную последовательность команд(в нем уже есть эти последовательности команд)
	if (v) 
		L1->run();
	else
	{ 
		if (L2)
			L2->run();
	}
}
	

void StmtWhile::run()
{
	bool v = e->eval();
	while (v)
	{
		L->run();
		v = e->eval();
	} 
}

void StmtWhileForOneCommand::run()
{
	bool v = e->eval();
	while (v)
	{
		L->run();
		v = e->eval();
	} 
}


void StmtFor::run()
{
	//int first = e1->e->eval();
	int second = e2->eval();
	StmtAssign *my = new StmtAssign(name.c_str(), e1);
	my->run();
	struct id_tab *tab;
	tab = get_id(name.c_str());
	int first = tab->value;		 
	for (int i = first; i <= second; ++i)
	{ 	
		L->run();
		tab->value = tab->value + 1;
	}
		
}

void StmtForForOneCommand::run()
{
	int second = e2->eval();
	StmtAssign *my = new StmtAssign(name.c_str(), e1);
	my->run();
	struct id_tab *tab;
	tab = get_id(name.c_str());
	int first = tab->value;		 
	for (int i = first; i <= second; ++i)
	{ 	
		L->run();
		tab->value = tab->value + 1;
	}
		
}


void StmtReadln::run()
{
	int newValue;
	scanf("%d",&newValue); 
	struct id_tab *tab;  // указатель на структуру id_tab
	if ((tab = get_id(name.c_str())))// get_id ищем в списке переменных переменную с именем name
	{
		tab->value = newValue;
	} 
	else 
	{
		//add_id(name, value);
		printf("Error");// если переменной нет, значит она не была обявлена (значит мы ее не можем использовать)
	}
	
}


void StmtWriteln::run()
{
	struct id_tab *tab;  // указатель на структуру id_tab
	if ((tab = get_id(name.c_str())))// get_id ищем в списке переменных переменную с именем name
	{
		cout << tab->value << endl;
	} 
	else 
	{
		//add_id(name, value);
		cerr << "Error: we haven't this variable." << endl;// если переменной нет, значит она не была обявлена (значит мы ее не можем использовать)
	}
}


void StmtWrite::run()
{
	struct id_tab *tab;  
	if ((tab = get_id(name.c_str())))
	{
		cout << tab->value; // без прехода на следующую строку
	} 
	else 
	{
		//add_id(name, value);
		cerr << "Error: we haven't this variable." << endl;
	}
}


void StmtAssign::run()
{
			int value = e->eval();
			struct id_tab *tab;
			if ((tab = get_id(name))) 
			{
				tab->value = value;
			} 
			else 
			{
				add_id(name, value);
			}
}

ListStmt *Program;
