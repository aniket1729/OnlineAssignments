#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

int encode(const char* data) { cout << "In encode()" << endl; }
int decode(const char* data) { cout << "In decode()" << endl; }


class MyDevice
{
public:
    int send(const char* data) { cout << "In MyDevice::send() non-static" << endl; }
    int recv(const char* data) { cout << "In MyDevice::recv() non-static" << endl; }

    static int save_in_temp_buffer(const char* data) { cout << "In MyDevice::save() static" << endl; }
    static int process_data(const char* data) { cout << "In MyDevice::process() static" << endl; }

    int (*func_ptr_member)(const char*);

    // only a non-static member function may be const qualified
    void display(void) const    { cout << "In display() const" << endl; }
};

#define DATA "random data"

void general_oper_func(const void* data, int (*general_fun_ptr)(const void*) )
    { cout << "From general_oper_func ..."; general_fun_ptr(data); }

template <class T>
void general_oper_template(T* data,  int (*general_fun_ptr)(T*) )
    { cout << "From general_oper_template ... ";    general_fun_ptr(data); }


int main(int argc, char** argv)
{
//Ordinary Functions
    int (*oper_func_ptr_1)(const char*);
    oper_func_ptr_1 = &encode;
    oper_func_ptr_1(DATA);
    oper_func_ptr_1 = decode;
    (*oper_func_ptr_1)(DATA);

    /* int (*ERROR_func_ptr)(char*);    //COMPILE ERROR for non matching argument
    ERROR_func_ptr = decode; */


    typedef int (*OperFuncPtr)(const char*);
    OperFuncPtr oper_func_ptr_2;

    oper_func_ptr_2 = &encode;
    oper_func_ptr_2(DATA);
    //or other way


    int (*oper_func_ptr_3[2])(const char*) = {encode, &decode};
    oper_func_ptr_3[0] = encode;
    oper_func_ptr_3[1](DATA);
    //or other way

    OperFuncPtr oper_func_ptr_4[2] = {&encode, decode};
    oper_func_ptr_4[1] = decode;
    oper_func_ptr_4[0](DATA);
    //or other way


    int (**oper_func_ptr_6)(const char*) = new OperFuncPtr[2];
    oper_func_ptr_6[0] = encode;
    oper_func_ptr_6[0](DATA);

    OperFuncPtr* oper_func_ptr_7 = (OperFuncPtr*) calloc( 2, sizeof( int(*)(const char*) ));
    oper_func_ptr_7[1] = decode;
    oper_func_ptr_7[1](DATA);


    cout << endl;
//Static Member Functions
    oper_func_ptr_1 = MyDevice::save_in_temp_buffer;
    oper_func_ptr_1(DATA);
    //or other way


    oper_func_ptr_2 = MyDevice::process_data;
    oper_func_ptr_2(DATA);
    //or other way

    OperFuncPtr proc_func_ptr_5[] = {MyDevice::save_in_temp_buffer, &MyDevice::process_data, encode, decode};
    proc_func_ptr_5[0] = MyDevice::save_in_temp_buffer;
    proc_func_ptr_5[0](DATA);
    //or other way



    cout << endl;
//Non-Static Member Functions
    MyDevice objDevice;

    // oper_func_ptr_1 = MyDevice::send;    //COMPILE ERROR for using ordinary func ptr for member func

    int (MyDevice::*transfer_mem_func_ptr_1)(const char*);
    transfer_mem_func_ptr_1 = &MyDevice::send;
    //transfer_mem_func_ptr_1 = MyDevice::send;    //COMPILER ERROR
    //transfer_mem_func_ptr_1 = &(MyDevice::send);    //COMPILER ERROR

    // transfer_mem_func_ptr_1(DATA);    //COMPILE ERROR
    // (objDevice.transfer_mem_func_ptr_1)(DATA);    //COMPILE ERROR
    // objDevice.transfer_mem_func_ptr_1(DATA);    //COMPILE ERROR
    (objDevice.*transfer_mem_func_ptr_1)(DATA);




    typedef int (MyDevice::*TransferMemFuncPtr)(const char*);
    TransferMemFuncPtr transfer_mem_func_ptr_2;
    transfer_mem_func_ptr_2 = &MyDevice::recv;
    (objDevice.*transfer_mem_func_ptr_2)(DATA);


    int (MyDevice::*transfer_mem_func_ptr_3[2])(const char*) = {};
    //int (MyDevice::*transfer_mem_func_ptr_3)[2](const char*);    //IMPROPER (as array of function)
    transfer_mem_func_ptr_3[0] = &MyDevice::send;
    (objDevice.*transfer_mem_func_ptr_3[0])(DATA);
    // (objDevice.*transfer_mem_func_ptr_3)[0](DATA);    //COMPILE ERROR

    TransferMemFuncPtr transfer_mem_func_ptr_4[2] = {};
    transfer_mem_func_ptr_4[1] = &MyDevice::recv;
    (objDevice.*transfer_mem_func_ptr_4[1])(DATA);


    #define CALL_MEMBER_FN_PTR(object, ptrToMember)  ((object).*(ptrToMember))
    CALL_MEMBER_FN_PTR(objDevice, transfer_mem_func_ptr_1)(DATA);
    CALL_MEMBER_FN_PTR(objDevice, transfer_mem_func_ptr_4[1])(DATA);


    int (MyDevice::**transfer_mem_func_ptr_6)(const char*) = new TransferMemFuncPtr[2];
    transfer_mem_func_ptr_6[0] = &MyDevice::send;
    CALL_MEMBER_FN_PTR(objDevice, transfer_mem_func_ptr_6[0])(DATA);

    TransferMemFuncPtr* transfer_mem_func_ptr_7 = (TransferMemFuncPtr*) calloc( 2, sizeof( int(MyDevice::*)(const char*) ));
    transfer_mem_func_ptr_7[1] = &MyDevice::recv;
    CALL_MEMBER_FN_PTR(objDevice, transfer_mem_func_ptr_7[1])(DATA);


    void (MyDevice::*const_func_ptr)(void) const;
    const_func_ptr = &MyDevice::display;
    (objDevice.*const_func_ptr)();

    cout << endl;
//Function Pointer Member
    objDevice.func_ptr_member = decode;
    objDevice.func_ptr_member(DATA);
    // (objDevice.*func_ptr_member)(DATA);    //COMPILE ERROR as it is member variable not function pointer
    // objDevice.(*func_ptr_member)(DATA);    //COMPILE ERROR


//void* and Template<T>
    // general_oper_func(DATA, &encode);    //COMPILE ERROR for using any datatype in place of void*

    general_oper_template<const char>(DATA, &encode);

    return 0;
}

/* void general_oper_func(const void* data, int (*general_fun_ptr)(const void*) )
    { cout << "From general_oper_func ..."; general_fun_ptr(data); }

template <class T>
void general_oper_template(T* data,  int (*general_fun_ptr)(T*) )
    { cout << "From general_oper_template ... ";    general_fun_ptr(data); }

void display(void) const
    { cout << "In display()" << endl; }  */
