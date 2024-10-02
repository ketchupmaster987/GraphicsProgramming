#include <stdio.h>
#include <iostream>

int add(int a, int b)
{
    return a + b;
}

void print(std::string s)
{
    std::cout << s << std::endl;
}

int main(int args, char ** argv)
{
    int sum = add(1, 2);
    std::cout << sum << std::endl;
    return 0;
}
