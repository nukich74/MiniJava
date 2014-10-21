%{       
%} 

%error-verbose

%token <> Id
%token <> Num
%token If Else While Main Class Public Static Return Extends

%token <> Int
%token <> Boolean
%token <> Void
%token <> String

%token True
%token False
%token This
%token New
%token Length

%token Point '.'
%token Semicolomn ';'
%token Equal '='
%token Not '!'
%token Comma ','
%token FOpBracer '{'
%token FClBracer '}'
%token ROpBracer '('
%token RClBracer ')'
%token SOpBracer ']'
%token SClBracer '['
%token <> Plus
%token <> Minus
%token <> Mult
%token <> Div
%token <> And
%token <> Less

%left Minus PLUS
%left Mult DIV
%left And
%left Less
%left UMINUS ///????? %prec...
%nonassoc '!' ///??????
%left Point

%type <Program> Program
%type <MainClass> MainClass
%type <ClassDeclaration> ClassDeclaration
%type <ClassDeclarationList> ClassDeclarationList
%type <VarDeclaration> VarDeclarations
%type <VarDeclarationList> VarDeclarationList
%type <MethodDeclaration> MethodDeclaration
%type <MethodDeclarationList> MethodDeclarationList
%type <FormalList> FormalList
%type <FormalRestList> FormalRestList
%type </*Add your class*/> Type
%type <Statement> Statement
%type <StatementList> StatememtList
%type <Expr> Expr 
%type <ExprList> ExprList 
%type <ExprList> ExprRest

%union{
}
 

%%
Program 
	:	MainClass ClassDeclaration { //do smth }
	;

MainClass 
	:	Class Id '{' Public Static Void Main '(' String '[' ']' Id ')' '{' Statement '}' '}' {}
	;
	
ClassDeclaration 
	:	ClassDeclaration Class Id  '{' VarDeclaration MethodDeclaration '}' { }
	|	ClassDeclaration Class Id Extends Id '{' VarDeclarationList MethodDeclarationList '}' { }
	| /* epsilon */  { }
	;

VarDeclaration 
	: Type Id ';' { };
	;

VarDeclarationList 
	:	VarDeclarationList VarDeclaration
	|	/*epsilon*/
	;

MethodDeclaration
	: Public Type Id '(' FormalList ')' '{' VarDeclarationsList StatementList Return Expr ';' '}'
	;

MethodDeclarationList
	:	MethodDeclarationList MethodDeclaration 
	|	/*epsilon*/
	;

FormalList	
	:	Type Id FormalRestList
	|	/*epsilon*/
	;

FormalRestList
	: ',' Type Id FormalRestList
	| /*epsilon*/
	;

Type
	:	Int
    |	Bool
    |	Id
	;

StatementList
	:	Statement StatementList
	|	/*epsilon*/
	;

Statement
	:	'{' StatementList '}'
	|	If '(' Expr ')' Statement Else Statement
	|	While '(' Expr ')' Statement
	|	Print '(' Expr ')' ';'
	|	Id '=' Expr ';'
	|	Id '[' Expr ']' '=' Expr ';'
	;

Expr
	:	Expr Plus Expr
	|	Expr Minus Expr
	|	Expr Mult Expr
	|	Expr Div Expr
	|	Expr And Expr
	|	Expr '[' Expr ']'
	|	Expr '.' Length
	|	Expr '.' Id '(' ExpList ')'
	|	Num
	|	True
	|	False
	|	Id 
	|	This
	|	New Int '[' Expr ']'
	|	New Id '(' ')'
	|	'!' Expr
	|	'(' Expr ')'
	;

ExprList
	:	Expr ExprRest 
	|	/*epsilon*/
	;

ExprRest
	: ',' Expr 
	| /*epsilon*/
	;

%%