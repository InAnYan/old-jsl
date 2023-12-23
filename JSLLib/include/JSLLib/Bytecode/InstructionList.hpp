//
// Created by rusla on 19.12.2023.
//

#ifndef INSTRUCTIONLIST_HPP
#define INSTRUCTIONLIST_HPP

#define JSL_INSTRUCTION_LIST(o) \
    o(PushConstant, Constant)   \
    o(Pop, Simple)              \
    o(Print, Simple)            \
    o(Return, Simple)           \
    o(Negate, Simple)           \
    o(Not, Simple)              \
    o(Add, Simple)              \
    o(Subtract, Simple)         \
    o(Multiply, Simple)         \
    o(Divide, Simple)           \
    o(Equal, Simple)            \
    o(Greater, Simple)          \
    o(Less, Simple)

#endif //INSTRUCTIONLIST_HPP
