#include "cimpl.h"

void prepare_impl(std::ofstream &fd) {
    fd << "#include <stdio.h>" << std::endl;
    fd << "#include <stdlib.h>" << std::endl;
    fd << "int main(int argc, char** argv) {" << std::endl;
    fd << "int* Memory = calloc(4096, sizeof(int));" << std::endl;
    fd << "int* ptr = Memory;" << std::endl;
}


void end_impl(std::ofstream &fd) {
    fd << "free(Memory);" << std::endl;
    fd << "return 0;}" << std::endl;
}


void command_impl(std::ofstream &fd, CommandType instr) {
    switch (instr) {
    case COMM_NEXT:
        fd << "ptr++;" << std::endl; 
    break;
    case COMM_PREV:
        fd << "ptr--;" << std::endl;
    break;

    case COMM_PLUS:
        fd << "(*ptr)++;" << std::endl;
    break;
    case COMM_MINUS:
        fd << "(*ptr)--;" << std::endl;
    break;

    case COMM_PRINT:
        fd << "printf(\"%c\", (char)(*ptr));" << std::endl;
    break;
    case COMM_READ:
        fd << "scanf(\"%c\", (char*)ptr);" << std::endl;
    break;

    default:
        assert(0 && "wtf man 2???");
    break;
    }
}


void Compiler::compile(std::string filename, std::string code) {
    std::ofstream fd(filename + "_inter.c");

    Block* programm = parse_blocks(code);
    Block* current_block = programm;
    
    prepare_impl(fd);

    while (current_block->type != BLOCK_UNKNOWN) {
        if (current_block->type == COMMAND) {
            command_impl(fd, current_block->command);

            if (current_block->next_block == nullptr) {
                Block* temp = current_block;
                do {
                    fd << '}' << std::endl;
                    temp = temp->parent_block;
                } while (temp->next_block == nullptr);
                
                current_block = temp->next_block;
            } else {
                current_block = current_block->next_block;
            }
        }
        else if (current_block->type == SUBBLOCK) {
            fd << "while (*ptr) {" << std::endl;

            current_block = current_block->child;
        }    

        fd << std::endl;
    }

    end_impl(fd);

    fd.close();

    system(("gcc " + filename + "_inter.c " + "-o " + filename).c_str());
    remove((filename + "_inter.c").c_str());
}
