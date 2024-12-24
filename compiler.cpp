#include "compiler.h"
using namespace Compiler;


Block* Compiler::parse_blocks(std::string text) {
    Block* Main = new Block;

    Block* current_block = Main;

    int index = 0;
    for (char ch: text) {
        InstructionType inst = parse_instruction(ch);
        switch (inst) {

        case INST_OPEN: {
            current_block->type = SUBBLOCK;

            Block* new_block = new Block;
            new_block->parent_block = current_block;
            current_block->child = new_block;

            current_block = new_block;
        }
        break;
        
        case INST_END: {
            if (current_block->parent_block == nullptr) {
                exit_on_error(69,
                    std::format("Unexpected ] : index {}\n{}", index, text.substr(std::max(0, index - 4), std::min((int)text.size(), index + 4 + 1)))
                );
            }
            if (current_block->prev_block == nullptr) {
                exit_on_error(69,
                    std::format("Empty cycles are banned! : index {}\n{}", index, text.substr(std::max(0, index - 4), std::min((int)text.size(), index + 4 + 1)))
                );
                break;
            }
            current_block = current_block->prev_block;

            Block* new_block = current_block->next_block;
            current_block->next_block = nullptr;

            current_block = current_block->parent_block;
            
            new_block->prev_block = current_block;
            new_block->parent_block = current_block->parent_block;
            current_block->next_block = new_block;

            current_block = new_block;
        }
        break;
        
        default: {
            current_block->type = COMMAND;
            current_block->command = parse_command(inst);

            Block* new_block = new Block;
            new_block->prev_block = current_block;
            new_block->parent_block = current_block->parent_block;
            current_block->next_block = new_block;

            current_block = new_block;
        }
        break;
        }

        index++;
    }

    if (current_block->parent_block != nullptr) {
        exit_on_error(69,
            std::format("Did not find closing ]: index {}\n{}", index, text.substr(std::max(0, index - 4), std::min((int)text.size(), index + 4 + 1)))
        );
    }

    return Main;
}

InstructionType Compiler::parse_instruction(char ch) {
    InstructionType inst = (InstructionType)ch;
    switch (ch) {
    case '>':
    case '<':
    case '+':
    case '-':
    case '.':
    case ',':
    case '[':
    case ']':
        return inst;
    break;
    
    default: {
        exit_on_error(1488,
            std::format("Unknown command: {}", ch)
        );
    }
    break;
    }

    return inst;
}

void Compiler::print_blocks(Block* Main) {
    int tabs = 0;
    Block* current_block = Main;

    while (current_block->type != BLOCK_UNKNOWN) {
        for (int currtabs = 0; currtabs < tabs; currtabs++) {
            std::cout << "  ";
        }

        if (current_block->type == COMMAND) {
            std::cout << (char)current_block->command;

            if (current_block->next_block == nullptr) {
                Block* temp = current_block;
                do {
                    tabs--;
                    std::cout << std::endl;
                    for (int currtabs = 0; currtabs < tabs; currtabs++) {
                        std::cout << "  ";
                    }
                    std::cout << ']';
                    temp = temp->parent_block;
                } while (temp->next_block == nullptr);
                
                current_block = temp->next_block;
            } else {
                current_block = current_block->next_block;
            }
        }
        else if (current_block->type == SUBBLOCK) {
            tabs++;
            std::cout << '[';

            current_block = current_block->child;
        }    

        std::cout << std::endl;
    }
    
}

CommandType Compiler::parse_command(InstructionType inst) {
    return (CommandType)inst;
}

void Compiler::exit_on_error(int code, std::string error) {
    std::cerr << error << std::endl;
    exit(code);
}