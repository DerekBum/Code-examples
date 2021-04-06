#include "my_vector.h"

namespace product {

    class Product {
    public:
        Product(const char* name, int quantity, double price) : quantity_(quantity), price_(price) {
            name_ = new char[strlen(name) + 1];
            strcpy(name_, name);
        }
        Product(const Product& other) : Product(other.name_, other.quantity_, other.price_) {}
        Product() : Product("Sample", 123, -2.5) {}
        ~Product() {
            delete [] name_;
        }

        char* name() const {
            return name_;
        }
        int quantity() const {
            return quantity_;
        }
        double price() const {
            return price_;
        }

        Product & operator= (const Product& pr) {
            if (this == &pr)
                return *this;
            delete [] name_;
            quantity_ = pr.quantity_;
            price_ = pr.price_;
            name_ = new char[strlen(pr.name_) + 1];
            strcpy(name_, pr.name_);
            return *this;
        }

    private:
        char* name_;
        int quantity_;
        double price_;
    };

    void print(const containers::my_vector<Product>& v) {
        std::cout << v << std::endl;
    }

    std::ostream & operator<< (std::ostream& out, const Product& pr) {
        return out << pr.name() << " "<< pr.quantity() << " " << pr.price();
    }

}  // namespace product

template <typename T>
void test_my_vector(T first, T second) {
    containers::my_vector<T> arr;
    containers::my_vector<T> arr2;
    assert(arr.empty() && "Empty check fail");
    arr.push_back(first);
    assert(arr.size() == 1 && "Wrong size");
    arr.reserve(5);
    assert(arr.capacity() == 8 && "Wrong capacity after reserve");
    arr.push_back(second);
    arr.push_back(first);
    std::cout << "Last element: " << arr[2] << '\n';
    std::cout << "Array: " << arr << '\n';
    arr.pop_back();
    std::cout << "Array: " << arr << '\n';
    arr2 = arr;
    containers::my_vector<T> arr3(arr2);
    arr.clear();
    assert(arr.empty() && "Clear fail");
    arr2.clear();
    std::cout << "Array: " << arr3 << '\n' << '\n';
}

template <typename T>
void test_my_vector_default_constructible(T first, T second) {
    containers::my_vector<T> arr(16);
    assert(arr.capacity() == 16 && "Default constructor fail");
    assert(arr.size() == 16 && "Size after constructor fail");
    arr.resize(4);
    assert(arr.size() == 4 && "Size after resize fail");
    arr.push_back(first);
    arr.reserve(5);
    assert(arr.capacity() == 16 && "Wrong capacity after reserve");
    arr.resize(17);
    assert(arr.capacity() == 32 && "Wrong capacity after reserve");
    arr[0] = second;
    arr.push_back(first);
    std::cout << "Array: " << arr << '\n';
    arr.pop_back();
    std::cout << "Array: " << arr << '\n' << '\n';
    arr.clear();
    assert(arr.empty() && "Clear fail");
}

using namespace product;

int main() {
    test_my_vector<int>(5, 10);
    test_my_vector<Product>(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));
    test_my_vector_default_constructible<int>(5, 10);
    test_my_vector_default_constructible<Product>(Product("Apple", 4, 12.0), Product("Orange", -1, 7.5));
    return 0;
}