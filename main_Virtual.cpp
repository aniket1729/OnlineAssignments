#include <iostream>
using namespace std;

class Base
{
public:
    int id;
    Base() : id(11) {}
    virtual ~Base() {}
    virtual void DoSome1(void) {};
};

class Same
{
public:
    int id;
    Same() : id(1111) {}
    ~Same() {}
    void DoSome1(void) {};
};

class Derived : public Base
{
public:
    Derived() { id = 22; }
    virtual void DoSome1(void) {};
    virtual void DoSome2(void) {};
};

int main(int argc, char** argv)
{
{
    cout << "int size= " << sizeof(int) << endl;
    cout << "void* size= " << sizeof(void*) << endl;
    cout << "Base size= " << sizeof(Base) << endl;
    cout << "Same size= " << sizeof(Same) << endl;
    cout << "Derived size= " << sizeof(Derived) << endl;
    cout << endl;
}
{
    Same same;
    Base base;
    cout << "BEFORE Same= " << same.id << ", Base= " << base.id << endl;

    int* pSid = (int*)&same;
    int* pBid = (int*)&base;
    *(pSid+0) = 7777;
    *(pBid+0) = 77;
    cout << "AFTER Same= " << same.id << ", Base= " << base.id << endl;
    
    cout << endl;
}
{
    Base base;
    cout << "Base __vptr addr= " << (int*)(&base+0) << endl;
    cout << "Base __vptr val= " << (int*)*(int*)(&base+0) << endl;
    cout << "Base __vptr 1st entry val= " << (int*)*(int*)*(int*)(&base+0) << endl;
    cout << "Base __vptr 1st entry val= " << (int*)*((int*)*(int*)(&base+0)+0) << endl;
    cout << "Base __vptr 2nd entry val= " << (int*)*((int*)*(int*)(&base+0)+1)  << endl;
    cout << endl;
}
{    
    Derived derived;
    cout << "Derived __vptr addr= " << (int*)(&derived+0) << endl;
    Base* pBase = &derived;
    cout << "Derived __vptr addr= " << (int*)(pBase+0) << endl;
    cout << "Derived __vptr val= " << (int*)*(int*)(pBase+0) << endl;
    cout << "Derived __vptr 1st entry val= " << (int*)*(int*)*(int*)(pBase+0) << endl;
    cout << "Derived __vptr 1st entry val= " << (int*)*((int*)*(int*)(pBase+0)+0) << endl;
    cout << "Derived __vptr 2nd entry val= " << (int*)*((int*)*(int*)(pBase+0)+1)  << endl;
    cout << endl;
}
    return 0;
}
