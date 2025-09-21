#include <iostream>

int main() 
{
    // no fractional numbers
    signed char c1; // 1 bytes, 256 values, -128...127
    unsigned char c2; // 1 bytes, 256 values, 0...255
    short s1; // 2 bytes, 65536 values, -32768...32767
    unsigned short us2; // 2 bytes, 65536 values, 0...65535
    int i1; // 4 bytes, 4,147 billions values, -2^31...(2^31)-1
    unsigned int ui2; // 4 bytes, 4,147 billions values 0...(2^32)-1
    long long ll1; // 8 bytes
    unsigned long long ull2; // 8 bytes

    i1 = 10.5;
    std::cout << i1 << std::endl;

    //symbols
    char c3 = 'a';

    //fractionals
    float f = 3.141592f; // 4 bytes, 6-7 numbers
    double d = 3.14159265853111111; // 8 bytes , 15-16 numbers

    float f1 = 10; 

    // logic
    bool b = true; // false(0)
    bool b1 = 123456; // 1 bytes

    std::cout << sizeof(b) << std::endl;
    std::cout <<"залупа иди нахуй" << std::endl;

    return 0;
}