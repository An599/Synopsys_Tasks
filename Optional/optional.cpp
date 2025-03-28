#include <iostream>
#include <optional>

template <typename T>
class Optional {
	private:
		std::aligned_storage_t<sizeof(T), alignof(T)> storage;
		bool valid_value;
	public:	
		Optional(): valid_value(false) {}

		Optional(const T& value) : valid_value(true)
		{
			new (&storage) T(value);
		}

		bool has_value() const {
			return valid_value;
		}

		void reset() {
			if (has_value()) {
				value().~T();
				valid_value = false;
			}
		}
		~Optional() {
			reset();
		}
		T& operator*() {
			return *reinterpret_cast<T*>(&storage);
		}
		const T& operator*() const{
			return *reinterpret_cast<const T*>(&storage);
		}
		T& value() {
			if (!has_value())
				throw std::bad_variant_access();
			return **this;
		}
		const T& value() const{
			if (!has_value())
				throw std::bad_variant_access();
			return **this;
		}

		template <typename... Args>
		void emplace(Args&& ...args) {
			reset();
			new(&storage) T(std::forward<Args>(args)...);
			valid_value = true;
		}
};

int main() {
	Optional<int> obj;
	std::cout << "Has value: " << obj.has_value()<< std::endl; 

	obj.emplace(42);
	std::cout << "Has value: " << obj.has_value() << std::endl; 
	std::cout << "Value: " << *obj << std::endl; 

	obj.reset();
	std::cout << "Has value: " << obj.has_value() << std::endl; 

	return 0;
}
