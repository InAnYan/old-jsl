//
// Created by rusla on 12/18/2023.
//

#ifndef EXPR_HPP
#define EXPR_HPP
#include <variant>
#include <JSLLib/Syntax/AST/Exprs/UnaryExpr.hpp>

#include "Exprs/BinaryExpr.hpp"
#include "Exprs/IntegerLiteralExpr.hpp"

namespace JSL {

using ExprVariant = std::variant<BinaryExpr, UnaryExpr, IntegerLiteralExpr>;

class Expr final : ExprVariant {
public:
    using ExprVariant::ExprVariant;
};

} // JSL

#endif //EXPR_HPP
