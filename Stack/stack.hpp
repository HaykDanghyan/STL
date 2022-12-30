#include "stack.h"

template <typename T>
stack<T>::stack() : m_stack(nullptr), m_sp{0} {};

template <typename T>
stack<T>::stack(size_t count) : m_sp{count - 1} {
    m_stack = new T[count];
    for (int i = 0; i < count; ++i) {
        m_stack[i] = T();
    }
}

template <typename T>
stack<T>::stack(size_t count, const T& val) : m_sp{count - 1} {
    m_stack = new T[count];
    for (int i = 0; i < count; ++i) {
        m_stack[i] = val;
    }
}

template <typename T>
stack<T>::stack(const std::initializer_list<T>& init) : m_sp{init.size() - 1} {
    m_stack = new T[init.size()];
    int i = 0;
    for (const auto& el : init) {
        m_stack[i++] = el;
    }
}

template <typename T>
stack<T>::stack(const stack<T>& st) : m_sp{st.m_sp} {
    if (m_stack) {
        delete[] m_stack;
    }
    m_stack = new T[m_sp + 1];
    for (int i = 0; i < m_sp + 1; ++i) {
        m_stack[i] = st.m_stack[i];
    }
}

template <typename T>
stack<T>::stack(stack<T>&& st) : m_sp{st.m_sp} {
    m_stack = st.m_stack;
    st.m_stack = nullptr;
}

template <typename T>
stack<T>& stack<T>::operator=(const stack<T>& st) {
    if (this == &st) {
        return *this;
    }
    m_sp = st.m_sp;
    if (m_stack) {
        delete[] m_stack;
    }
    m_stack = new T[m_sp + 1];
    for (int i = 0; i < m_sp + 1; ++i) {
        m_stack[i] = st.m_stack[i];
    }
    return *this;
}

template <typename T>
stack<T>& stack<T>::operator=(stack<T>&& st) {
    if (this == &st) {
        return *this;
    }
    m_sp = st.m_sp;
    m_stack = st.m_stack;
    st.m_stack = nullptr;
    return *this;
}

template <typename T>
stack<T>& stack<T>::operator=(const std::initializer_list<T>& init) {
    auto it = init.begin();
    if (it == init.end()) {
        return *this;
    }
    if (m_stack) {
        delete[] m_stack;
    }
    m_sp = init.size() - 1;
    m_stack = new T[init.size()];
    int i = 0;
    for (; it != init.end(); ++it) {
        m_stack[i++] = *it;
    }
    return *this;
}

template <typename T>
stack<T>::~stack() {
    delete[] m_stack;
    m_stack = nullptr;
}

template <typename T>
const T& stack<T>::top() const {
    return m_stack[m_sp];
}

template <typename T>
T& stack<T>::top() {
    return m_stack[m_sp];
}

template <typename T>
const T& stack<T>::operator[](size_t pos) const {
    return m_stack[pos];
}

template <typename T>
T& stack<T>::operator[](size_t pos) {
    return m_stack[pos];
}

template <typename T>
bool stack<T>::empty() const {
    return m_stack == nullptr && m_sp == 0;
}

template <typename T>
size_t stack<T>::size() const {
    return m_sp + 1;
}

template <typename T>
void stack<T>::push(const T& val) {
    ++m_sp;
    T* tmp = new T[m_sp + 1];
    tmp[0] = val;
    for (int i = 1; i < m_sp + 1; ++i) {
        tmp[i] = m_stack[i - 1];
    }
    delete[] m_stack;
    m_stack = tmp;
    tmp = nullptr;
}

template <typename T>
void stack<T>::pop() {
    --m_sp;
    T* tmp = new T[m_sp + 1];
    for (int i = 0; i < m_sp + 1; ++i) {
        tmp[i] = m_stack[i + 1];
    }
    delete[] m_stack;
    m_stack = tmp;
    tmp = nullptr;
}

template <typename T>
void stack<T>::swap(stack<T>& oth) noexcept {
    m_sp = oth.m_sp;
    std::swap(m_stack, oth.m_stack);
}