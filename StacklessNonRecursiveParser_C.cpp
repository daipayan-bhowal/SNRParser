/*
  Stackless Non-Recursive(SNR) Parser for C language 
  2024 Copyright@ Daipayan Bhowal 
*/

#include <stdio.h>
#include "commons.h"
#include <stdlib.h>

void function_caller(_bool*);
void declaration_specifiers(_bool* is_decl_sp, int* type);
void args(_bool* is_args);
void block_start_statement(_bool* is_blk);


enum parser_check // enum is used for indexing the different types of language elements such as expr, stmt, func_def
{
    START_INDEX,
    is_mdecl,
    is_func_def,
    is_func_decl,
    is_blk_end,
    is_enum_def,
    is_enum_func_def,
    is_enum_func_decl,
    is_struct_def,
    is_struct_dcl,
    is_struct_fun_def,
    is_struct_fun_dcl,
    is_func_caller,
    is_stmt,
    MAX_SIZE
};

_bool parsing_check[MAX_SIZE + 1] = { FALSE }; // for checking if any one of parsing is successful
int startToken[MAX_SIZE + 1] = { 0 }; // needed for backtracking

_bool is_expr(_bool* expr)
{
    *expr = FALSE;
    int count = 0;
 /*   _bool* func_caller = FALSE;
    function_caller(&func_caller);
    if (func_caller == TRUE)
    {
        *expr = TRUE;
        return;
    } */
  while ( tok == '+' ||
          tok == '-' ||
          tok == '/' ||
          tok == '*' ||
          tok == '%' ||
          tok == '^' ||
          tok == '<' ||
          tok == '>' ||
          tok == '|' ||
          tok == '?' ||
          tok == ':' ||
          tok == '(' ||
          tok == ')' ||
          tok == '~' ||
          tok == '=' ||
          tok == '!' ||
          tok == ID ||
          tok == ADD_ASSIGN ||
          tok == INC_OP ||
          tok == SUB_ASSIGN ||
          tok == DEC_OP ||
          tok == DIV_ASSIGN ||
          tok == MUL_ASSIGN ||
          tok == MOD_ASSIGN ||
          tok == AND_ASSIGN ||
          tok == XOR_ASSIGN ||
          tok == OR_ASSIGN ||
          tok == NOT_ASSIGN ||
          tok == RIGHT_OP ||
          tok == LEFT_OP ||
          tok == EQ_EQ_COND ||
          tok == GRT_EQ_OP ||
          tok == LESR_EQ_OP ||
          tok == INT_CONST ||
          tok == CHAR_CONST ||
          tok == F_CONST ||
          tok == OCTAL_CONST ||
          tok == USIGN_INT_CONST ||
          tok == LONG_INT_CONST ||
          tok == LONG_DOUBLE_CONST ||
          tok == E_F_CONST)
  { 
      count++;
      nextToken();
  }
  if (tok != ';' &&
      tok != '+' &&
      tok != '-' &&
      tok != '/' &&
      tok != '*' &&
      tok != '%' &&
      tok != '^' &&
      tok != '<' &&
      tok != '>' &&
      tok != '|' &&
      tok != '?' &&
      tok != ':' &&
      tok != '(' &&
      tok != ')' &&
      tok != '{' &&
      tok != '}' &&
      tok != '[' &&
      tok != ']' &&
      tok != '~' &&
      tok != '=' &&
      tok != '!' &&
      tok != ID &&
      tok != ADD_ASSIGN &&
      tok != INC_OP &&
      tok != SUB_ASSIGN &&
      tok != DEC_OP &&
      tok != DIV_ASSIGN &&
      tok != MUL_ASSIGN &&
      tok != MOD_ASSIGN &&
      tok != AND_ASSIGN &&
      tok != XOR_ASSIGN &&
      tok != OR_ASSIGN &&
      tok != NOT_ASSIGN &&
      tok != RIGHT_OP &&
      tok != LEFT_OP &&
      tok != EQ_EQ_COND &&
      tok != GRT_EQ_OP &&
      tok != LESR_EQ_OP &&
      tok != INT_CONST &&
      tok != CHAR_CONST &&
      tok != F_CONST &&
      tok != OCTAL_CONST &&
      tok != USIGN_INT_CONST &&
      tok != LONG_INT_CONST &&
      tok != LONG_DOUBLE_CONST &&
      tok != E_F_CONST)
  {
      printf("error: expression token at %d is invalid!", getTokenNumber());
      exit(0);
  }
  if (count >= 0 && (tok == ';' || tok == '{'))
  {
      printf("expr is true\n");
      *expr = TRUE;
  }

    return *expr;
}

_bool is_circularbraces_expr(_bool* expr, int curly_brace_level)
{
    *expr = FALSE;
    int count = 0;
    /*   _bool* func_caller = FALSE;
       function_caller(&func_caller);
       if (func_caller == TRUE)
       {
           *expr = TRUE;
           return;
       } */
    while (tok == '+' ||
        tok == '-' ||
        tok == '/' ||
        tok == '*' ||
        tok == '%' ||
        tok == '^' ||
        tok == '<' ||
        tok == '>' ||
        tok == '|' ||
        tok == '?' ||
        tok == ':' ||
        tok == ';' ||
        tok == '(' ||
        tok == ')' ||
        tok == '~' ||
        tok == '=' ||
        tok == '!' ||
        tok == ID ||
        tok == ADD_ASSIGN ||
        tok == INC_OP ||
        tok == SUB_ASSIGN ||
        tok == DEC_OP ||
        tok == DIV_ASSIGN ||
        tok == MUL_ASSIGN ||
        tok == MOD_ASSIGN ||
        tok == AND_ASSIGN ||
        tok == XOR_ASSIGN ||
        tok == OR_ASSIGN ||
        tok == NOT_ASSIGN ||
        tok == RIGHT_OP ||
        tok == LEFT_OP ||
        tok == EQ_EQ_COND ||
        tok == GRT_EQ_OP ||
        tok == LESR_EQ_OP ||
        tok == INT_CONST ||
        tok == CHAR_CONST ||
        tok == F_CONST ||
        tok == OCTAL_CONST ||
        tok == USIGN_INT_CONST ||
        tok == LONG_INT_CONST ||
        tok == LONG_DOUBLE_CONST ||
        tok == E_F_CONST)
    {
        count++;

        if (tok == '(')
        {
            curly_brace_level++;
        }
        else if(tok == ')')
            curly_brace_level--;
        else if (tok == ';' && curly_brace_level > 0)
        {
            printf("error: expected '(' before ';' ");
            exit(0);
        }
        nextToken();
    }
    if (curly_brace_level != 0)
    {
        if (curly_brace_level > 0)
            printf("error: ')' missing! ");
        else
            printf("error: ')' expected! ");
        *expr = FALSE;
        exit(0);
    }
    if (tok != ';' &&
        tok != '+' &&
        tok != '-' &&
        tok != '/' &&
        tok != '*' &&
        tok != '%' &&
        tok != '^' &&
        tok != '<' &&
        tok != '>' &&
        tok != '|' &&
        tok != '?' &&
        tok != ':' &&
        tok != '(' &&
        tok != ')' &&
        tok != '{' &&
        tok != '}' &&
        tok != '[' &&
        tok != ']' &&
        tok != '~' &&
        tok != '=' &&
        tok != '!' &&
        tok != ID &&
        tok != ADD_ASSIGN &&
        tok != INC_OP &&
        tok != SUB_ASSIGN &&
        tok != DEC_OP &&
        tok != DIV_ASSIGN &&
        tok != MUL_ASSIGN &&
        tok != MOD_ASSIGN &&
        tok != AND_ASSIGN &&
        tok != XOR_ASSIGN &&
        tok != OR_ASSIGN &&
        tok != NOT_ASSIGN &&
        tok != RIGHT_OP &&
        tok != LEFT_OP &&
        tok != EQ_EQ_COND &&
        tok != GRT_EQ_OP &&
        tok != LESR_EQ_OP &&
        tok != INT_CONST &&
        tok != CHAR_CONST &&
        tok != F_CONST &&
        tok != OCTAL_CONST &&
        tok != USIGN_INT_CONST &&
        tok != LONG_INT_CONST &&
        tok != LONG_DOUBLE_CONST &&
        tok != E_F_CONST)
    {
        printf("error: expression token at %d is invalid!", getTokenNumber());
        exit(0);
    }
    if (count >= 0 && (tok == ';' || tok == '{'))
    {
        printf("expr is true\n");
        *expr = TRUE;
    }

    return *expr;
}

void enum_def(_bool* is_enum_dcl, _bool* is_enum_func_def, _bool* is_enum_func_decl)
{
    if (tok == TYPEDEF)
    {
        nextToken();
    }
    if (tok == ENUM)
    {
        if (block_level > 0)
        {
            make_error("error: enum allowed only in global scope", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
            return;
        }
        nextToken();
        if (tok == '{' )
        {
            nextToken();
            while (tok == ID)
            {

                nextToken();
                if (tok == '=')
                {
                    nextToken();
                    if (tok == USIGN_INT_CONST)
                    {
                        *is_enum_dcl = TRUE;
                        nextToken();
                    }
                    else
                    {
                        _bool expr= FALSE;
                        is_expr(&expr);
                        if (expr == false)
                        {
                            printf("error: enum only supports constant expression !");
                            exit(0);
                        }
                    }

                }

                if (tok == '}')
                {
                    nextToken();
                    if (tok == ';')
                    {
                        nextToken();
                        *is_enum_dcl = TRUE;
                        return;
                    }
                }
                else if (tok != ',')
                {
                    *is_enum_dcl = FALSE;
                    //make_error()
                    exit(0); // exit is necessary, enum declaration is wrong
                }
               
                if (tok == ',')
                {
                    nextToken();
                }
                else 
                {
                    //make_error();
                    exit(0);  // exit is necessary, enum declaration is wrong
                }

            }


        }
        else if (tok == ID)
        {
            nextToken();
            if (tok == '{')
            {
                nextToken();
                while (tok == ID && tok != EOF)
                {

                    nextToken();
                    if (tok == '}')
                    { 
                        nextToken();
                        if (tok == ';')
                        {
                            nextToken();
                            *is_enum_dcl = TRUE;
                            return;
                        }
                    }
                    else if (tok != ',')
                    {
                        *is_enum_dcl = FALSE;
                        //make_error()
                        exit(0); // exit is necessary, enum declaration is wrong
                    }

                    if (tok == ',')
                    {
                        nextToken();
                    }
                    else
                    {
                        //make_error();
                        exit(0);  // exit is necessary, enum declaration is wrong
                    }

                }
            }
            else if (tok == '(') // enum returning function
            {
                _bool is_args = FALSE;
                _bool is_blk = FALSE;
                if (block_level > 1)
                {
                    make_error("nested function is not allowed!\n", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
                    return;
                }
                nextToken();
                args(&is_args);
                block_start_statement(&is_blk);

                if (is_blk == TRUE && is_args == TRUE)
                {
                    //statement_list( &is_stmt);
                   // block_end_statement( &is_blk);
                    *is_enum_func_def = TRUE;
                }
                else if (tok == ';')
                {
                    *is_enum_func_decl = TRUE;
                }

                return;
            }


        }
        else 
        {
            printf("error: enum defination is not correct !\n");
            exit(0);
        }
    }

}

void  struct_defination_or_declaration(_bool* is_struct_def, _bool* is_struct_dcl, _bool* is_struct_fun_def, _bool* is_struct_fun_dcl)
{
    // debugToken();

    if (tok == TYPEDEF)
    {
        nextToken();
    }

    if (tok == STRUCT ||
        tok == UNION)
    {

        if (prevToken() == '(' || prevToken() == ',')
        {
            return;
        }

        nextToken();
        if (tok == ID)
        {
            nextToken();
            if (tok == ID)
            {
                nextToken();
                if (tok == ';')
                {
                    nextToken();
                    *is_struct_dcl = TRUE;
                    return;
                }
                else if (tok == '(') // function raturn type is struct
                {
                    _bool is_args = FALSE;
                    _bool is_blk = FALSE;
                    if (block_level > 1)
                    {
                        make_error("nested function is not allowed!\n", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
                        return;
                    }
                    nextToken();
                    args(&is_args);
                    block_start_statement(&is_blk);

                    if (is_blk == TRUE && is_args == TRUE)
                    {
                        //statement_list( &is_stmt);
                       // block_end_statement( &is_blk);
                        *is_struct_fun_def = TRUE;
                    }
                    else if (tok == ';')
                    {
                        *is_struct_fun_dcl = TRUE;
                    }

                    return;
                }
                else if (tok == ',') // multiple struct declaration
                {
                    // nextToken();
                    _bool toggle = FALSE;
                    while (tok != ';' && tok != EOF)
                    {
                        if (tok == ',' && toggle == FALSE)
                        {
                            nextToken();
                            toggle = TRUE;
                        }
                        else if (tok == ID && toggle == TRUE)
                        {
                            nextToken();
                            toggle = FALSE;
                        }

                    }
                    if (tok == ';')
                    {
                        nextToken();
                        printf("multiple structure declaration is true\n");
                        *is_struct_dcl = TRUE;
                        return;
                    }
                    else if (tok != EOF)
                    {
                        make_error("error: multiple declaration is wrong!\n", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
                        *is_struct_dcl = FALSE;
                        return;
                    }
                }

            }
            else if (tok == '{')
            {
                nextToken();
                _bool is_dcl = FALSE;
                int type;
                declaration_specifiers(&is_dcl, &type);
                while (is_dcl == TRUE)
                {
                    _bool term = FALSE;
                    if (tok == ';')
                    {
                        nextToken();
                        term = TRUE;
                    }

                    if (term == TRUE && tok == '}')
                    {
                        nextToken();
                        if (block_level > 0)
                        {
                            make_error("error: struct allowed only in global scope", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
                            return;
                        }
                        *is_struct_def = TRUE;
                        break;
                    }
                    else if (term == FALSE)
                    {
                        *is_struct_def = FALSE;
                        return;
                    }

                    declaration_specifiers(&is_dcl, &type);
                }
                if (tok == ID)
                {
                    nextToken();
                    if (tok == ';')
                    {
                        nextToken();
                        if (block_level > 0)
                        {
                            make_error("error: struct allowed only in global scope", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
                            return;
                        }
                        printf("structure declaration is true\n");
                        *is_struct_def = TRUE;
                        return;

                    }

                }
                else if (tok == ';')
                {
                    nextToken();
                    if (block_level > 0)
                    {
                        make_error("error: struct allowed only in global scope", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
                        return;
                    }
                    printf("structure declaration is true, tok: %d\n", tok);
                    *is_struct_def = TRUE;
                    return;
                }
                else {
                    printf("error: ; or ID expected at end of struct defination !");
                    exit(0);
                }
            }
            else
            {
                printf("error: structure declaration is wromg!\n");
                exit(0);
            }

        }
        else
        {
            printf("error: wrong usage of struct/union keyword\n");
            exit(0);
        }

        //struct_or_union();
    }

}


void statement(_bool* is_stmt, int *type)
{
    _bool expr = FALSE;
    int circular_brace_level = 0;
    static int switch_level = 0;
     switch(tok)
     {
        case FOR:
        {
           nextToken();
           if (tok == '(')
           {
               circular_brace_level++;
               nextToken();
               _bool paramter_var = FALSE;
               is_expr(&expr);
             if (tok == ';')
             {
                 nextToken();
                 is_expr(&expr);
                 if (tok == ';')
                 {
                     nextToken();
                     is_circularbraces_expr(&expr, circular_brace_level);
                     //printf("tok:%c prevToken:%c tok_pos:%d prev_tok_pos: %d\n", tok, arr[i-1], getTokenNumber(), i-1);
                     if (tok != '{' && tok != ';')
                     {
                         printf("For loop definaion is wrong ! tok:%c tok_pos:%d", tok, getTokenNumber());
                         exit(0);
                     }
                     else
                     {
                        // printf("FOR loop statement is true!");
                         *type = FOR;
                         *is_stmt = TRUE;
                         if (tok == '{')
                             block_level++;
                         nextToken();
                         return;
                     }
                 }
             }
             else // fatal error
             {
                 printf("error: ; expected after FOR ! tok is:%d", tok);
                 exit(0);
             }


             break;
           }
        }
    case SWITCH:
        setKeywordToken(tok);
        nextToken();
        if (tok == '(')
        {
            nextToken();
            is_expr(&expr);
            if (tok == ')')
            {
                *type = SWITCH;
                *is_stmt = TRUE;
                nextToken();
                if (tok == '{')
                {
                    block_level++;
                    nextToken();
                }
                else
                {
                    printf("error: '{' expected !");
                    exit(0);
                }
            }
            else
            {
                printf("error: ')' expected !");
                exit(0);
            }
        }
        else
        {
            printf("error: '(' expected !");
            exit(0);
        }

    break;
    case CASE:
        if (lastKeywordToken() != SWITCH)
        {
            printf("error: switch keyword is missing !");
            exit(0);

        }
        nextToken();
        is_expr(&expr);
            if (tok == ':')
            {
                *is_stmt = TRUE;
                *type = CASE;
                nextToken();
                if (tok == '{')
                {
                    block_level++;
                    nextToken();
                }
            }
            else
            {
                printf("error: ':' is missing !");
                exit(0);
            }
    break;

    case DEFAULT:
        if (lastKeywordToken() != SWITCH)
        {
            printf("error: switch keyword is missing !");
            exit(0);
        }
        nextToken();
        if (tok == ':')
        {
            *is_stmt = TRUE;
            *type = DEFAULT;
            nextToken();
            if (tok == '{')
            {
                block_level++;
                nextToken();
            }
        }
        else
        {
            printf("error: ':' is missing !");
            exit(0);
        }
    break;
    case WHILE:
       
       nextToken();
       if (tok == '(')
       {
               circular_brace_level++;
               nextToken();
               is_circularbraces_expr(&expr, circular_brace_level);
               if (tok == '{')
               {
                   setKeywordToken(tok);
                   *type = WHILE;
                   *is_stmt = TRUE;
                   nextToken();
                   return;
               }
               else if (tok == ';') // do-while successful
               {
                   if (lastKeywordToken() != DO)
                   {
                       printf("error: 'do' keyword is missing !");
                       exit(0);
                   }

                   *type = DO;
                   *is_stmt = TRUE;
                   nextToken();
                   return;

               }
               else
               {
                   printf("error: 'while' keyword is not used properly !");
                   exit(0);

               }
       }
       else // fatal error
       {
          printf("error: ( expected !");
          exit(0);
        }
  
    break;

    case DO:
       setKeywordToken(tok);
       nextToken();
       if(tok == '{')
      {
          block_level++;
          nextToken();
          return;
      }

    break;

    case IF:
       nextToken();
       if (tok == '(')
       {
           circular_brace_level++;
           nextToken();
           is_circularbraces_expr(&expr, circular_brace_level);
           if (tok == '{')
           {
               *type = IF;
               *is_stmt = TRUE;
               block_level++;
               nextToken();
               return;
           }
           else if (tok == ';')
           {
               *type = IF;
               *is_stmt = TRUE;
               nextToken();
               return;
           }
           else
           {
               is_expr(&expr);
               if (expr == FALSE)
               {
                   printf("error: wrong symbol present !");
                   return;
               }
               *type = IF;
               *is_stmt = TRUE;
               nextToken();
               return;

           }

       }
       else // fatal error
       {
           printf("error: ( expected !");
           exit(0);
       }

    break;

    case ELSE:
    nextToken();
     if(tok == '{')
     {
         *type = ELSE;
         *is_stmt = TRUE;
        block_level++;
        nextToken();
        return;
     }
     else if(tok == IF)
     {
        nextToken();
        if (tok == '(')
        {
            circular_brace_level++;
            nextToken();
            is_circularbraces_expr(&expr, circular_brace_level);
            if (tok == '{')
            {
                *type = IF;
                *is_stmt = TRUE;
                nextToken();
                return;
            }
            else // fatal error
            {
                is_expr(&expr);
                if (expr == false)
                {
                    printf("error: ) expected !");
                    exit(0);
                }
            }

        }
        else // fatal error
        {
            printf("error: ( expected !");
            exit(0);
        }
     }

    break;

   }

}
void array_decl(_bool* is_arraydecl)
{
    static _bool is_open_sqbr = FALSE;
    static int count = 0;
    if (tok == '[')
    {
        count++;
        if (count > 1)
        {
            make_error("unexpected [ \n", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
            return;
        }

        is_open_sqbr = TRUE;
        nextToken();
    }
    else if (tok == ID || tok == ICONST || tok == FCONST)
    {
        _bool expr;
        if (is_expr(&expr))
        {

        }
        else if (tok == ID && lookupToken() == '(')
        {
            function_caller(&expr);
        }
        else
        {

        }


        // need to check whether it's an expression
        nextToken();
    }
    else if (tok == ']')
    {
        count--;
        if (is_open_sqbr == FALSE)
        {
            make_error("expected [ \n", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
            return;
        }
        *is_arraydecl = TRUE;
        is_open_sqbr = FALSE;
        nextToken();
        return;
    }
    else if (is_open_sqbr == TRUE) // expression
    {
        nextToken();
    }

    if (tok == EOF)
        return;
    else if (tok != ID && tok != ';')
        array_decl(is_arraydecl);

    return;
}


void declaration_specifiers(_bool* is_decl_sp, int* type)
{ 
    *is_decl_sp = FALSE;
    char specifier_bit1 = 0, specifier_bit2 = 0, specifier_bit3 = 0;
    printf("declaration_specifiers: is_decl_sp:%d\n", *is_decl_sp);
    dispToken(tok);
    if (tok == TYPEDEF ||
        tok == EXTERN ||
        tok == STATIC ||
        tok == AUTO ||
        tok == REGISTER)
    {
        specifier_bit1 = 1;
        nextToken();
        
    }
    if (tok == CONST ||
        tok == VOLATILE)
    {

        nextToken();
    }

    if (tok == SIGNED ||
        tok == UNSIGNED)
    {
        specifier_bit2 = 1;
        nextToken();
    }
    printf("declaration_specifiers: tok is: %d %d\n", tok, __LINE__);
    dispToken(tok);
    if (tok == VOID ||
        tok == CHAR ||
        tok == SHORT ||
        tok == INT ||
        tok == LONG ||
        tok == FLOAT ||
        tok == DOUBLE ||
        tok == SIGNED ||
        tok == UNSIGNED
        )
    {
        *type = tok;
        *is_decl_sp = TRUE;
        specifier_bit3 = 1;
        nextToken();
    }
    else if(tok == ID && lookupToken() == '(') // backtrack, it's a function call
    {
        *is_decl_sp = FALSE;
        return;
    }
    // for struct arguments in a function arguments, chances of infinite loop is more in below check
    else if (getTokenNumber() != 0 && (prevToken() == '(' || prevToken() == ',') && (tok == STRUCT || tok == UNION)) // need to backtrack if failed! as struct is commons between 2 driver functions so conflict can occur, only support struct arguments
    {
        *type = tok;
        nextToken();
        if (tok == ID)
        {
            nextToken();
            if (tok == '*')
            {
                nextToken();
                if (tok == ID)
                {
                    nextToken();
                    if (tok == ')' || tok == ',')
                    {
                        *is_decl_sp = TRUE;
                        return;
                    }

                }
                else {

                }

            }
            else if (tok == ID)
            {
                nextToken();
                if (tok == ')' || tok == ',')
                {
                    *is_decl_sp = TRUE;
                    return;
                }
            }
        }
        
    }
    else {
        make_error("Type missing in declaration\n", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
        *is_decl_sp = FALSE;
        return;
    }
    while (tok == '*')
    {
        nextToken();
    }
    if (tok == '[')
    {
        _bool is_validarr = FALSE;
        array_decl(&is_validarr);

    }
    if (!(specifier_bit1 | specifier_bit2 | specifier_bit3)) // if any one of the bit is set, then it's a declaration
    {
        *is_decl_sp = FALSE;
        return;
    }
    dispToken(tok);
    if (tok == ID && *is_decl_sp == TRUE)
    {
        *is_decl_sp = TRUE;
        printf("declarataion parsing successful !\n");
        nextToken();

    }
    else {
        make_error("Identifier missing in declaration\n", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
        return;
    }


    return;
}
void args(_bool* is_args)
{
    static _bool is_comma = FALSE;
    if (tok == '(')
    {
        *is_args = TRUE;
        nextToken();
        if (tok == ')') // this case is for better optimization
        {
            nextToken();
            return;
        }
    }
    else if (tok == ',')
    {
        is_comma = TRUE;
        nextToken();

    }
    else if (tok == ')')
    {
        if (is_comma == TRUE) // for case " int id ,)"
        {
            make_error("expected identifier between , and ) \n", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
            return;
        }

        if (*is_args == FALSE)
        {
            make_error("expected \'( \' \n", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
            return;
        }


        nextToken();
        return;
    }
    else
    {
        if (*is_args == FALSE && is_comma == FALSE)
        {
            make_error("expected , or ( before  \n", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
            return;
        }
        _bool paramter_var = FALSE;
        int type;
        declaration_specifiers(&paramter_var, &type);
        if (paramter_var == FALSE)
        {
            make_error("Function argument is invalid\n", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
        }
        else
        {
            is_comma = FALSE;
        }
    }

    if (tok == ';')
        return;
    else if (tok == EOF)
    {
        make_error(" ; expected!\n", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
        return; // return is needed to kill the infinite recursion
    }
    else if (tok != ';')
        args(is_args);
}

void function_caller(_bool* is_func_caller)
{
    _bool is_id_before = FALSE;
    if (tok == ID)
    {
        nextToken();
        if (tok == '(')
        {
            if (block_level < 1)
            {
                make_error(" function caller cannot be global!\n", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
                return;
            }
            nextToken();
            while (tok != ')' && tok != EOF && tok != ';')
            {
                switch (tok)
                {
                case ID:
                    is_id_before = TRUE;
                    nextToken();
                    break;

                case ',':
                    nextToken();
                    if (is_id_before == FALSE)
                    {
                        make_error("Function callee is expecting id before ,\n", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
                        return;
                    }
                    else
                        is_id_before = FALSE;
                    break;

                default:
                    make_error("Function callee is expecting id before ,\n", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
                    *is_func_caller = FALSE;
                    return;

                }

            }
            if (tok == ')')
            {
                nextToken();
                if (is_id_before == FALSE)
                {
                    make_error("Function callee is expecting id before )\n", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
                    return;
                }
                if (tok == ';')
                {
                    nextToken();
                    *is_func_caller = TRUE;
                    return;
                }
            }
            else
                *is_func_caller = FALSE;
        }
        else {
            *is_func_caller = FALSE;
            return;
        }

    }


}


void block_start_statement(_bool* is_blk)
{
    if (tok == '{')
    {
        block_level++;
        *is_blk = TRUE;
        nextToken();
    }

}
void block_end_statement(_bool* is_blk)
{
    if (tok == '}')
    {
        block_level--;
        *is_blk = TRUE;
        nextToken();
    }

}



void function_definition_or_declaration(_bool* is_func_def, _bool* is_func_decl)
{
    _bool is_decl = FALSE, is_args = FALSE, is_blk = FALSE, is_stmt = FALSE;
    int type;
    declaration_specifiers(&is_decl, &type);
    debugToken();
    printf("func_decl_or_def %d %d tok:%d tok_pos:%d\n ", *is_func_def, *is_func_decl, tok, getTokenNumber());
    if (is_decl == FALSE)
    {
        *is_func_def = FALSE;
        *is_func_decl = FALSE;
        return;
    }
    args(&is_args);
    block_start_statement(&is_blk);
    if (is_blk == TRUE && is_args == TRUE)
    {
        //statement_list( &is_stmt);
       // block_end_statement( &is_blk);
        *is_func_def = TRUE;
    }
    else if (tok == ';' && is_args == TRUE)
    {
        *is_func_decl = TRUE;
    }

   // printf("func_decl_or_def %d %d\n ", *is_func_def, *is_func_decl);
    if (block_level > 1)
    {
        make_error("nested function is not allowed!\n", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
        return;
    }

}

void multiple_declaration(_bool* is_multidecl)
{
    //debugToken();
    _bool is_decl_sp = FALSE, is_comma = FALSE;
    int type;
    printf("multiple_declaration is is_decl_sp:%s tok:%c\n", (is_decl_sp == TRUE) ? "TRUE" : "FALSE", tok);
    declaration_specifiers(&is_decl_sp, &type);
   
    if (tok == '(') // backtrack needed, this case needs to be handled by func_defination_or_declarartion()
    {
        *is_multidecl = FALSE;       
        resetToken(startToken[is_mdecl]); // backtracking by reseting the token position to the place just before starting the parsing
        printf("backtracking multiple_declaration is is_decl_sp:%s tok:%c tok_pos is:%d start_tok_pos is %d\n", (is_decl_sp == TRUE) ? "TRUE" : "FALSE", tok, getTokenNumber(), startToken[is_mdecl]);
        return;
    }
    if (is_decl_sp == FALSE)
    {
        *is_multidecl = FALSE;
        return;
    }
    if (tok == ';')
    {
        *is_multidecl = TRUE;
        nextToken();
        return;
    }
    else if (tok == '=') // for single declaration plus expression together, example:- int i = y + 5;
    {
        _bool expr = FALSE;
        *is_multidecl = TRUE;
        nextToken();
        is_expr(&expr);
        return;
    }

    printf("multiple_declaration: tok is: %d , is_decl_sp:%d\n", tok, (is_decl_sp == TRUE) ? "TRUE" : "FALSE");
    if (tok == ',')
    {
        is_comma = TRUE;
        while (tok != ';' && tok != EOF)
        {
            switch (tok)
            {
            case ',':
                if (is_comma == TRUE)
                {
                    make_error("Multiple commas notices \n", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
                    return;
                }
                nextToken();
                break;
            case ID:
                if (is_comma == FALSE)
                {
                    make_error("illegal declarations!\n", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
                    return;
                }
                is_comma = FALSE;
                nextToken();
                break;


            }
        }
        if (tok == ';')
        {
            *is_multidecl = TRUE;
            printf("declaration ; encountered!\n");
            nextToken();
            return;
        }
        else if (tok == EOF)
        {
            make_error("; expected ! \n", _FATAL_ERR, getTokenNumber(), __LINE__, __func__);
            return;
        }
    }
}



void init_parsing_table()
{
    parsing_check[is_mdecl] = FALSE;
    parsing_check[is_func_def] = FALSE;
    parsing_check[is_func_decl] = FALSE;
    parsing_check[is_blk_end] = FALSE;
    parsing_check[is_enum_def] = FALSE;
    parsing_check[is_enum_func_def] = FALSE;
    parsing_check[is_enum_func_decl] = FALSE;
    parsing_check[is_struct_dcl] = FALSE;
    parsing_check[is_struct_def] = FALSE;
    parsing_check[is_struct_fun_def] = FALSE;
    parsing_check[is_struct_fun_dcl] = FALSE;
    parsing_check[is_func_caller] = FALSE;
    parsing_check[is_stmt] = FALSE;
}
void global_scope()
{

    int j = 1, dist = 0;
    int type = 0;
    init_error();
    init_parsing_table();
    while (tok != EOF)
    {
          startToken[is_mdecl] = getTokenNumber();
          multiple_declaration(&parsing_check[is_mdecl]);
          startToken[is_func_def] = getTokenNumber();
          startToken[is_func_decl] = getTokenNumber();
          function_definition_or_declaration(&parsing_check[is_func_def], &parsing_check[is_func_decl]);
          startToken[is_blk_end] = getTokenNumber();
          block_end_statement(&parsing_check[is_blk_end]);
          startToken[is_enum_def] = getTokenNumber();
          enum_def(&parsing_check[is_enum_def], &parsing_check[is_enum_func_def], &parsing_check[is_enum_func_decl]);
          startToken[is_struct_dcl] = getTokenNumber();
          startToken[is_struct_def] = getTokenNumber();
          startToken[is_struct_fun_def] = getTokenNumber();
          startToken[is_struct_fun_dcl] = getTokenNumber();
          struct_defination_or_declaration(&parsing_check[is_struct_dcl], &parsing_check[is_struct_def], &parsing_check[is_struct_fun_def], &parsing_check[is_struct_fun_dcl]);
          startToken[is_func_caller] = getTokenNumber();        
          function_caller(&parsing_check[is_func_caller]);
          startToken[is_stmt] = getTokenNumber();
          statement(&parsing_check[is_stmt], &type);
         // debugToken();
         // printf("\ntoken is: %c token position is:%d\n", tok, getTokenNumber());
 /*       for (j = 1; j < MAX_SIZE; j++) // index refers to enum parser_check
        {
            if (parsing_check[j] == TRUE)
            {
                printf("j is %d\n", j);
                break;
            }

        }
 */


        printf("before switch is %d\n", getTokenNumber());

            if (parsing_check[is_mdecl] == TRUE)
            {
                dist = getTokenNumber() - startToken[is_mdecl];
                printf("multiple declaration!");
            }
            if (parsing_check[is_func_def] == TRUE)
            {
                dist = getTokenNumber() - startToken[is_func_def];
                printf("function defination!");
            }
            if (parsing_check[is_func_decl] == TRUE)
            {
                dist = getTokenNumber() - startToken[is_func_decl];
                printf("function declaration!");
            }
            if (parsing_check[is_blk_end] == TRUE)
            {
                dist = getTokenNumber() - startToken[is_blk_end];
                printf("block end encountered!");
            }
            if (parsing_check[is_enum_def] == TRUE)
            {
                dist = getTokenNumber() - startToken[is_enum_def];
                printf("enum encountered!");
            }
            if (parsing_check[is_struct_def] == TRUE)
            {
                dist = getTokenNumber() - startToken[is_struct_def];
                printf("struct defination encountered!");
            }
            if (parsing_check[is_struct_dcl]==TRUE)
            {
                dist = getTokenNumber() - startToken[is_struct_dcl];
                printf("struct declaration encountered!");
            }
            if (parsing_check[is_struct_fun_def] == TRUE)
            {
                dist = getTokenNumber() - startToken[is_struct_fun_def];
                printf("struct func def encountered!");
            }
            if (parsing_check[is_struct_fun_dcl] == TRUE)
            {
                dist = getTokenNumber() - startToken[is_struct_fun_dcl];
                printf("struct func dcl encountered!");
            }
            if (parsing_check[is_func_caller] == TRUE)
            {
                dist = getTokenNumber() - startToken[is_func_caller];
               // debugToken();
                printf("func caller encountered! %d", startToken[is_func_caller]);
            }
            if (parsing_check[is_stmt] == TRUE)
            {
                dist = getTokenNumber() - startToken[is_stmt];
                // debugToken();
                printf("statement encountered! %d , type is:%d", startToken[is_stmt], type);
            }
            printf("\n");

            if (
                parsing_check[is_mdecl] == FALSE &&
                parsing_check[is_func_def] == FALSE &&
                parsing_check[is_func_decl] == FALSE &&
                parsing_check[is_blk_end] == FALSE &&
                parsing_check[is_enum_def] == FALSE &&
                parsing_check[is_struct_def] == FALSE &&
                parsing_check[is_struct_dcl] == FALSE &&
                parsing_check[is_struct_fun_def] == FALSE &&
                parsing_check[is_struct_fun_dcl] == FALSE &&
                parsing_check[is_enum_func_def] == FALSE &&
                parsing_check[is_enum_func_decl] == FALSE &&
                parsing_check[is_func_caller] == FALSE &&
                parsing_check[is_stmt] == FALSE
                )
            {
                //i = startToken[is_mdecl];
                show_error();
                exit(0);
            }
            init_parsing_table(); // need to reintialize the table
    }
}

int main()
{
    int s = 0;
    arr[s++] = STRUCT;
    arr[s++] = ID;
    arr[s++] = '{';
    arr[s++] = INT;
    arr[s++] = ID;
    arr[s++] = ';';
    arr[s++] = INT;
    arr[s++] = ID;
    arr[s++] = ';';
    arr[s++] = '}';
    arr[s++] = ';';
    arr[s++] = REGISTER;
    arr[s++] = INT;
    arr[s++] = ID;
    arr[s++] = '(';
    arr[s++] = INT;
    arr[s++] = ID;
    arr[s++] = ')';
    arr[s++] = '{';
    arr[s++] = INT;
    arr[s++] = ID;
    arr[s++] = ';';
    arr[s++] = ID;
    arr[s++] = '(';
    arr[s++] = ID;
    arr[s++] = ',';
    arr[s++] = ID;
    arr[s++] = ')';
    arr[s++] = ';';
    arr[s++] = FOR;
    arr[s++] = '(';
    arr[s++] = ID;
    arr[s++] = ';';
    arr[s++] = ID;
    arr[s++] = ';';
    arr[s++] = ID;
    arr[s++] = ')';
    arr[s++] = '{';
    arr[s++] = '}';
    arr[s++] = IF;
    arr[s++] = '(';
    arr[s++] = ID;
    arr[s++] = ')';
    arr[s++] = '{';
    arr[s++] = '}';
    arr[s++] = '}';
    arr[s++] = EOF;
    // arr[7] = EOF;
    global_scope();
    return 0;
}

