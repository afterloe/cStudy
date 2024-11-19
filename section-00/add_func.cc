#include <iostream>

using namespace std;

extern int add(int, int);

int main()
{
    int a, b;
    cout << "step 1: Enter first num" << endl;
    cin >> a;
    cout << "step 2: Enter second num" << endl;
    cin >> b;
    int sum = add(a, b);
    cout << a;
    cout << " + ";
    cout << b;
    cout << " = ";
    cout << sum;
    cout << endl;
    return EXIT_SUCCESS;
}

int add(int a = 1, int b = 1)
{
    return a + b;
}