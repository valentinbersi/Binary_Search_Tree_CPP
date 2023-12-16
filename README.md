# Binary_Search_Tree_CPP
 My implementation of a Binary Search Tree in C++.

Manual:

- add(new_element): adds new_element to the tree. If the tree is empty, it creates a new root.

- remove(element): deletes the element from the tree. If it doesn´t exist, it does nothing.

- find(element): returns true if the element is in the tree. If there are no elements, it returns false.

- inorder(): returns the inorder traversal.

- preorder(): returns the preorder traversal.

- postorder(): returns the postorder traversal.

- width_order(): returns the width order traversal.

- execute(): executes the method/function in each node.

- size(): returns the number of elements in the tree.

- height(): returns the height of the tree, if the tree is empty it returns 0.

- empty(): returns true if the tree is empty.

The tree doesn´t accept repeated elements, (or repeated ids for an element if you are using an ADT). If add() is called with a repeated element or id, it will end the execution of the program throwing an exception.
