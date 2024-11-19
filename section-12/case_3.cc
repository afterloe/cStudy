#include <iostream>
#include <fstream>

using namespace::std;

int main(int argc, char** argv)
{
    ifstream ism;
    ism.open("../case_3.cc", ios::in);
    if (!ism)
    {
        cout << "open failed" << endl;
        exit(EXIT_FAILURE);
    }

    char chunk[1500] = {0};
    while(!ism.eof())
    {
        ism.getline(chunk, 1500);
        cout << chunk << endl;
    }

    ism.close();


    return EXIT_SUCCESS;
}