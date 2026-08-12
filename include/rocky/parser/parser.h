#ifndef ROCKY_PARSER_PARSER_H
#define ROCKY_PARSER_PARSER_H

#include <rocky/arena.h>
#include <rocky/adt/linked_list.h>
#include <rocky/parser/ast.h>
#include <rocky/parser/nodes.h>

/** @brief Parser state over a linked list of Token pointers. */
typedef struct Parser {
    /** @brief Token stream (each node data is a Token *). */
    LinkedList* tokens;
    int pos;
    Arena* arena;
} Parser;

void parser_init(Parser* p, LinkedList* tokens, Arena* arena);
Expr* parse_expr(Parser* p, int min_bp);
Stmt* parse_program(Parser* p);

#endif
