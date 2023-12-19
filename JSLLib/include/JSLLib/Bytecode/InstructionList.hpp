//
// Created by rusla on 19.12.2023.
//

#ifndef INSTRUCTIONLIST_HPP
#define INSTRUCTIONLIST_HPP

#define JSL_INSTRUCTION_LIST(o) \
    o(PushConstant, Constant)   \
    o(Pop, Simple)              \
    o(Print, Simple)            \
    o(Return, Simple)

#endif //INSTRUCTIONLIST_HPP
