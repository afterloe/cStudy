#include <iostream>
#include <cstring>

using namespace std;

typedef struct _p
{
    char* name;
    int age;

    void print(struct _p *);

} Persion;

int main()
{
    Persion * persion = NULL;
    persion = new Persion();
    persion->name = new char(32);
    cout << "input persion name: ";
    cin >> persion->name;
    cout << "input age: ";
    cin >> persion->age;
    persion->print(persion);
    delete persion->name;
    delete persion;

    return EXIT_SUCCESS;
}

void Persion::print(struct _p * ptr)
{
    cout << "your name: " << ptr->name << endl;
    cout << "age is:" << ptr->age << endl;
}