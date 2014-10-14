#include <string.h>
#include <stdlib.h>
#include "miniJava.h"

// здесь реализуется методы структуры tab

int ntab = 0;

struct id_tab Table[10000];


// ищет команду с нужным именем, пробегаю по массиву команд
// по имени выдает нужну команду
struct id_tab *get_id(string name)
{
	int i;
	for (i = 0; i < ntab; ++i) {
		if (name == Table[i].name)
		       return &(Table[i]);
	}
	return NULL;
}


/*
int pow_int(int x, int n)
{
	int buffer = x;
	for(int i = 0; i < n; ++i)
	{
		x = x * buffer;
	}
	return x; 
}
*/


// добавляет команду с нужным именем и значением
void add_id(string name, int value)
{
/*	Table[ntab].name = (char*)malloc(1000);

	strcpy(Table[ntab].name, name); */
	Table[ntab].name = name;
	Table[ntab].value = value; 
	++ntab; // увеличиваем счетчик команд
}
