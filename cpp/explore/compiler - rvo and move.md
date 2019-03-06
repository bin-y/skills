### compiler result
![screenshot](/images/compiler - rvo and move.png)

### conclustion
This is correct: http://www.dietmar-kuehl.de/mirror/c++-faq/ctors.html#faq-10.9

### the code
``` cpp
#include <utility>
#include <iostream>
#include <cstring>
struct A{
    bool b;
    int arr[1024];
    __attribute__((noinline)) A(){std::cout << __LINE__;}
    A(const A&& a) { std::cout << __LINE__; }
    A(const A& a) {std::cout << __LINE__;}
};


__attribute__((noinline)) A ca() {
    A a;
    a.arr[0]=1;a.b=true;
    return a;
}

void test() {
    {
        // good
        A a = ca();
    }
    {
        // not necessary, bad if the implemention of A::A(const A&&) is awful
        A a = std::move(ca());
    }
}
```