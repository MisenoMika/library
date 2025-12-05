#include "BigInt.h"
#include <cstring>
#include <cctype>

BigInt::BigInt(size_t n)
{
    if(n == 0){
        this->len = 1;
        this->size = 11; // Default size
        this->isZero = true;
        this->number = new char[this->size];
        this->number[0] = '0';
        this->number[1] = '\0';
        return;
    }
    int dig = 0;
    size_t temp = n;
    while((temp /= 10) >= 1){
        dig++;
    }
    dig++; // Count the last digit
    len = dig;
    size = dig + 10;
    if(n == 0 )isZero = true;
    else isZero = false;
    this->number = new char[size];
    number[len] = '\0';
    for(int i=0; i<len; i++){
        number[i] = (n % 10) + '0';
        n = n / 10;
    }
}

BigInt::BigInt()
{
    this->len = 1;
    this->size = 11; // Default size
    this->isZero = true;
    this->number = new char[this->size];
    this->number[0] = '0';
    this->number[1] = '\0';
}

BigInt::~BigInt()
{
    delete[] this->number;
}

BigInt::BigInt(const BigInt& other)
{
    this->len = other.len;
    this->size = other.size;
    this->isZero = other.isZero;
    this->number = new char[this->size];
    for(size_t i = 0; i < this->len; i++) {
        this->number[i] = other.number[i];
    }
    this->number[this->len] = '\0';
}

BigInt::BigInt(const char* string)
{
    size_t start = 0;
    while (string[start] == '0' && string[start] != '\0') {
        start++;
    }
    if(start == std::strlen(string)){
        len == 1;
        size = 11;
        isZero = true;
        number = new char[size];
        number[0] = '0';
        number[1] = '\0';
        return ;
    }

    this->len = std::strlen(string) - start;
    this->size = this->len + 10; // +1 for null terminator
    if(this->len == 1 && string[start] == '0') {
        this->isZero = true;
    } 
    else {
        this->isZero = false;
    }
    this->number = new char[this->size];
    for(size_t i = 0; i < this->len; i++) {
        this->number[len - i - 1] = string[i+start];
    }
    this->number[this->len] = '\0';
}

BigInt& BigInt::operator=(const BigInt& other)
{
    if(this == &other) return *this;    
    if (this != &other) {
        delete[] this->number; // Free existing resource
        this->len = other.len;
        this->size = other.size;
        this->isZero = other.isZero;
        this->number = new char[this->size];
        std::strcpy(this->number, other.number);
        }
    return *this;
    
}

BigInt& BigInt::operator+=(const BigInt& other)
{
    if(other.isZero) return *this;
    int carry = 0;
    int maxlen = (this->len > other.len) ? this->len : other.len;
    if(maxlen >= this->size)this->expand(maxlen + 1);
    for(int i=0 ; i<maxlen; i++){
        int digit1 = (i < this->len) ? this->number[i] - '0' : 0;
        int digit2 = (i < other.len) ? other.number[i] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        this->number[i] = (sum % 10) + '0';
        carry = sum / 10;
    }
    if(carry > 0){
        this->number[maxlen] = carry + '0';
        this->len = maxlen + 1;
    }
    else {
        this->len = maxlen;
    }
    this->len = (carry > 0)? maxlen+1 : maxlen;
    this->number[this->len] = '\0';
    return *this;
}

BigInt BigInt::operator+(const BigInt& other)
{
    if(other.isZero) return *this;
    int carry = 0;
    BigInt result = *this;
    int maxlen = (this->len > other.len) ? this->len : other.len;
    if(maxlen >= this->size)result.expand(maxlen + 10);
    for(int i=0 ; i<maxlen; i++){
        int digit1 = (i < this->len) ? result.number[i] - '0' : 0;
        int digit2 = (i < other.len) ? other.number[i] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        result.number[i] = (sum % 10) + '0';
        carry = sum / 10;
    }
    if(carry > 0){
        result.number[maxlen] = carry + '0';
        result.len = maxlen + 1;
    }
    else {
        result.len = maxlen;
    }
    result.len = (carry > 0)? maxlen+1 : maxlen;
    result.number[result.len] = '\0';
    return result;
}

BigInt BigInt::operator*(const BigInt& other)
{
    BigInt result;
    int carry = 0;
    int maxlen = this->len + other.len;
    delete[] result.number;
    result.size = maxlen + 10;
    result.len = maxlen;
    result.number = new char[result.size];
    result.isZero = false;
    for(size_t i = 0; i < result.size; i++) {
        result.number[i] = '0';
    }
    if(other.isZero || this->isZero) {
        for(size_t i = 0; i < result.len; i++) {
            result.number[i] = '0';
        }
        result.isZero = true;
        return result;
    }
    
    //doing multiplication
    for (size_t i = 0; i < this->len; i++) { 
        int carry = 0;
        int digit1 = this->number[i] - '0'; 
        for (size_t j = 0; j < other.len; j++) { 
            int digit2 = other.number[j] - '0'; 
           
            int sum = (result.number[i + j] - '0') + digit1 * digit2 + carry;
            result.number[i + j] = (sum % 10) + '0';
            carry = sum / 10; 
        }

        if (carry > 0) {
            result.number[i + other.len] += carry;
        }
    }
    while (result.len > 1 && result.number[result.len - 1] == '0') {
        result.len--;
    }
    result.number[result.len] = '\0'; // 补充终止符
    return result;
}

BigInt& BigInt::operator*=(const BigInt& other)
{
    /*if(other.isZero || this->isZero) {
        for(size_t i = 0; i < this->len; i++) {
            this->number[i] = '0';
        }
        this->isZero = true;
        return *this;
    }

    int carry = 0;
    int maxlen = this->len + other.len;
    this->expand(maxlen + 10);

    for (size_t i = 0; i < this->len; i++) { 
        int carry = 0;
        int digit1 = this->number[i] - '0'; 
        for (size_t j = 0; j < other.len; j++) { 
            int digit2 = other.number[j] - '0'; 
           
            int sum = (this->number[i + j] - '0') + digit1 * digit2 + carry;
            this->number[i + j] = (sum % 10) + '0';
            carry = sum / 10; 
        }

        if (carry > 0) {
            this->number[i + other.len] += carry;
        }
    }
    while (this->len > 1 && this->number[this->len - 1] == '0') {
        this->len--;
    }
    this->number[this->len] = '\0'; */ //没招了
    *this = *this * other;
    return *this;
}


bool BigInt::operator==(const BigInt& other)
{
    if (this->isZero && other.isZero) return true;
    if (this->isZero != other.isZero) return false;
    if (this->len != other.len) return false;
    bool result = strcmp(this->number, other.number);
    return result == 0;
}

bool BigInt::operator>(const BigInt& other)
{
    if(this -> isZero && other.isZero) return false;
    if (this->isZero) return false; 
    if (other.isZero) return true;
    
    if(this->len > other.len) return true;
    if(this->len < other.len) return false;
    
    BigInt temp_left = *this;
    BigInt temp_right = other;
    for(int i=0; i<temp_left.len; i++){
        temp_left.number[temp_left.len - i -1] = this->number[i];
    }
    for(int i=0; i<temp_right.len; i++){
        temp_right.number[temp_right.len - i -1] = other.number[i];
    }
    
    temp_left.number[temp_left.len] = '\0';
    temp_right.number[temp_right.len] = '\0';
    int result = strcmp(temp_left.number, temp_right.number);
    if(result > 0) return true;
    else return false;
}

bool BigInt::operator>=(const BigInt& other)
{
    if(this -> isZero && other.isZero) return true;
    if (this->isZero) return false; 
    if (other.isZero) return true;
    
    if(this->len > other.len) return true;
    if(this->len < other.len) return false;
    BigInt temp_left = *this;
    BigInt temp_right = other;
    for(int i=0; i<temp_left.len; i++){
        temp_left.number[temp_left.len - i -1] = this->number[i];
    }
    for(int i=0; i<temp_right.len; i++){
        temp_right.number[temp_right.len - i -1] = other.number[i];
    }
    temp_left.number[temp_left.len] = '\0';
    temp_right.number[temp_right.len] = '\0';
    int result = strcmp(temp_left.number, temp_right.number);
    if(result >= 0) return true;
    else return false;
}

bool BigInt::operator<(const BigInt& other)
{
    if(this -> isZero && other.isZero) return false;
    if (this->isZero) return true; 
    if (other.isZero) return false;

    if(this->len > other.len) return true;
    if(this->len < other.len) return false;
    BigInt temp_left = *this;
    BigInt temp_right = other;
    for(int i=0; i<temp_left.len; i++){
        temp_left.number[temp_left.len - i -1] = this->number[i];
    }
    for(int i=0; i<temp_right.len; i++){
        temp_right.number[temp_right.len - i -1] = other.number[i];
    }
    temp_left.number[temp_left.len] = '\0';
    temp_right.number[temp_right.len] = '\0';
    int result = strcmp(temp_left.number, temp_right.number);
    if(result < 0) return true;
    else return false;
}

bool BigInt::operator<=(const BigInt& other)
{
    if(this -> isZero && other.isZero) return true;
    if (this->isZero) return true; 
    if (other.isZero) return false;

    if(this->len > other.len) return true;
    if(this->len < other.len) return false;
    BigInt temp_left = *this;
    BigInt temp_right = other;
    for(int i=0; i<temp_left.len; i++){
        temp_left.number[temp_left.len - i -1] = this->number[i];
    }
    for(int i=0; i<temp_right.len; i++){
        temp_right.number[temp_right.len - i -1] = other.number[i];
    }
    temp_left.number[temp_left.len] = '\0';
    temp_right.number[temp_right.len] = '\0';
    int result = strcmp(temp_left.number, temp_right.number);
    if(result <= 0) return true;
    else return false;
}

bool BigInt::operator !=(const BigInt& other)
{
    if (this->isZero && other.isZero) return false;
    if (this->isZero != other.isZero) return true;
    if (this->len != other.len) return true;

    bool result = strcmp(this->number, other.number);
    return result != 0;
}

void BigInt::expand(size_t newsize) {
    if (newsize <= size) return; // No need to expand. Mayber it is not necessary

    char* newNumber = new char[newsize];
    std::memcpy(newNumber, number, len);
    std::memset(newNumber + len, '0', newsize - len);
    delete[] number;
    number = newNumber;
    size = newsize;
}

std::ostream& operator<<(std::ostream& os, const BigInt& obj) {
    if(obj.isZero) {
        os << '0';
        return os;
    }
    BigInt temp = obj;
    for(int i=0; i<temp.len; i++){
        temp.number[temp.len - i -1] = obj.number[i];
    }
    temp.number[temp.len] = '\0';
    os << temp.number;
    return os;
}