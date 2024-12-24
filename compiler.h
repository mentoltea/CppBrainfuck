#ifndef BRAINFUCK_COMPILER
#define BRAINFUCK_COMPILER

#include "langkernel.h"
#include <iostream>
#include <assert.h>
#include <string>
#include <format>
#include <algorithm>
#include <fstream>

namespace Compiler {

using namespace Kernel;

typedef enum BlockType {
    BLOCK_UNKNOWN = 0,
    COMMAND,
    SUBBLOCK,
} BlockType;

struct Block {
    Block* next_block = nullptr;
    Block* prev_block = nullptr;
    Block* parent_block = nullptr;

    BlockType type = BlockType::BLOCK_UNKNOWN;
    CommandType command = CommandType::COMM_UNKNOWN;
    Block* child = nullptr;
};

Block* parse_blocks(std::string text);

void print_blocks(Block* Main);

InstructionType parse_instruction(char c);

CommandType parse_command(InstructionType inst);

void exit_on_error(int code, std::string error="error");

void compile(std::string infilename, std::string code);

}
#endif //BRAINFUCK_COMPILER