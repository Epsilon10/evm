#include "vm.h"
#include <vector>

using namespace std;
int main() {
    StackVM vm;
    vector<i32> program{3,4,0x40000001, 0x40000000};
    vm.loadProgram(program);
    vm.run();
    return 0;
}