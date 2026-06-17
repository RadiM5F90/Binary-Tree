
#include "linked_list.h"

#define BINARY_TREE_SUCCESS 0;
#define BINARY_TREE_ERROR_NULL -1;
#define BINARY_TREE_ERROR_NODE_NULL -2;
#define BINARY_TREE_ERROR_EMPTY -3;
#define BINARY_TREE_ERROR_NOT_FOUND -4;


/*
 * _binary_tree and _tree_node structs;
 * Create and destroy the tree;
 * Set the root;
 * tree size, tree height, leaf count and node level;
 * pre-order in-order and post-order recursive and iterative (using Linked Lists)
 *
 * Create and destroy the tree_node;
 * Set left and right nodes;
 */

typedef struct _binary_tree* binary_tree;
typedef struct _tree_node* tree_node;

binary_tree binary_tree_create();

void binary_tree_destroy(binary_tree* _tree);

int set_root(binary_tree _tree, tree_node _root);

int binary_tree_size(binary_tree _tree);

int binary_tree_height(binary_tree _tree);

int leaf_count(binary_tree _tree);

int node_level(binary_tree _tree, int _value);



list pre_order_recursive(binary_tree _tree);

list in_order_recursive(binary_tree _tree);

list post_order_recursive(binary_tree _tree);



list pre_order_iterative(binary_tree _tree);

list in_order_iterative(binary_tree _tree);

list post_order_iterative(binary_tree _tree);

list tree_bfs(binary_tree _tree);



tree_node create_tree_node(int _value);

void destroy_tree_node(tree_node* _node);

int tree_node_set_left(tree_node _parent, tree_node _child);

int tree_node_set_right(tree_node _parent, tree_node _child);
