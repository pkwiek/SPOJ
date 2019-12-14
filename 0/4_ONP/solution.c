/*
 * =====================================================================================
 *
 *       Filename:  solution.c
 *
 *    Description: 
 *    ONP - Transform the Expression
 *    #stack
 *    Transform the algebraic expression with brackets into RPN form (Reverse Polish Notation). Two-argument operators: +, -, *, /, ^ (priority from the lowest to the highest), brackets ( ). Operands: only letters: a,b..,z. Assume that there is only one RPN form (no expressions like a*b*c).
 *
 *    Input
 *    t [the number of expressions <= 100]
 *    expression [length <= 400]
 *    [other expressions]
 *    Text grouped in [ ] does not appear in the input file.
 *
 *    Output
 *    The expressions in RPN form, one per line.
 *    Example
 *    Input:
 *    3
 *    (a+(b*c))
 *    ((a+b)*(z+x))
 *    ((a+t)*((b+(a+c))^(c+d)))
 *
 *    Output:
 *    abc*+
 *    ab+zx+*
 *    at+bac++cd+^* 
 *        Version:  1.0
 *        Created:  11/28/2019 06:26:10 PM
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:  PAWEL KWIEK (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define PUSH(arr,elem,currsize)                                                         \
        {                                                                               \
            if (currsize && !(currsize&(currsize-1)))                                   \
            {                                                                           \
                arr=(__typeof__(elem)*)realloc(arr,2UL*currsize*sizeof(elem));          \
            }                                                                           \
            else if (!currsize)                                                         \
            {                                                                           \
                arr=(__typeof__(elem)*)malloc(sizeof(elem));                            \
            }                                                                           \
            arr[currsize]=elem;                                                         \
            ++currsize;                                                                 \
        }

#define POP(arr,elem,currsize)                                                          \
        {                                                                               \
            --currsize;                                                                 \
            elem=arr[currsize];                                                         \
            if (currsize)                                                               \
            {                                                                           \
                if (currsize && !(currsize&(currsize-1)))                               \
                {                                                                       \
                    arr=(__typeof__(elem)*)realloc(arr,sizeof(elem)*currsize);          \
                }                                                                       \
            }                                                                           \
            else                                                                        \
            {                                                                           \
                free (arr);                                                             \
                arr = NULL;                                                             \
            }                                                                           \
        }

void infix2postfix ( char ** out, char * input );

int p ( char a );

int main (void)
{
    int t;
    char ** inp;

    scanf ( "%d", &t );

    inp = (char **) malloc (t*sizeof(char *));

    for ( int i = 0; i < t; i++ )
    {
        inp[i] = (char *) malloc (401*sizeof(char));
        scanf ( "%s", inp[i] );
    }

    char * buff = NULL;
    for ( int i = 0; i < t; i++ )
    {
        infix2postfix ( &buff, inp[i] );
        printf ( "%s\n", buff );
    }

    for ( int i = 0; i < t; i++ )
    {
        free ( inp[i] );
    }
    free ( inp );

    return 0;
}

void infix2postfix ( char ** out, char * input )
{
    char * op = NULL;
    *out = NULL;
    int out_size = 0, op_size = 0;
    char tmp_op;
    int i = 0;
    char nu = 0;

    while ( input[i] )
    {
//        printf ( "%c, out_size = %d, op_size = %d\n", input[i], out_size, op_size );
        if ( input[i] < 123 && input[i] > 96 ) 
        {
            PUSH((*out),input[i],out_size);
        }
        else if ( input[i] == '+' || input[i] == '-' || input[i] == '/' || input[i] == '*' || input[i] == '^' )
        {
            while (   (   op_size 
                        && ( p(op[op_size-1]) > p(input[i]) || ( p(op[op_size-1]) ==  p(input[i]) 
                            && op[op_size-1] != '^' ) ) )
                        && op[op_size-1] != '(' )
            {
                POP(op,tmp_op,op_size);
                PUSH((*out),tmp_op,out_size);
            }
            PUSH(op,input[i],op_size);
        }
        else if ( input [i] == '(' )
        {
            PUSH(op,input[i],op_size);
        }
        else if ( input [i] == ')' )
        {
            while ( op[op_size-1] != '(' )
            {
                POP(op,tmp_op,op_size);
                PUSH((*out),tmp_op,out_size);
            }
            if ( op[op_size-1] == '(' )
            {
                POP(op,tmp_op,op_size);
            }
        }
        ++i;
    }
    while ( op_size != 0 )
    {
        POP(op,tmp_op,op_size);
        PUSH((*out),tmp_op,out_size);
    }
    PUSH((*out),nu,out_size);
}

int p ( char a )
{
    switch (a)
    {
        case '-' :
            return 2;
        case '+' :
            return 2;
        case '*' :
            return 3;
        case '/' :
            return 3;
        case '^' :
            return 4;
        default:
            return 0;
    }
}
