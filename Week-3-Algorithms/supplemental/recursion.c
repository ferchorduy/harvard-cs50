// Factorial

int fact(int n)
{
    if (n <= 1) return 1;
    return n * fact(n-1);
}

// Fibonacci

int fib(int n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fib(n-1) + fib(n-2);
}

// Collatz

int col(int n)
{
    if (n <= 1) return 0;
    if (n % 2 == 0) return col(n/2) + 1;
    return col((3*n)+1) + 1;
}