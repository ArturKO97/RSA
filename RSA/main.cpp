//
//  main.cpp
//  RSA
//
//  Created by Artur Kozych on 22.04.2020.
//  Copyright © 2020 Artur Kozych. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

bool isPrime( long int prime)
{
    long int i, j;
    
    j = (long int)sqrt((long double)prime);
    
    for ( i = 2; i <= j; i++)
    {
        if ( prime % i == 0 )
        {
            return false;
        }
    }
    return true;
}

void rightInputPrime(long int& outPrime, char name)
{
    bool isRightInput;
    do
    {
        std::cout << "Enter a Prime number \'" << name << "\' : ";
        std::cin >> outPrime;
        isRightInput = isPrime( outPrime );
        
        if (!isRightInput)
        {
            std::cout << "\nWrong input\nTry again...\n" << std::endl;
        }
    } while (!isRightInput);
}

long int greatestCommonDivisor(long int e, long int t)
{
    while ( e > 0 )
    {
        long int tmp;
        tmp = e;
        e = t % e;
        t = tmp;
    }
    return t;
}

long int calculateE( long int t )
{
    long int e;
    for ( e = 2; e < t; e++ )
    {
        if (greatestCommonDivisor( e, t ) == 1 )
        {
            return e;
        }
    }
    return -1;
}

long int calculateD( long int e, long int t)
{
    long int d;
    long int k = 1;
    while (k % e != 0)
    {
        k = k + t;
    }
    d = (k / e);
    return d;
}

long int encrypt( long int i, long int e, long int n )
{
    long int current = i - 97;
    long int result = 1;
    for ( long int j = 0; j < e; j++ )
    {
        result = result * current;
        result = result % n;
    }
    return result;
}

long int decrypt(long int i, long int d, long int n)
{
    long int current = i;
    long int result = 1;
    for ( long int j = 0; j < d; j++ )
    {
        result = result * current;
        result = result % n;
    }
    return result + 97;
}

int main()
{
    long int p, q, n, t, e, d;
    long int encryptedMessage[80];
    memset(encryptedMessage, 0, sizeof(encryptedMessage));
    long int decryptedMessage[80];
    memset(decryptedMessage, 0, sizeof(decryptedMessage));
    
    std::cout << "Hello, it's RSA\n";
    
    rightInputPrime(p, 'p');
    rightInputPrime(q, 'q');
    
    n = p * q;
    std::cout << "\nn = p*q = " << n << "\n";
    
    t = ( p - 1 ) * ( q  - 1 );
    std::cout << "Euler's totient function:\t t = " << t << std::endl;
    
    e = calculateE(t);
    d = calculateD(e, t);

    std::cout << "\nRSA public key is (n = " << n << ", e = " << e << ")\n";
    std::cout << "RSA private key is (n = " << n << ", d = " << d << ")\n";
    std::cout << "\nEnter Message to be encryped:\n";

    std::string message;
    std::cin >> message;
    std::cout << "\nThe message is: " << message << std::endl;
    
    // Encryption:
    for (long int i = 0; i < message.length(); i++)
    {
        encryptedMessage[i] = encrypt( message[i], e, n);
    }
    
    std::cout << "\nEncripted message:\n";
    for ( long int i = 0; i < message.length(); i++ )
    {
        printf( "%c", (char)encryptedMessage[i] );
    }
    
    for (long int i = 0; i < message.length(); i++)
    {
        decryptedMessage[i] = decrypt(encryptedMessage[i], d, n);
    }
    
    std::cout << "\n\nDecrypted message:" << std::endl;
    for (long int i = 0; i < message.length(); i++)
    {
        printf( "%c", (char)decryptedMessage[i] );
    }
    
    std::cout << "\n";
    return 0;
}
