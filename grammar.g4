grammar JSL;

script : decl*;

decl
    : stmt;

var_decl : 'var' IDENTIFIER ('=' expr)? eos;

stmt
    : print_stmt
    | expr_stmt;

print_stmt : 'print' expr;

block_stmt : '{' stmt* '}';

// Well, I forgot how to deal with if ambiguity, so I left block_stmts there.
// In fact, in the programm they are just stmt.
if_stmt : 'if' block_stmt ('else' block_stmt)?;

expr_stmt : expr eos;

expr : equality;

// They are supposed to be left associative.

equality : logical_or (('==' | '!=') logical_or)*;
logical_or : logical_and ('||' logical_and)*;
logical_and : comparison ('&&' comparison)*;
comparison : term (('>' | '<' | '>=' | '<=') term)*;
term : factor (('+' | '-') factor)*;
factor : unary (('*' | '/') unary)*;

unary
    : '+' unary
    | '-' unary
    | '!' unary
    | primary;

primary : INTEGER | grouping | bool;

grouping : '(' expr ')';

bool : 'true' | 'false';

eos : ';'+;

INTEGER : [0-9]+;
IDENTIFIER : [a-zA-Z][a-zA-Z0-9_]*;