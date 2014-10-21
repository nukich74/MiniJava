#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "miniJava.h"

void yyparse();

extern FILE* yyin;

int main(int argc, char **argv)
{
	// от этой функции и запускается программа
	// на вход получает файл с программой
	// в argv[0] - имя или т.п.
	// в argv[1] - название файла который нам нужно обработать
	FILE *handle;
	if (argc != 2) 
	{
		cerr << "Usage: " << argv[0] << " program\n";
		exit(1);
	}
	if (!(handle = fopen(argv[1], "r"))) {
		cerr << "Error: cannot open file\n";
		exit(1);
	}
	yyin = handle; // тут разбор делает flex
	yyparse(); // тут bison нам делает дерево вывода по разбора сделаному flex (1)
	// запускаем нашу программу от корня дерева (у него есть метод run())
	// дерео мы получим от bison - а в пункте (1)
}

void yyerror(string s)
{
	cerr << "Parser error: " << s << "\n";
	exit(1);
}
