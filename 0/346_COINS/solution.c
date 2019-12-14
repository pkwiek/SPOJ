/*
 * =====================================================================================
 *
 *       Filename:  solution.c
 *
 *    Description:  
 *    COINS - Bytelandian gold coins
 *    #dynamic-programming
 *    In Byteland they have a very strange monetary system.
 *
 *    Each Bytelandian gold coin has an integer number written on it. A coin n can be exchanged in a bank into three coins: n/2, n/3 and n/4. But these numbers are all rounded down (the banks have to make a profit).
 *
 *    You can also sell Bytelandian coins for American dollars. The exchange rate is 1:1. But you can not buy Bytelandian coins.
 *
 *    You have one gold coin. What is the maximum amount of American dollars you can get for it?
 *
 *    Input
 *    The input will contain several test cases (not more than 10). Each testcase is a single line with a number n, 0 <= n <= 1 000 000 000. It is the number written on your coin.
 *
 *    Output
 *    For each test case output a single line, containing the maximum amount of American dollars you can make.
 *
 *    Example
 *    Input:
 *    12
 *    2
 *
 *    Output:
 *    13
 *    2
 *    You can change 12 into 6, 4 and 3, and then change these into $6+$4+$3 = $13. If you try changing the coin 2 into 3 smaller coins, you will get 1, 0 and 0, and later you can get no more than $1 out of them. It is better just to change the 2 coin directly into $2.
 *
 *
 *
 *        Version:  1.0
 *        Created:  12/04/2019 07:08:51 PM
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

#define PRE_RANGE 10000000

#define max(a,b)                    \
        ({                          \
            __typeof__(a) _a = a;   \
            __typeof__(b) _b = b;   \
            _a > _b ? _a : _b;      \
        })

void precompute ( long int * pre, int n );
long long int solve ( long int * pre, int n, int range );

int main (void)
{
    int t = 0, tc[10];
    char c;

    long int * pre = (long int *) malloc ( (unsigned long) (PRE_RANGE + 1)*sizeof(long int) );

    precompute ( pre, PRE_RANGE );

    while ( scanf ( "%c", &c ) == 1)
    {
        if ( c == '\n' )
        {
            break;
        }
        else
        {
            ungetc ( c, stdin );
            scanf ( "%d", &tc[t] );
            t++;
            while ( getchar() != '\n' )
                continue;
        }
    }

    for ( int i = 0; i < t; i++ )
    {
        printf ( "%llu\n", solve ( pre, tc[i], PRE_RANGE ) );
    }

    return 0;
}

void precompute ( long int * pre, int n )
{
    pre[0] = 0;
    for ( int i = 0; i < n+1; i++ )
    {
        pre[i] = max( i, pre[i/2] + pre[i/3] + pre[i/4] );
    }
}

long long int solve ( long int * pre, int n , int range)
{
    if ( n < range )
    {
        return (long long int) pre[n];
    }
    return  (long long int) solve ( pre, n/2, PRE_RANGE ) 
                            + solve ( pre, n/3, PRE_RANGE )
                            + solve ( pre, n/4, PRE_RANGE );
}
