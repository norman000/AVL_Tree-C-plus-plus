#include <iostream>
#include "AVL_Tree_head.h"

using namespace std;

int main() {

    AVLtree<int> tree;

    for (int i = 7; i >= 1; i--)
        tree.add(i);

    tree.print_AVL();

    system("pause");
    return 0;
}