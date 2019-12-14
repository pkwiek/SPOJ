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

void build ( vertex  * t, int * a, int v, int tl, int tr );
void printree ( vertex * t, int v, int tl, int tr );
vertex maxarr ( vertex * t, int v, int tl, int tr, int l, int r);
vertex makedata ( int val );
vertex combine ( vertex l, vertex r );

int main (void)
{
    int n, * arr = NULL, t, * l = NULL, * r = NULL;
    vertex * tree;

    scanf ( "%d", &n );
    arr = (int *) malloc ( n*sizeof(int) );
    tree = (vertex *) malloc ( 4UL*n*sizeof(vertex) );
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
        printf ( "%ld\n", (maxarr ( tree, 1, 0, n-1, l[i]-1, r[i]-1 )).ans );
    }

    free ( r );
    free ( l );
    free ( tree );
    free ( arr );

    return 0;
}


void build ( vertex * t, int * a, int v, int tl, int tr )
{
    if ( tl == tr )
    {
        t[v] = makedata( a[tl] );
    }
    else
    {
        int tm = (tl + tr) / 2;
        build ( t, a, v*2, tl, tm );
        build ( t, a, v*2+1, tm+1, tr );
        t[v] = combine( t[v*2], t[v*2+1] );
    }
    
}

void printree ( vertex * t, int v, int tl, int tr )
{
//    printf ( "%d: ans=%ld, sum=%ld, pref=%ld, suff=%ld\n", v, t[v].ans, t[v].sum, t[v].pref, t[v].suff );

    if ( tl != tr )
    {
        int tm = (tl + tr) / 2;
        printree ( t, v*2, tl, tm );
        printree ( t, v*2+1, tm+1, tr );
    }
}

vertex combine ( vertex l, vertex r )
{
    vertex result;
    result.sum = l.sum + r.sum;
    result.pref = max(l.pref, l.sum + r.pref);
    result.suff = max(r.suff, r.sum + l.suff);
    result.ans = max(max(l.ans, r.ans), l.suff + r.pref);
    return result;
}

vertex makedata ( int val )
{
    vertex result;
    result.pref = result.suff = result.ans = result.sum= val;
    return result;
}

vertex maxarr ( vertex * t, int v, int tl, int tr, int l, int r)
{
    if ( l > r )
    {
        // magic number from description, do not use 0 as it is not the smallest #
        return makedata ( -15007 );
    }
    if ( tl == l && tr == r )
    {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    return combine ( maxarr ( t, v*2, tl, tm, l, min(r,tm) ),
                        maxarr ( t, v*2+1, tm+1, tr, max(tm+1,l), r) );
}
