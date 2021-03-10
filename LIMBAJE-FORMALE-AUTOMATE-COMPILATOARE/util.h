#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_VARCONST 1
#define IS_VAR 2
#define IS_CONST 3
#define IS_FUNC 4
#define IS_STRUCT 5

#define TYPE_INT 1
#define TYPE_FLOAT 2
#define TYPE_CHAR 3
#define TYPE_STRING 4
#define TYPE_BOOL 5
#define TYPE_STRUCT 6

#define DIM_UNI 1
#define DIM_ARR 2

#define SCOPE_GLOBAL 1
#define SCOPE_FUNCTION 2
#define SCOPE_STRUCT 3

#define OP_EVALUARE 1
#define OP_PRINTARE 2
#define OP_DECL_VAR 3
#define OP_DECL_STRUCT 4
#define OP_DECL_FUNC 5
#define OP_ASIGNARE 6
#define OP_APEL_FUNC 7
#define OP_IF_START 8
#define OP_IF_STOP 9
#define OP_ELSE_START 10
#define OP_ELSE_STOP 11
#define OP_WHILE_START 12
#define OP_WHILE_STOP 13
#define OP_FOR_START 14
#define OP_FOR_STOP 15

#define MAX_ID 24
#define MAX_STR 48
#define MAX_LINES 256
#define MAX_PARAMS 16
#define MAX_DIM 128
#define MAX_TYPE 8
#define MAX_VARS 128
#define MAX_FUNC 128
#define MAX_STRUCT 128
#define MAX_ERR 96

#define NONE "\0"
#define INDENT 4

extern void yyerror(char* s);

int n_vars = 0;
int n_func = 0;
int n_struct = 0;

char NONE_I[MAX_ID] = {0};
char NONE_S[MAX_STR] = {0};
char NONE_T[MAX_TYPE] = {0};
char NONE_PV[MAX_PARAMS][MAX_STR] = {0};
char NONE_PT[MAX_PARAMS][MAX_TYPE] = {0};
char NONE_E[MAX_DIM][MAX_STR] = {0};

struct Line {
	int operation;
	int condition;
	char left[MAX_ID];
	struct Symbol* right;
	int start;
	int stop;
	int step;
} lines[MAX_LINES];

struct Symbol {
	char id[MAX_ID];
	int is;
	int type;
	int dim;
	char scope[MAX_STR];
    char structure[MAX_STR];
    int init;
	float numvalue;
	char chrvalue;
	char strvalue[MAX_STR];
    int n_params;
	char paramvals[MAX_PARAMS][MAX_STR];
	char paramtypes[MAX_PARAMS][MAX_TYPE];
    int n_elements;
    char elements[MAX_DIM][MAX_STR];
} variables[MAX_VARS], functions[MAX_FUNC], structures[MAX_STRUCT];

void update_scope(char curr_scope[MAX_STR], char new_scope[MAX_STR]) {
    strcpy(curr_scope, new_scope);
}

void update_symbol_scope(char pholder[MAX_STR], char parent[MAX_STR], int is) {
    char scope[MAX_STR];
    strcpy(scope, pholder);
    strcat(scope, " ");
    strcat(scope, parent);

    struct Symbol* symbols;
    int stop;


    switch(is){
        case IS_VARCONST:
            symbols = variables;
            stop = n_vars;
            break;        
        case IS_FUNC:
            symbols = functions;
            stop = n_func;
            break;
        case IS_STRUCT:
            symbols = structures;
            stop = n_struct;
            break;
    }
    
    for(int i = 0; i < stop; i++) {
        struct Symbol *symbol = &symbols[i];

        if(!strcmp(symbol->scope, pholder)) {
            strcpy(symbol->scope, scope);
        }
    }
}

void update_lastn_scope(int n, char scope[MAX_STR]) {
    for(int i = n_vars-1; i >= n_vars-n; i--) {
        struct Symbol* symbol = &variables[i];
        strcpy(symbol->scope, scope);
    }
}

void update_temp_scope(char id[MAX_STR]) {
    for(int i = 0; i < n_vars; i++) {
        struct Symbol* symbol = &variables[i];

        if(strstr(symbol->scope, "TEMP")) {
            char temp[MAX_STR];
            char scope[MAX_STR] = {0};
            strcpy(temp, symbol->scope);

            char* p = strtok(temp, " ");
            strcat(scope, p);
            strcat(scope, " ");

            p = strtok(NULL, " ");
            strcat(scope, id);
            strcat(scope, " ");

            p = strtok(NULL, " ");
            strcat(scope, p);
            
            strcpy(symbol->scope, scope);
        }
    }
}

int get_varconst_int(char varconst) {
    int val[2] = {IS_VAR, IS_CONST};
    char names[2] = {'?', '!'};
    
    for(int i = 0; i < 2; i++) {
        if(varconst == names[i]) {
            return val[i];
        }
    }

    return 0;
}

char* get_is(int is) {
    switch(is) {
        case IS_VARCONST:
            return "variable/constant";
        case IS_VAR:
            return "variable";
        case IS_CONST:
            return "constant";
        case IS_FUNC:
            return "function";
        case IS_STRUCT:
            return "structure";
    }

    return "none";
}

int get_type_int(char type[MAX_TYPE]) {
    int val[6] = {TYPE_INT, TYPE_FLOAT, TYPE_CHAR, TYPE_STRING, TYPE_BOOL, TYPE_STRUCT};
    char names[6][MAX_TYPE] = {"int", "float", "char", "string", "bool", "struct"};
    
    for(int i = 0; i < 6; i++) {
        if(!strcmp(type, names[i])) {
            return val[i];
        }
    }

    return 0;
}

char* get_type(int type) {
    switch(type) {
        case TYPE_INT:
            return "int";
        case TYPE_FLOAT:
            return "float";
        case TYPE_CHAR:
            return "char";
        case TYPE_STRING:
            return "string";
        case TYPE_BOOL:
            return "bool";
        case TYPE_STRUCT:
            return "struct";
    }

    return "none";
}

char* get_dim(int dim) {
    switch(dim) {
        case DIM_UNI:
            return "singular";
        case DIM_ARR:
            return "array";
    }

    return "none";
}

char* get_init(int init) {
    if(init) {
        return "yes";
    }

    return "no";
}

int get_string_type(char str[MAX_STR]) {
    if(str[0] == '\'') {
        return TYPE_CHAR;
    }

    if(str[0] == '\"') {
        return TYPE_STRING;
    }

    return TYPE_BOOL;
}

int get_num_type(float num) {
    if(num-(int)num == 0) {
        return TYPE_INT;
    }

    return TYPE_FLOAT;
}

int get_bool(char str[MAX_STR]) {
    if(!strcmp(str, "true")) {
        return 1;
    }

    return 0;
}

struct Symbol create_symbol(char id[MAX_ID],
                            int is, int type, int dim, char scope[MAX_STR], char structure[MAX_STR], 
                            int init, float numvalue, char chrvalue, char strvalue[MAX_STR],
                            int n_params, char paramvals[MAX_PARAMS][MAX_STR], char paramtypes[MAX_PARAMS][MAX_TYPE],
                            int n_elements, char elements[MAX_DIM][MAX_STR]) {
    struct Symbol symbol;
    
    strcpy(symbol.id, strlen(id) ? id : NONE);
    
    symbol.is = is;
    symbol.type = type;
    symbol.dim = dim;
    
    strcpy(symbol.scope, strlen(scope) ? scope : NONE);
    strcpy(symbol.structure, strlen(structure) ? structure : NONE);
    
    symbol.init = init;
    symbol.numvalue = numvalue;
    symbol.chrvalue = chrvalue;
    
    strcpy(symbol.strvalue, strlen(strvalue) ? strvalue : NONE);
    
    symbol.n_params = n_params;
    for(int i = 0; i < n_params; i++) {
        strcpy(symbol.paramvals[i], strlen(paramvals[i]) ? paramvals[i] : NONE);
        strcpy(symbol.paramtypes[i], strlen(paramtypes[i]) ? paramtypes[i] : NONE);
    }

    symbol.n_elements = n_elements;
    for(int i = 0; i < n_elements; i++) {
        strcpy(symbol.elements[i], strlen(elements[i]) ? elements[i] : NONE);
    }

    return symbol;
}

struct Symbol* get_variable(char id[MAX_ID], char scope[MAX_STR]) {
    struct Symbol* global = NULL;

    for(int i = 0; i < n_vars; i++) {
        struct Symbol* symbol = &variables[i];

        if(!strcmp(symbol->id, id)) {
          if(!strcmp(symbol->scope, scope)) {
            return symbol;
          }  
          else if(!strcmp(symbol->scope, "GLOBAL")) {
              global = symbol;
          }
        } 
    }

    if(global) {
        return global;
    }

    char err[MAX_ERR] = {0};
    strcpy(err, "object `");
    strcat(err, id);
    strcat(err, "` hasn't been defined anywhere");

    yyerror(err);

    return NULL;
}

struct Symbol* get_function(char id[MAX_ID], int n_params, char paramtypes[MAX_PARAMS][MAX_TYPE]) {
    for(int i = 0; i < n_func; i++) {
        struct Symbol* function = &functions[i];

        if(strcmp(id, function->id)) continue;

        if(n_params == function->n_params) {
            int dif = 0;

            for(int p = 0; p < n_params; p++) {
                if(
                    strcmp(paramtypes[p], function->paramtypes[p])
                    && !(!strcmp(paramtypes[p], "int") && !strcmp(function->paramtypes[p], "float"))
                ) {
                    dif = 1;
                    break;
                }
            }

            if(!dif) {
                return function;
            }
        }        
    }

    char err[MAX_ERR] = {0};
    sprintf(err, "function `%s` is either undefined or requires other parameters", id);

    yyerror(err);

    return NULL;
}

void add_symbol(int is, struct Symbol symbol) {
    switch(is) {
        case IS_VARCONST:
            variables[n_vars++] = symbol;
            break;
        case IS_FUNC:
            functions[n_func++] = symbol;
            break;
        case IS_STRUCT:
            structures[n_struct++] = symbol;
            break;
    }
}

struct Symbol* copy_symbol(struct Symbol* from) {
    struct Symbol* to = (struct Symbol*)malloc(sizeof(struct Symbol));
    // printf("--------------\n");
    strcpy(to->id, from->id);
    // printf("[%s]", from->id);
    to->is = from->is;
    // printf("[%i]", from->is);
    to->type = from->type;
    // printf("[%i]", from->type);
    to->dim = from->dim;
    // printf("[%i]", from->dim);
    strcpy(to->scope, from->scope);
    // printf("[%s]",from->scope);
    strcpy(to->structure, from->structure);
    // printf("[%s]",from->structure);
    to->init = from->init;
    // printf("[%i]",from->init);
    to->numvalue = from->numvalue;
    // printf("[%f]",from->numvalue);
    to->chrvalue = from->chrvalue;
    // printf("[%c]",from->chrvalue);
    
    strcpy(to->strvalue, from->strvalue);
    // printf("[%s]",from->strvalue);
    
    to->n_params = from->n_params;
    // printf("[%i]",from->n_params);
    for(int i = 0; i < to->n_params; i++) {
        strcpy(to->paramvals[i], from->paramvals[i]);
        // printf("[%s]",from->paramvals[i]);
        strcpy(to->paramtypes[i], from->paramtypes[i]);
        // printf("[%s]",from->paramtypes[i]);
    }

    to->n_elements = from->n_elements;
    // printf("[%i]",from->n_elements);
    for(int i = 0; i < to->n_elements; i++) {
        strcpy(to->elements[i], from->elements[i]);
        // printf("[%s]",from->elements[i]);
    }
    // printf("\n");

    return to;
}

void print_indent(FILE* out, int indent) {
    for(int i = 0; i < indent; i++) {
        fprintf(out, " ");    
    }
}

void print_symbols(FILE* out, char parent[MAX_STR], int indent) {
    struct Symbol* all_symbols[3] = {structures, functions, variables};
    int all_n[3] = {n_struct, n_func, n_vars};

    for(int k = 0; k < 3; k++) {
        struct Symbol* symbols = all_symbols[k];
        int n = all_n[k];

        for(int i = 0; i < n; i++) {
            struct Symbol* symbol = &symbols[i];

            if(strcmp(symbol->scope, parent)) {
                continue;
            }

            // id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
            print_indent(out, indent-1); fprintf(out, "*");
            
            fprintf(out, "ID: %s\n", symbol->id);
            print_indent(out, indent); fprintf(out, "IS: %s\n", get_is(symbol->is));
            print_indent(out, indent); fprintf(out, "TYPE: %s", get_type(symbol->type));
            if(strcmp(symbol->structure, NONE)) {
                fprintf(out, "<%s>", symbol->structure);
            }
            fprintf(out, "\n");

            print_indent(out, indent); fprintf(out, "SCOPE: %s\n", symbol->scope);

            
            if(symbol->dim) {
                print_indent(out, indent); fprintf(out, "DIMENSIONALITY: %s\n", get_dim(symbol->dim));
                
                if(symbol->dim == DIM_ARR) {
                    print_indent(out, indent); fprintf(out, "NO. OF ELEMENTS: %i\n", symbol->n_elements);
                }
            }

            if(symbol->is == IS_VAR || symbol->is == IS_CONST) {
                print_indent(out, indent); fprintf(out, "INITIALIZED: %s\n", get_init(symbol->init));
            }
            
            if(symbol->dim) {
                if(symbol->dim == DIM_UNI && symbol->init) {
                    if(strcmp(symbol->strvalue, NONE_S)) {
                        print_indent(out, indent); fprintf(out, "VALUE: %s\n", symbol->strvalue);
                    }
                    else if(symbol->chrvalue) {
                        print_indent(out, indent); fprintf(out, "VALUE: %c\n", symbol->chrvalue);
                    }
                    else {
                        print_indent(out, indent); fprintf(out, "VALUE: %i\n", symbol->numvalue);
                    }
                }
                else if(symbol->dim == DIM_ARR) {
                    if(symbol->n_elements && symbol->init) {
                        print_indent(out, indent); fprintf(out, "ELEMENTS: ");
                        for(int i = 0; i < symbol->n_elements; i++) {
                            fprintf(out, "%s; ", symbol->elements[i]);
                        }
                        fprintf(out, "\n");
                    }
                }
            }

            if(symbol->is == IS_FUNC) {
                print_indent(out, indent); fprintf(out, "NO. OF PARAMETERS: %i\n", symbol->n_params);

                if(symbol->n_params) {
                    print_indent(out, indent); fprintf(out, "PARAMETERS TYPES: ");
                    for(int i = 0; i < symbol->n_params; i++) {
                        fprintf(out, "%s; ", symbol->paramtypes[i]);
                    }
                    fprintf(out, "\n");
                }
            }

            char child[MAX_STR];
            strcpy(child, parent);
            strcat(child, " ");
            strcat(child, symbol->id);
            print_symbols(out, child, indent+INDENT);
        }
    }
}

void print_symbol_table() {
    FILE* out = fopen("symbol_table.txt", "w");

    fprintf(out, "@structures\n");
    print_symbols(out, "STRUCTURES", INDENT);
    fprintf(out, "@functions\n");
    print_symbols(out, "FUNCTIONS", INDENT);
    fprintf(out, "@global\n");
    print_symbols(out, "GLOBAL", INDENT);
    fprintf(out, "@main\n");
    print_symbols(out, "MAIN", INDENT);
}

void check_duplicate(char id[MAX_ID], char scope[MAX_STR], int is, int n_params, char paramtypes[MAX_PARAMS][MAX_TYPE]) {
    struct Symbol* all_symbols[3] = {structures, functions, variables};
    int all_n[3] = {n_struct, n_func, n_vars};
    
    for(int k = 0; k < 3; k++) {
        struct Symbol* symbols = all_symbols[k];
        int n = all_n[k];

        for(int i = 0; i < n; i++) {
            struct Symbol* symbol = &symbols[i];

            // printf("[%s<%s>] vs. [%s<%s>]\n", id,scope,symbol->id,symbol->scope);

            if(!strcmp(id, symbol->id)) {
                if(is == IS_FUNC) {
                    if(symbol->n_params == n_params) {
                        int dif = 0;
                        for(int p = 0; p < n_params; p++) {
                            if(strcmp(paramtypes[p], symbol->paramtypes[p])) {
                                int dif = 1;
                                break;
                            }
                        }

                        if(!dif) {
                            char err[MAX_ERR] = {0};
                            strcpy(err, "function `");
                            strcat(err, id);
                            strcat(err, "` is already defined");

                            yyerror(err);
                        }
                    }
                }
                else {
                    if(
                        strcmp(symbol->scope, scope)
                        && !(strstr("GLOBAL MAIN", scope) && strstr("STRUCTURES FUNCTION", symbol->scope))
                    ) continue;
                    
                    char err[MAX_ERR] = {0};
                    strcpy(err, "object `");
                    strcat(err, id);
                    strcat(err, "` is already defined");

                    yyerror(err);
                }
            }
        }
    }
}

void check_defined(char id[MAX_ID], char scope[MAX_STR]) {
    struct Symbol* all_symbols[3] = {structures, functions, variables};
    int all_n[3] = {n_struct, n_func, n_vars};
    
    for(int k = 0; k < 3; k++) {
        struct Symbol* symbols = all_symbols[k];
        int n = all_n[k];

        for(int i = 0; i < n; i++) {
            struct Symbol* symbol = &symbols[i];

            // printf("[%s<%s>] vs. [%s<%s>]\n", id,scope,symbol->id,symbol->scope);

            if(!strcmp(symbol->id, id)) {
                if(!strcmp(symbol->scope, scope) || strstr("STRUCTURES FUNCTIONS GLOBAL", symbol->scope)) {
                    return;
                }
            }
        }
    }

    char err[MAX_ERR] = {0};
    strcpy(err, "object `");
    strcat(err, id);
    strcat(err, "` hasn't been defined anywhere");

    yyerror(err);
}

void check_init(char id[MAX_ID], char scope[MAX_STR]) {
     if(strstr("STRUCTURES FUNCTIONS", scope)) return;

    for(int i = 0; i < n_vars; i++) {
        struct Symbol* symbol = &variables[i];

        // printf("[%s<%s>] vs. [%s<%s>]\n", id,scope,symbol->id,symbol->scope);

        if(!strcmp(symbol->id, id)) {
            
            if(!strcmp(symbol->scope, scope)) {
                if(symbol->init) {
                    return;
                }
            }
        }
    }

    char err[MAX_ERR] = {0};
    strcpy(err, "object `");
    strcat(err, id);
    strcat(err, "` hasn't been initialized");

    yyerror(err);
}

void check_type(struct Symbol* symbol, int type){
    if(symbol->type != type) {
        char err[MAX_ERR] = {0};
        sprintf(err, "object `%s` of type `%s` is not compatible with type `%s`", symbol->id, get_type(symbol->type), get_type(type));

        yyerror(err);
    }
}

void check_value(struct Symbol* symbol, char id[MAX_ID], char type[MAX_TYPE], struct Symbol* value){
    if(symbol) {
        // printf("1:%s<%s> vs %s<s>\n", symbol->id, get_type(symbol->type),value->id,get_type(value->type));
        if(symbol->type == value->type || (symbol->type == TYPE_FLOAT && symbol->type == TYPE_INT)) {
           return;
        }    

        char err[MAX_ERR] = {0};
        sprintf(err, "object `%s` of type `%s` is not compatible with type `%s`", symbol->id, symbol->type, get_type(value->type));

        yyerror(err);
    }
    // printf("2:%s<%s> vs %s<%s>\n", id, type,value->id,get_type(value->type));
    if(!strcmp(type, get_type(value->type)) || (!strcmp(type, "float") && value->type == TYPE_INT)) {
        return;
    }

    char err[MAX_ERR] = {0};
    sprintf(err, "object `%s` of type `%s` is not compatible with type `%s`", id, type, get_type(value->type));

    yyerror(err);
}

void check_array(struct Symbol* symbol, char id[MAX_ID], char type[MAX_TYPE], struct Symbol* value, int n_elements) {
    if(n_elements < value->n_elements) {
        char err[MAX_ERR] = {0};

        if(symbol) {
            sprintf(err, "array object `%s` can't hold %d elements (maximum size is %d)", symbol->id, value->n_elements, symbol->n_elements);
        }
        else {
            sprintf(err, "array object `%s` can't hold %d elements (maximum size is %d)", id, value->n_elements, n_elements);
        }
        yyerror(err);
    }

    check_value(symbol, id, type, value);
}

void check_const(char id[MAX_ID], char scope[MAX_STR], int is_changed) {
    if(is_changed) {
        struct Symbol* symbol = get_variable(id, scope);

        if(symbol) {
            if(symbol->is == IS_CONST) {
                char err[MAX_ERR] = {0};
                strcpy(err, "can't assign a new value for constant object `");
                strcat(err, id);
                strcat(err, "`");

                yyerror(err);
            }
        }
        else {
            char err[MAX_ERR] = {0};
            strcpy(err, "object `");
            strcat(err, id);
            strcat(err, "` hasn't been defined anywhere");

            yyerror(err);
        }
    }
    else {
        char err[MAX_ERR] = {0};
        strcpy(err, "constant object `");
        strcat(err, id);
        strcat(err, "` has to be initialised");

        yyerror(err);
    }
}

void check_length(char str[MAX_STR+1], int max) {
    if(strlen(str) >= max) {
        str[MAX_ID] = '\0';

        char err[MAX_ERR] = {0};
        sprintf(err, "string `%s...`  is longer than the maximum size allowed (%i)", str, max);

        yyerror(err);
    }
}

void check_size(int n, int max) {
    if(n >= max) {
        char err[MAX_ERR] = {0};
        sprintf(err, "array is bigger than the maximum size allowed (%i)", max);

        yyerror(err);
    }
}

void copy_params(char to[MAX_PARAMS][MAX_TYPE], char from[MAX_PARAMS][MAX_TYPE], int n) {
    for(int i = 0; i < n; i++) {
        strcpy(to[i], from[i]);
    }
}

void append_param(struct Symbol* to, struct Symbol* from) {
    if(to->n_params >= MAX_PARAMS) {
        char err[MAX_ERR] = {0};
        sprintf(err, "function has more parameters than the maximum size allowed (%i)", MAX_PARAMS);

        yyerror(err);
    }
    
    strcpy(to->paramtypes[to->n_params], get_type(from->type));

    to->n_params++;
}

void append_element(struct Symbol* to, struct Symbol* from) {
    int n = to->n_elements;
    
    if(n >= MAX_DIM) {
        char err[MAX_ERR] = {0};
        sprintf(err, "array can't have more elements than the maximum size allowed (%i)", MAX_DIM);

        yyerror(err);
    }

    char temp[MAX_STR] = {0};
    switch(from->type) {
        case TYPE_INT:
            sprintf(to->elements[n], "%i", (int)from->numvalue);
            break;
        case TYPE_FLOAT:
            sprintf(to->elements[n], "%f", from->numvalue);
            break;
        case TYPE_CHAR:
            sprintf(to->elements[n], "%c", from->chrvalue);
            break;
        case TYPE_STRING:
            sprintf(to->elements[n], "%s", from->strvalue);
            break;
        case TYPE_BOOL:
            sprintf(to->elements[n], "%s", from->strvalue);
            break;
        case TYPE_STRUCT:
            sprintf(to->elements[n], "%s", from->strvalue);
            break;
    }
    // printf("%s\n",to->elements[n]);
    to->n_elements++;
}

void assign_value(struct Symbol* variable, struct Symbol* value){
    if(variable->dim == DIM_ARR) {
        // printf("%i vs %i",variable->n_elements, value->n_elements);
        if(variable->n_elements >= value->n_elements) {
            for(int i = 0; i < value->n_elements; i++) {
                strcpy(variable->elements[i], value->elements[i]);
            }
            for(int i = value->n_elements; i < variable->n_elements; i++) {
                strcpy(variable->elements[i], NONE);
            }

            return;
        }
        char err[MAX_ERR] = {0};
        sprintf(err, "array object `%s` can't hold more than %i elements", variable->id, variable->n_elements);

        yyerror(err);

        return;
    }
    
    switch(variable->type){
        case TYPE_INT:
            variable->numvalue = value->numvalue;
            break;
        case TYPE_FLOAT:
            variable->numvalue = value->numvalue;
            break;
        case TYPE_CHAR:
            variable->chrvalue = value->chrvalue;
            break;
        case TYPE_STRING:
            strcpy(variable->strvalue, value->strvalue);
            break;
        case TYPE_BOOL:
            strcpy(variable->strvalue, value->strvalue);
            break;
        case TYPE_STRUCT:
            strcpy(variable->strvalue, value->id);
            break;
    } 
}

void concat_string(struct Symbol* variable, struct Symbol* value){
     if(strlen(variable->strvalue) + strlen(value->strvalue) >= MAX_STR){
        char err[MAX_ERR] = {0};
        sprintf(err, "resulting string exceeds maximum length (%i)", MAX_STR);

        yyerror(err);
    }
    else{
        variable->strvalue[strlen(variable->strvalue)-1] = '\0';
        strcpy(value->strvalue, value->strvalue+1);
        strcat(variable->strvalue, value->strvalue);
    }
}

void copy_string(struct Symbol* variable, struct Symbol* value){
    strcpy(variable->strvalue, value->strvalue);
    variable->init = 1;
}

void print_symbol(struct Symbol* symbol){
    if(symbol) {
        if(symbol->dim == DIM_ARR) {
            for(int i = 0; i < symbol->n_elements; i++) {
                printf("%s; ", symbol->elements[i]);
            }

            return;
        }

        if(symbol->dim == DIM_UNI) {
            switch(symbol->type) {
                case TYPE_INT:
                    printf("%i", (int)symbol->numvalue);
                    break;
                case TYPE_FLOAT:
                    printf("%f", symbol->numvalue);
                    break;
                case TYPE_CHAR:
                    printf("%c", symbol->chrvalue);
                    break;
                case TYPE_STRING:
                    printf("%s", symbol->strvalue);
                    break;
                case TYPE_BOOL:
                    printf("%s", symbol->strvalue);
                    break;
                case TYPE_STRUCT:
                    printf("structure<%s>",symbol->id);
                    break;
            }

            return;
         }

        if(!symbol->dim) {
            char err[MAX_ERR] = {0};
            sprintf(err, "object is not printable");

            yyerror(err);
         }
    }
    else {
        printf("\n");
    }
}

void err_length(int l1, int l2) {
    if(l1+l2 >= MAX_STR) {
        char err[MAX_ERR] = {0};
        sprintf(err, "resulting string exceeds maximum length (%i)", MAX_STR);

        yyerror(err);
    }
}

void add_expr(struct Symbol* left, struct Symbol* right) {
    if(left->dim == DIM_ARR || right->dim == DIM_ARR) {
        char err[MAX_ERR] = {0};
        sprintf(err, "can't have arrays in expression");

        yyerror(err);
    }

    if(left->type == TYPE_INT && right->type == TYPE_INT) {
        left->numvalue += right->numvalue;

        return;
    }

    if((left->type == TYPE_FLOAT && right->type == TYPE_INT) || (left->type == TYPE_INT && right->type == TYPE_FLOAT)) {
        left->type = TYPE_FLOAT;
        left->numvalue += right->numvalue;

        return;
    }

    if(left->type == TYPE_CHAR && right->type == TYPE_CHAR) {
        left->type = TYPE_STRING;
        sprintf(left->strvalue, "%c%c", left->chrvalue, right->chrvalue);
        left->chrvalue = 0;

        return;
    }

    if(left->type == TYPE_CHAR && right->type == TYPE_STRING) {
        strcpy(right->strvalue, right->strvalue+1);
        err_length(1, strlen(right->strvalue));

        left->type = TYPE_STRING;
        sprintf(left->strvalue, "\"%c%s", left->chrvalue, right->strvalue);
        left->chrvalue = 0;

        return;
    }

    if(left->type == TYPE_STRING && right->type == TYPE_CHAR) {
        left->strvalue[strlen(left->strvalue)-1] = '\0';
        err_length(strlen(left->strvalue), 1);

        sprintf(left->strvalue, "%s%c\"", left->strvalue, right->chrvalue);

        return;
    }
    if(left->type == TYPE_STRING && right->type == TYPE_STRING) {
        left->strvalue[strlen(left->strvalue)-1] = '\0';
        strcpy(right->strvalue, right->strvalue+1);
        err_length(strlen(left->strvalue), strlen(right->strvalue));


        sprintf(left->strvalue, "%s%s", left->strvalue, right->strvalue);

        return;
    }

    if(left->type == TYPE_BOOL && right->type == TYPE_BOOL) {
        left->type = TYPE_INT;

        left->numvalue = get_bool(left->strvalue) + get_bool(right->strvalue);
        strcpy(left->strvalue, NONE_S);

        return;
    }

    if(left->type == TYPE_BOOL && right->type == TYPE_INT) {
        left->type = TYPE_INT;

        left->numvalue = get_bool(left->strvalue) + right->numvalue;
        strcpy(left->strvalue, NONE_S);

        return;
    }

    if(left->type == TYPE_INT && right->type == TYPE_BOOL) {
        left->numvalue = left->numvalue + get_bool(right->strvalue);

        return;
    }

    char err[MAX_ERR] = {0};
    sprintf(err, "addition has incompatible types (`%s` and `%s`)", get_type(left->type), get_type(right->type));

    yyerror(err);
}

void sub_expr(struct Symbol* left, struct Symbol* right) {
    if(left->dim == DIM_ARR || right->dim == DIM_ARR) {
        char err[MAX_ERR] = {0};
        sprintf(err, "can't have arrays in expression");

        yyerror(err);
    }

    if(left->type == TYPE_INT && right->type == TYPE_INT) {
        left->numvalue -= right->numvalue;

        return;
    }

    if((left->type == TYPE_FLOAT && right->type == TYPE_INT) || (left->type == TYPE_INT && right->type == TYPE_FLOAT)) {
        left->type = TYPE_FLOAT;
        left->numvalue -= right->numvalue;

        return;
    }
    if(left->type == TYPE_BOOL && right->type == TYPE_BOOL) {
        left->type = TYPE_INT;

        left->numvalue = get_bool(left->strvalue) - get_bool(right->strvalue);
        strcpy(left->strvalue, NONE_S);

        return;
    }

    if(left->type == TYPE_BOOL && right->type == TYPE_INT) {
        left->type = TYPE_INT;

        left->numvalue = get_bool(left->strvalue) - right->numvalue;
        strcpy(left->strvalue, NONE_S);

        return;
    }

    if(left->type == TYPE_INT && right->type == TYPE_BOOL) {
        left->numvalue = left->numvalue - get_bool(right->strvalue);

        return;
    }

    char err[MAX_ERR] = {0};
    sprintf(err, "subtraction has incompatible types (`%s` and `%s`)", get_type(left->type), get_type(right->type));

    yyerror(err);
    
}

void mul_expr(struct Symbol* left, struct Symbol* right) {
    if(left->dim == DIM_ARR || right->dim == DIM_ARR) {
        char err[MAX_ERR] = {0};
        sprintf(err, "can't have arrays in expression");

        yyerror(err);
    }

    if(left->type == TYPE_INT && right->type == TYPE_INT) {
        left->numvalue *= right->numvalue;

        return;
    }

    if((left->type == TYPE_FLOAT && right->type == TYPE_INT) || (left->type == TYPE_INT && right->type == TYPE_FLOAT)) {
        left->type = TYPE_FLOAT;
        left->numvalue *= right->numvalue;

        return;
    }
    if(left->type == TYPE_BOOL && right->type == TYPE_BOOL) {
        left->type = TYPE_INT;

        left->numvalue = get_bool(left->strvalue) * get_bool(right->strvalue);
        strcpy(left->strvalue, NONE_S);

        return;
    }

    if(left->type == TYPE_BOOL && right->type == TYPE_INT) {
        left->type = TYPE_INT;

        left->numvalue = get_bool(left->strvalue) * right->numvalue;
        strcpy(left->strvalue, NONE_S);

        return;
    }

    if(left->type == TYPE_INT && right->type == TYPE_BOOL) {
        left->numvalue = left->numvalue * get_bool(right->strvalue);

        return;
    }

    char err[MAX_ERR] = {0};
    sprintf(err, "multiplication has incompatible types (`%s` and `%s`)", get_type(left->type), get_type(right->type));

    yyerror(err);
}

void div_expr(struct Symbol* left, struct Symbol* right) {
    if(left->dim == DIM_ARR || right->dim == DIM_ARR) {
        char err[MAX_ERR] = {0};
        sprintf(err, "can't have arrays in expression");

        yyerror(err);
    }

    if(left->type == TYPE_INT && right->type == TYPE_INT) {
        float temp = left->numvalue / right->numvalue; 
        if(get_num_type(temp) == TYPE_FLOAT){
            left->type = TYPE_FLOAT;
        }
        left->numvalue = temp;

        return;
    }

    if((left->type == TYPE_FLOAT && right->type == TYPE_INT) || (left->type == TYPE_INT && right->type == TYPE_FLOAT)) {
        float temp = left->numvalue / right->numvalue; 
        if(get_num_type(temp) == TYPE_FLOAT){
            left->type = TYPE_FLOAT;
        }
        else{
            left->type = TYPE_INT;
        }
        left->numvalue = temp;

        return;
    }
    if(left->type == TYPE_BOOL && right->type == TYPE_BOOL) {
        left->type = TYPE_INT;

        left->numvalue = get_bool(left->strvalue) / get_bool(right->strvalue);
        strcpy(left->strvalue, NONE_S);

        return;
    }

    if(left->type == TYPE_BOOL && right->type == TYPE_INT) {
        left->type = TYPE_INT;

        left->numvalue = get_bool(left->strvalue) / right->numvalue;
        strcpy(left->strvalue, NONE_S);

        return;
    }

    if(left->type == TYPE_INT && right->type == TYPE_BOOL) {
        if(get_bool(right->strvalue) == 0) {
            char err[MAX_ERR] = {0};
            sprintf(err, "can't divive to 0");

            yyerror(err);
        }
        else {
            left->numvalue = left->numvalue / get_bool(right->strvalue);

            return;
        }
    }

    char err[MAX_ERR] = {0};
    sprintf(err, "division has incompatible types (`%s` and `%s`)", get_type(left->type), get_type(right->type));

    yyerror(err);
}

void eq_expr(struct Symbol* left, struct Symbol* right) {
    if(left->dim == DIM_ARR || right->dim == DIM_ARR) {
        char err[MAX_ERR] = {0};
        sprintf(err, "can't have arrays in expression");

        yyerror(err);
    }

    if((left->type == TYPE_FLOAT && right->type == TYPE_INT) || (left->type == TYPE_INT && right->type == TYPE_FLOAT)) {
        left->type = TYPE_BOOL;
        
        if(left->numvalue*1.f == right->numvalue*1.f) {
            strcpy(left->strvalue, "true");

            return;
        }
        else {
            strcpy(left->strvalue, "false");

            return;
        }
    }

    if(left->type == right->type) {
        switch(left->type) {
            case TYPE_INT:
                if(left->numvalue == right->numvalue) {
                    strcpy(left->strvalue, "true");
                    left->numvalue = 0;
                }
                else {
                    strcpy(left->strvalue, "false");
                    left->numvalue = 0;
                }
                break;
            case TYPE_FLOAT:
                if(left->numvalue == right->numvalue) {
                    strcpy(left->strvalue, "true");
                    left->numvalue = 0;
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
            case TYPE_CHAR:
                if(left->chrvalue == right->chrvalue) {
                    strcpy(left->strvalue, "true");
                    left->chrvalue = 0;
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
            case TYPE_STRING:
                if(!strcmp(left->strvalue, right->strvalue)) {
                    strcpy(left->strvalue, "true");
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
            case TYPE_BOOL:
                if(!strcmp(left->strvalue, right->strvalue)) {
                    strcpy(left->strvalue, "true");
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
            case TYPE_STRUCT:
                if(!strcmp(left->id, right->id)) {
                    strcpy(left->strvalue, "true");
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
        }

        left->type = TYPE_BOOL;
    }
    else {
        char err[MAX_ERR] = {0};
        sprintf(err, "== operation has incompatible types (`%s` and `%s`)", get_type(left->type), get_type(right->type));

        yyerror(err);
    }
}

void gt_expr(struct Symbol* left, struct Symbol* right) {
    if(left->dim == DIM_ARR || right->dim == DIM_ARR) {
        char err[MAX_ERR] = {0};
        sprintf(err, "can't have arrays in expression");

        yyerror(err);
    }

    if((left->type == TYPE_FLOAT && right->type == TYPE_INT) || (left->type == TYPE_INT && right->type == TYPE_FLOAT)) {
        left->type = TYPE_BOOL;
        
        if(left->numvalue*1.f > right->numvalue*1.f) {
            strcpy(left->strvalue, "true");

            return;
        }
        else {
            strcpy(left->strvalue, "false");

            return;
        }
    }

    if(left->type == right->type) {
        switch(left->type) {
            case TYPE_INT:
                if(left->numvalue > right->numvalue) {
                    strcpy(left->strvalue, "true");
                    left->numvalue = 0;
                }
                else {
                    strcpy(left->strvalue, "false");
                    left->numvalue = 0;
                }
                break;
            case TYPE_FLOAT:
                if(left->numvalue > right->numvalue) {
                    strcpy(left->strvalue, "true");
                    left->numvalue = 0;
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
            case TYPE_CHAR:
                if(left->chrvalue > right->chrvalue) {
                    strcpy(left->strvalue, "true");
                    left->chrvalue = 0;
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
            case TYPE_STRING:
                if(strcmp(left->strvalue, right->strvalue)>0) {
                    strcpy(left->strvalue, "true");
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
            case TYPE_BOOL:
                if(strcmp(left->strvalue, right->strvalue)>0) {
                    strcpy(left->strvalue, "true");
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
            case TYPE_STRUCT:
                if(strcmp(left->id, right->id)>0) {
                    strcpy(left->strvalue, "true");
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
        }

        left->type = TYPE_BOOL;
    }
    else {
        char err[MAX_ERR] = {0};
        sprintf(err, "> operation has incompatible types (`%s` and `%s`)", get_type(left->type), get_type(right->type));

        yyerror(err);
    }
}

void lt_expr(struct Symbol* left, struct Symbol* right) {
    if(left->dim == DIM_ARR || right->dim == DIM_ARR) {
        char err[MAX_ERR] = {0};
        sprintf(err, "can't have arrays in expression");

        yyerror(err);
    }

    if((left->type == TYPE_FLOAT && right->type == TYPE_INT) || (left->type == TYPE_INT && right->type == TYPE_FLOAT)) {
        left->type = TYPE_BOOL;
        
        if(left->numvalue*1.f < right->numvalue*1.f) {
            strcpy(left->strvalue, "true");

            return;
        }
        else {
            strcpy(left->strvalue, "false");

            return;
        }
    }

    if(left->type == right->type) {
        switch(left->type) {
            case TYPE_INT:
                if(left->numvalue < right->numvalue) {
                    strcpy(left->strvalue, "true");
                    left->numvalue = 0;
                }
                else {
                    strcpy(left->strvalue, "false");
                    left->numvalue = 0;
                }
                break;
            case TYPE_FLOAT:
                if(left->numvalue < right->numvalue) {
                    strcpy(left->strvalue, "true");
                    left->numvalue = 0;
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
            case TYPE_CHAR:
                if(left->chrvalue < right->chrvalue) {
                    strcpy(left->strvalue, "true");
                    left->chrvalue = 0;
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
            case TYPE_STRING:
                if(strcmp(left->strvalue, right->strvalue) < 0) {
                    strcpy(left->strvalue, "true");
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
            case TYPE_BOOL:
                if(strcmp(left->strvalue, right->strvalue) < 0) {
                    strcpy(left->strvalue, "true");
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
            case TYPE_STRUCT:
                if(strcmp(left->id, right->id) < 0) {
                    strcpy(left->strvalue, "true");
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
        }

        left->type = TYPE_BOOL;
    }
    else {
        char err[MAX_ERR] = {0};
        sprintf(err, "< operation has incompatible types (`%s` and `%s`)", get_type(left->type), get_type(right->type));

        yyerror(err);
    }
}

void ge_expr(struct Symbol* left, struct Symbol* right) {
    if(left->dim == DIM_ARR || right->dim == DIM_ARR) {
        char err[MAX_ERR] = {0};
        sprintf(err, "can't have arrays in expression");

        yyerror(err);
    }

    if((left->type == TYPE_FLOAT && right->type == TYPE_INT) || (left->type == TYPE_INT && right->type == TYPE_FLOAT)) {
        left->type = TYPE_BOOL;
        
        if(left->numvalue*1.f >= right->numvalue*1.f) {
            strcpy(left->strvalue, "true");

            return;
        }
        else {
            strcpy(left->strvalue, "false");

            return;
        }
    }

    if(left->type == right->type) {
        switch(left->type) {
            case TYPE_INT:
                if(left->numvalue >= right->numvalue) {
                    strcpy(left->strvalue, "true");
                    left->numvalue = 0;
                }
                else {
                    strcpy(left->strvalue, "false");
                    left->numvalue = 0;
                }
                break;
            case TYPE_FLOAT:
                if(left->numvalue >= right->numvalue) {
                    strcpy(left->strvalue, "true");
                    left->numvalue = 0;
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
            case TYPE_CHAR:
                if(left->chrvalue >= right->chrvalue) {
                    strcpy(left->strvalue, "true");
                    left->chrvalue = 0;
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
            case TYPE_STRING:
                if(strcmp(left->strvalue, right->strvalue) >= 0) {
                    strcpy(left->strvalue, "true");
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
            case TYPE_BOOL:
                if(strcmp(left->strvalue, right->strvalue) >= 0) {
                    strcpy(left->strvalue, "true");
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
            case TYPE_STRUCT:
                if(strcmp(left->id, right->id) >= 0) {
                    strcpy(left->strvalue, "true");
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
        }

        left->type = TYPE_BOOL;
    }
    else {
        char err[MAX_ERR] = {0};
        sprintf(err, ">= operation has incompatible types (`%s` and `%s`)", get_type(left->type), get_type(right->type));

        yyerror(err);
    }
}

void le_expr(struct Symbol* left, struct Symbol* right) {
    if(left->dim == DIM_ARR || right->dim == DIM_ARR) {
        char err[MAX_ERR] = {0};
        sprintf(err, "can't have arrays in expression");

        yyerror(err);
    }

    if((left->type == TYPE_FLOAT && right->type == TYPE_INT) || (left->type == TYPE_INT && right->type == TYPE_FLOAT)) {
        left->type = TYPE_BOOL;
        
        if(left->numvalue*1.f <= right->numvalue*1.f) {
            strcpy(left->strvalue, "true");

            return;
        }
        else {
            strcpy(left->strvalue, "false");

            return;
        }
    }

    if(left->type == right->type) {
        switch(left->type) {
            case TYPE_INT:
                if(left->numvalue <= right->numvalue) {
                    strcpy(left->strvalue, "true");
                    left->numvalue = 0;
                }
                else {
                    strcpy(left->strvalue, "false");
                    left->numvalue = 0;
                }
                break;
            case TYPE_FLOAT:
                if(left->numvalue <= right->numvalue) {
                    strcpy(left->strvalue, "true");
                    left->numvalue = 0;
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
            case TYPE_CHAR:
                if(left->chrvalue <= right->chrvalue) {
                    strcpy(left->strvalue, "true");
                    left->chrvalue = 0;
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
            case TYPE_STRING:
                if(strcmp(left->strvalue, right->strvalue) <= 0) {
                    strcpy(left->strvalue, "true");
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
            case TYPE_BOOL:
                if(strcmp(left->strvalue, right->strvalue) <= 0) {
                    strcpy(left->strvalue, "true");
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
            case TYPE_STRUCT:
                if(strcmp(left->id, right->id) <= 0) {
                    strcpy(left->strvalue, "true");
                }
                else {
                    strcpy(left->strvalue, "false");
                }
                break;
        }

        left->type = TYPE_BOOL;
    }
    else {
        char err[MAX_ERR] = {0};
        sprintf(err, "<= operation has incompatible types (`%s` and `%s`)", get_type(left->type), get_type(right->type));

        yyerror(err);
    }
}

void and_expr(struct Symbol* left, struct Symbol* right) {
    if(left->dim == DIM_ARR || right->dim == DIM_ARR) {
        char err[MAX_ERR] = {0};
        sprintf(err, "can't have arrays in expression");

        yyerror(err);
    }

    int res1 = 0;
    switch(left->type) {
        case TYPE_INT:
            res1 = left->numvalue;
            break;
        case TYPE_FLOAT:
            res1 = left->numvalue;
            break;
        case TYPE_CHAR:
            res1 = left->chrvalue;
            break;
        case TYPE_STRING:
            res1 = strlen(left->strvalue);
            break;
        case TYPE_BOOL:
            res1 = get_bool(left->strvalue);
            break;
        case TYPE_STRUCT:
            res1 = strlen(left->id);
            break;
    }

    int res2 = 0;
    switch(right->type) {
        case TYPE_INT:
            res2 = right->numvalue;
            break;
        case TYPE_FLOAT:
            res2 = right->numvalue;
            break;
        case TYPE_CHAR:
            res2 = right->chrvalue;
            break;
        case TYPE_STRING:
            res2 = strlen(right->strvalue);
            break;
        case TYPE_BOOL:
            res2 = get_bool(right->strvalue);
            break;
        case TYPE_STRUCT:
            res2 = strlen(right->id);
            break;
    }

    left->type = TYPE_BOOL;

    if(res1 && res2) {
        strcpy(left->strvalue, "true");
    }
    else {
        strcpy(left->strvalue, "false");
    }

    left->numvalue = 0;
    left->chrvalue = 0;
}

void or_expr(struct Symbol* left, struct Symbol* right) {
    if(left->dim == DIM_ARR || right->dim == DIM_ARR) {
        char err[MAX_ERR] = {0};
        sprintf(err, "can't have arrays in expression");

        yyerror(err);
    }

    int res1 = 0;
    switch(left->type) {
        case TYPE_INT:
            res1 = left->numvalue;
            break;
        case TYPE_FLOAT:
            res1 = left->numvalue;
            break;
        case TYPE_CHAR:
            res1 = left->chrvalue;
            break;
        case TYPE_STRING:
            res1 = strlen(left->strvalue);
            break;
        case TYPE_BOOL:
            res1 = get_bool(left->strvalue);
            break;
        case TYPE_STRUCT:
            res1 = strlen(left->id);
            break;
    }

    int res2 = 0;
    switch(right->type) {
        case TYPE_INT:
            res2 = right->numvalue;
            break;
        case TYPE_FLOAT:
            res2 = right->numvalue;
            break;
        case TYPE_CHAR:
            res2 = right->chrvalue;
            break;
        case TYPE_STRING:
            res2 = strlen(right->strvalue);
            break;
        case TYPE_BOOL:
            res2 = get_bool(right->strvalue);
            break;
        case TYPE_STRUCT:
            res2 = strlen(right->id);
            break;
    }

    left->type = TYPE_BOOL;

    if(res1 || res2) {
        strcpy(left->strvalue, "true");
    }
    else {
        strcpy(left->strvalue, "false");
    }

    left->numvalue = 0;
    left->chrvalue = 0;
}

void xor_expr(struct Symbol* left, struct Symbol* right) {
    if(left->dim == DIM_ARR || right->dim == DIM_ARR) {
        char err[MAX_ERR] = {0};
        sprintf(err, "can't have arrays in expression");

        yyerror(err);
    }

    int res1 = 0;
    switch(left->type) {
        case TYPE_INT:
            res1 = left->numvalue;
            break;
        case TYPE_FLOAT:
            res1 = left->numvalue;
            break;
        case TYPE_CHAR:
            res1 = left->chrvalue;
            break;
        case TYPE_STRING:
            res1 = strlen(left->strvalue);
            break;
        case TYPE_BOOL:
            res1 = get_bool(left->strvalue);
            break;
        case TYPE_STRUCT:
            res1 = strlen(left->id);
            break;
    }

    int res2 = 0;
    switch(right->type) {
        case TYPE_INT:
            res2 = right->numvalue;
            break;
        case TYPE_FLOAT:
            res2 = right->numvalue;
            break;
        case TYPE_CHAR:
            res2 = right->chrvalue;
            break;
        case TYPE_STRING:
            res2 = strlen(right->strvalue);
            break;
        case TYPE_BOOL:
            res2 = get_bool(right->strvalue);
            break;
        case TYPE_STRUCT:
            res2 = strlen(right->id);
            break;
    }

    left->type = TYPE_BOOL;

    if((res1 && !res2) || (!res1 && res2)) {
        strcpy(left->strvalue, "true");
    }
    else {
        strcpy(left->strvalue, "false");
    }

    left->numvalue = 0;
    left->chrvalue = 0;
}

void not_expr(struct Symbol* right) {
    if(right->dim == DIM_ARR) {
        char err[MAX_ERR] = {0};
        sprintf(err, "can't have arrays in expression");

        yyerror(err);
    }

    int res = 0;
    switch(right->type) {
        case TYPE_INT:
            res = right->numvalue;
            break;
        case TYPE_FLOAT:
            res = right->numvalue;
            break;
        case TYPE_CHAR:
            res = right->chrvalue;
            break;
        case TYPE_STRING:
            res = strlen(right->strvalue);
            break;
        case TYPE_BOOL:
            res = get_bool(right->strvalue);
            break;
        case TYPE_STRUCT:
            res = strlen(right->id);
            break;
    }

    right->type = TYPE_BOOL;

    if(res) {
        strcpy(right->strvalue, "false");
    }
    else {
        strcpy(right->strvalue, "true");
    }

    right->numvalue = 0;
    right->chrvalue = 0;
}

struct Symbol access_array(struct Symbol* symbol, struct Symbol* index) {
    struct Symbol value;

    if(index->dim != DIM_ARR) {
        int type = symbol->type;
        char scope[MAX_STR]; strcpy(scope, symbol->scope);

        int ind = 0;
        if(index->type == TYPE_INT) {
            ind = index->numvalue;
        }
        else if(index->type == TYPE_FLOAT) {
            ind = index->numvalue;
        }
        else if(index->type == TYPE_BOOL) {
            ind = get_bool(index->strvalue);
        }
        else {
            char err[MAX_ERR] = {0};
            sprintf(err, "array object `%s` has invalid index type `%s`", symbol->id, get_type(index->type));

            yyerror(err);
        }

        float numval = 0;
        char chrval = 0;
        char strval[MAX_STR] = {0};

        if(ind >= symbol->n_elements) {
            char err[MAX_ERR] = {0};
            sprintf(err, "index out of array object `%s` size (%i)", symbol->id, symbol->n_elements);

            yyerror(err);
        }

        char element[MAX_STR];
        strcpy(element, symbol->elements[ind]);

        switch(symbol->type) {
            case TYPE_INT:
                numval = atoi(element);
                break;
            case TYPE_FLOAT:
                numval = atof(element);
                break;
            case TYPE_CHAR:
                chrval = element[0];
                break;
            case TYPE_STRING:
                strcpy(strval, element);
                break;
            case TYPE_BOOL:
                strcpy(strval, element);
                break;
            case TYPE_STRUCT:
                strcpy(strval, element);
                break;
        }
        // id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
        value = create_symbol(NONE_I, 0, type, DIM_UNI, scope, NONE_S, 1, numval, chrval, strval, 0, NONE_PV, NONE_PT, 0, NONE_E);
        return value;      
    }
    else {
        char err[MAX_ERR] = {0};
        sprintf(err, "index can't be null or an array");

        yyerror(err);
    }
}