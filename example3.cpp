#include <iostream>
#include <stdexcept>
#include <memory>

using namespace std;

struct MyError : public logic_error
{
    MyError() : logic_error("Passed d. d is prohibited") {}
};

class Resource
{ 
public:
    void use(const char* N)
    {
//        cout << "Using resource. Passed " << *N << endl;
        if (*N == 'd')
        {
            throw MyError();
        }
    };
};

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
  //      cerr << "You need to pass 1 argument" << endl;
        exit(-1);
    }
    const char* N = argv[1];
    //Resource* rsc = nullptr;
    try
    {
        unique_ptr<Resource> rsc = make_unique<Resource>();
        rsc->use(N);
     //   delete rsc;
    }
    catch (logic_error & e)
    {
     //   delete rsc;
        //cout << e.what() << endl;
    }
    return 0;
}

