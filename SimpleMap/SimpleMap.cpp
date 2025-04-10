#include "SimpleMap.h"

template <typename Key, typename Value>
SimpleMap<Key, Value>::Node::Node(const Key& key, const Value& value, Node* l, Node* r)
    : data(key, value), left(l), right(r) {
}

template <typename Key, typename Value>
SimpleMap<Key, Value>::SimpleMap() : root(nullptr) {}

template <typename Key, typename Value>
SimpleMap<Key, Value>::~SimpleMap() {
    clear();
}

template <typename Key, typename Value>
void SimpleMap<Key, Value>::clearRecursive(Node* node) {
    if (node) {
        clearRecursive(node->left);
        clearRecursive(node->right);
        delete node;
    }
}

template <typename Key, typename Value>
void SimpleMap<Key, Value>::clear() {
    clearRecursive(root);
    root = nullptr;
}

template <typename Key, typename Value>
typename SimpleMap<Key, Value>::Node* SimpleMap<Key, Value>::findNode(const Key& key) const {
    Node* current = root;
    while (current) {
        if (key < current->data.first) {
            current = current->left;
        }
        else if (key > current->data.first) {
            current = current->right;
        }
        else {
            return current; 
        }
    }
    return nullptr; 
}

template <typename Key, typename Value>
Value& SimpleMap<Key, Value>::operator[](const Key& key) {
    Node* found = findNode(key);
    if (!found) {
        insert(key, Value()); 
        found = findNode(key); 
    }
    return found->data.second;
}

template <typename Key, typename Value>
Value& SimpleMap<Key, Value>::at(const Key& key) {
    Node* found = findNode(key);
    if (!found) {
        throw std::out_of_range("Key not found");
    }
    return found->data.second;
}

template <typename Key, typename Value>
const Value& SimpleMap<Key, Value>::at(const Key& key) const {
    return const_cast<SimpleMap*>(this)->at(key); 
}

template <typename Key, typename Value>
void SimpleMap<Key, Value>::insert(const Key& key, const Value& value) {
    if (!root) {
        root = new Node(key, value);
        return;
    }

    Node* current = root;
    Node* parent = nullptr;

    while (current) {
        parent = current;
        if (key < current->data.first) {
            current = current->left;
        }
        else if (key > current->data.first) {
            current = current->right;
        }
        else {
            current->data.second = value; 
            return;
        }
    }

    if (key < parent->data.first) {
        parent->left = new Node(key, value);
    }
    else {
        parent->right = new Node(key, value);
    }
}

template <typename Key, typename Value>
bool SimpleMap<Key, Value>::contains(const Key& key) const {
    return findNode(key) != nullptr;
}

template class SimpleMap<int, int>;
template class SimpleMap<std::string, int>;
