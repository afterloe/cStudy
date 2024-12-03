#include <iostream>
#include <cstring>

using namespace std;

class Student
{
    friend Student& operator== (Student&, Student&);
    friend ostream& operator<< (ostream&, Student&);
public:
    Student();
    Student(char*& name, const int age);
    virtual void Play();
    ~Student();
    bool operator=(const Student& stu);
private:
    char* name;
    int age;
};


int main()
{
    char name[32] = "ubuntu";
    char* n = name;
    
    Student stu;
    Student stu2(n, 24);
    // stu.Play();
    stu2.Play();
    stu = stu2; // 运算符重载
    stu.Play();

    cout << stu2;
    return EXIT_SUCCESS;
}

Student::Student(): name(NULL), age(0)
{
    
}

Student::Student(char*& name, const int age)
{
    this->name = new char(32);
    strcpy(this->name, name);
    this->age = age;
}

Student::~Student()
{
    if (name != NULL)
    {
        delete name;
        name = NULL;
    }
}



bool Student::operator=(const Student& stu)
{
    if (this->name == NULL)
    {
        this->name = new char(32);
    }
    strcpy(this->name, stu.name);
    this->age = stu.age;
    return true;
}

void Student::Play()
{
    cout << this->name << " is Play" << endl;
}

Student& operator==(Student& stu1, Student& stu2)
{
    return stu1;
}

ostream& operator<<(ostream& os, Student& stu)
{
    os << "name: " << stu.name << " age: " << stu.age << endl;
    return os;
}
