#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// expression related words, which needs to be removed as lexer already has 
enum expr
{
    ELIF,
    ADD_ASSIGN,
    INC_OP,
    SUB_ASSIGN,
    DEC_OP,
    DIV_ASSIGN,
    MUL_ASSIGN,
    MOD_ASSIGN,
    AND_ASSIGN,
    XOR_ASSIGN,
    OR_ASSIGN,
    NOT_ASSIGN,
    RIGHT_OP,
    LEFT_OP,
    EQ_EQ_COND,
    GRT_EQ_OP,
    LESR_EQ_OP,
    INT_CONST,
    CHAR_CONST,
    F_CONST,
    OCTAL_CONST,
    USIGN_INT_CONST,
    LONG_INT_CONST,
    LONG_DOUBLE_CONST,
    E_F_CONST
};


enum keywords
{
    TYPEDEF,
    EXTERN,
    STATIC,
    AUTO,
    REGISTER,
    CONST,
    VOLATILE,
    VOID,
    CHAR,
    SHORT,
    INT,
    LONG,
    FLOAT,
    DOUBLE,
    SIGNED,
    UNSIGNED,
    STRUCT,
    ENUM ,
    UNION,
    ID,
    ICONST,
    FCONST,
    DO,
    IF,
    ELSE,
    FOR,
    WHILE,
    SWITCH,
    CASE,
    DEFAULT
};


int arr[128];
//char* arr[15];
int tok;
int block_level = 0;
int lastKeywordTok;
static int i = 0;
void nextToken()
{
    tok = arr[i];
    i++;
}
int prevToken()
{
    return arr[i - 1];
}
int lookupToken()
{
    return arr[i + 1];
}
void resetToken(int k)
{
    i = k;
    nextToken();
}
int getTokenNumber()
{
    return i;
}
void setKeywordToken(int token)
{
    lastKeywordTok = token;
}
int lastKeywordToken()
{
    return lastKeywordTok;
}
void debugToken()
{
    int z;
    for (z = i; arr[z] != EOF; z++)
    {
        switch (arr[z])
        {
        case TYPEDEF:
            printf("TYPEDEF");
            break;
        case EXTERN:
            printf("EXTERN");
            break;
        case STATIC:
            printf("STATIC");
            break;
        case AUTO:
            printf("AUTO");
            break;
        case REGISTER:
            printf("REGISTER");
            break;
        case CONST:
            printf("CONST");
            break;
        case VOLATILE:
            printf("VOLATILE");
            break;
        case VOID:
            printf("VOID");
            break;
        case CHAR:
            printf("CHAR");
            break;
        case SHORT:
            printf("SHORT");
            break;
        case INT:
            printf("INT");
            break;
        case LONG:
            printf("LONG");
            break;
        case FLOAT:
            printf("FLOAT");
            break;
        case DOUBLE:
            printf("DOUBLE");
            break;
        case SIGNED:
            printf("SIGNED");
            break;
        case UNSIGNED:
            printf("UNSIGNED");
            break;
        case STRUCT:
            printf("STRUCT");
            break;
        case ENUM:
            printf("ENUM");
            break;
        case UNION:
            printf("UNION");
            break;
        case ID:
            printf("ID");
            break;
        case ICONST:
            printf("ICONST");
            break;
        case FCONST:
            printf("FCONST");
            break;
        case DO:
            printf("DO");
            break;
        case IF:
            printf("IF");
            break;
        case ELSE:
            printf("ELSE");
            break;
        case FOR:
            printf("FOR");
            break;
        case WHILE:
            printf("WHILE");
            break;
        default:
            printf("%c", arr[z]);
            break;
        }
        printf(" ");
    }
    printf("\n");
}
void dispToken(int tok)
{
    printf("Token is :");
        switch (tok)
        {
        case TYPEDEF:
            printf("TYPEDEF");
            break;
        case EXTERN:
            printf("EXTERN");
            break;
        case STATIC:
            printf("STATIC");
            break;
        case AUTO:
            printf("AUTO");
            break;
        case REGISTER:
            printf("REGISTER");
            break;
        case CONST:
            printf("CONST");
            break;
        case VOLATILE:
            printf("VOLATILE");
            break;
        case VOID:
            printf("VOID");
            break;
        case CHAR:
            printf("CHAR");
            break;
        case SHORT:
            printf("SHORT");
            break;
        case INT:
            printf("INT");
            break;
        case LONG:
            printf("LONG");
            break;
        case FLOAT:
            printf("FLOAT");
            break;
        case DOUBLE:
            printf("DOUBLE");
            break;
        case SIGNED:
            printf("SIGNED");
            break;
        case UNSIGNED:
            printf("UNSIGNED");
            break;
        case STRUCT:
            printf("STRUCT");
            break;
        case ENUM:
            printf("ENUM");
            break;
        case UNION:
            printf("UNION");
            break;
        case ID:
            printf("ID");
            break;
        case ICONST:
            printf("ICONST");
            break;
        case FCONST:
            printf("FCONST");
            break;
        case DO:
            printf("DO");
            break;
        case IF:
            printf("IF");
            break;
        case ELSE:
            printf("ELSE");
            break;
        case FOR:
            printf("FOR");
            break;
        case WHILE:
            printf("WHILE");
            break;
        default:
            printf("%c", tok);
            break;
        }
        printf("\n");

}
typedef enum boolean
{
    FALSE,
    TRUE
}_bool;


_bool is_expr(_bool*);

typedef enum error_type
{
    _FATAL_ERR,
    _WARN_ERR,
    _CONTINUE_ERR
} errtype;

struct err
{
    char* err_msg;
    errtype type;
    int token_number;
    int line;
    char* func;
};
/**** error is not for logs, but for crashing the software at end, instead of crashing inside the parser ***/
/**** parser will try n combinations, after that it will decide whether to exit the software or not ***/
struct err** e;
int error_lines = 0;
void init_error()
{
    e = (struct err**)malloc(sizeof(struct err*));
    if (e == NULL)
    {
        printf("init_error() failed!\n");
        exit(0);
    }
    
}

void make_error(const char* error_message, errtype typ, int token_no, int line, const char* func) {
    struct err* new_err = (struct err*)malloc(sizeof(struct err));
    if (new_err == NULL) {
        printf("make_error() failed to allocate memory for new_err!\n");
        exit(1);
    }

    size_t length_err = strlen(error_message) + 1;
    size_t length_func = strlen(func) + 1;

    new_err->err_msg = (char*)malloc(length_err);
    new_err->func = (char*)malloc(length_func);

    if (new_err->err_msg == NULL || new_err->func == NULL) {
        printf("make_error() failed to allocate memory for err_msg or func!\n");
        if (new_err->err_msg != NULL) free(new_err->err_msg);
        if (new_err->func != NULL) free(new_err->func);
        free(new_err);
        exit(1);
    }

    strcpy_s(new_err->err_msg, length_err, error_message);
    new_err->type = typ;
    new_err->token_number = token_no;
    new_err->line = line;
    strcpy_s(new_err->func, length_func, func);

    struct err** temp = (struct err**)realloc(e, (error_lines + 1) * sizeof(struct err*));
    if (temp == NULL) {
        printf("make_error() failed to reallocate memory for e!\n");
        free(new_err->err_msg);
        free(new_err->func);
        free(new_err);
        exit(1);
    }
    e = temp;
    e[error_lines] = new_err;
    error_lines++;
}


void show_error()
{
    int k = 0;
    for (k = 0; k < error_lines && *(e+k) != NULL; k++)
    {
        printf("%s:%d %s token pos is %d\n", e[k]->func, e[k]->line, e[k]->err_msg, e[k]->token_number);
        free(e[k]);
    }

    free(e);
}




