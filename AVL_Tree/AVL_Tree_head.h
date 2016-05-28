#ifndef AVL_TREE_HEAD_H
#define AVL_TREE_HEAD_H


template<class Item>
struct AVLnode {
    enum balance {
        dleft = -1, bal, dright
    };
    balance status;
    AVLnode *left, *right, *parent;
    Item data;

    AVLnode(const Item &dat, AVLnode *par) : status(bal), left(0), right(0), parent(par), data(dat) { };
};

template<class Item>
void swap_data(AVLnode<Item> *n1, AVLnode<Item> *n2) {
    Item d = n1->data;
    n1->data = n2->data;
    n2->data = d;
}

template<class Item>
class AVLtree {
    AVLnode<Item> *top;
    int m_size;
    int m_height;

public:
    AVLtree();

    AVLtree(const Item &);

    ~AVLtree();

    int size() const;

    int height() const;

    void print_AVL() const;

    void add(const Item &data);

private:
    void del_subtree(AVLnode<Item> *);

    int height(AVLnode<Item> *) const;

    void print_AVL(AVLnode<Item> *) const;

    void add_item(const Item &, AVLnode<Item> *);

    void set_status(AVLnode<Item> *);

    void SingleRotateRight(AVLnode<Item> *);

    void SingleRotateLeft(AVLnode<Item> *);
};

template<class Item>
AVLtree<Item>::AVLtree() {
    top = 0;
    m_size = 0;
    m_height = 0;
}

template<class Item>
AVLtree<Item>::AVLtree(const Item &data) {
    top = new AVLnode<Item>(data, 0);
    m_size = 1;
    m_height = 1;
}

template<class Item>
AVLtree<Item>::~AVLtree() {
    del_subtree(top);
}

template<class Item>
void AVLtree<Item>::del_subtree(AVLnode<Item> *subtop) {
    if (subtop != 0) {
        if (subtop->left != 0) del_subtree(subtop->left);
        if (subtop->right != 0) del_subtree(subtop->right);
        delete subtop;
    }
}

template<class Item>
int AVLtree<Item>::size() const {
    return m_size;
}

template<class Item>
int AVLtree<Item>::height() const {
    return height(top);
}

template<class Item>
int AVLtree<Item>::height(AVLnode<Item> *subtop) const {
    if (subtop == 0) return 0;
    int hl = height(subtop->left);
    int hr = height(subtop->right);
    return 1 + std::max(hl, hr);
}

template<class Item>
void AVLtree<Item>::print_AVL() const {
    print_AVL(top);
}

template<class Item>
void AVLtree<Item>::print_AVL(AVLnode<Item> *subtop) const {

    if (subtop == 0) return;

    if (subtop->right != 0)
        print_AVL(subtop->right);
    for (int i = 1; i <= height() - height(subtop); i++)
        cout << "\t";
    cout << subtop->data << endl;
    if (subtop->left != 0)
        print_AVL(subtop->left);
}

template<class Item>
void AVLtree<Item>::add(const Item &data) {
    if (top == 0) {
        top = new AVLnode<Item>(data, 0);
        m_size = 1;
        m_height = 1;
        return;
    }
    else
        add_item(data, top);
}

template<class Item>
void AVLtree<Item>::add_item(const Item &data, AVLnode<Item> *subtop) {

    if (subtop->data > data) {
        if (subtop->left != 0) {
            add_item(data, subtop->left);

            if (subtop->status == AVLnode<Item>::dleft) {
                if (subtop->left->status == AVLnode<Item>::dleft)
                    SingleRotateRight(subtop);

                else if (subtop->left->status == AVLnode<Item>::dright) {
                    SingleRotateLeft(subtop->left);
                    SingleRotateRight(subtop);
                }

            }
        }
        else {
            subtop->left = new AVLnode<Item>(data, subtop);
            m_size++;
        }

    }
    else {
        if (subtop->right != 0) {
            add_item(data, subtop->right);

            if (subtop->status == AVLnode<Item>::dright) {
                if (subtop->right->status == AVLnode<Item>::dright)
                    SingleRotateLeft(subtop);

                else if (subtop->right->status == AVLnode<Item>::dleft) {
                    SingleRotateRight(subtop->right);
                    SingleRotateLeft(subtop);
                }

            }
        }
        else {
            subtop->right = new AVLnode<Item>(data, subtop->right);
            m_size++;
        }
    }
    set_status(subtop);

}

template<class Item>
void AVLtree<Item>::set_status(AVLnode<Item> *subtop) {
    subtop->status = (AVLnode<Item>::balance) (height(subtop->right) - height(subtop->left));
    if (subtop->left != 0)
        set_status(subtop->left);
    if (subtop->right != 0)
        set_status(subtop->right);
}

template<class Item>
void AVLtree<Item>::SingleRotateRight(AVLnode<Item> *node) {
    AVLnode<Item> *Lnode = node->left;
    AVLnode<Item> *LLnode = Lnode->left;
    swap_data(Lnode, node);

    Lnode->left = Lnode->right;
    Lnode->right = node->right;
    node->right = Lnode;
    node->left = LLnode;
}

template<class Item>
void AVLtree<Item>::SingleRotateLeft(AVLnode<Item> *node) {
    AVLnode<Item> *Rnode = node->right;
    AVLnode<Item> *RRnode = Rnode->right;
    swap_data(Rnode, node);

    Rnode->right = Rnode->left;
    Rnode->left = node->left;
    node->left = Rnode;
    node->right = RRnode;
}


#endif
