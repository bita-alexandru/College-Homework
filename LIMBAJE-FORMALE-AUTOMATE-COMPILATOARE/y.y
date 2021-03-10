%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

char scope[MAX_STR] = "STRUCTURES";
int var_in_func = 0;

extern FILE* yyin;
extern char* yytext;
extern int yylineno;
%}

%union {
	int intval;
	float numval;
	char charval;
	char* strval;

	struct Symbol* symbol;
}

%type <symbol>listaParam 
%type <symbol>declarareParam
%type <symbol>parametru
%type <symbol>listaValori
%type <symbol>valoare
%type <symbol>expresie
%type <symbol>accesArray
%type <symbol>accesStruct
%type <symbol>apelFunctie

%token EVAL
%token <strval>ID <strval>TIP <charval>VARCONST <strval>SIR
%token ATRIBUIRE
%token <intval>DIMENSIUNE
%token <numval>NUMAR 
%token STRUCT SELECTOR
%token STRUCTURI FUNCTII GLOBAL MAIN
%token IF ELSE WHILE FOR
%token FOR_START FOR_STOP FOR_STEP
%token FUNC RETURN
%token ADD SUB DIV MUL
%token AND OR XOR NOT
%token EQ GT GE LT LE
%token PRINT
%token CONCAT COPY

%start limbaj

%left NOT
%left ADD SUB
%left MUL DIV 
%left EQ GT GE LT LE
%left AND OR XOR
%left SELECTOR
%right ATRIBUIRE

%left '(' ')'
%left '[' ']'
%left '{' '}'
%%
limbaj: blocStructuri blocFunctii blocGlobal blocMain {
	// TODO: construieste blocul de cod

	printf("program corect sintactic\n");
	print_symbol_table();
	}
	;

blocStructuri:
	STRUCTURI '{' '}' {
		update_scope(scope, "FUNCTIONS");
	}
	| STRUCTURI '{' listaStructuri '}' {
		update_scope(scope, "FUNCTIONS");
	}
	;
blocFunctii:
	FUNCTII '{' '}' {
		update_scope(scope, "GLOBAL");
	}
	| FUNCTII '{' listaFunctii '}' {
		update_scope(scope, "GLOBAL");
	}
	;
blocGlobal:
	GLOBAL '{' '}' {
		update_scope(scope, "MAIN");
	}
	| GLOBAL '{' listaDeclarari '}' {
		update_scope(scope, "MAIN");
	}
	;
blocMain: 
	MAIN '{' '}'
	| MAIN '{' blocCod '}'
	;

listaStructuri :
	constructieStruct ';'
	| listaStructuri constructieStruct ';'
	;
constructieStruct: 
    STRUCT ID '{' listaVar listaFunctii '}' {
		// verifica daca id-ul depaseste lungimea maxima
		check_length($2, MAX_ID);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate($2, scope, 0, 0, NONE_PT);
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =
		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			$2, IS_STRUCT, 0, 0, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);
		add_symbol(IS_STRUCT, symbol);

		update_symbol_scope("STRUCTURES", $2, IS_VARCONST);
		update_symbol_scope("STRUCTURES", $2, IS_FUNC);
		update_temp_scope($2);
	}
	| STRUCT ID '{' listaVar '}' {
		// verifica daca id-ul depaseste lungimea maxima
		check_length($2, MAX_ID);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate($2, scope, 0, 0, NONE_PT);
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			$2, IS_STRUCT, 0, 0, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);
		add_symbol(IS_STRUCT, symbol);

		update_symbol_scope("STRUCTURES", $2, IS_VARCONST);
		update_symbol_scope("STRUCTURES", $2, IS_FUNC);
		update_temp_scope($2);
	}
	| STRUCT ID '{' listaFunctii '}' {
		// verifica daca id-ul depaseste lungimea maxima
		check_length($2, MAX_ID);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate($2, scope, 0, 0, NONE_PT);
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			$2, IS_STRUCT, 0, 0, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);
		add_symbol(IS_STRUCT, symbol);

		update_symbol_scope("STRUCTURES", $2, IS_VARCONST);
		update_symbol_scope("STRUCTURES", $2, IS_FUNC);
		update_temp_scope($2);
	}
    ;
declarareStruct:
	'#' ID ID {
		// verifica daca id-ul depaseste lungimea maxima
		check_length($3, MAX_ID);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate($3, scope, 0, 0, NONE_PT);
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			$3, IS_VAR, TYPE_STRUCT, DIM_UNI, scope, $2, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);
		add_symbol(IS_VARCONST, symbol);
	}
	| '#' ID DIMENSIUNE ID {
		// verifica daca id-ul depaseste lungimea maxima
		check_length($4, MAX_ID);
		// verifica daca dimensiunea array-ului depaseste lungimea maxima
		check_size($3, MAX_DIM);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate($4, scope, 0, 0, NONE_PT);
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			$4, IS_VAR, TYPE_STRUCT, DIM_ARR, scope, $2, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, $3, NONE_E
			);
		add_symbol(IS_VARCONST, symbol);
	}
	;
listaVar:
	declarareVar ';'
	| listaVar declarareVar ';'
	;

listaFunctii:
    declarareFunctie 
    | listaFunctii declarareFunctie
    ;
declarareFunctie: 
    FUNC TIP ID '(' ')' '{' blocCod RETURN valoare ';' '}' {
		// verifica daca id-ul depaseste lungimea maxima
		check_length($3, MAX_ID);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate($3, scope, IS_FUNC, 0, NONE_PT);
		check_value(0, $3, $2, $9);
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		int type = get_type_int($2);

		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			$3, IS_FUNC, type, 0, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);
		add_symbol(IS_FUNC, symbol);

		update_symbol_scope("FUNCTIONS", $3, IS_VARCONST);
		if(!strcmp(scope, "STRUCTURES")) {
			char newscope[MAX_STR];
			strcpy(newscope, scope);
			strcat(newscope, " TEMP ");
			strcat(newscope, $3);
			update_lastn_scope(var_in_func, newscope);
		}
		var_in_func = 0;

		free($9);
	}
	| FUNC TIP ID '(' ')' '{' RETURN valoare ';' '}' {
		// verifica daca id-ul depaseste lungimea maxima
		check_length($3, MAX_ID);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate($3, scope, IS_FUNC, 0, NONE_PT);
		check_value(0, $3, $2, $8);
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		int type = get_type_int($2);

		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			$3, IS_FUNC, type, 0, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);
		add_symbol(IS_FUNC, symbol);

		update_symbol_scope("FUNCTIONS", $3, IS_VARCONST);
		if(!strcmp(scope, "STRUCTURES")) {
			char newscope[MAX_STR];
			strcpy(newscope, scope);
			strcat(newscope, " TEMP ");
			strcat(newscope, $3);
			update_lastn_scope(var_in_func, newscope);
		}
		var_in_func = 0;

		free($8);
	}
    | FUNC TIP ID '(' declarareParam ')' '{' blocCod RETURN valoare ';' '}' {
		// verifica daca id-ul depaseste lungimea maxima
		check_length($3, MAX_ID);
		check_value(0, $3, $2, $10);
		// TODO: verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		int type = get_type_int($2);
		int n_params = $5->n_params;
		char paramtypes[MAX_PARAMS][MAX_TYPE] = {0}; copy_params(paramtypes, $5->paramtypes, n_params);

		check_duplicate($3, scope, IS_FUNC, n_params, paramtypes);
		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			$3, IS_FUNC, type, 0, scope, NONE_S, 0, 0, 0, NONE_S, n_params, NONE_PV, paramtypes, 0, NONE_E
			);
		add_symbol(IS_FUNC, symbol);

		update_symbol_scope("FUNCTIONS", $3, IS_VARCONST);
		if(!strcmp(scope, "STRUCTURES")) {
			char newscope[MAX_STR];
			strcpy(newscope, scope);
			strcat(newscope, " TEMP ");
			strcat(newscope, $3);
			update_lastn_scope(var_in_func, newscope);
		}
		var_in_func = 0;

		free($5); free($10);
	}
	| FUNC TIP ID '(' declarareParam ')' '{' RETURN valoare ';' '}' {
		// verifica daca id-ul depaseste lungimea maxima
		check_length($3, MAX_ID);
		check_value(0, $3, $2, $9);
		// TODO: verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica d	aca valoarea din dreapta = are acelasi tip ca var din stanga =

		int type = get_type_int($2);
		int n_params = $5->n_params;
		char paramtypes[MAX_PARAMS][MAX_TYPE] = {0}; copy_params(paramtypes, $5->paramtypes, n_params);

		check_duplicate($3, scope, IS_FUNC, n_params, paramtypes);
		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			$3, IS_FUNC, type, 0, scope, NONE_S, 0, 0, 0, NONE_S, n_params, NONE_PV, paramtypes, 0, NONE_E
			);
		add_symbol(IS_FUNC, symbol);
		
		update_symbol_scope("FUNCTIONS", $3, IS_VARCONST);
		if(!strcmp(scope, "STRUCTURES")) {
			char newscope[MAX_STR];
			strcpy(newscope, scope);
			strcat(newscope, " TEMP ");
			strcat(newscope, $3);
			update_lastn_scope(var_in_func, newscope);
		}
		var_in_func = 0;

		free($5); free($9);
	}
    ;
apelFunctie:
    '~' ID '(' ')' {
		check_length($2, MAX_ID);
		// TODO: verifica daca func apelata a fost definita
		check_defined($2, scope);
		// TODO: verifica daca func apelata are parametrii valizi

		struct Symbol* symbol = get_function($2, 0, NONE_PT);

		$$ = copy_symbol(symbol);
	}
    | '~' ID '(' listaParam ')' {
		check_length($2, MAX_ID);
		// TODO: verifica daca func apelata a fost definita
		// TODO: verifica daca func apelata are parametrii valizi

		struct Symbol* symbol = get_function($2, $4->n_params, $4->paramtypes);

		$$ = copy_symbol(symbol);
		free($4);
	}
    ;
listaParam:
	valoare {
		$$ = copy_symbol($1);
		append_param($$, $1);

		free($1);
	}
	| listaParam ',' valoare {
		append_param($1, $3);
		
		$$ = copy_symbol($1);
		free($1); free($3);
	}
	;
declarareParam:
    parametru {
		$$ = copy_symbol($1);
		append_param($$, $1);

		free($1);

		var_in_func++;
		}
    | declarareParam ',' parametru {
		append_param($1, $3);
		
		$$ = copy_symbol($1);
		free($1); free($3);
			
		var_in_func++;
		}
    ;
parametru:
	VARCONST TIP ID {
		// verifica daca id-ul depaseste lungimea maxima
		check_length($3, MAX_ID);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate($3, scope, 0, 0, NONE_PT);
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		int varconst = get_varconst_int($1);
		int type = get_type_int($2);

		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			$3, varconst, type, DIM_UNI, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);
		add_symbol(IS_VARCONST, symbol);

		$$ = copy_symbol(&symbol);
	}
	| VARCONST TIP DIMENSIUNE ID {
		// verifica daca id-ul depaseste lungimea maxima
		check_length($4, MAX_ID);
		// verifica daca dimensiunea array-ului depaseste lungimea maxima
		check_size($3, MAX_DIM);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate($4, scope, 0, 0, NONE_PT);
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		int varconst = get_varconst_int($1);
		int type = get_type_int($2);

		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			$4, varconst, type, DIM_ARR, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, $3, NONE_E
			);
		add_symbol(IS_VARCONST, symbol);

		$$ = copy_symbol(&symbol);
	}
	;

listaDeclarari:
	declarareVar ';'
	| listaDeclarari declarareVar ';'
	| declarareStruct ';'
	| listaDeclarari declarareStruct ';'
	;
declarareVar:
	VARCONST TIP ID {
		// verifica daca id-ul depaseste lungimea maxima
		check_length($3, MAX_ID);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate($3, scope, 0, 0, NONE_PT);
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		int varconst = get_varconst_int($1);
		int type = get_type_int($2);

		if(varconst == IS_CONST) check_const($3, scope, 0);

		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			$3, varconst, type, DIM_UNI, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);
		
		add_symbol(IS_VARCONST, symbol);
	}
	| VARCONST TIP ID ATRIBUIRE valoare {
		// verifica daca id-ul depaseste lungimea maxima
		check_length($3, MAX_ID);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate($3, scope, 0, 0, NONE_PT);
		check_value(0, $3, $2, $5);
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		int varconst = get_varconst_int($1);
		int type = get_type_int($2);


		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			$3, varconst, type, DIM_UNI, scope, NONE_S, 1, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);
		assign_value(&symbol, $5);
		add_symbol(IS_VARCONST, symbol);
		
		free($5);
	}
	| VARCONST TIP DIMENSIUNE ID {
		// verifica daca id-ul depaseste lungimea maxima
		check_length($4, MAX_ID);
		// verifica daca dimensiunea array-ului depaseste lungimea maxima
		check_size($3, MAX_DIM);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate($4, scope, 0, 0, NONE_PT);
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		int varconst = get_varconst_int($1);
		int type = get_type_int($2);

		if(varconst == IS_CONST) check_const($4, scope, 0);
		
		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			$4, varconst, type, DIM_ARR, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, $3, NONE_E
			);
		add_symbol(IS_VARCONST, symbol);
	}
	| VARCONST TIP DIMENSIUNE ID ATRIBUIRE '[' listaValori ']'  {
		// verifica daca id-ul depaseste lungimea maxima
		check_length($4, MAX_ID);
		// verifica daca dimensiunea array-ului depaseste lungimea maxima
		check_size($3, MAX_DIM);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate($4, scope, 0, 0, NONE_PT);
		check_array(0, $4, $2, $7, $3);
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		int varconst = get_varconst_int($1);
		int type = get_type_int($2);
		
		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			$4, varconst, type, DIM_ARR, scope, NONE_S, 1, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, $3, NONE_E
			);
		assign_value(&symbol, $7);
		add_symbol(IS_VARCONST, symbol);

		free($7);
	}
	;
listaValori:
	valoare {
		$$ = copy_symbol($1);
		append_element($$, $1);

		free($1);
	}
	| listaValori ',' valoare {
		append_element($1, $3);

		$$ = copy_symbol($1);
		free($1); free($3);
	}
	;
valoare:
	SIR {
		int type = get_string_type($1);
		char chrvalue = (type == TYPE_CHAR) ? $1[1] : 0;
		char strvalue[MAX_STR] = {0}; if(type == TYPE_STRING) strcpy(strvalue, $1); 
		
		struct Symbol symbol = create_symbol(
			// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
			NONE_I, 0, type, DIM_UNI, scope, NONE_S, 0, 0, chrvalue, strvalue, 0, NONE_PV, NONE_PT, 0, NONE_E
			);

		$$ = copy_symbol(&symbol);
	}
	| NUMAR {
		int type = get_num_type($1);

		struct Symbol symbol = create_symbol(
			// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
			NONE_I, 0, type, 0, scope, NONE_S, 0, $1, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);

		$$ = copy_symbol(&symbol);
	}
	| '-' NUMAR {
		int type = get_num_type($2);

		struct Symbol symbol = create_symbol(
			// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
			NONE_I, 0, type, DIM_UNI, scope, NONE_S, 0, -$2, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);

		$$ = copy_symbol(&symbol);
	}
	| ID {
		check_length($1, MAX_ID);
		check_defined($1, scope);
		check_init($1, scope);

		struct Symbol* symbol = get_variable($1, scope);
		
		$$ = copy_symbol(symbol);
	}
	| accesArray {
		$$ = copy_symbol($1);
		free($1);
		// TODO: returneaza valoarea pt accesului unui element din array/struct
	}
	| accesStruct {
		$$ = copy_symbol($1);
		free($1);
		// TODO: returneaza valoarea pt accesului unui element din array/struct
	}
	| apelFunctie {
		$$ = copy_symbol($1);
		free($1);
		// TODO: returneaza valoarea in urma apelului unei functii
	}
	| '$' expresie '$' {
		$$ = copy_symbol($2);
		free($2);
		// TODO: construieste simbolul pt o valoare
	}
	;
expresie:
	ID {
		check_length($1, MAX_ID);
		check_defined($1, scope);
		check_init($1, scope);

		struct Symbol* symbol = get_variable($1, scope);
		
		$$ = copy_symbol(symbol);
	}
	| NUMAR {
		int type = get_num_type($1);

		struct Symbol symbol = create_symbol(
			// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
			NONE_I, 0, type, DIM_UNI, scope, NONE_S, 0, $1, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);

		$$ = copy_symbol(&symbol);
	}
	| SIR {
		int type = get_string_type($1);
		char chrvalue = (type == TYPE_CHAR) ? $1[1] : 0;
		char strvalue[MAX_STR] = {0}; if(type == TYPE_STRING) strcpy(strvalue, $1); 
		
		struct Symbol symbol = create_symbol(
			// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
			NONE_I, 0, type, DIM_UNI, scope, NONE_S, 0, 0, chrvalue, strvalue, 0, NONE_PV, NONE_PT, 0, NONE_E
			);

		$$ = copy_symbol(&symbol);
	}
	| accesArray {
		$$ = copy_symbol($1);
		free($1);
		// TODO: returneaza valoarea pt accesului unui element din array/struct
	}
	| accesStruct {
		$$ = copy_symbol($1);
		free($1);
		// TODO: returneaza valoarea pt accesului unui element din array/struct
	}
	| apelFunctie {
		$$ = copy_symbol($1);
		free($1);
		// TODO: returneaza valoarea in urma apelului unei functii
	}
	| '(' expresie ')' {
		$$ = copy_symbol($2);
		free($2);
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
	| expresie ADD expresie {
		add_expr($1, $3);

		$$ = copy_symbol($1);
		free($1); free($3);
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
	| expresie SUB expresie {
		sub_expr($1, $3);

		$$ = copy_symbol($1);
		free($1); free($3);
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
	| expresie MUL expresie {
		mul_expr($1, $3);

		$$ = copy_symbol($1);
		free($1); free($3);
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
	| expresie DIV expresie {
		div_expr($1, $3);

		$$ = copy_symbol($1);
		free($1); free($3);
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
	| expresie EQ expresie {
		eq_expr($1, $3);

		$$ = copy_symbol($1);
		free($1); free($3);
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
	| expresie GT expresie {
		gt_expr($1, $3);

		$$ = copy_symbol($1);
		free($1); free($3);

		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
	| expresie LT expresie {
		lt_expr($1, $3);

		$$ = copy_symbol($1);
		free($1); free($3);
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
	| expresie GE expresie {
		ge_expr($1, $3);

		$$ = copy_symbol($1);
		free($1); free($3);
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
	| expresie LE expresie {
		le_expr($1, $3);

        $$ = copy_symbol($1);
		free($1); free($3);
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
	| expresie AND expresie {
		and_expr($1, $3);

        $$ = copy_symbol($1);
		free($1); free($3);
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
	| expresie OR expresie {
		or_expr($1, $3);

        $$ = copy_symbol($1);
		free($1); free($3);
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
	| expresie XOR expresie {
		xor_expr($1, $3);

        $$ = copy_symbol($1);
		free($1); free($3);
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
	| NOT expresie {
		not_expr($2);

        $$ = copy_symbol($2);
		free($2);
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
	;

blocCod:
	linieCod
	| blocCod linieCod
	;
linieCod:
	evaluare ';'
	| printare ';'
	| declarareVar ';' {var_in_func++;}
	| constructieStruct ';'
	| declarareStruct ';'
	| asignare ';'
	| apelFunctie ';' {
		free($1);
	}
	| controlString ';'
	| controlIfElse
	| controlWhile
	| controlFor
	;

evaluare:
	EVAL '(' valoare ')' {
		// TODO: implementeaza Eval(int expr)
		check_type($3, TYPE_INT);
		print_symbol($3);
		print_symbol(0);

		free($3);
	}
	;
printare:
	PRINT '(' ')' {
		// TODO: implementeaza afisarea pe ecran
		print_symbol(0);
	}
	| PRINT '(' valoare ')' {
		// TODO: implementeaza afisarea pe ecran
		print_symbol($3);
		free($3);
	}
	;
asignare:
	ID ATRIBUIRE valoare {
		check_length($1, MAX_ID);
		check_defined($1, scope);
		check_const($1, scope, 1);

		struct Symbol* symbol = get_variable($1, scope);
		check_value(symbol, NONE_I, NONE_T, $3);
		assign_value(symbol, $3);

		free($3);
	}
	| ID ATRIBUIRE '[' listaValori ']' {
		check_length($1, MAX_ID);
		check_defined($1, scope);
		check_const($1, scope, 1);

		struct Symbol* symbol = get_variable($1, scope);
		check_array(symbol, NONE_I, NONE_T, $4, 0);
		assign_value(symbol, $4);

		free($4);
		// TODO: verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		// TODO: verifica daca id-ul depaseste lungimea maxima
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =
	}
	| accesArray ATRIBUIRE valoare {
		check_value($1, NONE_I, NONE_T, $3);
		assign_value($1, $3);

		free($1); free($3);
		// TODO: verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		// TODO: verifica daca id-ul depaseste lungimea maxima
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =
	}
	| accesStruct ATRIBUIRE valoare {
		check_value($1, NONE_I, NONE_T, $3);
		assign_value($1, $3);

		free($1); free($3);
	}
	| accesStruct ATRIBUIRE '[' listaValori ']' {
		check_value($1, NONE_I, NONE_T, $4);
		assign_value($1, $4);

		free($1); free($4);
		// TODO: verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		// TODO: verifica daca id-ul depaseste lungimea maxima
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =
	}
	;
	
accesArray:
	ID '[' valoare ']' {
		check_length($1, MAX_ID);
		check_defined($1, scope);

		struct Symbol* symbol = get_variable($1, scope);
		struct Symbol value = access_array(symbol, $3);

		$$ = copy_symbol(&value);
		free($3);
		// TODO: returneaza valoarea pt accesului unui element din array/struct
	}
	; 
accesStruct:
	ID SELECTOR ID  {
		check_length($1, MAX_ID);
		check_defined($1, scope);

		struct Symbol symbol = create_symbol(
			// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
			NONE_I, 0, 0, 0, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);

		$$ = copy_symbol(&symbol);
		// TODO: returneaza valoarea pt accesului unui element din array/struct
	}
	| ID SELECTOR accesArray {
		check_length($1, MAX_ID);
		check_defined($1, scope);

		struct Symbol symbol = create_symbol(
			// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
			NONE_I, 0, 0, 0, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);

		$$ = copy_symbol(&symbol);
		free($3);
		// TODO: returneaza valoarea pt accesului unui element din array/struct
	}
	;

controlString:
    CONCAT '(' ID ',' valoare ')' {
        check_length($3, MAX_ID);
        check_defined($3, scope);

        struct Symbol* symbol = get_variable($3, scope);
        check_type(symbol, TYPE_STRING);

        concat_string(symbol, $5);
        
        free($5);
        // TODO: operatii cu stringuri
        // TODO: verifica daca parametrii sunt stringuri
    }
    | COPY '(' ID ',' valoare ')' {
        check_length($3, MAX_ID);
        check_defined($3, scope);

        struct Symbol* symbol = get_variable($3, scope);
        check_type(symbol, TYPE_STRING);

        copy_string(symbol, $5);
        
        free($5);
        // TODO: operatii cu stringuri
        // TODO: verifica daca parametrii sunt stringuri
    }
    ;
controlIfElse:
	IF '(' valoare ')' '{' blocCod '}' {
		free($3);
		// TODO: implementeaza if/else/while/for
		// TODO: implementeaza rularea unei functii si returneaza valoarea
	}
	| IF '(' valoare ')' ';' {
		free($3);
		// TODO: implementeaza if/else/while/for
		// TODO: implementeaza rularea unei functii si returneaza valoarea
	}
	| IF '(' valoare ')' '{' blocCod '}' ELSE '{' blocCod '}' {
		free($3);
		// TODO: implementeaza if/else/while/for
		// TODO: implementeaza rularea unei functii si returneaza valoarea
	}
	| IF '(' valoare ')' '{' blocCod '}' ELSE ';' {
		free($3);
		// TODO: implementeaza if/else/while/for
		// TODO: implementeaza rularea unei functii si returneaza valoarea
	}
	| IF '(' valoare ')' ';' ELSE '{' blocCod '}' {
		free($3);
		// TODO: implementeaza if/else/while/for
		// TODO: implementeaza rularea unei functii si returneaza valoarea
	}
	| IF '(' valoare ')' ';' ELSE ';' {
		free($3);
		// TODO: implementeaza if/else/while/for
		// TODO: implementeaza rularea unei functii si returneaza valoarea
	}
	;
controlWhile:
	WHILE '(' valoare ')' '{' blocCod '}' {
		free($3);
		// TODO: implementeaza if/else/while/for
		// TODO: implementeaza rularea unei functii si returneaza valoarea
	}
	;
controlFor:
	FOR '(' FOR_START ATRIBUIRE valoare ',' FOR_STOP ATRIBUIRE valoare ',' FOR_STEP ATRIBUIRE valoare ')' '{' blocCod '}' {
		free($5); free($9); free($13);
		// TODO: implementeaza if/else/while/for
		// TODO: implementeaza rularea unei functii si returneaza valoarea
	}
	;

%%
void yyerror(char* s){
	printf("Eroare: %s\nLinia: %d\nToken: %s\n", s, yylineno, yytext);
	exit(-1);
}

int main(int argc, char** argv){
	/* extern int yydebug;
	yydebug = 1; */

	yyin = fopen("cod.txt","r");
	yyparse();
} 