#include <cstdint>
#include <type_traits>

void main() {
    uint16_t a = 1;
    auto b = a + (uint16_t)1;
    // static assertion failed with "hmmm..."
    static_assert(std::is_same<decltype(b), decltype(a)>::value, "hmmm...");
    // see: https://stackoverflow.com/a/5563131/4533234
}