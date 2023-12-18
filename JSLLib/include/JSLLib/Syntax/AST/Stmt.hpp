//
// Created by rusla on 12/18/2023.
//

#ifndef STMT_HPP
#define STMT_HPP
#include "Stmts/ExprStmt.hpp"
#include "Stmts/PrintStmt.hpp"

namespace JSL {
using StmtVariant = std::variant<ExprStmt, PrintStmt>;
class Stmt final : StmtVariant {
public:
    using StmtVariant::StmtVariant;
};

} // JSL

#endif //STMT_HPP
