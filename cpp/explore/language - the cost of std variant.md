### compiler result
![screenshot](images/lanuage%20-%20the%20cost%20of%20std%20variant.png)

### conclusion
Every get/get_if call best case happens when type matches, will cost a cmp + jne
```
cmp BYTE PTR[], index
jne throw_exception / assign_zero
```

### the code
``` cpp
#include <variant>
#include <iostream>
#include <string>
using std::string;

void add(int* a) {
    if (a) {
        (*a)++;
    }
}

int test() {
    std::variant<string, int> a;
    a = 1234;
    auto p = std::get_if<string>(&a);
    std::cout << p;
  	add(std::get_if<int>(&a));
    std::cout << *std::get_if<int>(&a);
    std::cout << std::get<int>(a);
    std::cout << std::get<string>(a);
    return 1;
}
```
