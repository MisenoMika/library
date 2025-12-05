#ifndef BIGINT_H
#define BIGINT_H
#include <cstddef>
#include <iostream>
class BigInt
{
     // Class members and methods go here
     size_t size; // Size of the BigInt
     size_t len;
     bool isZero;
     char* number;
public:
    BigInt();
    BigInt(size_t len);
    ~BigInt();
    BigInt(const BigInt& other);
    BigInt(const char*string);
    BigInt& operator=(const BigInt& other);
    BigInt& operator+=(const BigInt& other);
    BigInt operator+(const BigInt& other) ;
    BigInt operator*(const BigInt& other) ;
    BigInt& operator*=(const BigInt& other);
    bool operator==(const BigInt& other) ;
    bool operator>(const BigInt& other) ;
    bool operator>=(const BigInt& other) ;
    bool operator<(const BigInt& other);
    bool operator<=(const BigInt& other) ;
    bool operator!=(const BigInt& other) ;
    
    void expand(size_t newsize);
    friend std::ostream& operator<<(std::ostream& os, const BigInt& obj);
    

};

#endif