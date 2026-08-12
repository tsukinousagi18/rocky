/**
 * @file parser.h
 * @brief Pratt parser entry points and parser state.
 * @ingroup Parser
 */

#ifndef ROCKY_PARSER_PARSER_H
#define ROCKY_PARSER_PARSER_H

#include <rocky/parser/ast.h>
#include <rocky/arena.h>
#include <rocky/adt/linked_list.h>

/** @brief Parser state over a linked list of Token pointers. */
typedef struct {
    /** @brief Token stream (each node data is a Token *). */
    LinkedList *tokens;
    /** @brief Current token index. */
    int         pos;
    /** @brief Arena used for AST node allocation. */
    Arena      *arena;
} Parser;

/**
 * @brief Initializes parser state.
 * @param p Parser output state.
 * @param tokens Linked list of Token * (caller owns list and tokens).
 * @param arena Arena allocator used for AST nodes.
 */
void  parser_init(Parser *p, LinkedList *tokens, Arena *arena);

/**
 * @brief Parses expression using Pratt binding power recursion.
 * @param p Parser to advance.
 * @param min_bp Minimum binding power for this parse level.
 * @return Root AST expression node.
 */
Expr *parse_expr(Parser *p, int min_bp);

#endif
