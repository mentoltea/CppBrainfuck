#ifndef BRAINFUCK_KERNEL
#define BRAINFUCK_KERNEL

#include <stdint.h>

namespace Kernel {

typedef int64_t Memory_t;

typedef enum InstructionType {
    INST_UNKNOWN = 0,

    INST_NEXT = '>',
    INST_PREV = '<',
    INST_PLUS = '+',
    INST_MINUS = '-',
    INST_PRINT = '.',
    INST_READ = ',',
    INST_OPEN = '[',
    INST_END = ']',
} InstructionType;

typedef enum CommandType {
    COMM_UNKNOWN = 0,

    COMM_NEXT = INST_NEXT,
    COMM_PREV = INST_PREV,
    COMM_PLUS = INST_PLUS,
    COMM_MINUS = INST_MINUS,
    COMM_PRINT = INST_PRINT,
    COMM_READ = INST_READ,
} CommandType;

}
#endif // BRAINFUCK_KERNEL