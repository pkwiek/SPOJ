/*
 * =====================================================================================
 *
 *       Filename:  solution.c
 *
 *    Description: 
 *    AGGRCOW - Aggressive cows
 *    #binary-search
 *    Farmer John has built a new long barn, with N (2 <= N <= 100,000) stalls. The stalls are located along a straight line at positions x1..,xN (0 <= xi <= 1,000,000,000).
 *
 *    His C (2 <= C <= N) cows don't like this barn layout and become aggressive towards each other once put into a stall. To prevent the cows from hurting each other, FJ wants to assign the cows to the stalls, such that the minimum distance between any two of them is as large as possible. What is the largest minimum distance?
 *    Input
 *    t – the number of test cases, then t test cases follows.
 *    * Line 1: Two space-separated integers: N and C
 *    * Lines 2..N+1: Line i+1 contains an integer stall location, xi
 *    Output
 *    For each test case output one integer: the largest minimum distance.
 *    Example
 *    Input:
 *
 *    1
 *    5 3
 *    1
 *    2
 *    8
 *    4
 *    9
 *    Output:
 *
 *    3
 *    Output details:
 *
 *    FJ can put his 3 cows in the stalls at positions 1, 4 and 8,
 *    resulting in a minimum distance of 3. 
 *
 *        Version:  1.0
 *        Created:  11/29/2019 07:44:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  PAWEL KWIEK (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int binSearch ( int c, int numSt, int * stalls );
int isPossible ( int dist, int c, int numSt, int * stalls);
int cmpf ( const void * a, const void *b );

int main (void)
{
    int t;
    int * n, * c, ** stalls;

    scanf ( "%d", &t );
    stalls = (int **) malloc ( t*sizeof(int *) );
    n = (int *) malloc ( t*sizeof(int) );
    c = (int *) malloc ( t*sizeof(int) );
    for ( int i = 0; i < t; i++ )
    {
        scanf ( "%d%d", &n[i], &c[i] );
        stalls[i] = (int *) malloc ( n[i]*sizeof(int) );
        for ( int j = 0; j < n[i]; j++ )
        {
            scanf ( "%d", &stalls[i][j] );
        }
    }

    for ( int i = 0; i < t; i++ )
    {
        qsort ( stalls[i], n[i], sizeof(int), cmpf );
        printf ( "%d\n", binSearch ( c[i], n[i], stalls[i] ) );
    }

    free ( n );
    free ( c );
    for ( int i = 0; i < t; i++ )
    {
        free ( stalls[i] );
    }
    free ( stalls );

    return 0;
}

int cmpf ( const void * a, const void * b )
{
    return (*(int *)a > *(int *)b) - (*(int *)a < *(int *)b);
}

int binSearch ( int c, int numSt, int * stalls )
{
    int low, high, mid;

    low = 0;
    high = stalls[numSt-1];
    while ( low != high)
    {
        mid = ceil( (low + high) / 2.0 );
//        printf ( "low = %d, mid = %d, high = %d\n", low, mid, high );
        if ( isPossible ( mid, c, numSt, stalls ) )
        {
            low = mid;
        }
        else
        {
            high = mid - 1;
        }
    }
    
    return low;
}

int isPossible ( int dist, int c, int numSt, int * stalls)
{
    for ( int i = 0, cur_cows = 1, last = stalls[0]; i < numSt; i++ )
    {
        if ( (stalls[i] - last) >= dist )
        {
            last = stalls[i];
            if ( ++cur_cows == c )
            {
                return 1;
            }
        }
    }
    return 0;
}
