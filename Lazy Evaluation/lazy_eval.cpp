#include <iostream>
#include <vector>
#include <functional>

template <typename T>
class LazyVector {
private:
    std::vector<T> data;
    std::vector<std::function<T(T)>> transformations;

public:
    LazyVector(std::vector<T> vec) : data(std::move(vec)) {}

    void addTransformation(std::function<T(T)> func) {
        transformations.push_back(func);
    }

    T operator[](size_t index) const {
        T value = data[index];
        for (const auto& func : transformations) {
            value = func(value);
        }
        return value;
    }

    void print() const {
        for (const auto& elem : data) {
            std::cout << (*this)[&elem - &data[0]] << " ";
        }
        std::cout << std::endl;
    }
};


int main() {
    LazyVector<int> vec({ 1, 2, 3, 4, 5 });
    vec.addTransformation([](int x) { return x * x; });   
    vec.addTransformation([](int x) { return x + 1; });   
    vec.print();
}
