#ifndef STACK_H
#define STACK_H

#include <iostream>

template <typename T>
class stack {
public: // special member functions
    stack();
    stack(size_t);
    stack(size_t, const T&);
    stack(const std::initializer_list<T>&);
    stack(const stack<T>&);
    stack(stack<T>&&);
    stack& operator=(const stack<T>&);
    stack& operator=(stack<T>&&);
    stack& operator=(const std::initializer_list<T>&);
    ~stack();

public: // element access
    const T& top() const;
    T& top();

    const T& operator[](size_t) const;
    T& operator[](size_t);

public: // capacity
    bool empty() const;
    size_t size() const;

public:
    void push(const T&); 
    void pop();
    void swap(stack<T>&) noexcept;  

public: // non-member functions
    template <typename E>
    friend std::ostream& operator<<(std::ostream& os, stack<E>& st) {
        for (int i = 0; i < st.m_sp + 1; ++i) {
            os << st.m_stack[i] << "  ";
        }
        return os;
    }
    template <typename E>
    friend bool operator==(const stack<E>& s1, const stack<E>& s2) {
        if (s1.size() != s2.size()) {
            return false;
        }
        for (int i = 0; i < s1.size(); ++i) {
            if (s1.m_stack[i] != s2.m_stack[i]) {
                return false;
            }
        }
        return true;
    }
    
    template <typename E>
    friend bool operator !=(const stack<E>& s1, const stack<E>& s2) {
        return !(s1 == s2);
    }
private:
    T* m_stack;
    size_t m_sp;
};
#include "stack.hpp"
#endif // STACK_H