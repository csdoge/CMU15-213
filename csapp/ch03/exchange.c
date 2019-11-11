#include<stdio.h>

long exchange(long *xp, long y)
{
    long x = *xp;
    *xp = y;
    y = x;
    printf("After exchange, the value of *xp is %ld, the value of y is %ld\n", *xp, y);
    return x;
}

int main()
{
    long xp = 10;
    long y = 15;
    long t = exchange(&xp, y);
    printf("The value of x is %ld, the value of xp is %ld, the value of y is %ld\n", t, xp, y);
    // The value of xp has changed
    return 0;
}