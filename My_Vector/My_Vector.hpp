#pragma once
#include <cstdlib>
#include <new>
template <typename T>
class My_Vector {
private:
	size_t size;
	size_t capacity;
	T* data;
public:
	My_Vector()
	{
		size = 0;
		capacity = 0;
		data = nullptr;
	}
	My_Vector(size_t count)
	{
		size = count;
		capacity = count;
		data = static_cast<T*>(malloc(sizeof(T) * count));
		for (size_t i = 0; i < count; i++)
			new (data + i) T();
	}
	My_Vector(size_t count, const T& info)
	{
		size = count;
		capacity = count;
		data = static_cast<T*>(malloc(sizeof(T) * count));
		for (size_t i = 0; i < count; i++)
			new (data + i) T(info);
	}
	My_Vector(const My_Vector& vec) {
		size = vec.size;
		capacity = vec.capacity;
		if (size == 0)
		{
			data = nullptr;
			return;
		}
		data = static_cast<T*>(malloc(sizeof(T) * capacity));
		for (size_t i = 0; i < size; i++)
			new (data + i) T(vec.data[i]);
	};
	~My_Vector() {
		for (size_t i = 0; i < size; i++)
			data[i].~T();
		free(data);
		size = 0;
		capacity = 0;
		data = nullptr;
	};
	My_Vector& operator = (const My_Vector& vec)
	{
		if (this == &vec)
			return *this;
		for (size_t i = 0; i < size; i++)
			data[i].~T();
		free(data);
		size = vec.size;
		capacity = vec.capacity;
		if (size == 0)
		{
			data = nullptr;
			return;
		}
		data = static_cast<T*>(malloc(sizeof(T) * capacity));
		for (size_t i = 0; i < size; i++)
			new(data + i) T(vec.data[i]);
		return *this;
	}
	T& operator[](size_t i)
	{
		return data[i];
	}
	size_t get_size()
	{
		return size;
	}
	size_t get_capacity()
	{
		return capacity;
	}
	void pop_back()
	{
		if (size == 0)
			return;
		data[size - 1].~T();
		size--;
	}
	void push_back(const T& x) {
		if (capacity != 0 && size == capacity)
		{
			capacity = size * 2;
			data = static_cast<T*>(realloc(data, sizeof(T) * capacity));
		}
		else if (capacity == 0)
		{
			data = static_cast<T*>(malloc(sizeof(T)));
			capacity = 1;
		}
		new (data + size) T(x);
		size++;
	}
};

