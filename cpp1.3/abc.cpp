#include <iostream>
#include <cstdio>

int main()
{
    std::puts("please, enter three numbers");
    int a = 0;
    int b = 0;
    int c = 0;
    std::scanf("%d %d %d", &a, &b, &c);
    int d = a + b + c;
    std::printf("solution: %d\n", d);
}