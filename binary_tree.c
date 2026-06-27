#include <stdlib.h>

#include "binary_tree.h"
#include "list_stack.h"
#include "list_queue.h"
#include "linked_list.h"

#define IS_LEAF(n) (n->left == NULL && n->right == NULL)


// Private functions
void destroy_nodes(tree_node _node);
int compute_tree_size(tree_node _node);
int compute_tree_height(tree_node _node);
int count_leaves(tree_node _node);
int compute_tree_node_levels(tree_node _node, int value);


// TREE Implementation

struct _tree_node {
    int value;
    struct _tree_node* left;
    struct _tree_node* right;
};

struct _binary_tree {
    tree_node root;
};

binary_tree binary_tree_create() {
    binary_tree tree = malloc(sizeof(struct _binary_tree));
    if (tree != NULL) tree->root = NULL;

    return tree;
}

void binary_tree_destroy(binary_tree* _tree) {
    if (_tree == NULL || *_tree == NULL) return;

    destroy_nodes((*_tree)->root);
    free(*_tree);
    *_tree = NULL;
}

int set_root(binary_tree _tree, tree_node _root) {
    if (_tree == NULL) return BINARY_TREE_ERROR_NULL;

    _tree->root = _root;
    return BINARY_TREE_SUCCESS;
}

int binary_tree_size(binary_tree _tree) {
    if (_tree == NULL) return BINARY_TREE_ERROR_NULL;

    return compute_tree_size(_tree->root);
}

int binary_tree_height(binary_tree _tree) {
    if (_tree == NULL) return BINARY_TREE_ERROR_NULL;
    if (_tree->root == NULL) return BINARY_TREE_ERROR_EMPTY;

    return compute_tree_height(_tree->root);
}

int leaf_count(binary_tree _tree) {
    if (_tree == NULL) return BINARY_TREE_ERROR_NULL;

    return count_leaves(_tree->root);
}

int node_level(binary_tree _tree, int _value) {
    if (_tree == NULL) return BINARY_TREE_ERROR_NULL;

    int level = compute_tree_node_levels(_tree->root, _value);

    return (level >= 0) ? level : BINARY_TREE_ERROR_NOT_FOUND;
}



// NODE Implementation

tree_node create_tree_node(int _value) {
    tree_node _node = malloc(sizeof(struct _tree_node));
    if (_node != NULL) {
        _node->value = _value;
        _node->left = _node->right = NULL;
    }
    return _node;
}

void destroy_tree_node(tree_node* _node) {
    if (_node == NULL || *_node == NULL) return;

    free(*_node);
    *_node = NULL;
}

int tree_node_set_left(tree_node _parent, tree_node _child) {
    if (_parent == NULL) return BINARY_TREE_ERROR_NODE_NULL;

    _parent->left = _child;
    return BINARY_TREE_SUCCESS;
}

int tree_node_set_right(tree_node _parent, tree_node _child) {
    if (_parent == NULL) return BINARY_TREE_ERROR_NODE_NULL;

    _parent->right = _child;
    return BINARY_TREE_SUCCESS;
}


// Recursive Tree Visits

// PRE-ORDER
void tree_pre_order_rec(tree_node _node, list _list) {
    if (_node == NULL) return;

    insert_back(_list, _node->value);
    tree_pre_order_rec(_node->left, _list);
    tree_pre_order_rec(_node->right, _list);
}
list pre_order_recursive(binary_tree _tree) {
    if (_tree == NULL) return NULL;

    list _list = create_list();
    tree_pre_order_rec(_tree->root, _list);
    return _list;
}


// IN-ORDER
void tree_in_order_rec(tree_node _node, list _list) {
    if (_node == NULL) return;

    tree_in_order_rec(_node->left, _list);
    insert_back(_list, _node->value);
    tree_in_order_rec(_node->right, _list);
}
list in_order_recursive(binary_tree _tree) {
    if (_tree == NULL) return NULL;

    list _list = create_list();
    tree_in_order_rec(_tree->root, _list);

    return _list;
}


// POST-ORDER
void tree_post_order_rec(tree_node _node, list _list) {
    if (_node == NULL) return;

    tree_post_order_rec(_node->left, _list);
    tree_post_order_rec(_node->right, _list);
    insert_back(_list, _node->value);
}
list post_order_recursive(binary_tree _tree) {
    if (_tree == NULL) return NULL;

    list _list = create_list();
    tree_post_order_rec(_tree->root, _list);

    return _list;
}


// ITERATIVE FUNCTIONS
list pre_order_iterative(binary_tree _tree) {
    if (_tree == NULL) return NULL;

    list _list = create_list();
    stack _s = create_stack(1000);
    stack_push(_s, _tree->root);

    while (!stack_is_empty(_s)) {
        tree_node _node;
        stack_pop(_s, (void**)&_node);
        insert_back(_list, _node->value);

        if (_node->right) stack_push(_s, _node->right);
        if (_node->left) stack_push(_s, _node->left);
    }
    destroy_stack(&_s);
    return _list;
}


list in_order_iterative(binary_tree _tree) {
    if (_tree == NULL) return NULL;

    list _list = create_list();
    stack _s = create_stack(1000);
    tree_node _current = _tree->root;

    while (_current != NULL || !stack_is_empty(_s)) {
        while (_current != NULL) {
            stack_push(_s, _current);
            _current = _current->left;
        }
        stack_pop(_s, (void**)&_current);
        insert_back(_list, _current->value);
        _current = _current->right;
    }
    destroy_stack(&_s);
    return _list;
}


list post_order_iterative(binary_tree _tree) {
    if (_tree == NULL) return NULL;

    list _list = create_list();
    stack s1 = create_stack(1000);
    stack s2 = create_stack(1000);
    stack_push(s1, _tree->root);

    while (!stack_is_empty(s1)) {
        tree_node _node;
        stack_pop(s1, (void**)&_node);
        stack_push(s2, _node);

        if (_node->left) stack_push(s1, _node->left);
        if (_node->right) stack_push(s1, _node->right);
    }

    while (!stack_is_empty(s2)) {
        tree_node _node;
        stack_pop(s2, (void**)&_node);
        insert_back(_list, _node->value);
    }
    destroy_stack(&s1);
    destroy_stack(&s2);

    return _list;
}



// Iterative BFS
list tree_bfs(binary_tree _tree) {
    if (_tree == NULL) return NULL;

    list _list = create_list();
    queue _q = create_queue(1000);

    enqueue(_q, _tree->root);

    while (!queue_is_empty(_q)) {
        tree_node _node;
        dequeue(_q, (void**)&_node);
        insert_back(_list, _node->value);

        if (_node->left) enqueue(_q, _node->left);
        if (_node->right) enqueue(_q, _node->right);
    }
    queue_destroy(&_q);
    return _list;
}



// Private Functions
void destroy_nodes(tree_node _node) {
    if (_node == NULL) return;

    destroy_nodes(_node->left);
    destroy_nodes(_node->right);
    free(_node);
}

int compute_tree_size(tree_node _node) {
    if (_node == NULL) return 0;
    return 1 + compute_tree_size(_node->left) + compute_tree_size(_node->right);
}

int compute_tree_height(tree_node _node) {
    if (_node == NULL) return -1;

    int left_height = compute_tree_height(_node->left);
    int right_height = compute_tree_height(_node->right);

    return (left_height > right_height ? left_height : right_height) + 1;
}
int count_leaves(tree_node _node) {
    if (_node == NULL) return 0;

    if (IS_LEAF(_node)) return 1;
    return count_leaves(_node->left) + count_leaves(_node->right);
}

int compute_tree_node_levels(tree_node _node, int value) {
    if (_node == NULL) return -1;
    if (_node->value == value) return 0;

    int left = compute_tree_node_levels(_node->left, value);
    int right = compute_tree_node_levels(_node->right, value);

    if (left >= 0) return left + 1;
    if (right >= 0) return right + 1;

    return -1;
}
