#include "tree.h"
#include "transform.h"
#include <math.h>

int match_power(Tree *t)
{
    return ((*t) != NULL) && ((*t)->node.type == OPERATOR)
           && ((*t)->node.data.operator_name == '^')

           && (((*t)->left->node.type == INTEGER &&
            (*t)->left->node.data.value_int != 0) ||
               ((*t)->left->node.type == FLOATING &&
            (*t)->left->node.data.value_float != 0) ||
               ((*t)->left->node.type == VARIABLE))
            
           && (((*t)->right->node.type == OPERATOR)
           && ((*t)->right->node.data.operator_name == '-'))
           
           && (((*t)->right->left->node.type == INTEGER &&
            (*t)->left->node.data.value_int != 0) ||
               ((*t)->right->left->node.type == VARIABLE))

           && (((*t)->right->right->node.type == INTEGER &&
            (*t)->left->node.data.value_int != 0) ||
               ((*t)->right->right->node.type == VARIABLE));
}

void transform_power(Tree *t)
{
    //renaming operators
    (*t)->node.data.operator_name = '/';
    (*t)->right->node.data.operator_name = '^';

    //alllocating memory for leaves
    (*t)->left->left = (Tree) malloc(sizeof(struct tree_node));
    (*t)->left->right = (Tree) malloc(sizeof(struct tree_node));
    
    //moving b
    float num = 14;
    char ch;
    if ((*t)->right->left->node.type == INTEGER) {
        num = (*t)->right->left->node.data.value_int;
        (*t)->left->right->node.type = INTEGER;
        (*t)->left->right->node.data.value_int = num;
        //(*t)->right->left->node.data.value_int = NULL;
    } else {
        ch = (*t)->right->left->node.data.variable_name;
        (*t)->left->right->node.type = VARIABLE;
        (*t)->left->right->node.data.operator_name = ch;
        //(*t)->right->left->node.data.variable_name = NULL;
    }

    float base = 0;
    // moving a
    if ((*t)->left->node.type == INTEGER) {
        base = (*t)->left->node.data.value_int;
        (*t)->left->left->node.type = INTEGER;
        (*t)->left->left->node.data.value_int = (int) base;
        (*t)->right->left->node.type = INTEGER;
        (*t)->right->left->node.data.value_int = (int) base;
        //(*t)->left->node.data.value_int = NULL;
    } else if ((*t)->left->node.type == FLOATING) {
        base = (*t)->left->node.data.value_float;
        (*t)->left->left->node.type = FLOATING;
        (*t)->left->left->node.data.value_float = base;
        (*t)->right->left->node.type = FLOATING;
        (*t)->right->left->node.data.value_float = base;
        //free((*t)->left->node.data.value_float);
    } else {
        char ch = (*t)->left->node.data.variable_name;
        (*t)->left->left->node.type = VARIABLE;
        (*t)->left->left->node.data.variable_name = ch;
        (*t)->right->left->node.type = VARIABLE;
        (*t)->right->left->node.data.variable_name = ch;
        //(*t)->left->node.data.variable_name = NULL;
    }
    
    //a to oper
    (*t)->left->node.type = OPERATOR;
    (*t)->left->node.data.operator_name = '^';

    (*t)->left->left->left = NULL;
    (*t)->left->left->right = NULL;
    (*t)->left->right->left = NULL;
    (*t)->left->right->right = NULL;
}

void tree_transform(Tree *t)
{
    if ((*t) != NULL) {
        tree_transform(&((*t)->left));
        tree_transform(&((*t)->right));

        if (match_power(t)) {
            transform_power(t);
        }
    }
}
