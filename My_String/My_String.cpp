#include "My_String.h"
#include <cstring>

My_String::My_String() {
    isSmall = true;
    data[0] = '\0';
}
char& My_String::operator[] (int i) {
    if (i < 0 || i > size() - 1)
        return (isSmall)? data[size()] : defstr.data[size()];
    if (isSmall)
        return data[i];
    return defstr.data[i];
}
My_String& My_String::operator =(const My_String& strd) {
    if (this == &strd)
        return *this;
    if (this->isSmall == 1 && strd.isSmall == 1)
        strcpy_s(this->data, strd.data);
    else if (strd.isSmall == 0 && this->isSmall == 1)
    {
        this->isSmall = false;
        this->defstr.capacity = strd.defstr.capacity;
        this->defstr.size = strd.defstr.size;
        this->defstr.data = new char[this->defstr.capacity];
        strcpy_s(this->defstr.data, strd.defstr.size + 1, strd.defstr.data);
    }
    else if (strd.isSmall == 1 && this->isSmall == 0)
    {
        delete[] this->defstr.data;
        this->isSmall = 1;
        strcpy_s(this->data, strd.data);
    }
    else
    {
        delete[] this->defstr.data;
        this->defstr.capacity = strd.defstr.capacity;
        this->defstr.size = strd.defstr.size;
        this->defstr.data = new char[strd.defstr.capacity];
        strcpy_s(this->defstr.data, this->defstr.size + 1, strd.defstr.data);
    }
    return *this;
}
My_String::My_String(const My_String& strd) {
    this->isSmall = strd.isSmall;
    if (isSmall) {
        strcpy_s(this->data, strd.data);
    }
    else {
        this->defstr.capacity = strd.defstr.capacity;
        this->defstr.size = strd.defstr.size;
        this->defstr.data = new char[strd.defstr.capacity];
        strcpy_s(this->defstr.data, strd.defstr.size + 1, strd.defstr.data);
    }
}
My_String& My_String::operator =(const char* strd)
{
    if (this->isSmall == 1 && strlen(strd) < 23)
        strcpy_s(this->data, strd);
    else if (this->isSmall == 1 && strlen(strd) >= 23)
    {
        this->isSmall = false;
        this->defstr.size = strlen(strd);
        this->defstr.capacity = 2 * this->defstr.size;
        this->defstr.data = new char[this->defstr.capacity];
        strcpy_s(this->defstr.data, this->defstr.size + 1, strd);
    }
    else if (this->isSmall == 0 && strlen(strd) < 23)
    {
        delete[] this->defstr.data;
        this->isSmall = true;
        strcpy_s(this->data, strd);
    }
    else {
        delete[] this->defstr.data;
        this->defstr.size = strlen(strd);
        this->defstr.capacity = 2 * this->defstr.size;
        this->defstr.data = new char[this->defstr.capacity];
        strcpy_s(this->defstr.data, this->defstr.size + 1, strd);
    }
    return *this;
}
My_String::My_String(const char* cstr)
{
    if (strlen(cstr) < 23)
    {
        isSmall = true;
        strcpy_s(data, cstr);
    }
    else
    {
        isSmall = false;
        defstr.size = strlen(cstr);
        defstr.capacity = 2 * defstr.size;
        defstr.data = new char[defstr.capacity];
        strcpy_s(this->defstr.data, this->defstr.size + 1, cstr);
    }
}
My_String::~My_String() {
    if (isSmall == false)
        delete[] defstr.data;
}
size_t My_String::size() {
    if (isSmall)
        return strlen(data);
    return defstr.size;
}

size_t My_String::capacity() {
    if (isSmall)
        return 24;
    return defstr.capacity;
}

void My_String::push_back(char x) {
    if (size() < 23) {
        data[size() + 1] = '\0';
        data[size()] = x;
    }
    else if (size() == 23)
    {
        char temp[24];
        this->isSmall = false;
        strcpy_s(temp, this->data);
        defstr.size = 24;
        defstr.capacity = 48;
        defstr.data = new char[48];
        strcpy_s(defstr.data, 24, temp);
        defstr.data[25] = '\0';
        defstr.data[24] = x;
    }
    else if (this->defstr.capacity == defstr.size + 1)
    {
        char* temp = new char[defstr.size + 2];
        strcpy_s(temp, defstr.size + 1, defstr.data);
        temp[defstr.size + 1] = '\0';
        temp[defstr.size] = x;
        defstr.size++;
        delete[] defstr.data;
        defstr.capacity = defstr.size * 2;
        defstr.data = new char[defstr.capacity];
        strcpy_s(defstr.data, defstr.size + 1, temp);
    }
    else
    {
        defstr.data[defstr.size + 1] = '\0';
        defstr.data[defstr.size] = x;
        defstr.size++;
    }
}

void My_String::pop_back()
{
    if (size() > 0 && size() < 24)
    {
        data[size() - 1] = '\0';
    }
    else if (size() == 24)
    {
        char temp[25];
        isSmall = true;
        strcpy_s(temp, defstr.size + 1, defstr.data);
        delete[] defstr.data;
        strcpy_s(data, temp);
        data[23] = '\0';
    }
    else
    {
        defstr.data[defstr.size - 1] = '\0';
        defstr.size--;
    }
}