#include <iostream>
#include <exception>

using namespace std;

class BizException: public exception
{
    public:
        int bizCode;
        string msg;

    public:
        BizException(const string msg, const int code)
        {
            this->bizCode = code;
            this->msg = msg;
        }

        int GetBizeCode()
        {
            return this->bizCode;
        }

        const char* what() const noexcept override
        {
            
            return this->msg.c_str();
        }
};

void t1() {
    cout << "111";
    cout << endl;
    throw BizException("数据库连接失败", 500);
}

int main()
{
    try
    {
        t1();
    }
    catch(const BizException& e)
    {
        cout << e.bizCode << endl;
        cout << e.what();
    }
    return EXIT_SUCCESS;
}