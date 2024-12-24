#include "compiler.h"
using namespace std;

int main() {
    string program = "><><[++->]>>--";

    Compiler::Block* Main = Compiler::parse_blocks(program);
    Compiler::print_blocks(Main);


    return 0;
}