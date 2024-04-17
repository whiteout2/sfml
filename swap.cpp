#include <iostream>

void swap1(int x, int y)
{
    int z = x;
    x = y;
    y = z;
}

void swap2(int *x, int *y)
{
    int z = *x;
    *x = *y;
    *y = z;
}

void swap3(int& x, int& y)
{
    int z = x;
    x = y;
    y = z;
}
 
// Driver Code
int main()
{
    int a = 33, b = 66;

    std::cout << "Before Swap\n";
    std::cout << "a = " << a << " b = " << b << "\n";
 
    swap1(a, b);
 
    std::cout << "After Swap with pass by value\n";
    std::cout << "a = " << a << " b = " << b << "\n";

    a = 33, b = 66;

    std::cout << "Before Swap\n";
    std::cout << "a = " << a << " b = " << b << "\n";
 
    swap2(&a, &b);
 
    std::cout << "After Swap with pass by pointer\n";
    std::cout << "a = " << a << " b = " << b << "\n";

    a = 33, b = 66;

    std::cout << "Before Swap\n";
    std::cout << "a = " << a << " b = " << b << "\n";
 
    swap3(a, b);
 
    std::cout << "After Swap with pass by reference\n";
    std::cout << "a = " << a << " b = " << b << "\n";
}