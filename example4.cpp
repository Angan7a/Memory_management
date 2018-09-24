//#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

struct Resource
{
    Resource(char* byte) : byte_(byte) {}
    char* byte() const { return byte_; }
    virtual string name() const = 0;
    virtual ~Resource() { delete byte_; }

protected:
    char* byte_ = nullptr;
};

struct ResourceA : Resource
{
    ResourceA(char* byte) : Resource(byte) {}
    string name() const override { return string("ResourceA ").append(byte_); }
};

struct ResourceB : Resource
{
    ResourceB(char* byte) : Resource(byte) {}
    string name() const override { return string("ResourceB ").append(byte_); }
};

struct ResourceFactory
{ 
    auto makeResourceA(char* byte) { return make_shared<ResourceA>(byte); }
    auto makeResourceB(char* byte) { return make_shared<ResourceB>(byte); }
};

struct ResourceCollection
{
    void add(shared_ptr<Resource> r) { resources.push_back(r); }
    void clear() { resources.clear(); }
    shared_ptr<Resource> operator[](int index) { return resources[index]; }
    void printAll()
    {
        for (const auto & res : resources)
        {
 //           cout << res->name() << endl;
        }
    }
    void erase(int index)
    {
        resources.erase(resources.begin() + index);
    }

private:
    vector<shared_ptr<Resource>> resources;
};

int main()
{
    ResourceCollection collection;
    ResourceFactory rf;
    collection.add(rf.makeResourceA(new char{0x01}));
    collection.add(rf.makeResourceB(new char{0x02}));
    collection.printAll();

    collection.erase(1);
    auto firstByte = collection[0]->byte();
    collection.clear();
 //   cout << *firstByte << endl;

    return 0;
}

