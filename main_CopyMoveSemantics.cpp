#include <iostream>
#include <cstring>
using namespace std;

class MyDevice
{
public:
    char name[10];
    MyDevice(void) { strcpy(name, ""); cout << "MyDevice::ctor() this= " << this << ", name= " << name << "." << endl; }
    ~MyDevice(void) { cout << "MyDevice::dtor() this= " << this << ", name= " << name << "." << endl; strcpy(name, "DELETED"); }

    MyDevice(const char* str) { strcpy(name, str); cout << "MyDevice::ctor() this= " << this << ", name= " << name << "." << endl; }

    MyDevice(const MyDevice& cp_dev)
    {
        cout << "MyDevice::cpctor() cp_dev= " << &cp_dev << ", cp_name= " << cp_dev.name << ", this= " << this << ", name= " << name << endl;
        strcpy(name, cp_dev.name);
    }


    MyDevice& operator=(const MyDevice& cp_dev) { cout << "MyDevice::assign() cp_dev= " << &cp_dev << ", this= " << this << endl; }

    MyDevice(const MyDevice&& mv_dev) { cout << "MyDevice::mvctor() mv_dev= " << &mv_dev << ", this= " << this << endl; }
    MyDevice& operator=(const MyDevice&& mv_dev) { cout << "MyDevice::move() mv_dev= " << &mv_dev << ", this= " << this << endl; }
};

void func_arg_val(MyDevice dev)    //call Copy ctor and so dtor called after scope end after func
{
    cout << "func_arg_val() dev= " << &dev << endl;
};

void func_arg_ref(MyDevice& dev)    //
{
    cout << "func_arg_ref() dev= " << &dev << endl;
};

MyDevice func_ret_val_local(void)
{
    MyDevice dev("RetLocVal");
    cout << "func_ret_val_local() dev= " << &dev << ", dname= " << dev.name << "." << endl;
    return dev;    //return as Reference and so dtor not called

// copy elision is permitted -> like return statement in a function with a class return type. Object being return is treated as a rvalue. Due to RVO (Return Value Optimization), std::move is implicitly applied to Local objects being returned.
};

MyDevice& func_ret_ref(void)
{
    MyDevice dev("RetLocRef");
    cout << "func_ret_ref() dev= " << &dev << ", dname= " << dev.name << "." << endl;
    return dev;
//dtor for Local, which may lead ISSUE
// if assignment then additional Copy ctor of reference passed
};

MyDevice func_arg_ref_ret_val(MyDevice& dev)
{
    cout << "func_arg_ref_ret_val() dev= " << &dev << ", dname= " << dev.name << "." << endl;
    return dev;
//if assignment then additional Copy ctor called here, as usual
};

int main(int argc, char** argv)
{
    {
        cout << "Simple object" << endl;
        MyDevice dev1("simple");
        cout << "dev1= " << &dev1 <<", dname1= " << dev1.name << "." << endl;
        cout << "END" << endl;
    }
    cout << endl;

    {
        cout << "Argument pass by value" << endl;
        MyDevice dev1("PassVal");
        cout << "dev1= " << &dev1 <<", dname1= " << dev1.name << "." << endl;
        func_arg_val(dev1);
        cout << "END" << endl;
    }
    cout << endl;

    {
        cout << "Argument pass by reference" << endl;
        MyDevice dev1("PassRef");
        cout << "dev1= " << &dev1 <<", dname1= " << dev1.name << "." << endl;
        func_arg_ref(dev1);
        cout << "END" << endl;
    }
    cout << endl;

    {
        cout << "Return pass by value local" << endl;
        MyDevice dev1 = func_ret_val_local();
        cout << "dev1= " << &dev1 <<", dname1= " << dev1.name << "." << endl;
        cout << "END" << endl;
    }
    cout << endl;

    {
        cout << "Return pass by reference" << endl;
        MyDevice dev1 = func_ret_ref();
        //MyDevice dev1; func_ret_ref();
        cout << "dev1= " << &dev1 <<", dname1= " << dev1.name << "." << endl;
        cout << "END" << endl;
    }
    cout << endl;

    {
        cout << "Return pass by value non-local" << endl;
        MyDevice dev1("RetNoLoVal");
        cout << "dev1= " << &dev1 <<", dname1= " << dev1.name << "." << endl;
        MyDevice dev2 = func_arg_ref_ret_val(dev1);
        //MyDevice dev2; func_arg_ref_ret_val(dev1);
        cout << "dev2= " << &dev2 <<", dname2= " << dev2.name << "." << endl;
        cout << "END" << endl;
    }
    cout << endl;

    return 0;
}
