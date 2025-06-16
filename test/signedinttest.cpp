//
// Created by Lumi on 25. 6. 16.
//

#include <cstdint>
#include <span>

#include "ArbitrarySignedInt.h"
#include "storage/CPUStorage.h"
int main() {
    ArbitrarySignedInt<8, 0, CPUStorage<2> > a = 127;
    std::cout << a;
}
