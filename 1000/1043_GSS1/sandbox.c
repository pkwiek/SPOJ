/*
 * =====================================================================================
 *
 *       Filename:  solution.c
 *
 *    Description:  
 *    GSS1 - Can you answer these queries I
 *    #tree
 *    You are given a sequence A[1], A[2], ..., A[N] . ( |A[i]| ≤ 15007 , 1 ≤ N ≤ 50000 ). A query is defined as follows:
 *    Query(x,y) = Max { a[i]+a[i+1]+...+a[j] ; x ≤ i ≤ j ≤ y }.
 *    Given M queries, your program must output the results of these queries.
 *
 *    Input
 *    treehe first line of the input file contains the integer N.
 *    In the second line, N numbers follow.
 *    treehe third line contains the integer M.
 *    M lines follow, where line i contains 2 numbers xi and yi.
 *    Output
 *    Your program should output the results of the M queries, one query per line.
 *
 *    Example
 *    Input:
 *    3 
 *    -1 2 3
 *    1
 *    1 2
 *
 *    Output:
 *    2
 *
 *        Version:  1.0
 *        Created:  12/03/2019 04:28:15 PM
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

#define max(a,b)                    \
        ({                          \
            __typeof__ (a) _a = a;  \
            __typeof__ (b) _b = b;  \
            _a > _b ? _a : _b;      \
        })

#define min(a,b)                    \
        ({                          \
            __typeof__ (a) _a = a;  \
            __typeof__ (b) _b = b;  \
            _a < _b ? _a : _b;      \
        })

typedef struct
{
    long int sum, pref, suff, ans;
} vertex;

void build ( int * t, int * a, int v, int tl, int tr );
long int sum ( int * t, int v, int tr, int tl, int l, int r);
void printree ( int * t, int v, int tl, int tr );
long int maxarr (

int main (void)
{
    int n, * arr = NULL, * tree, t, * l = NULL, * r = NULL;

    scanf ( "%d", &n );
    arr = (int *) malloc ( n*sizeof(int) );
    tree = (int *) malloc ( 4UL*n*sizeof(int) );
    for ( int i = 0; i < n; i++ )
    {
        scanf ( "%d", &arr[i] );
    }

    build ( tree, arr, 1, 0, n-1 );
    printree ( tree, 1, 0, n-1 );

    scanf ( "%d", &t );
    l = (int *) malloc ( t*sizeof(int) );
    r = (int *) malloc ( t*sizeof(int) );
    for ( int i = 0; i < t; i++ )
    {
        scanf ( "%d%d", &l[i], &r[i] );
    }

    for ( int i = 0; i < t; i++ )
    {
        printf ( "%lu\n", sum ( tree, 1, 0, n-1, l[i]-1, r[i]-1 ) );
    }

    free ( r );
    free ( l );
    free ( tree );
    free ( arr );

    return 0;
}


void build ( int * t, int * a, int v, int tl, int tr )
{
    if ( tl == tr )
    {
        t[v] = a[tl];
    }
    else
    {
        int tm = (tl + tr) / 2;
        build ( t, a, v*2, tl, tm );
        build ( t, a, v*2+1, tm+1, tr );
        t[v] = t[v*2] + t[v*2+1];
    }
    
}

long int sum ( int * t, int v, int tl, int tr, int l, int r)
{
    if ( r < l )
    {
        return 0;
    }
    if ( tr == r && tl == l )
    {
        return (long int) t[v];
    }
    int tm = (tr + tl) / 2;
    return sum ( t, v*2, tl, tm, l, min(r,tm) )
            + sum (t , v*2+1, tm+1, tr, max(l,tm+1), r );
}

void printree ( int * t, int v, int tl, int tr )
{
    printf ( "%d: %d\n", v, t[v] );

    if ( tl != tr )
    {
        int tm = (tl + tr) / 2;
        printree ( t, v*2, tl, tm );
        printree ( t, v*2+1, tm+1, tr );
    }
}
