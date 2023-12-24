#include "tree.hpp"
tree::iterator operator+(tree::iterator const &self, ptrdiff_t diff) {
tree_node *node = self.p;
ptrdiff_t subtree_size = node->left ? node->left->subtree_size : 0;
if (diff >= 0 && diff < subtree_size) {
return operator+(tree::iterator(node->left.get()), diff);
} else if (diff >= subtree_size && diff < subtree_size + 1) {
return tree::iterator(node);
} else {
return operator+(tree::iterator(node->right.get()), diff - subtree_size - 1);
}
}

ptrdiff_t operator-(tree::iterator const &self, tree::iterator other) {
tree_node *node1 = self.p;
tree_node *node2 = other.p;
while (node1 != node2) {
if (node1->up != nullptr) {

ptrdiff_t subtree_size = node1->left ? node1->left->subtree_size : 0;
if (node1->up->left.get() == node1) {

node1 = node1->up;
} else {

node1 = node1->up->left.get();
subtree_size += node1->subtree_size + 1;
}
}
}
return self.p->subtree_size - node1->subtree_size - 1;
}
auto tree::begin() const -> iterator {
if (root == nullptr) {
return tree::iterator(nullptr);
}
tree_node* node = root.get();
while (node->left) {
node = node->left.get();
}
return tree::iterator(node);
}

auto tree::end() const -> iterator {
if (root == nullptr) {
return tree::iterator(nullptr);
}
tree_node* node = root.get();
while (node->right) {
node = node->right.get();
}
return iterator(node);
}
