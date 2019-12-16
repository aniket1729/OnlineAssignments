#include <iostream>
using namespace std;

#define AUTO_PTR   0
#define UNIQUE_PTR 1    //with -std=c++11
#define SHARED_PTR 2    //with/without -std=c++11
#define WEAK_PTR   3
//NOTE: enum not available at compile time

#define SMART_PTR  2

class MyClass
{
public:
    MyClass() { cout << "MyClass::ctor() this= " << this << endl; }
    ~MyClass() { cout << "MyClass::dtor() this= " << this << endl; }

    void DoSomething(void) { cout << "DoSomething() this= " << this << endl; }
};

#if SMART_PTR == AUTO_PTR

  #include <memory>
  using namespace std;
 
  typedef std::auto_ptr<MyClass> MyClassAuto;

  void func1_arg(MyClassAuto smart_ptr1) {
    cout << "func1_arg() ptr= " << smart_ptr1.get() << "." << endl;
  }

  void func2_refarg(MyClassAuto& smart_ptr1) {
    cout << "func2_refarg() ptr= " << smart_ptr1.get() << "." << endl;
  }

  MyClassAuto func3_ret(void) {
    MyClassAuto p1(new MyClass());
    cout << "func3_ret() p1 ptr= " << p1.get() << "." <<  endl;
    return p1;
  }

  MyClassAuto func4_refarg_ret(MyClassAuto& smart_ptr1) {
    cout << "func4_refarg_ret() ptr= " << smart_ptr1.get() << "." << endl;
    return smart_ptr1;
    //return move(smart_ptr1);
  }

  int main(int argc, char** argv)
  {
    cout << "Begin auto_ptr" << endl;
    cout << endl;

    {
        cout << "p1 START" << endl;
        MyClassAuto p1(new MyClass());
        cout << "p1 ptr= " << p1.get() << "." <<  endl;
        p1->DoSomething();
        cout << "p1 END " << endl;
    }
    cout << endl;

  //auto_ptr Strict Ownership
    {
        cout << "p1 START" << endl;
        MyClassAuto p1(new MyClass());
        cout << "p1 ptr= " << p1.get() <<  endl;
        p1->DoSomething();


        cout << "p2 START" << endl;
        MyClassAuto p2(p1);    //IMPLICITLY or silently transfer ownership
        cout << "p1 ptr= " << p1.get() << ", p2 ptr= " << p2.get() << "."  <<  endl;
        p2->DoSomething();

        cout << "p1 & p2 END " << endl;
    }
    cout << endl;

    {
        cout << "p1 START" << endl;
        MyClassAuto p1(new MyClass());
        cout << "Before passing by value p1 ptr= " << p1.get() << "." <<  endl;
        func1_arg(p1);    //same effect for move() on auto_ptr    func1_arg(move(p1));
        cout << "After p1 ptr= " << p1.get() << "." <<  endl;
        cout << "p1 END " << endl;
    }
    cout << endl;

    {
        cout << "p1 START" << endl;
        MyClassAuto p1(new MyClass());
        cout << "Before passing by reference p1 ptr= " << p1.get() << "." <<  endl;
        func2_refarg(p1);    //Passing by reference
        cout << "After p1 ptr= " << p1.get() << "." <<  endl;
        cout << "p1 END " << endl;
    }
    cout << endl;

    {
        cout << "p1 START" << endl;
        //auto => MyClassAuto
        auto p1 = func3_ret();
        cout << "After p1 ptr= " << p1.get() << "." <<  endl;
        cout << "p1 END " << endl;
    }
    cout << endl;

    {
        cout << "p1 START" << endl;
        MyClassAuto p1(new MyClass());
        cout << "p2 START Before p1 ptr= " << p1.get() << "." <<  endl;
        auto p2 = func4_refarg_ret(p1);    // auto => MyClassAuto
        cout << "After p1 ptr= " << p1.get() << ", p2 ptr= " << p2.get() << "."  <<  endl;
        cout << "p1 & p2 END " << endl;
    }
    cout << endl;

    cout << "Finish" << endl;
    return 0;
  }

#elif SMART_PTR == UNIQUE_PTR 

  #include <memory>
  using namespace std;
 
  typedef unique_ptr<MyClass> MyClassUnique;    //with -std=c++11

  void func1_arg(MyClassUnique smart_ptr1) {
    cout << "func1_arg() ptr= " << smart_ptr1.get() << "." << endl;
  }

  void func2_refarg(MyClassUnique& smart_ptr1) {
    cout << "func2_refarg() ptr= " << smart_ptr1.get() << "." << endl;
  }

  MyClassUnique func3_ret(void) {
    MyClassUnique p1(new MyClass());
    cout << "func3_ret() p1 ptr= " << p1.get() << "." <<  endl;
    return p1;    //OK for local unique_ptr, not to use move()
  }

  MyClassUnique func4_refarg_ret(MyClassUnique& smart_ptr1) {
    cout << "func4_refarg_ret() ptr= " << smart_ptr1.get() << "." << endl;
    //return smart_ptr1;    //COMPILE ERROR non-local unique_ptr needs to use move()
    return move(smart_ptr1);
  }

  int main(int argc, char** argv)
  {
    cout << "Begin unique_ptr" << endl;
    cout << endl;

    {
        cout << "p1 START" << endl;
        MyClassUnique p1(new MyClass());
        cout << "p1 ptr= " << p1.get() << "." <<  endl;
        p1->DoSomething();
        cout << "p1 END " << endl;
    }
    cout << endl;

  //unique_ptr Explicit Transfer Ownership
    {
        cout << "p1 START" << endl;
        MyClassUnique p1(new MyClass());    //NOTE: = std::make_unique<MyClass>(); only with -std=c++1y or c++14 in GCC5
        cout << "p1 ptr= " << p1.get() <<  endl;
        p1->DoSomething();


        cout << "p2 START" << endl;
        MyClassUnique p2(move(p1));
        //MyClassUnique p3;        p3 = move(p1);    Compile OK

        //MyClassUnique p3(p1);                      Compile ERR
        //MyClassUnique p4;        p4 = p1;          Compile ERR

        cout << "p1 ptr= " << p1.get() << ", p2 ptr= " << p2.get() << "."  <<  endl;
        p2->DoSomething();

        cout << "p1 & p2 END " << endl;
    }
    cout << endl;

    {
        cout << "p1 START" << endl;
        MyClassUnique p1(new MyClass());
        cout << "Before passing by value p1 ptr= " << p1.get() << "." <<  endl;
        //func1_arg(p1);    Compile ERR    Passing by Value, implies making a copy. That wouldn't be unique.
        func1_arg(move(p1));    //EXPLICITLY implies passing Ownership
        cout << "After p1 ptr= " << p1.get() << "." <<  endl;
        cout << "p1 END " << endl;
    }
    cout << endl;

    {
        cout << "p1 START" << endl;
        MyClassUnique p1(new MyClass());
        cout << "Before passing by reference p1 ptr= " << p1.get() << "." <<  endl;
        func2_refarg(p1);    //Passing by reference
        cout << "After p1 ptr= " << p1.get() << "." <<  endl;
        cout << "p1 END " << endl;
    }
    cout << endl;

    {
        cout << "p1 START" << endl;
        //auto => MyClassUnique
        auto p1 = func3_ret();    //for certain criteria -> copy elision is permitted -> like return statement in a function with a class return type. Object being return is treated as a rvalue. Due to RVO (Return Value Optimization), std::move is implicitly applied to Local objects being returned.
        cout << "After p1 ptr= " << p1.get() << "." <<  endl;
        cout << "p1 END " << endl;
    }
    cout << endl;
    /* Reference 1: https://stackoverflow.com/questions/4316727/returning-unique-ptr-from-functions
       Reference 2: https://code-examples.net/en/q/41de37 */

    {
        cout << "p1 START" << endl;
        MyClassUnique p1(new MyClass());
        cout << "p2 START Before p1 ptr= " << p1.get() << "." <<  endl;
        auto p2 = func4_refarg_ret(p1);    // auto => MyClassUnique
        cout << "After p1 ptr= " << p1.get() << ", p2 ptr= " << p2.get() << "."  <<  endl;
        cout << "p1 & p2 END " << endl;
    }
    cout << endl;

    cout << "Finish" << endl;
    return 0;
  }

#elif ( SMART_PTR == SHARED_PTR )

  //#include <tr1/memory>    without -std=c++11
  #include <memory>
  using namespace std;

  class OwnerPtr;
  //typedef tr1::shared_ptr<OwnerPtr> OwnerPtrShared;
  typedef shared_ptr<OwnerPtr> OwnerPtrShared;

  class OwnerPtr
  {
  public:
    OwnerPtrShared other;

    OwnerPtr() { cout << "OwnerPtr::ctor() this= " << this << endl; }
    ~OwnerPtr() { cout << "OwnerPtr::dtor() this= " << this << endl; }
  };

  int main(int argc, char** argv)
  {
    cout << "Begin shared_ptr" << endl;
    cout << endl;

    {
        cout << "p1 START" << endl;
        OwnerPtrShared p1(new OwnerPtr());    //NOTE: = std::make_shared<OwnerPtr>(); only with -std=c++1y or c++14 in GCC5
        cout << "p1 END. count1= " << p1.use_count() << endl;
    }
    cout << endl;

    {
        cout << "p1 START" << endl;
        OwnerPtrShared p1;
        cout << "count1= " << p1.use_count() << "." << endl;
        {
            cout << "p2 START" << endl;
            OwnerPtrShared p2(new OwnerPtr());
            cout << "count1= " << p1.use_count() << ", count2= " << p2.use_count() << "." << endl;
            p1 = p2;
            cout << "p2 END, assigned to p1. count1= " << p1.use_count() << ", count2= " << p2.use_count() << "." << endl;
        }
        cout << "p1 END. count1= " << p1.use_count() << endl;
    }
    cout << endl;

  //Circular Reference Drawback
    {
        cout << "p1 START" << endl;
        OwnerPtrShared p1(new OwnerPtr());
        cout << "count1= " << p1.use_count() << "." << endl;
        {
            cout << "p2 START" << endl;
            OwnerPtrShared p2(new OwnerPtr());
            cout << "count1= " << p1.use_count() << ", count2= " << p2.use_count() << "." << endl;
            p1->other = p2;
            cout << "p2 assigned to p1. count1= " << p1.use_count() << ", count2= " << p2.use_count() << "." << endl;
            p2->other = p1;
            cout << "p2 END, p1 assigned to p2. count1= " << p1.use_count() << ", count2= " << p2.use_count() << "." << endl;
        }
        cout << "p1 END. count1= " << p1.use_count() << endl;
    }
    cout << endl;

    cout << "Finish" << endl;
    return 0;
  }

#elif ( SMART_PTR == WEAK_PTR )

  #include <memory>
  using namespace std;

  class OwnerPtr;
  typedef shared_ptr<OwnerPtr> OwnerPtrShared;
  typedef weak_ptr<OwnerPtr> NonOwnerPtrShared;

  class OwnerPtr
  {
  public:
    NonOwnerPtrShared other;

    OwnerPtr() { cout << "OwnerPtr::ctor() this= " << this << endl; }
    ~OwnerPtr() { cout << "OwnerPtr::dtor() this= " << this << endl; }
  };

  int main(int argc, char** argv)
  {
    cout << "Begin shared_ptr & weak_ptr" << endl;
    cout << endl;

    //NonOwnerPtrShared p1(new OwnerPtr());    COMPILE ERROR weak_ptr can't be created directly


  //shared_ptr Circular Reference Drawback
    {
        cout << "p1 START" << endl;
        OwnerPtrShared p1(new OwnerPtr());
        cout << "count1= " << p1.use_count() << "." << endl;
        {
            cout << "p2 START" << endl;
            OwnerPtrShared p2(new OwnerPtr());
            cout << "count1= " << p1.use_count() << ", count2= " << p2.use_count() << "." << endl;
            p1->other = p2;
            cout << "p2 assigned to p1. count1= " << p1.use_count() << ", count2= " << p2.use_count() << "." << endl;
            p2->other = p1;
            cout << "p2 END, p1 assigned to p2. count1= " << p1.use_count() << ", count2= " << p2.use_count() << "." << endl;
        }
        cout << "p1 END. count1= " << p1.use_count() << endl;
    }
    cout << endl;

    {
        cout << "p1 START" << endl;
        OwnerPtrShared p1(new OwnerPtr());
        cout << "count1= " << p1.use_count() << "." << endl;
        {
            cout << "p2 START" << endl;
            OwnerPtrShared p2(new OwnerPtr());
            cout << "count1= " << p1.use_count() << ", count2= " << p2.use_count() << "." << endl;
            p1->other = p2;
            cout << "p2 assigned to p1. count1= " << p1.use_count() << ", count2= " << p2.use_count() << "." << endl;
            p2->other = p1;
            cout << "p1 assigned to p2. count1= " << p1.use_count() << ", count2= " << p2.use_count() << "." << endl;

            {
                //OwnerPtrShared p1_other = p1->other;    COMPILE ERROR weak_ptr to shared_ptr
                OwnerPtrShared p1_other = p1->other.lock();
                cout << "p1other Owner lock() START. count1= " << p1.use_count() << ", count2= " << p2.use_count() << ", count1oth= " << p1_other.use_count() << "." << endl;
            }
            cout << "p1other END. count1= " << p1.use_count() << ", count2= " << p2.use_count() << "." << endl;
            cout << endl;

            {
                auto p1_other = p1->other.lock();    //auto .lock() => shared_ptr
                cout << "p1other auto lock() START. count1= " << p1.use_count() << ", count2= " << p2.use_count() << ", count1oth= " << p1_other.use_count() << "." << endl;
            }
            cout << "p1other END. count1= " << p1.use_count() << ", count2= " << p2.use_count() << "." << endl;
            cout << endl;


            {
                NonOwnerPtrShared p1_other = p1->other;
                cout << "p1other NonOwner START. count1= " << p1.use_count() << ", count2= " << p2.use_count() << ", count1oth= " << p1_other.use_count() << "." << endl;
            }
            cout << "p1other END. count1= " << p1.use_count() << ", count2= " << p2.use_count() << "." << endl;
            cout << endl;

            {
                NonOwnerPtrShared p1_other = p1->other.lock();    //also to get another weak_ptr, no effect on reference count
                cout << "p1other NonOwner lock(). count1= " << p1.use_count() << ", count2= " << p2.use_count() << ", count1oth= " << p1_other.use_count() << "." << endl;
            }
            cout << "p1other END. count1= " << p1.use_count() << ", count2= " << p2.use_count() << "." << endl;
            cout << endl;

            {
                auto p1_other = p1->other;    //without .lock() => weak_ptr
                cout << "p1other auto. count1= " << p1.use_count() << ", count2= " << p2.use_count() << ", count1oth= " << p1_other.use_count() << "." << endl;
            }
            cout << "p1other END. count1= " << p1.use_count() << ", count2= " << p2.use_count() << "." << endl;
            cout << endl;
        }
        cout << "p1 END. count1= " << p1.use_count() << endl;
    }
    cout << endl;

    cout << "Finish" << endl;
    return 0;
  }


#else

  int main(int argc, char** argv)
  {
    return 0;
  }

#endif
