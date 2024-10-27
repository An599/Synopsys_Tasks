#pragma once

class My_String
{
public:
	My_String(); //+v
	My_String(const My_String&); //+v
	My_String(const char* cstr); //+
	~My_String(); //+v
	void push_back(char); //+v
	void pop_back(); //+
	size_t size();//+v
	size_t capacity(); //+v
	My_String& operator =(const My_String&); //+v
	My_String& operator =(const char *); //+
	char& operator[](int); //+v
private:
	struct def_string {
		size_t size;
		size_t capacity;
		char* data;
	};
	union
	{
		def_string defstr;
		char data[24];
	};
	bool isSmall;
};
