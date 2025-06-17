//
// Created by Lumi on 25. 6. 16.
//

#include <cstdint>
#include <span>

#include "ArbitrarySignedInt.h"
#include "storage/CPUStorage.h"
int main() {
    ArbitrarySignedInt<16, 0, CPUMemoryPlace> a = 127;
    std::cout << a;
}
