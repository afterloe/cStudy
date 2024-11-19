#include <iostream>
#include <iomanip>

using namespace std;

typedef int INT32;

int main(int argc, char** args) {
    INT32 num = 103;
    cout << "十进制 " << num << endl;
    cout << "八进制 " << oct << num << endl;
    cout << "十六进制 " << hex << num << endl;
    return EXIT_SUCCESS;
}
