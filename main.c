#include <stdio.h>
#include "binary_tree.h"


void print_list(const list _list) {
    iterator _it = iterator_create(_list);

    while (has_iterator_next(_it)) {
        int val = iterator_next(_it);
        printf("%d\n", val);
    }
    destroy_iterator(&_it);
    printf("\n");
}

int main() {
    binary_tree _tree = binary_tree_create();

    tree_node n1 = create_tree_node(1);
    tree_node n2 = create_tree_node(2);
    tree_node n3 = create_tree_node(3);
    tree_node n4 = create_tree_node(4);
    tree_node n5 = create_tree_node(5);

    set_root(_tree, n1);
    tree_node_set_left(n1, n2);
    tree_node_set_right(n1, n3);

    tree_node_set_left(n2, n4);
    tree_node_set_right(n2, n5);


    printf("--------Recursive Pre-Order--------\n");
    list pre_rec = pre_order_recursive(_tree);
    print_list(pre_rec);
    destroy_list(&pre_rec);


    printf("--------Recursive In-Order--------\n");
    list in_rec = in_order_recursive(_tree);
    print_list(in_rec);
    destroy_list(&in_rec);


    printf("--------Recursive Post-Order--------\n");
    list post_rec = post_order_recursive(_tree);
    print_list(post_rec);
    destroy_list(&post_rec);


    printf("--------BFS--------\n");
    list bfs = tree_bfs(_tree);
    print_list(bfs);
    destroy_list(&bfs);


    int size =  binary_tree_size(_tree);
    int height = binary_tree_height(_tree);
    int leaves = leaf_count(_tree);
    int level = node_level(_tree, 5);


    printf("\nTree size: %d\n", size);
    printf("Height: %d\n", height);
    printf("Leaves: %d\n", leaves);
    printf("Level of the node with value 5: %d\n", level);

    binary_tree_destroy(&_tree);

    return 0;
}

