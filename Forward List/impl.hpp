#include "forward.h"

template <typename T>
forward_list<T>::forward_list() : head{nullptr} {}

template <typename T>
forward_list<T>::forward_list(size_t count) {
    head = new Node();
    Node* curr = head;
    for(int i = 0; i < count - 1; ++i) {
        curr -> next = new Node();
        curr = curr -> next;
    }
}

template <typename T>
forward_list<T>::forward_list(size_t count, const T& value) {
    head = new Node(value);
    Node* curr = head;
    for(int i = 0; i < count - 1; ++i) {
        curr -> next = new Node(value);
        curr = curr -> next; 
    }
}

template <typename T>
forward_list<T>::forward_list(const forward_list<T>& oth) {
    if(oth.head == nullptr) {
        return;
    }
    head = new Node(oth.head -> value);
    Node* curr1 = oth.head -> next;
    Node* curr2 = head;
    while(curr1 != nullptr) {
        curr2 -> next = new Node(curr1 -> value);
        curr1 = curr1 -> next;
        curr2 = curr2 -> next;
    }
}

template <typename T>
forward_list<T>::forward_list(forward_list<T>&& oth) {
    head = oth.head;
    delete oth.head;
    oth.head = new Node();
}

template <typename T>
forward_list<T>::forward_list(std::initializer_list<T> init) {
    auto begin = init.begin();
    auto end = init.end();
    if(begin == end) {
        return;
    }
    head = new Node(*(begin++));
    Node* curr = head;
    while(begin != end) {
        curr -> next = new Node(*(begin++));
        curr = curr -> next;
    }
}

template <typename T> 
forward_list<T>::~forward_list() {
    clear();
}

template <typename T>
forward_list<T>& forward_list<T>::operator=(const forward_list<T>& fl) {
    this -> clear();
    if(fl.head == nullptr) {
        return *this;
    }
    head = new Node(fl.head -> value);
    Node* curr1 = fl.head;
    Node* curr2 = head;
    while(curr1 -> next != nullptr) {
        curr2 -> next = new Node(*curr1 -> next);
        curr1 = curr1 -> next;
        curr2 = curr2 -> next;
    }
    return *this;
}

template <typename T>
void forward_list<T>::clear() noexcept {
    delete head;
    head = nullptr;
}

template <typename T>
forward_list<T>& forward_list<T>::operator=(forward_list<T>&& fl) {
    this -> clear();
    head = fl.head;
    fl.head = nullptr;
    return *this;
} 

template <typename T>
forward_list<T>& forward_list<T>::operator=(std::initializer_list<T> init) {
    auto begin = init.begin();
    auto end = init.end();
    if(begin == end) {
        return *this;
    }
    head = new Node(*(begin++));
    Node* curr = head;
    while(begin != end) {
        curr -> next = new Node(*(begin++));
        curr = curr -> next;
    }
    return *this;
}

template <typename T>
forward_list<T> forward_list<T>::assign(size_t count, T value) {
    if(count == 0) {
        return *this;
    }
    this -> clear();
    head = new Node(value);
    Node* curr = head;
    for(int i = 0; i < count - 1; ++i) {
        curr -> next = new Node(value);
        curr = curr -> next;
    }
    return *this;
}

template <typename T>
forward_list<T> forward_list<T>::assign(std::initializer_list<T> init) {
    return operator=(init);
}

template <typename T>
void forward_list<T>::swap(forward_list<T>& fl) noexcept {
    Node* tmp = head;
    head = fl.head;
    fl.head = tmp;
}

template <typename T>
const T& forward_list<T>::front() const {
    return head -> value;
}

template <typename T>
bool forward_list<T>::empty() const {
    return head == nullptr;
}

template <typename T>
size_t forward_list<T>::max_size() {
    size_t value{};
    Node* curr = head;
    while(curr != nullptr) {
        ++value;
        curr = curr -> next;
    }
    return value;
}

template <typename T>
void forward_list<T>::push_front(const T& val) {
    Node* curr = head;
    curr = new Node(val);
    curr -> next = head;
    head = curr;
}

template <typename T>
void forward_list<T>::insert_after(size_t pos, const T& value) {
    if(pos == 0) {
        push_front(value);
        return;
    }
    Node* curr = head;
    size_t size{};
    while(size != pos and curr != nullptr) {
        ++size;
        curr = curr -> next;
    }
    Node* tmp = new Node(value, curr -> next);
    curr -> next = tmp;
    tmp = nullptr;
}

template <typename T>
void forward_list<T>::pop_front() {
    head = head -> next;
}

template <typename T>
void forward_list<T>::insert_after(size_t pos, size_t count, const T& value) {
    while(count--) {
        insert_after(pos, value);
    }
}

template <typename T>
void forward_list<T>::erase_after(size_t pos) {
    Node* curr = head;
    size_t count {};
    while(count != pos and curr != nullptr) {
        ++count;
        curr = curr -> next;
    }
    if(curr -> next != nullptr) {
        Node* tmp = curr -> next;
        curr -> next = curr -> next -> next;
        delete tmp;
    }
}

template <typename T>
void forward_list<T>::sort() {
    Node* start = new Node();
    start -> next = head;
    Node* curr = head;
    Node* prev = start;
    while(curr != nullptr) {
        if(curr -> next && curr -> next -> value < curr -> value) {
            while(prev -> next && prev -> next -> value < curr -> next -> value) {
                prev = prev -> next;
            }
            auto tmp = prev -> next;
            prev -> next = curr -> next;
            curr -> next = curr -> next -> next;
            prev -> next -> next = tmp;
            prev = start;
        }
        else {
            curr = curr -> next;
        }
    }
    head = start -> next;
}

template <typename T>
void forward_list<T>::reverse() {
    Node* curr = head;
    Node* prev = nullptr;
    while(curr != nullptr) {
        Node* next = curr -> next;
        curr -> next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}


template <typename T>
bool forward_list<T>::operator==(const forward_list<T>& fl) const {
    Node* curr1 = head;
    Node* curr2 = fl.head;
    while(curr1 != nullptr && curr2 != nullptr) {
        if(curr1 -> value != curr2 -> value) {
            return false;
        }
        curr1 = curr1 -> next;
        curr2 = curr2 -> next;
    }
    if(curr1 != nullptr || curr2 != nullptr) {
        return false;
    }
    return true;
}

template <typename T>
bool forward_list<T>::operator!=(const forward_list<T>& fl) const {
    return !(*this == fl);
}

template <typename T>
bool forward_list<T>::operator<(const forward_list<T>& fl) const {
    Node* curr1 = head;
    Node* curr2 = fl.head;
    if (curr1 && !curr2) {
        return false;
    } 
    if (!curr1 && curr2) {
        return false;
    }
    while (curr1 != nullptr && curr2 != nullptr) {
        if (curr1 -> value > curr2 -> value) {
            return false;
        }
        curr1 = curr1 -> next;
        curr2 = curr2 -> next;
    }
    return true;
}

template <typename T>
bool forward_list<T>::operator<=(const forward_list<T>& fl) const {
    return (*this == fl) || (*this < fl);
}

template <typename T>
bool forward_list<T>::operator>(const forward_list<T>& fl) const {
    return !(this->operator<(fl));
}

template <typename T>
bool forward_list<T>::operator>=(const forward_list<T>& fl) const {
    return (*this == fl) || (*this > fl);
}
