#define _USE
#include <cstdio>
#include <iostream>

extern "C" int yyparse();
extern FILE* yyin;

void yyerror(const char *s) {
	std::cout << s << std::endl;
	getchar();
}

int main(int argc, char **argv)
{
	FILE* program;
	if( fopen_s( &program, "sample.java", "r" ) ) {
		std::cout << "I can't open file!" << std::endl;
	} else {
		yyin = program;	
		do {
			int rCode = yyparse();
		} while( !feof( yyin ) );
	}
	return 0;
}