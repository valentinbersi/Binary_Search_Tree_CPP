#ifndef BSTNODE_HPP
#define BSTNODE_HPP

#include <vector>
#include <queue>
#include <algorithm>

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
class BSTNode {

private:
    T element{};
    BSTNode<T, less, equal> *parent;
    BSTNode<T, less, equal> *left;
    BSTNode<T, less, equal> *right;

    static const std::size_t TWO_CHILDREN = 2;
    static const std::size_t ONE_CHILD = 1;
    static const std::size_t NO_CHILDREN = 0;

    // Pre: ~
    // Pos: returns the number of children a node has
    size_t number_of_children();

    // Pre: ~
    // Pos: returns the minimun node of the subtree
    BSTNode<T, less, equal> *minimum();

    // Pre: ~
    // Pos: returns the successor of a node
    BSTNode<T, less, equal> *successor();

    // Pre: ~
    // Pos: returns true if the node is the left child of its parent
    bool is_left_child();

    // Pre: the node is a leaf
    // Pos: disconnects the parent of the node from its corresponding child
    void disconnect();

    // Pre: ~
    // Pos: disconnects the children of the node
    void disconnect_children();

    // Pre: the node has only one child
    // Pos: connects the right child of the node with its parent, assigning the correct child to the parent
    void right_bypass();

    // Pre: ~
    // Pos: replaces the node with replace_node, this means that the parent and children from the node are assigned to
    // replace_node
    void replace(BSTNode<T, less, equal> *replacement_node);

    // Pre: ~
    // Pos: deletes the node without children and returns the new root if the node was the root
    BSTNode<T, less, equal> *remove_with_0_children();

    // Pre: ~
    // Pos: deletes the node with one child and returns the new root if the node was the root
    BSTNode<T, less, equal> *remove_with_1_child();

    // Pre: ~
    // Pos: deletes the node with two children and returns the new root if the node was the root
    BSTNode<T, less, equal> *remove_with_2_children();

public:
    // Constructor.
    explicit BSTNode(T element);

    // Pre: ~
    // Post: adds new_element to the tree.
    void add(T new_element);

    // Pre: ~
    // Post: removes the element from the tree and returns the new root, if there is one.
    BSTNode<T, less, equal> *remove(T element_to_remove);

    // Pre: ~
    // Post: returns true if the element is in the subtree.
    bool find(T element);

    // Pre: ~
    // Post: loads in elements the elements of the subtree in inorder.
    void inorder(std::vector<T> &elements);

    // Pre: ~
    // Post: loads in elements the elements of the subtree in preorder.
    void preorder(std::vector<T> &elements);

    // Pre: ~
    // Post: loads in elements the elements of the subtree in postorder.
    void postorder(std::vector<T> &elements);

    // Pre: ~
    // Post: loads in elements the elements of the subtree in width.
    void width_order(std::queue<BSTNode<T, less, equal> *> &nodes, std::vector<T> &elements);

    // Pre: ~
    // Post: executes the method/function in the subtree.
    void execute(void method(T));

    // Pre: ~
    // Pos: returns the height of the subtree.
    size_t height();

    // Destructor.
    ~BSTNode();
};

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
size_t BSTNode<T, less, equal>::number_of_children() {
    if (left && right) return TWO_CHILDREN;
    if (left || right) return ONE_CHILD;
    return NO_CHILDREN;
}


template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
BSTNode<T, less, equal> *BSTNode<T, less, equal>::minimum() {
    if (left) return left->minimum();
    return this;
}


template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
BSTNode<T, less, equal> *BSTNode<T, less, equal>::successor() {
    if (right) return right->minimum();

    BSTNode<T, less, equal> *aux_parent = parent;
    BSTNode<T, less, equal> *aux_this = this;
    while (aux_parent && aux_this == aux_parent->hijo_derecho) {
        aux_this = aux_parent;
        aux_parent = aux_this->parent;
    }

    if (aux_parent) return aux_parent;

    return nullptr;
}


template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
bool BSTNode<T, less, equal>::is_left_child() {
    if (!parent) return false;
    if (less(element, parent->element)) return true;
    return false;
}


template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
void BSTNode<T, less, equal>::disconnect() {
    is_left_child() ? parent->left = nullptr : parent->right = nullptr;
}


template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
void BSTNode<T, less, equal>::disconnect_children() {
    left = nullptr;
    right = nullptr;
}


template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
void BSTNode<T, less, equal>::right_bypass() {
    if (is_left_child()) {
        parent->left = right;
        right->parent = parent;
    } else {
        parent->right = right;
        right->parent = parent;
    }
}


template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
void BSTNode<T, less, equal>::replace(BSTNode<T, less, equal> *replacement_node) {
    replacement_node->parent = parent;
    replacement_node->right = right;
    replacement_node->left = left;

    if (parent) is_left_child() ? parent->left = replacement_node : parent->right = replacement_node;
    if (left) left->parent = replacement_node;
    if (right) right->parent = replacement_node;
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
BSTNode<T, less, equal> *BSTNode<T, less, equal>::remove_with_0_children() {
    if (parent) is_left_child() ? parent->left = nullptr : parent->right = nullptr;
    delete this;
    return nullptr;
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
BSTNode<T, less, equal> *BSTNode<T, less, equal>::remove_with_1_child() {
    if (!parent) {
        BSTNode<T, less, equal> *new_root;
        if (left) {
            left->parent = nullptr;
            new_root = left;

        } else {
            right->parent = nullptr;
            new_root = right;
        }

        disconnect_children();
        delete this;
        return new_root;
    }

    if (left) {
        is_left_child() ? parent->left = left : parent->right = left;
        left->parent = parent;

    } else {
        is_left_child() ? parent->left = right : parent->right = right;
        right->parent = parent;
    }

    disconnect_children();
    delete this;
    return nullptr;
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
BSTNode<T, less, equal> *BSTNode<T, less, equal>::remove_with_2_children() {
    BSTNode<T, less, equal> *replacement_node = successor();

    switch (replacement_node->number_of_children()) {
        case NO_CHILDREN:
            replacement_node->disconnect();
            break;

        default:
            replacement_node->right_bypass();
    }

    replace(replacement_node);
    disconnect_children();

    if (!parent) {
        delete this;
        return replacement_node;
    }

    delete this;
    return nullptr;
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
BSTNode<T, less, equal>::BSTNode(T element) {
    this->element = element;
    parent = nullptr;
    right = nullptr;
    left = nullptr;
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
void BSTNode<T, less, equal>::add(T new_element) {
    if (less(new_element, element)) {
        if (left) {
            left->add(new_element);
        } else {
            left = new BSTNode<T, less, equal>(new_element);
            left->parent = this;
        }

    } else {
        if (right) {
            right->add(new_element);
        } else {
            right = new BSTNode<T, less, equal>(new_element);
            right->parent = this;
        }
    }
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
BSTNode<T, less, equal> *BSTNode<T, less, equal>::remove(T element_to_remove) {
    if (less(element_to_remove, element) && left) return left->remove(element_to_remove);

    if (!equal(element_to_remove, element) && right) return right->remove(element_to_remove);

    switch (number_of_children()) {
        case NO_CHILDREN:
            return remove_with_0_children();

        case ONE_CHILD:
            return remove_with_1_child();

        default:
            return remove_with_2_children();
    }
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
bool BSTNode<T, less, equal>::find(T element_to_find) {
    if (equal(element_to_find, element)) return true;

    if (less(element, this->element)) {
        if (left) return left->find(element_to_find);
        return false;
    }

    if (right) return right->find(element_to_find);

    return false;
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
void BSTNode<T, less, equal>::inorder(std::vector<T> &elements) {
    if (left) left->inorder(elements);

    elements.push_back(element);

    if (right) right->inorder(elements);
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
void BSTNode<T, less, equal>::preorder(std::vector<T> &elements) {
    elements.push_back(element);

    if (left) left->preorder(elements);

    if (right) right->preorder(elements);
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
void BSTNode<T, less, equal>::postorder(std::vector<T> &elements) {
    if (left) left->postorder(elements);

    if (right) right->postorder(elements);

    elements.push_back(element);
}


template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
void BSTNode<T, less, equal>::width_order(std::queue<BSTNode<T, less, equal> *> &nodes, std::vector<T> &elements) {
    elements.push_back(element);

    if (left) nodes.push(left);

    if (right) nodes.push(right);
}


template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
void BSTNode<T, less, equal>::execute(void (*method)(T)) {
    if (left) {
        left->execute(method);
    }

    if (right) {
        right->execute(method);
    }

    method();
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
size_t BSTNode<T, less, equal>::height() {
    if (right && left) return std::max(right->height(), left->height()) + 1;

    if (left) return left->height() + 1;

    if (right) return right->height() + 1;

    return 1;
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
BSTNode<T, less, equal>::~BSTNode() {
    parent = nullptr;
    delete left;
    delete right;
    right = nullptr;
    left = nullptr;
}

#endif //BSTNODE_HPP
