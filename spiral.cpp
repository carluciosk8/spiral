/***************************************************************************
    Original code written in: May 2008    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "spiral.h"

#include <cmath>


void get_point_n(int n, int& x, int& y)
{
    x = 0;
    y = 0;

    int incx = 0;
    int incy = 1;

    int len = 1;
    int c = 0;

    for (int i = 0; i < n; i++)
    {
        x += incx;
        y += incy;
        c++;

        if (c == len)
        {
            incx = -1;
            incy = 0;
        }
        else
        if (c == 2*len)
        {
            incx = 0;
            incy = -1;
        }
        else
        if (c == 3*len + 1)
        {
            incx = 1;
            incy = 0;
        }
        else
        if (c == 4*len + 2)
        {
            c = 0;
            len += 2;
            incx = 0;
            incy = 1;
        }
    }
}



void get_point_sqrtn(int n, int& x, int& y)
{
    int base = sqrtf(n);
    int half = (base + 1)/2;
    int sign = powf(-1, base % 2);

    x = sign * (-half) - 1*(base % 2);
    y = sign * (-half);

    for (int i = 0; i < (n-base*base); i++)
    {
        x += (i <  2*half - 1*(base % 2)) ? sign : 0;
        y += (i >= 2*half - 1*(base % 2)) ? sign : 0;
    }
}



void get_point_1(int n, int& x, int& y)
{
    int base  = sqrtf(n);
    int half  = (base + 1)/2;
    int length  = 2*half;
    int delta = (n - base*base + (base % 2));
    int sign  = powf(-1, base % 2);
    int dx    = ( delta <= length ) ? delta : length;
    int dy    = ( delta <= length ) ? 0 : (delta - length);

    x = sign * (-half + dx);
    y = sign * (-half + dy);
}



int get_x(int n)
{
    return powf(-1, int(sqrtf(n)) % 2) *(-(int(sqrtf(n)) + 1)/2 +(n - int(sqrtf(n))*int(sqrtf(n)) + int(sqrtf(n)) % 2 <= 2*((int(sqrtf(n)) + 1)/2) ? (n - int(sqrtf(n))*int(sqrtf(n)) + (int(sqrtf(n)) % 2)) : 2*((int(sqrtf(n)) + 1)/2)));
}



int get_y(int n)
{
    return powf(-1, int(sqrtf(n)) % 2) * (-(int(sqrtf(n)) + 1)/2 + (( (n - int(sqrtf(n))*int(sqrtf(n)) + (int(sqrtf(n)) % 2)) <= 2*((int(sqrtf(n)) + 1)/2) ) ? (0) : ((n - int(sqrtf(n))*int(sqrtf(n)) + (int(sqrtf(n)) % 2)) - 2*((int(sqrtf(n)) + 1)/2))));
}



bool is_prime(int n)
{
    if (n <= 3)
    {
        return n > 1;
    }
    if (n % 2 == 0 || n % 3 == 0)
    {
        return false;
    }
    for (int i = 5; i < sqrtf(n) + 1; i += 6)
    {
        if (n % i == 0 || n % (i+2) == 0)
        {
            return false;
        }
    }

    return true;
}
