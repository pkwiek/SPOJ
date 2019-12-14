/*
 * =====================================================================================
 *
 *       Filename:  solution.c
 *
 *    Description:  
 *    ACODE - Alphacode
 *    #dynamic-programming
 *    Alice and Bob need to send secret messages to each other and are discussing ways to encode their messages:
 *
 *    Alice: “Let’s just use a very simple code: We’ll assign ‘A’ the code word 1, ‘B’ will be 2, and so on down to ‘Z’ being assigned 26.”
 *
 *    Bob: “That’s a stupid code, Alice. Suppose I send you the word ‘BEAN’ encoded as 25114. You could decode that in many different ways!”
 *    Alice: “Sure you could, but what words would you get? Other than ‘BEAN’, you’d get ‘BEAAD’, ‘YAAD’, ‘YAN’, ‘YKD’ and ‘BEKD’. I think you would be able to figure out the correct decoding. And why would you send me the word ‘BEAN’ anyway?”
 *    Bob: “OK, maybe that’s a bad example, but I bet you that if you got a string of length 5000 there would be tons of different decodings and with that many you would find at least two different ones that would make sense.”
 *    Alice: “How many different decodings?”
 *    Bob: “Jillions!”
 *
 *    For some reason, Alice is still unconvinced by Bob’s argument, so she requires a program that will determine how many decodings there can be for a given string using her code.
 *
 *    Input
 *    Input will consist of multiple input sets. Each set will consist of a single line of at most 5000 digits representing a valid encryption (for example, no line will begin with a 0). There will be no spaces between the digits. An input line of ‘0’ will terminate the input and should not be processed.
 *
 *    Output
 *    For each input set, output the number of possible decodings for the input string. All answers will be within the range of a 64 bit signed integer.
 *
 *    Example
 *    Input:
 *
 *    25114
 *    1111111111
 *    3333333333
 *    0
 *
 *    Output:
 *
 *    6
 *    89
 *    1
 *
 *        Version:  1.0
 *        Created:  12/04/2019 09:50:49 PM
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

long int count ( char * s );

int main (void)
{
    char buffer[5001];
    long int * ans;
    int size;

    ans = (long int *) malloc (sizeof(long int));
    size = 1;

    while ( scanf ( "%[^\n]", buffer ) )
    {
        getchar();
        if ( buffer[0] == '0' )
        {
            break;
        }
        ans[size-1] = count ( buffer );
        ans = (long int *) realloc (ans, ++size * sizeof(long int));
    }

    for ( int i = 0; i < size-1; i++ )
    {
        printf ( "%ld\n", ans[i] );
    }

    return 0;
}

long int count ( char * s )
{
    long int k = 0L, k_1 = 1L, k_2 = 1L;
    int i, res;
    i = strlen ( s ) - 2;

    if ( i == -1 )
    {
        return 1;
    }

    while ( i >= 0 )
    {
        res = s[i+1]-48 + (s[i]-48)*10;
//        printf ( "res = %d\n", res );
        if ( res == 0 || (!(res%10) && res>26) )
        {
            return 0;
        }
        if ( res < 27 && res > 10 && res%10 && s[i+2]!='0')
        {
            k = k_1 + k_2;
        }
        else
        {
            k = k_1;
        }
//        printf ( "k= %ld, k-1= %ld, k-2 = %ld\n", k, k_1, k_2 );
        k_2 = k_1;
        k_1 = k;
        i--;
    }

    return k;
}
