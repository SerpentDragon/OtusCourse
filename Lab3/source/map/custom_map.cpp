#include <memory>
#include <iostream>
#include "map_iterator.cpp"

template<class Key, class Value, class Allocator 
    = std::allocator<std::pair<const int, int>>>
class custom_map
{
public:

    custom_map() : root_(nullptr), size_(0)
    {

    }

    ~custom_map()
    {
        std::cout << "Destructor\n";
        clear(root_);
    }

public:

    using iterator = MapIterator<const Key, Value>;
    using value_type = Node<const Key, Value>;

    void insert(const std::pair<const Key, Value> element)
    {
        root_ = insert(element, root_, nullptr);
    }

    void erase(iterator it)
    {
        const Key key = (*it).key_;
        erase(key);
        size_--;
    }

    void erase(const Key key)
    {
        erase(key, root_);
        size_--;
    }

    iterator begin() const
    {
        value_type* node = root_;
        while(node->left_ != nullptr) node = node->left_;

        return MapIterator<const Key, Value>(node);
    }

    iterator end() const
    {
        value_type* node = root_;
        while(node->right_ != nullptr) node = node->right_;

        return MapIterator<const Key, Value>(node + sizeof(value_type));
    }

    iterator find(const Key key) const
    {
        value_type* node = root_;

        while(node->key_ != key)
        {
            if (key < node->key_) node = node->left_;
            else node = node->right_;

            if (node == nullptr) break;
        }

        return node == nullptr ? 
            end() : MapIterator<const Key, Value>(node);
    }

    void clear() 
    { 
        clear(root_);
        root_ = nullptr; 
    }

    std::size_t size() const { return size_; }

    bool empty() const { return size_ == 0; }
    

private:

    value_type* insert(const std::pair<const Key, Value> element, 
            value_type* node, value_type* parent_)
    {
        if (node == nullptr)
        {
            size_++;
            return new value_type(element.first, element.second, parent_);
        }

        if(node->key_ == element.first)
            return nullptr;
        else if (node->key_ > element.first)
            node->left_ = insert(element, node->left_, node);
        else
            node->right_ = insert(element, node->right_, node);

        return node;
    }

    void erase(const Key key, value_type* node)
    {
        while(node != nullptr && node->key_ != key)
        {
            if (key < node->key_) node = node->left_;
            else node = node->right_;
        }
        if (node == nullptr) return;

        if (node->left_ == nullptr && node->right_ == nullptr)
        {
            if (node != root_)
            {
                if (node->parent_->left_ == node)
                    node->parent_->left_ = nullptr;
                else node->parent_->right_ = nullptr;
            }
            else root_ = nullptr;

            delete node;
        }
        else if (node->left_ != nullptr && node->right_ != nullptr)
        {
            value_type* min = min_element(node->right_);

            std::pair<const Key, Value> data = { min->key_, min->value_};
            erase(min->key_, root_);

            node->key_ = data.first;
            node->value_ = data.second;
        }
        else
        {
            value_type* child = node->left_ != nullptr ? node->left_ : node->right_;

            if (node != root_)
            {
                if (node == node->parent_->left_) node->parent_->left_ = child;
                else node->parent_->right_ = child;
            }
            else root_ = child;

            delete node;
        }

        size_--;
    }

    void clear(value_type* node)
    {
        if (node != nullptr)
        {
            if (node->left_ != nullptr) clear(node->left_);
            if (node->right_ != nullptr) clear(node->right_);

            delete node;
        }
    }

    value_type* min_element(value_type* node)
    {
        if (node == nullptr) return nullptr;

        while (node->left_ != nullptr) node = node->left_;

        return node;
    }

private:

    value_type* root_;

    std::size_t size_;
};

int main()
{
    custom_map<int, int> map;
    map.insert({1, 1});
    map.insert({3, 3});
    map.insert({4, 4});
    map.insert({2, 2});
    map.insert({0, 0});

    for(auto it = map.begin(); it != map.end(); it++)
    {
        std::cout << it->key_ << " " << it->value_ << std::endl;
    }
    std::cout << std::endl;

    map.erase(1);

    for(auto it = map.begin(); it != map.end(); it++)
    {
        std::cout << it->key_ << " " << it->value_ << std::endl;
    }

    std::cout << "size: " << map.size() << std::endl;

    return 0;
}