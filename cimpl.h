#ifndef BRAINFUCK_C_IMPLEMENTATION
#define BRAINFUCK_C_IMPLEMENTATION

#include "compiler.h"
using namespace Compiler;

void prepare_impl(std::ofstream &fd);

void command_impl(std::ofstream &fd, CommandType instr);

void end_impl(std::ofstream &fd);


#endif // BRAINFUCK_C_IMPLEMENTATION