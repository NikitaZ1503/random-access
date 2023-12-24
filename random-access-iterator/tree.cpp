#include "tree.hpp"
#include <stdexcept>

static tree_node *move_any_direction_because_im_good(tree_node *node,
                                                     ptrdiff_t diff) {
    if (!node)
        throw std::out_of_range(
            "WHY ARE YOU DOING THIS, STOP CAUSING OOB EXCEPTIONS\n"
            "asshole");

    if (diff == 0)
        return node;

    if (diff > 0) {
        if (!node->right)
            if (!node->up)
                if (diff == 1)
                    return nullptr;
                else
                    throw std::out_of_range("asdohpdfgo");
            else if (node->up->right && node->up->right.get() == node)
                return move_any_direction_because_im_good(
                    node->up,
                    diff + 1 + (node->left ? node->left->subtree_size : 0));
            else
                return move_any_direction_because_im_good(node->up, diff - 1);
        else if (diff <= node->right->subtree_size)
            return move_any_direction_because_im_good(
                node->right.get(),
                diff - 1 -
                    (node->right->left ? node->right->left->subtree_size : 0));
        else if (!node->up)
            if (diff == node->right->subtree_size + 1)
                return nullptr;
            else
                throw std::out_of_range("asdkjh");
        else if (node->up->right && node->up->right.get() == node)
            return move_any_direction_because_im_good(
                node->up,
                diff + 1 + (node->left ? node->left->subtree_size : 0));
        else
            return move_any_direction_because_im_good(
                node->up, diff - 1 - node->right->subtree_size);
    } else {
        if (!node->left)
            if (!node->up)
                if (diff == -1)
                    return nullptr;
                else
                    throw std::out_of_range("asdohpdfgo");
            else if (node->up->left && node->up->left.get() == node)
                return move_any_direction_because_im_good(
                    node->up,
                    diff - 1 - (node->right ? node->right->subtree_size : 0));
            else
                return move_any_direction_because_im_good(node->up, diff + 1);
        else if (-diff <= node->left->subtree_size)
            return move_any_direction_because_im_good(
                node->left.get(),
                diff + 1 +
                    (node->left->right ? node->left->right->subtree_size : 0));
        else if (!node->up)
            if (diff == -node->left->subtree_size - 1)
                return nullptr;
            else
                throw std::out_of_range("asdohpdfgo");
        else if (node->up->left && node->up->left.get() == node)
            return move_any_direction_because_im_good(
                node->up,
                diff - 1 - (node->right ? node->right->subtree_size : 0));
        else
            return move_any_direction_because_im_good(
                node->up, diff + 1 + node->left->subtree_size);
    }
}

tree::iterator operator+(tree::iterator const &self, ptrdiff_t diff) {
    if (!self.p && diff == 0)
        return self;
    if (!self.p && diff < 0) {
        tree_node *node = self.root;
        if (!node)
            throw std::out_of_range("index out of range");

        while (node->right)
            node = node->right.get();

        return tree::iterator{
            move_any_direction_because_im_good(node, diff + 1), self.root};
    }
    return tree::iterator{move_any_direction_because_im_good(self.p, diff),
                          self.root};
}

// i is not end
static ptrdiff_t reverse_index(tree::iterator i) {
    int c = 0;
    try {
        while (true) {
            i++;
            c++;
        }
    } catch (std::out_of_range e) {
        return c;
    }
    return 0; // wtf should never happen
}

ptrdiff_t operator-(tree::iterator const &self, tree::iterator other) {
    ptrdiff_t reverse_index_left = reverse_index(self);
    ptrdiff_t reverse_index_right = reverse_index(other);

    return reverse_index_right - reverse_index_left;
}

tree::iterator tree::begin() const {
    if (!root)
        return iterator{nullptr, nullptr};

    tree_node *res = root.get();
    while (res->left)
        res = res->left.get();
    return iterator{res, root.get()};
}

auto tree::end() const -> iterator { return iterator{nullptr, root.get()}; }
