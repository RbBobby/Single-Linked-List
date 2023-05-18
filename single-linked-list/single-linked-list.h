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
            node_ = node_->next_node;
            return *this;
        }

        // �������� ��������������. ����� ��� ������ �������� ��������� �� ��������� ������� ������
        // ���������� ������� �������� ���������
        // ��������� ���������, �� ������������ �� ������������ ������� ������,
        // �������� � �������������� ���������
        BasicIterator operator++(int) noexcept {
            auto old_value(*this); // ��������� ������� �������� ������� ��� ������������ ��������
            ++(*this); // ���������� ������ ���������� ����� ����������
            return old_value;
        }

        // �������� �������������. ���������� ������ �� ������� �������
        // ����� ����� ��������� � ���������, �� ������������ �� ������������ ������� ������,
        // �������� � �������������� ���������
        [[nodiscard]] reference operator*() const noexcept {
            return node_->value;
        }

        // �������� ������� � ����� ������. ���������� ��������� �� ������� ������� ������
        // ����� ����� ��������� � ���������, �� ������������ �� ������������ ������� ������,
        // �������� � �������������� ���������
        [[nodiscard]] pointer operator->() const noexcept {
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
        SingleLinkedList<Type> copy;
        SingleLinkedList<Type> copy_1;

        for (auto p : other) {
            // �������� ������, ���� ��������� �� ���� ���������
            auto p_copy = p;  // new ����� ��������� ����������

            // �� �������� ����������, �. �. � vector ������ ��� ���������������
            copy.PushFront(p_copy);
        }
        for (auto p : copy) {
            // �������� ������, ���� ��������� �� ���� ���������
            auto p_copy = p;  // new ����� ��������� ����������

            // �� �������� ����������, �. �. � vector ������ ��� ���������������
            copy_1.PushFront(p_copy);
        }



        copy_1.swap(*this);


    }

    SingleLinkedList& operator=(const SingleLinkedList& rhs) {
        SingleLinkedList<Type> copy;
        SingleLinkedList<Type> copy_1;
        for (auto p : rhs) {
            // �������� ������, ���� ��������� �� ���� ���������
            auto p_copy = p;  // new ����� ��������� ����������

            // �� �������� ����������, �. �. � vector ������ ��� ���������������
            copy.PushFront(p_copy);
        }
        for (auto p : copy) {
            // �������� ������, ���� ��������� �� ���� ���������
            auto p_copy = p;  // new ����� ��������� ����������

            // �� �������� ����������, �. �. � vector ������ ��� ���������������
            copy_1.PushFront(p_copy);
        }



        copy_1.swap(*this);


        return *this;
    }

    // ���������� ���������� ������� �� ����� O(1)
    void swap(SingleLinkedList& other) noexcept {
        if (other.begin() == this->begin()) return;
        int buf = other.size_;
        other.size_ = this->size_;
        this->size_ = buf;
        auto it_buf = other.head_.next_node;

        other.head_.next_node = this->head_.next_node;

        this->head_.next_node = it_buf;

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
        pos.node_->next_node = new Node(value, pos.node_->next_node);
        this->size_ += 1;
        return Iterator(pos.node_->next_node);
    }

    void PopFront() noexcept {
        Node new_head = *(this->head_.next_node);
        this->head_ = new_head;

        this->size_ -= 1;

    }

    /*
     * ������� �������, ��������� �� pos.
     * ���������� �������� �� �������, ��������� �� ��������
     */
    Iterator EraseAfter(ConstIterator pos) noexcept {
        Node* deleted_elem = pos.node_->next_node;
        auto buf = deleted_elem->next_node;
        pos.node_->next_node = deleted_elem->next_node;
        delete deleted_elem;
        Iterator it(pos.node_->next_node);
        this->size_ -= 1;
        return it;
    }
private:
    // ��������� ����, ������������ ��� ������� "����� ������ ���������"
    Node head_;
    size_t size_ = 0;
};

template <typename Type>
void swap(SingleLinkedList<Type>& lhs, SingleLinkedList<Type>& rhs) noexcept {
    lhs.swap(rhs);
}

template <typename Type>
bool operator==(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    size_t size_lhs = lhs.GetSize();
    size_t size_rhs = rhs.GetSize();
    if (size_lhs == size_rhs) {

        auto it_lhs = lhs.begin();
        auto it_rhs = rhs.begin();
        for (auto it = lhs.begin(); it != lhs.end(); ++it) {
            if (*it_lhs != *it_rhs) {

                return false;
            }
            ++it_lhs;
            ++it_rhs;
        }
        return true;

    }
    return false;
}

template <typename Type>
bool operator!=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    size_t size_lhs = lhs.GetSize();
    size_t size_rhs = rhs.GetSize();
    if (size_lhs == size_rhs) {

        auto it_lhs = lhs.begin();
        auto it_rhs = rhs.begin();
        for (auto it = lhs.begin(); it != lhs.end(); ++it) {
            if (*it_lhs != *it_rhs) {

                return true;
            }
            ++it_lhs;
            ++it_rhs;
        }
        return false;

    }
    return true;
}


template <typename Type>
bool operator<(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    size_t size_lhs = lhs.GetSize();
    size_t size_rhs = rhs.GetSize();
    if (size_lhs == size_rhs) {

        auto it_lhs = lhs.begin();
        auto it_rhs = rhs.begin();
        for (auto it = lhs.begin(); it != lhs.end(); ++it) {
            if (*it_lhs < *it_rhs) {

                return true;
            }
            ++it_lhs;
            ++it_rhs;
        }
        return false;

    }
    return true;
}

template <typename Type>
bool operator<=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    size_t size_lhs = lhs.GetSize();
    size_t size_rhs = rhs.GetSize();
    if (size_lhs == size_rhs) {

        auto it_lhs = lhs.begin();
        auto it_rhs = rhs.begin();
        for (auto it = lhs.begin(); it != lhs.end(); ++it) {
            if (*it_lhs <= *it_rhs) {

                return true;
            }
            ++it_lhs;
            ++it_rhs;
        }
        return false;

    }
    return true;
}

template <typename Type>
bool operator>(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    size_t size_lhs = lhs.GetSize();
    size_t size_rhs = rhs.GetSize();
    if (size_lhs == size_rhs) {

        auto it_lhs = lhs.begin();
        auto it_rhs = rhs.begin();
        for (auto it = lhs.begin(); it != lhs.end(); ++it) {
            if (*it_lhs > *it_rhs) {

                return true;
            }
            ++it_lhs;
            ++it_rhs;
        }
        return false;

    }
    return true;
}

template <typename Type>
bool operator>=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    size_t size_lhs = lhs.GetSize();
    size_t size_rhs = rhs.GetSize();
    if (size_lhs == size_rhs) {

        auto it_lhs = lhs.begin();
        auto it_rhs = rhs.begin();
        for (auto it = lhs.begin(); it != lhs.end(); ++it) {
            if (*it_lhs >= *it_rhs) {

                return true;
            }
            ++it_lhs;
            ++it_rhs;
        }
        return false;

    }
    return true;
}
