/*
 * =====================================================================================
 *
 *       Filename:  solution_segment_tree.c
 *
 *    Description:  
 *    INVCNT - Inversion Count
 *    #graph-theory #number-theory #shortest-path #sorting #bitmasks
 *    Let A[0...n - 1] be an array of n distinct positive integers. If i < j and A[i] > A[j] then the pair (i, j) is called an inversion of A. Given n and an array A your task is to find the number of inversions of A.
 *
 *    Input
 *    The first line contains t, the number of testcases followed by a blank space. Each of the t tests start with a number n (n <= 200000). Then n + 1 lines follow. In the ith line a number A[i - 1] is given (A[i - 1] <= 10^7). The (n + 1)th line is a blank space.
 *
 *    Output
 *    For every test output one line giving the number of inversions of A.
 *
 *    Example
 *    Input:
 *    2
 *
 *    3
 *    3
 *    1
 *    2
 *
 *    5
 *    2
 *    3
 *    8
 *    6
 *    1
 *
 *
 *    Output:
 *    2
 *    5
 *
 *        Version:  1.0
 *        Created:  12/07/2019 03:06:06 PM
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
#include <string.h>

#define MAX_LEN 512000 // power of 2 greater than 2*200000 (max n)

typedef struct Tree Tree;
struct Tree
{
    int base;
    long long int * ver;
};

void build ( Tree * tree, int n ); 
void update ( Tree  * tree, int val ); 
long long int query ( Tree * tree, int v, int l, int r, int tl, int tr );
void print ( Tree * tree, int v, int l, int r, int tl, int tr );

int main (void)
{
    Tree tree;
    tree.base = 0;
    long long int * arr;
    arr = (long long int *) malloc ( 35000000 * sizeof(long long int));
    tree.ver = arr;
    int tc, n, new_val;
    long long int * ans, result;

    scanf ( "%d", &tc );
    ans = (long long int *) malloc ( tc*sizeof(long long int) );
    for ( int i = 0; i < tc; i++ )
    {
        scanf ( "%d", &n );
        build ( &tree, 10000000 );
        result = 0;
        for ( int j = 0; j < n; j++ )
        {
            scanf ( "%d", &new_val );
            // array is A={1..n} 
            result += query ( &tree, 1, new_val-1, (1<<tree.base)-1, 0, (1<<tree.base)-1); 
            update ( &tree, new_val );
        }
//        print ( &tree, 1, 0, (1<<tree.base)-1, 0, (1<<tree.base)-1);
        ans[i] = result;
    }

    for ( int i = 0; i < tc; i++ )
    {
        printf ( "%lld\n", ans[i] );
    }


    return 0;
}

void build ( Tree * tree, int n)
{
    int i;

    for ( i = 0; n > 0; i++ )
    {
        n >>= 1;
    }
    tree->base = i;


    memset ( tree->ver, 0, (1<<(tree->base+1))*sizeof(long long int) ); 
//    printf ( "Memset: %lu\n", (1<<(tree->base+1))*sizeof(int) );
//    printf ( "base: %d\n", i );
}

void update ( Tree * tree, int val)
{
    // since there are only positive integers, 0 is not needed in the array
    for ( int node = (1<<tree->base) + val - 1; node > 0; node>>=1 ) 
    {
        (tree->ver)[node]++;
//        printf ( "update: %d\n", node );
    }
}

long long int query ( Tree * tree, int v, int l, int r, int tl, int tr )
{
    if ( r==tr && l==tl )
    {
        return (tree->ver)[v];
    }
    int tm = (tr+tl)>>1;
    if ( r <= tm )
    {
        return query ( tree, (v<<1), l, r, tl, tm ); 
    }
    else if ( l > tm )
    {
        return query ( tree, (v<<1)|1, l, r, tm+1, tr);
    }
    else
    {
        return query ( tree, (v<<1), l, tm, tl, tm )
                + query ( tree, (v<<1)|1, tm+1, r, tm+1, tr);
    }
    
}

void print ( Tree * tree, int v, int l, int r, int tl, int tr )
{
    printf ( "v= %d, val = %ld\n", v, (tree->ver)[v] );
    if ( tl != tr )
    {
        int tm = (tr+tl)>>1;
        print ( tree, v*2, l, r, tl, tm );
        print ( tree, v*2+1, l, r, tm+1, tr );
    }
}
