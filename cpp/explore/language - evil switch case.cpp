#include <iostream>

int main() {
    // usage of this hack on old time:
    // https://en.wikipedia.org/wiki/Duff%27s_device
    // I don't see a good situation to use this hack on modern compiler
    // following negative example will output "30"

    int n = 3;
    switch (n) {
        case 1:
        if (false) {
            n--;
            break;
            case 3: std::cout << n--;
        }
        case 2:
         n = 0;
         break;
    };
    std::cout << n;
    return n;
}

