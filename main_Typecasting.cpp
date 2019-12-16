#include <iostream>
using namespace std;

void func(int x) { cout << "In func() x= " << x << endl; }

int main(int argc, char** argv)
{
    int a = 123;
    double b = 2.55;

    cout << "Initial a= " << a << ", b= " << b << endl;
    a = b;
    cout << "implicit conversion a= " << a << endl;
    a = (int)b;
    cout << "C style explicit conversion a= " << a << endl;
    a = int(b);
    cout << "C++ style explicit conversion a= " << a << endl;
    cout << endl;

    enum my_numbers { a1=10, a3=100, a5=1000 };
    const my_numbers a2 = static_cast<my_numbers> (50);
    const my_numbers a4 = static_cast<my_numbers> (500);
    cout << "a2= " << a2 << ", a4= " << a4 << endl;
    cout << endl;


    int i = 0x7fff; // Max pos value = 32767
    long l;
    float f;
    cout << "Initial i= " << i << ", l= " << l << ", f= " << f << endl;
  
// Typical castless conversions:
    l = i;
    f = i;
    cout << "castless i= " << i << ", l= " << l << ", f= " << f << endl;
    // Also works:
    l = static_cast<long>(i);
    f = static_cast<float>(i);
    cout << "static_cast Typical i= " << i << ", l= " << l << ", f= " << f << endl;
    cout << endl;

// Narrowing conversions:
    i = l; // May lose digits
    i = f; // May lose info
    cout << "Narrowing i= " << i << ", l= " << l << ", f= " << f << endl;
    // to explicitly eliminates warnings:
    i = static_cast<int>(l);
    i = static_cast<int>(f);
    char c = static_cast<char>(i);
    cout << "static_cast Narrowing i= " << i << ", l= " << l << ", f= " << f << ", c= " << c << endl;
    cout << endl;

// Forcing a void* conversion:
    void* vp = &i;
    // Old way produces a dangerous conversion:
    float* fp = (float*)vp;
    cout << "old cast i= " << i << ", *fp= " << *fp << endl;
    // The new way is equally dangerous:
    fp = static_cast<float*>(vp);
    cout << "static_cast i= " << i << ", *fp= " << *fp << endl;
    cout << endl;

// Implicit type conversions, normally by the compiler:
    double d = 12345.345;
    int x = d; // Automatic type conversion
    cout << "auto conversion d= " << d << ", x= " << x << endl;
    x = static_cast<int>(d); // More explicit
    cout << "static_cast d= " << d << ", x= " << x << endl;
    cout << "auto conversion => ";
    func(d); // Automatic type conversion
    cout << "static_cast => ";
    func(static_cast<int>(d)); // More explicit
    cout << endl;


    {
        const int w = 10;
        int* wp = const_cast <int*> (&w);
        *wp = 20;
        cout << "w= " << w << ", *wp= " << *wp << endl;
    }
    {
        int i = 10;
        const int w = i;
        int* wp = const_cast <int*> (&w);
        *wp = 20;
        cout << "i= " << i << ", w= " << w << ", *wp= " << *wp << endl;
    }
    {
        const int i = 10;
        const int w = i;
        int* wp = const_cast <int*> (&w);
        *wp = 20;
        cout << "i= " << i << ", w= " << w << ", *wp= " << *wp << endl;
    }
    cout << endl;

    return 0;
}
//void func(int x) { cout << "In func() x= " << x << endl; }

