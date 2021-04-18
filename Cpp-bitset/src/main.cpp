#include "my_array.h"

using lab_13::my_array;

template<typename T, std::size_t N>
void test_core() {
    my_array<T, N> a;
    const my_array<T, N> &ca = a;
    a.empty();
    ca.empty();
    a.size();
    ca.size();

    a.at(0);
    ca.at(0);
    a[0];
    ca[0];
    (void)static_cast<const T &>(a[0]);
    (void)static_cast<const T &>(ca[0]);
}

template<typename T, std::size_t N>
void test_assign() {
    my_array<T, N> a;
    a.fill(1);
    for (size_t i = 0; i < N; i++)
        assert(a[i] == 1);
    assert(sizeof(my_array<bool, 9>) == 2);
}

class NonCopyable {
public:
    NonCopyable() {}
private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator=(const NonCopyable);
};

int main() {
    test_core<int, 10>();
    test_core<std::string, 10>();
    test_core<bool, 10>();
    test_core<NonCopyable, 10>();

    test_assign<int, 10>();
    test_assign<bool, 10>();
}
