%{
#include <stdio.h>
#include <math.h>
#include <string.h>
%}

/* Выше можем подключать любые С-ишные файлы (чтобы пользоваться функцией atoi() например) */

%option noyywrap

ID       [a-z][a-z0-9]*

%%

["<"][ ]*["b"][ ]*[">"]                                  { printf ( "\\textbf{" ); }

["<"][ ]*["/"][ ]*["b"][ ]*[">"]                          { printf ( "}" ); }


["<"][ ]*"em"[ ]*[">"]                                  { printf ( "\\emph{" ); }

["<"][ ]*["/"][ ]*"em"[ ]*[">"]                          { printf ( "}" ); }


["<"][ ]*"ol"[ ]*[">"]                                  { printf ( "\\begin{enumerate}" ); }

["<"][ ]*["/"][ ]*"ol"[ ]*[">"]                          { printf ( "\\end{enumerate}" ); }


["<"][ ]*"ul"[ ]*[">"]                                  { printf ( "\\begin{itemize}" ); }

["<"][ ]*["/"][ ]*"ul"[ ]*[">"]                          { printf ( "\\end{itemize}" ); }



["<"][ ]*"li"[ ]*[">"]                                  { printf ( "\\item " ); }

["<"][ ]*["/"][ ]*"li"[ ]*[">"]                          /*пропускаем просто*/ /* eat up this teg */ 


["<"][ ]*["i"][ ]*[">"]                                  { printf ( "\\textit{" ); }

["<"][ ]*["/"][ ]*["i"][ ]*[">"]                        { printf ( "}" ); }





["<"][ ]*"title"[ ]*[">"]                                  { printf ( "\\title{" ); }

["<"][ ]*["/"][ ]*"title"[ ]*[">"]                         { printf ( "}" ); }



["<"][ ]*"time"[ ]*[">"]                                  { printf ( "\\date{" ); }

["<"][ ]*["/"][ ]*"time"[ ]*[">"]                         { printf ( "}" ); }


["<"][ ]*"div"[ ]*"="[]*{ID}[">"]                                  { printf ( "\\date{" ); }

["<"][ ]*["/"][ ]*"div"[ ]*[">"]                         { printf ( "}" ); }



["<"][ ]*["u"][ ]*[">"]                                  { printf ( "\\underline{" ); }

["<"][ ]*["/"][ ]*["u"][ ]*[">"]                          { printf ( "}" ); }


["<"][ ]*"center"[ ]*[">"]                                  { printf ( "\\begin{center}" ); }

["<"][ ]*["/"][ ]*"center"[ ]*[">"]                         { printf ( "\\end{center}" ); }



["<"][ ]*"strong"[ ]*[">"]                                  { printf ( "\\textbf{" ); }

["<"][ ]*["/"][ ]*"strong"[ ]*[">"]                          { printf ( "}" ); }




["<"][ ]*"font"[ ]+"color"[ ]*"="["\""]{ID}["\""][ ]*[">"]                   { 
																				if ( strstr(yytext,"red") !=NULL)
																						printf("\\color{red}");
																				else
																				{
																					if (strstr(yytext,"green") != NULL) 
																						printf("\\color{green}");
																					else
																					    printf("\\color{black}");
																						
																				
																				}
																				
																			}
										                                                                         
["<"][ ]*["/"][ ]*"font"[ ]*[">"]                                 



.                                                         { printf (yytext); }



%%

int main(void)
{

	yylex();
	return 0;
}
