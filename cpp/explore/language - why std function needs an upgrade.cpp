#include <memory>
#include <functional>

template <typename T>
void ct(T&& a) {
    a();
}

void cf(std::function<void()> a) {
    a();
}

void cp(void (*a)()) {
    a();
}

int main()
{
    auto p = std::make_unique<int>();
    auto a = [p = std::move(p)](){};
    ct(a); // good
    // cf(std::move(a)); // bad for a is non-copyable
    // cp(a); // bad for a have capure
}
