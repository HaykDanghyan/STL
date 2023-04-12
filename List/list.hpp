#include "list.h"

template <typename T>
List<T>::List() : m_head{nullptr}, m_tail{nullptr}, m_size{} {}

template <typename T>
List<T>::List(size_t count, const T& val) : m_head{nullptr}, m_tail{nullptr}, m_size{} {
    m_head = new ListNode(val, nullptr, nullptr);
    ListNode* curr = m_head;
    m_size = count;
    for (int i = 0; i < count - 1; ++i) {
        curr->next = new ListNode(val, nullptr, curr);
        curr = curr->next;
        m_tail = curr;
    }
}

template <typename T>
List<T>::List(const List<T>& rhs) : m_head{nullptr}, m_tail{nullptr}, m_size{} {
    if (rhs.m_head != nullptr) {
        m_size = rhs.m_size;
        ListNode* rhsHead = rhs.m_head;
        m_head = new ListNode(rhsHead->value);
        ListNode* thisHead = m_head;
        if (m_size > 1) {
            rhsHead = rhsHead->next;
            for (int i = 0; i < m_size - 1; ++i) {
                thisHead->next = new ListNode(rhsHead->value, nullptr, thisHead);
                thisHead = thisHead->next;
                rhsHead = rhsHead->next;
                m_tail = thisHead;
            }
        }
    }
} 

template <typename T>
List<T>::List(List<T>&& rhs) : m_head{nullptr}, m_tail{nullptr}, m_size{} {
    m_head = rhs.m_head;
    m_tail = rhs.m_tail;
    m_size = rhs.m_size;
    rhs.m_size = 0;
    rhs.m_head = nullptr;
    rhs.m_tail = nullptr;
}

template <typename T>
List<T>::List(std::initializer_list<T> init) : m_head{nullptr}, m_tail{nullptr}, m_size{} {
    for (const auto& el : init) {
        push_back(el);
    }
}

template <typename T>
List<T>::~List() {
    clear();
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& rhs) {
    if (this != &rhs) {
        if (rhs.m_head != nullptr) {
            m_size = rhs.m_size;
            ListNode* rhsHead = rhs.m_head;
            m_head = new ListNode(rhsHead->value);
            ListNode* thisHead = m_head;
            if (m_size > 1) {
                rhsHead = rhsHead->next;
                for (int i = 0; i < m_size - 1; ++i) {
                    thisHead->next = new ListNode(rhsHead->value, nullptr, thisHead);
                    thisHead = thisHead->next;
                    rhsHead = rhsHead->next;
                    m_tail = thisHead;
                }
            }
        }
    }
    return *this;
}

template <typename T> 
List<T>& List<T>::operator=(List<T>&& rhs) {
    if (this != &rhs) {
        m_head = rhs.m_head;
        m_tail = rhs.m_tail;
        m_size = rhs.m_size;
        rhs.m_size = 0;
        rhs.m_head = nullptr;
        rhs.m_tail = nullptr;
    }
    return *this;
}

template <typename T>
void List<T>::assign(size_t count, const T& val) {
    List tmp(count, val);
    m_head = tmp.m_head;
    m_tail = tmp.m_tail;
    m_size = tmp.m_size;
    tmp.m_head = nullptr;
    tmp.m_tail = nullptr;
    tmp.m_size = 0;    
}

template <typename T>
void List<T>::assign(std::initializer_list<T> init) {
    List tmp(init);
    m_head = tmp.m_head;
    m_tail = tmp.m_tail;
    m_size = tmp.m_size;
    tmp.m_head = nullptr;
    tmp.m_tail = nullptr;
    tmp.m_size = 0;    
    
}

template <typename T>
T& List<T>::front() {
    return m_head->value;
}

template <typename T>
const T& List<T>::front() const {
    return m_head->value;
}

template <typename T>
T& List<T>::back() {
    return m_tail->value;
}

template <typename T>
const T& List<T>::back() const {
    return m_tail->value;
}

template <typename T>
bool List<T>::empty() const {
    return m_size == 0;
}

template <typename T>
size_t List<T>::size() const {
    return m_size;
}

template <typename T>
void List<T>::clear() {
    if (m_head == nullptr) {
        return;
    }
    while (m_head != m_tail) {
        ListNode* curr = m_head;
        m_head = m_head->next;
        delete curr;
        curr = nullptr;
    }
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

template <typename T>
void List<T>::push_back(const T& value) {
    ListNode* new_node = new ListNode(value);
    if (m_tail == nullptr) {
        m_head = new_node;
        m_tail = new_node;
    } else {
        new_node->prev = m_tail;
        m_tail->next = new_node;
        m_tail = new_node;
    }
    ++m_size;
}

template <typename T>
void List<T>::push_back(T&& value) {
    ListNode* new_node = new ListNode(value);
    if (m_tail == nullptr) {
        m_head = new_node;
        m_tail = new_node;
    } else {
        new_node->prev = m_tail;
        m_tail->next = new_node;
        m_tail = new_node;
    }
    ++m_size;
}

template <typename T>
void List<T>::push_front(const T& value) {
    ListNode* new_node = new ListNode(value);
    if (m_head == nullptr) {
        m_head = new_node;
        m_tail = new_node;
    } else {
        new_node->next = m_head;
        m_head->prev = new_node;
        m_head = new_node;
    }
    ++m_size;
}

template <typename T>
void List<T>::push_front(T&& value) {
    ListNode* new_node = new ListNode(value);
    if (m_head == nullptr) {
        m_head = new_node;
        m_tail = new_node;
    } else {
        new_node->next = m_head;
        m_head->prev = new_node;
        m_head = new_node;
    }
    ++m_size;
}

template <typename T>
void List<T>::pop_back() {
    if (m_tail != nullptr) {
        ListNode* prev = m_tail->prev;
        if (prev != nullptr) {
            delete m_tail;
            m_tail = prev;
            m_tail->next = nullptr;
        } else {
            delete m_tail;
            m_head = nullptr;
            m_tail = nullptr;
        }
        --m_size;
    }
}

template <typename T>
void List<T>::pop_front() {
    if (m_head != nullptr) {
        ListNode* next = m_head->next;
        if (next != nullptr) {
            delete m_head;
            m_head = next;
            m_head->prev = nullptr;
        } else {
            delete m_head;
            m_head = nullptr;
            m_tail = nullptr;
        }
        --m_size;
    }
}

template <typename T>
void List<T>::resize(size_t count, const T& val) {
    if (m_size == count) {
        return;
    }
    while (m_size < count) {
        push_back(val);
    } 
    while (m_size > count) {
        pop_back();
    }
}

template <typename T>
void List<T>::reverse() {
    ListNode* curr = m_head;
    ListNode* prev = nullptr;
    ListNode* next = nullptr;
    while (curr != nullptr) {
        next = curr->next;
        prev = curr->prev;
        curr->next = prev;
        curr->prev = next;
        prev = curr;
        curr = next;
    }
    m_head = prev;
}

template <typename T>
void List<T>::merge(List<T>& rhs) {
    ListNode* head1 = m_head;
    ListNode* head2 = rhs.m_head;
    List<T> newList;
    while (head1 != nullptr && head2 != nullptr) {
        if (head1->value < head2->value) {
            newList.push_back(head1->value);
            head1 = head1->next;
        } else {
            newList.push_back(head2->value);
            head2 = head2->next;
        }
    }
    while (head1 != nullptr) {
        newList.push_back(head1->value);
        head1 = head1->next;
    }
    while (head2 != nullptr) {
        newList.push_back(head2->value);
        head2 = head2->next;
    } 
    m_head = newList.m_head;
    m_tail = newList.m_tail;
    m_size = newList.m_size;
    newList.m_head = nullptr;
    newList.m_tail = nullptr;
    newList.m_size = 0;
}

template <typename T>
void List<T>::merge(List<T>&& rhs) {
    ListNode* head1 = m_head;
    ListNode* head2 = rhs.m_head;
    List<T> newList;
    while (head1 != nullptr && head2 != nullptr) {
        if (head1->value < head2->value) {
            newList.push_back(head1->value);
            head1 = head1->next;
        } else {
            newList.push_back(head2->value);
            head2 = head2->next;
        }
    }
    while (head1 != nullptr) {
        newList.push_back(head1->value);
        head1 = head1->next;
    }
    while (head2 != nullptr) {
        newList.push_back(head2->value);
        head2 = head2->next;
    } 
    m_head = newList.m_head;
    m_tail = newList.m_tail;
    m_size = newList.m_size;
    newList.m_head = nullptr;
    newList.m_tail = nullptr;
    newList.m_size = 0;
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator pos) {
    ListNode* it = pos.curr;
    if (it == nullptr) {
        return end();
    }
    if (it->prev) {
        it->prev->next = it->next;
    } else {
        m_head = it->next;
    }
    if (it->next) {
        it->next->prev = it->prev;
    } else {
        m_tail = it->prev;
    }
    auto next_it = iterator(it->next);
    delete it;
    --m_size;
    return next_it;
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator pos, const T& value) {
    ListNode* node = pos.curr;
    if (node == nullptr) {
        push_back(value);
    }
    else if (node == m_head) {
        push_front(value);
    } else {
        ListNode* new_node = new ListNode(value, node, node->prev);
        node->prev->next = new_node;
        node->prev = new_node;
        ++m_size;
    }
    return pos;
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator pos, T&& value) {
    ListNode* node = pos.curr;
    if (node == nullptr) {
        push_back(value);
    }
    else if (node == m_head) {
        push_front(value);
    } else {
        ListNode* new_node = new ListNode(value, node, node->prev);
        node->prev->next = new_node;
        node->prev = new_node;
        ++m_size;
    }
    return pos;
}

template <typename T>
typename List<T>::iterator List<T>::begin() const noexcept {
    return iterator(m_head);
}

template <typename T>
typename List<T>::iterator List<T>::end() const noexcept {
    return iterator(m_tail->next);
}

template <typename T>
typename List<T>::iterator List<T>::rbegin() const noexcept {
    return iterator(m_tail);
}

template <typename T>
typename List<T>::iterator List<T>::rend() const noexcept {
    return iterator(m_head->prev);
}