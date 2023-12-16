#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <exception>
#include "BSTNode.hpp"

class FrequencyException : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "The element is already in the tree.";
    }
};

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
class BSTree {
private:
    BSTNode<T, less, equal> *root;
    size_t _size;

    const size_t EMPTY = 0;
public:
    // Constructor.
    BSTree();

    // Copy constructor.
    BSTree(const BSTree &tree);

    // Assign operator
    BSTree<T, less, equal> &operator=(const BSTree &tree);

    // Pre: new_element can´t be in the tree.
    // Post: adds new_element to the tree. If the tree is empty, it creates a new root.
    void add(T new_element);

    // Pre: -
    // Post: deletes the element from the tree. If it doesn´t exist, it does nothing.
    void remove(T element);

    // Pre: -
    // Post: returns true if the element is in the tree. If there are no elements, it returns false.
    [[nodiscard]] bool find(T element);

    // Pre: -
    // Post: returns the inorder traversal.
    [[nodiscard]] std::vector<T> inorder();

    // Pre: -
    // Post: returns the preorder traversal.
    [[nodiscard]] std::vector<T> preorder();

    // Pre: -
    // Post: returns the postorder traversal.
    [[nodiscard]] std::vector<T> postorder();

    // Pre: -
    // Post: returns the width order traversal.
    [[nodiscard]] std::vector<T> width_order();

    // Pre: -
    // Post: executes the method/function in each node.
    void execute(void method(T));

    // Pre: -
    // Post: returns the number of elements in the tree.
    [[nodiscard]] std::size_t size();

    // Pre: ~
    // Pos: returns the height of the tree, if the tree is empty it returns 0.
    [[nodiscard]] std::size_t height();

    // Pre: -
    // Post: returns true if the tree is empty.
    [[nodiscard]] bool empty();

    // Destructor.
    ~BSTree();
};

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
BSTree<T, less, equal>::BSTree() {
    root = nullptr;
    _size = 0;
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
BSTree<T, less, equal>::BSTree(const BSTree<T, less, equal> &tree) {
    root = nullptr;
    _size = 0;

    std::vector<T> elements = tree.width_order();
    for (T &element: elements) {
        add(element);
    }
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
BSTree<T, less, equal> &BSTree<T, less, equal>::operator=(const BSTree<T, less, equal> &tree) {
    BSTree<T, less, equal> aux(tree);

    root = nullptr;
    _size = 0;

    std::vector<T> elements = aux.width_order();
    for (T &element: elements) {
        add(element);
    }

    return *this;
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
void BSTree<T, less, equal>::add(T new_element) {
    if (find(new_element)) throw FrequencyException();

    if (empty()) {
        root = new BSTNode<T, less, equal>(new_element);

    } else {
        root->add(new_element);
    }

    _size++;
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
void BSTree<T, less, equal>::remove(T element) {
    if (find(element)) {
        BSTNode<T, less, equal> *new_root = root->remove(element);

        if (new_root || size() == 1) root = new_root;

        _size--;
    }
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
bool BSTree<T, less, equal>::find(T element) {
    if (empty()) return false;
    return root->find(element);
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
std::vector<T> BSTree<T, less, equal>::inorder() {
    if (empty()) return {};

    std::vector<T> elements{};
    root->inorder(elements);
    return elements;
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
std::vector<T> BSTree<T, less, equal>::preorder() {
    if (empty()) return {};

    std::vector<T> elements{};
    root->preorder(elements);
    return elements;
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
std::vector<T> BSTree<T, less, equal>::postorder() {
    if (empty()) return {};

    std::vector<T> datos{};
    root->postorder(datos);
    return datos;
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
std::vector<T> BSTree<T, less, equal>::width_order() {
    if (empty()) return {};

    std::vector<T> elements{};
    std::queue<BSTNode<T, less, equal> *> nodes;
    nodes.push(root);

    BSTNode<T, less, equal> *current_node;
    while (!nodes.empty()) {
        current_node = nodes.front();
        current_node->width_order(nodes, elements);
        nodes.pop();
    }

    return elements;
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
void BSTree<T, less, equal>::execute(void (*method)(T)) {
    if (!empty()) {
        root->execute(method);
    }
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
std::size_t BSTree<T, less, equal>::size() {
    return _size;
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
std::size_t BSTree<T, less, equal>::height() {
    if (empty()) return EMPTY;

    return root->altura();
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
bool BSTree<T, less, equal>::empty() {
    return !root;
}

template<typename T, bool (*less)(T, T), bool (*equal)(T, T)>
BSTree<T, less, equal>::~BSTree() {
    delete root;
}

#endif
