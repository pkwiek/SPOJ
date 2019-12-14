/*
 * =====================================================================================
 *
 *       Filename:  solution.c
 *
 *    Description:  
 *
 *    PRIME1 - Prime Generator
 *    #number-theory
 *    Peter wants to generate some prime numbers for his cryptosystem. Help him! Your task is to generate all prime numbers between two given numbers!
 *
 *    Input
 *    The input begins with the number t of test cases in a single line (t<=10). In each of the next t lines there are two numbers m and n (1 <= m <= n <= 1000000000, n-m<=100000) separated by a space.
 *
 *    Output
 *    For every test case print all prime numbers p such that m <= p <= n, one number per line, test cases separated by an empty line.
 *
 *    Example
 *    Input:
 *    2
 *    1 10
 *    3 5
 *
 *    Output:
 *    2
 *    3
 *    5
 *    7
 *
 *    3
 *    5
 *
 *        Version:  1.0
 *        Created:  11/26/2019 10:05:16 AM
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
#include <string.h>

#define PUSHBACK(arr,elem,currsize)                                             \
    {                                                                           \
        if (currsize && !(currsize&(currsize-1)))                               \
        {                                                                       \
            arr=(__typeof__(elem)*)realloc(arr,2UL*currsize*sizeof(elem));      \
        }                                                                       \
        else if (!currsize)                                                     \
        {                                                                       \
            arr=(__typeof__(elem)*)malloc(sizeof(elem));                        \
        }                                                                       \
        arr[currsize]=elem;                                                     \
        ++currsize;                                                             \
    }                                                                           \

typedef struct 
{
    unsigned long * arr;
    int size;
} array;

void simpleSieve ( unsigned long limit, array * primes );
void rangeSieve ( unsigned long ll, unsigned long hl, array * primes );

//void segmentedSieve ( int limit );


int main (void)
{
    unsigned long m[10], n[10], t;
    unsigned long i, j;

    scanf ( "%lu", &t );

    for ( i = 0; i < (unsigned long) t; i++ )
    {
        scanf ( "%lu%lu", &m[i], &n[i] );
    }

    array p;
    p.arr = NULL;
    p.size = 0;

    simpleSieve ( sqrt(1000000000), &p );

    for ( j = 0; j < (unsigned long) t; j++ )
    {

        rangeSieve (m[j],n[j],&p);
        printf ( "\n" );
    }

    free ( p.arr );

    return 0;
}

void simpleSieve ( unsigned long limit, array * primes )
{
    unsigned long i, j;
    char * mark = (char *) malloc ( sizeof(char) * (limit + 1) );
    memset ( mark, 1, (limit+1)*sizeof(char) );

    for ( i = 2; i*i <= limit; i++ )
    {
        if ( mark[i] )
        {
            for ( j = 2 * i; j <= limit; j += i )
            {
                mark[j] = 0;
            }
        }
    }

    for ( i = 2; i <= limit; i++ )
    {
        if ( mark[i] )
        {
            PUSHBACK(primes->arr,i,primes->size);
        }
    }

    free ( mark );
}

void rangeSieve ( unsigned long ll, unsigned long hl, array * primes )
{
    unsigned long i, j;
    unsigned long limit = hl - ll + 1;
    char * mark = (char *) malloc ( sizeof(char) * (limit) );
    memset ( mark, 1, (limit)*sizeof(char) );
    unsigned long primell;

    for ( i = 0; i < (unsigned long) primes->size; i++ )
    {
            primell = floor(ll/primes->arr[i]) * primes->arr[i];
            if (primell < ll)
            {
                primell += primes->arr[i];
            }
            if (primell <= primes->arr[i])
            {
                primell = 2*primes->arr[i];
            }
            for ( j = primell; j <= hl; j += primes->arr[i] )
            {
                mark[j-ll] = 0;
//                printf ( "i=%lu,j=%lu,mark=%lu\n", i,j,j-ll );
            }
    }
    if ( ll == 1 )
    {
        mark[0] = 0;
    }

    for ( i = 0; i < limit; i++ )
    {
        if ( mark[i] )
        {
            printf ( "%lu\n", i + ll );
        }
    }

    free ( mark );
}

void segmentedSieve ( int low, int high )
{
    int range  = high - low + 1;
    int i, j, limit= 0;
    array primes;
    primes.arr = NULL;
    primes.size = 0;

    simpleSieve ( limit, &primes );

    int ll = low;
    int hl = 2*limit;

    char * mark = (char *) malloc ( sizeof(char) * (limit + 1) );
    while ( ll < low )
    {
        memset ( mark, 1, (limit + 1)*sizeof(char) );

        
        for ( i = 0; i < primes.size; i++ )
        {
            int primell = floor(ll/primes.arr[i]) * primes.arr[i];
            
            if ( primell < ll )
            {
                primell += primes.arr[i];
            }
        
            for ( j = primell; j <= hl; j += primes.arr[i] )
            {
                mark[j-ll] = 0;
            }
        }

        for ( i = ll; i <= hl; i++ )
        {
            if ( mark[i-ll] )
            {
                printf ( "%d\n", i );
            }
        }
        
        ll += limit;
        hl += limit;
    }

    free ( mark );
}
