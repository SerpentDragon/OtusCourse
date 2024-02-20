template<class Key, class Value>
struct Node
{
    Node(const int key, int value, Node<const Key, Value>* parent)
        : key_(key), value_(value),
        left_(nullptr), right_(nullptr),
        parent_(parent) {}

    ~Node()
    {
        left_ = nullptr;
        right_ = nullptr;
        parent_ = nullptr;
    }

    const Key key_;
    Value value_;

    Node<const Key, Value>* left_;
    Node<const Key, Value>* right_;
    Node<const Key, Value>* parent_;
};


template<class Key, class Value>
class MapIterator
{
public:

    MapIterator() = default;

    MapIterator(Node<const Key, Value>* node) : node_(node) {}

    MapIterator(const MapIterator&) = default;

    MapIterator(MapIterator&&) noexcept = default;

    MapIterator& operator=(const MapIterator&) = default;

    MapIterator& operator=(MapIterator&&) noexcept = default;

    ~MapIterator()
    {
        node_ = nullptr;
    }

    MapIterator& operator++()
    {
        if (node_->right_ != nullptr)
        {
            node_ = node_->right_;
            while(node_->left_ != nullptr) node_ = node_->left_;
        }
        else
        {
            if (node_->parent_ != nullptr)
            {
                const Key key = node_->key_;
                Node<const Key, Value>* end = 
                    node_ + sizeof(Node<const Key, Value>);

                while(node_->parent_ != nullptr)
                {
                    if (node_->parent_->key_ < key)
                        node_ = node_->parent_;
                    else break;
                }
                node_ = node_->parent_;

                if (node_ == nullptr)
                    node_ = end;
            }
        }

        return *this;
    }

    MapIterator operator++(int)
    {
        MapIterator it = *this;
        ++(*this);
        return it;
    }

    MapIterator& operator--()
    {
        if (node_->left_ != nullptr)
        {
            node_ = node_->left_;
            while(node_->right_ != nullptr) node_ = node_->right_;
        }
        else
        {
            if (node_->parent_ != nullptr)
            {
                const Key key = node_->key_;
                Node<const Key, Value>* begin = node_;

                while(node_->parent_ != nullptr)
                {
                    if (node_->parent_->key_ > key)
                        node_ = node_->parent_;
                    else break;
                }
                node_ = node_->parent_;

                if (node_ == nullptr)
                    node_ = begin;
            }
        }

        return *this;
    }

    MapIterator operator--(int)
    {
        MapIterator it = *this;
        --(*this);
        return it;
    }

    bool operator==(const MapIterator<Key, Value>& it) const { return node_ == it.node_; }

    bool operator!=(const MapIterator<Key, Value>& it) const { return node_ != it.node_; }

    const Node<const Key, Value>* operator->() const { return node_; }

    const Node<const Key, Value>& operator*() const { return *node_; }

private:

    Node<const Key, Value>* node_;
};