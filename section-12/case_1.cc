#include <iostream>

using namespace std;

template<class T>
void swapOne(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

class Person
{
    friend ostream& operator<< (ostream&, Person&);
public:
    Person(string name, int age)
    {
        this->name = name;
        this->age = age;
    }

    string name;
    int age;
};

/**
 * 指定对象进行 模板适配  进行交换
 */
template<>void swapOne<Person>(Person& a, Person& b)
{
    string nameT;
    int ageT;

    nameT = a.name;
    a.name = b.name;
    b.name = nameT;

    // TODO
}

int main()
{
    int a = 10, b = 20;
    cout << a << " " << b << endl;
    swapOne(a, b);
    cout << a << " " << b << endl;

    Person c("a", 10), d("b", 12);
    cout << c << endl;
    cout << d << endl;

    swapOne(c, d);
    cout << c << endl;
    cout << d << endl;
    return EXIT_SUCCESS;
}

ostream& operator<<(ostream& out, Person& p)
{
    out << p.name << " - " << p.age;
    return out;
}
