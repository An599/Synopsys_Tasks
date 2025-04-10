#ifndef SIMPLE_MAP_H
#define SIMPLE_MAP_H

#include <utility>  
#include <stdexcept> 

template <typename Key, typename Value>
class SimpleMap {
private:
    struct Node {
        std::pair<const Key, Value> data;
        Node* left;
        Node* right;

        Node(const Key& key, const Value& value, Node* l = nullptr, Node* r = nullptr);
    };

    Node* root;

    Node* findNode(const Key& key) const;
    void clearRecursive(Node* node);

public:
    SimpleMap();
    ~SimpleMap();

    Value& operator[](const Key& key);
    Value& at(const Key& key);
    const Value& at(const Key& key) const;

    void insert(const Key& key, const Value& value);
    void clear();
    
    bool contains(const Key& key) const;
};

#endif 
