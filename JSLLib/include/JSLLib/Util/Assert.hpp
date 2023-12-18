//
// Created by rusla on 12/18/2023.
//

#ifndef ASSERT_HPP
#define ASSERT_HPP

#include <string_view>

#define JSL_ASSERT(expr, errorMsg) \
    JSL::Assert((expr), (#expr), (errorMsg), __LINE__, __FILE__)

#define JSL_BUG(errorMsg) JSL_ASSERT(false, errorMsg)

namespace JSL
{
    void Assert(bool expr, std::string_view exprStr, std::string_view errorMsg, int line, std::string_view fileName);
}

#endif //ASSERT_HPP
