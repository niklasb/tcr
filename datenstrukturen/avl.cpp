#include <algorithm>
struct avl_t {
    avl_t *left, *right, *up;
    int height, size, key;

    void reset(); int balance(); avl_t *leftrot(); avl_t *rightrot(); avl_t *fixup();
    avl_t *latch(avl_t *, avl_t *); avl_t *find(int);
    avl_t *minimum(); avl_t *maximum(); avl_t *pred(); avl_t *succ();
};
inline void avl_t::reset() {
    height = max(left != NULL ? left->height + 1 :0, right != NULL ? right->height + 1 :0);
    size = 1 + (left != NULL ? left->size : 0) + (right != NULL ? right->size : 0);
}
inline int avl_t::balance() {
    return (right != NULL ? right->height + 1 : 0) - (left != NULL ? left->height + 1 : 0);
}
avl_t *avl_t::leftrot() {
    avl_t *temp = right;
    if ((right = temp->left) != NULL) right->up = this;
    temp->left = this; temp->up = up; up = temp;
    reset(); temp->reset();
    return temp;
}
avl_t *avl_t::rightrot() {
    avl_t *temp = left;
    if ((left = temp->right) != NULL) left->up = this;
    temp->right = this; temp->up = up; up = temp;
    reset(); temp->reset();
    return temp;
}
avl_t *avl_t::fixup() {
    int bal = balance();
    if (bal == 2) {
        if (right->balance() < 0) right = right->rightrot();
        return leftrot();
    } else if (bal == -2) {
        if (left->balance() > 0) left = left->leftrot();
        return rightrot();
    }
    return this;
}
avl_t *avl_t::latch(avl_t *root, avl_t *parent) {
    if (root == NULL) { left = right = NULL; up = parent; reset(); return this; }
    if (key < root->key) root->left = latch(root->left, root);
    else if (root->key < key) root->right = latch(root->right, root);
    root->reset();
    return root->fixup();
}
avl_t *avl_t::find(int value) {
    avl_t *temp = this;
    while (temp != NULL) {
        if (value < temp->key) temp = temp->left;
        else if (temp->key < value) temp = temp->right;
        else return temp;
    }
    return NULL;
}
avl_t *avl_t::minimum() {
    avl_t *temp = this;
    while (temp->left != NULL) temp = temp->left;
    return temp;
}
avl_t *avl_t::maximum() {
    avl_t *temp = this;
    while (temp->right != NULL) temp = temp->right;
    return temp;
}
avl_t *avl_t::pred() {
    avl_t *temp = this;
    if (left != NULL) return left->maximum();
    while (temp->up != NULL && temp == temp->up->left) temp = temp->up;
    return temp->up;
}
avl_t *avl_t::succ() {
    avl_t *temp = this;
    if (right != NULL) return right->minimum();
    while (temp->up != NULL && temp == temp->up->right) temp = temp->up;
    return temp->up;
}
