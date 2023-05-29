#pragma once

#include <initializer_list>
#include <cstddef>
#include <string>
#include <utility>
#include <cassert>
template <typename Type>
class SingleLinkedList {
    // ���� ������
    struct Node {
        Node() = default;
        Node(const Type& val, Node* next)
            : value(val)
            , next_node(next) {
        }
        Type value;
        Node* next_node = nullptr;
    };

    template <typename ValueType>
    class BasicIterator {
        // ����� ������ ����������� �������������, ����� �� ������� ������
        // ��� ������ � ��������� ������� ���������
        friend class SingleLinkedList;

        // �������������� ����������� ��������� �� ��������� �� ���� ������
        explicit BasicIterator(Node* node) :node_(node) {}

    public:
        // ����������� ���� ���� �������� ����������� ���������� � ��������� ����� ���������

        // ��������� ��������� � forward iterator
        // (��������, ������� ������������ �������� ���������� � ������������ �������������)
        using iterator_category = std::forward_iterator_tag;
        // ��� ���������, �� ������� ������������ ��������
        using value_type = Type;
        // ���, ������������ ��� �������� �������� ����� �����������
        using difference_type = std::ptrdiff_t;
        // ��� ��������� �� ����������� ��������
        using pointer = ValueType*;
        // ��� ������ �� ����������� ��������
        using reference = ValueType&;

        BasicIterator() = default;

        // �������������� �����������/����������� �����������
        // ��� ValueType, ����������� � Type, ������ ���� ����������� ������������
        // ��� ValueType, ����������� � const Type, ������ ���� ��������������� ������������
        BasicIterator(const BasicIterator<Type>& other) noexcept :node_(other.node_) {}

        // ����� ���������� �� ������� �������������� �� ���������� ��������� = ��� �������
        // ����������������� ������������ �����������, ���� ������� �������� = �
        // �������� ���������� ������������� ��� �� ���
        BasicIterator& operator=(const BasicIterator& rhs) = default;

        // �������� ��������� ���������� (� ���� ������� ��������� ��������� ����������� ��������)
        // ��� ��������� �����, ���� ��� ��������� �� ���� � ��� �� ������� ������ ���� �� end()
        [[nodiscard]] bool operator==(const BasicIterator<const Type>& rhs) const noexcept {
            return node_ == rhs.node_;
        }

        // �������� �������� ���������� �� �����������
        // �������������� !=
        [[nodiscard]] bool operator!=(const BasicIterator<const Type>& rhs) const noexcept {
            return node_ != rhs.node_;
        }

        // �������� ��������� ���������� (� ���� ������� ��������� ��������)
        // ��� ��������� �����, ���� ��� ��������� �� ���� � ��� �� ������� ������ ���� �� end()
        [[nodiscard]] bool operator==(const BasicIterator<Type>& rhs) const noexcept {
            return node_ == rhs.node_;
        }

        // �������� �������� ���������� �� �����������
        // �������������� !=
        [[nodiscard]] bool operator!=(const BasicIterator<Type>& rhs) const noexcept {
            return node_ != rhs.node_;
        }

        // �������� ��������������. ����� ��� ������ �������� ��������� �� ��������� ������� ������
        // ���������� ������ �� ������ ����
        // ��������� ���������, �� ������������ �� ������������ ������� ������, �������� � �������������� ���������
        BasicIterator& operator++() noexcept {
            assert(node_ != nullptr);
            node_ = node_->next_node;
            return *this;
        }

        // �������� ��������������. ����� ��� ������ �������� ��������� �� ��������� ������� ������
        // ���������� ������� �������� ���������
        // ��������� ���������, �� ������������ �� ������������ ������� ������,
        // �������� � �������������� ���������
        BasicIterator operator++(int) noexcept {
            assert(node_ != nullptr);
            auto old_value(*this); // ��������� ������� �������� ������� ��� ������������ ��������
            ++(*this); // ���������� ������ ���������� ����� ����������
            return old_value;
        }

        // �������� �������������. ���������� ������ �� ������� �������
        // ����� ����� ��������� � ���������, �� ������������ �� ������������ ������� ������,
        // �������� � �������������� ���������
        [[nodiscard]] reference operator*() const noexcept {
            assert(node_ != nullptr);
            return node_->value;
        }

        // �������� ������� � ����� ������. ���������� ��������� �� ������� ������� ������
        // ����� ����� ��������� � ���������, �� ������������ �� ������������ ������� ������,
        // �������� � �������������� ���������
        [[nodiscard]] pointer operator->() const noexcept {
            assert(node_ != nullptr);
            return &(node_->value);
        }

    private:
        Node* node_ = nullptr;
    };

public:
    using value_type = Type;
    using reference = value_type&;
    using const_reference = const value_type&;

    // ��������, ����������� ��������� ��������� ������
    using Iterator = BasicIterator<Type>;
    // ����������� ��������, ��������������� ������ ��� ������ � ��������� ������
    using ConstIterator = BasicIterator<const Type>;


    SingleLinkedList(std::initializer_list<Type> values) {
        auto it_ = values.end();
        --it_;
        for (auto it = it_; it >= values.begin(); --it) {
            head_.next_node = new Node(*it, head_.next_node);
            ++size_;
        }

    }

    SingleLinkedList(const SingleLinkedList& other) {
        CopyAndSwap(other);
       
    }

    SingleLinkedList& operator=(const SingleLinkedList& rhs) {
        CopyAndSwap(rhs);
        return *this;
    }

    // ���������� ���������� ������� �� ����� O(1)
    void swap(SingleLinkedList& other) noexcept {
       if (other.begin() == begin()) return;
       std::swap(other.size_, size_);
       std::swap(other.head_.next_node, head_.next_node);
    }
    // ���������� ��������, ����������� �� ������ �������
    // ���� ������ ������, ������������ �������� ����� ����� end()
    [[nodiscard]] Iterator begin() noexcept {
        Iterator begin(head_.next_node);
        return begin;
    }

    // ���������� ��������, ����������� �� �������, ��������� �� ��������� ��������� ������������ ������
    // �������������� ���� �������� ������ � ������� ������������� ������� � �������������� ���������
    [[nodiscard]] Iterator end() noexcept {
        return {};
    }

    // ���������� ����������� ��������, ����������� �� ������ �������
    // ���� ������ ������, ������������ �������� ����� ����� end()
    // ��������� ������ ������������ ������ ������ cbegin()
    [[nodiscard]] ConstIterator begin() const noexcept {
        Iterator begin(head_.next_node);
        return begin;
    }

    // ���������� ����������� ��������, ����������� �� �������, ��������� �� ��������� ��������� ������������ ������
    // �������������� ���� �������� ������ � ������� ������������� ������� � �������������� ���������
    // ��������� ������ ������������ ������ ������ cend()
    [[nodiscard]] ConstIterator end() const noexcept {
        return {};
    }

    // ���������� ����������� ��������, ����������� �� ������ �������
    // ���� ������ ������, ������������ �������� ����� ����� cend()
    [[nodiscard]] ConstIterator cbegin() const noexcept {
        Iterator begin(head_.next_node);
        return begin;
    }

    // ���������� ����������� ��������, ����������� �� �������, ��������� �� ��������� ��������� ������������ ������
    // �������������� ���� �������� ������ � ������� ������������� ������� � �������������� ���������
    [[nodiscard]] ConstIterator cend() const noexcept {
        return {};
    }

    SingleLinkedList() {
    }

    void PushFront(const Type& value) {
        head_.next_node = new Node(value, head_.next_node);
        ++size_;
    }

    ~SingleLinkedList() {
        Clear();
    }

    void Clear() noexcept {
        while (head_.next_node) {
            auto temp = head_.next_node->next_node;
            delete head_.next_node;
            head_.next_node = temp;
        }
        size_ = 0;
    }

    // ���������� ���������� ��������� � ������ �� ����� O(1)
    [[nodiscard]] size_t GetSize() const noexcept {
        return size_;
    }

    // ��������, ������ �� ������ �� ����� O(1)
    [[nodiscard]] bool IsEmpty() const noexcept {
        return size_ == 0;
    }
    // ���������� ��������, ����������� �� ������� ����� ������ ��������� ������������ ������.
   // �������������� ���� �������� ������ - ������� ������������� ������� � �������������� ���������
    [[nodiscard]] Iterator before_begin() noexcept {

        return Iterator(&head_);
    }

    // ���������� ����������� ��������, ����������� �� ������� ����� ������ ��������� ������������ ������.
    // �������������� ���� �������� ������ - ������� ������������� ������� � �������������� ���������
    [[nodiscard]] ConstIterator cbefore_begin() const noexcept {

        return ConstIterator(const_cast<SingleLinkedList<Type>::Node*>(&head_));
    }

    // ���������� ����������� ��������, ����������� �� ������� ����� ������ ��������� ������������ ������.
    // �������������� ���� �������� ������ - ������� ������������� ������� � �������������� ���������
    [[nodiscard]] ConstIterator before_begin() const noexcept {
        // ���������� ��������������
        return ConstIterator(const_cast<SingleLinkedList<Type>::Node*>(&head_));
    }

    /*
     * ��������� ������� value ����� ��������, �� ������� ��������� pos.
     * ���������� �������� �� ����������� �������
     * ���� ��� �������� �������� ����� ��������� ����������, ������ ��������� � ������� ���������
     */
    Iterator InsertAfter(ConstIterator pos, const Type& value) {
        assert(pos.node_);
        pos.node_->next_node = new Node(value, pos.node_->next_node);
        ++size_;
        return Iterator(pos.node_->next_node);
    }

    void PopFront() noexcept {
        assert(!this->IsEmpty());
        Node new_head = *(head_.next_node);
        head_ = new_head;

        --size_;
    }

    /*
     * ������� �������, ��������� �� pos.
     * ���������� �������� �� �������, ��������� �� ��������
     */
    Iterator EraseAfter(ConstIterator pos) noexcept {
        assert(!IsEmpty());
        assert(pos != cend());
        Node* deleted_elem = pos.node_->next_node;
        pos.node_->next_node = deleted_elem->next_node;
        delete deleted_elem;
        Iterator it(pos.node_->next_node);
        --size_;
        return it;
    }
private:
    // ��������� ����, ������������ ��� ������� "����� ������ ���������"
    Node head_;
    size_t size_ = 0;

    void CopyAndSwap(const SingleLinkedList& rhs) {
        SingleLinkedList<Type> copy;
        Iterator p_copy = copy.before_begin();
        for (auto p : rhs) {
            copy.InsertAfter(p_copy, p);
            ++p_copy;
        }
        copy.swap(*this);
    }
};

template <typename Type>
void swap(SingleLinkedList<Type>& lhs, SingleLinkedList<Type>& rhs) noexcept {
    lhs.swap(rhs);
}

template <typename Type>
bool operator==(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    if (lhs.GetSize() == rhs.GetSize()) {
`       return std::equal(lhs.begin(), lhs.end(), rhs.begin());
        }
    return false;
}

template <typename Type>
bool operator!=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return !(lhs == rhs);
}


template <typename Type>
bool operator<(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    if (lhs.GetSize() == rhs.GetSize()) {
        return  (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) > 0 ? true : false);
    }
    return true;
}

template <typename Type>
bool operator<=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return !(rhs < lhs);
}

template <typename Type>
bool operator>(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return (rhs < lhs);
}

template <typename Type>
bool operator>=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return !(lhs < rhs);
}
