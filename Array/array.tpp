#include "array.hpp"

template <typename T, size_t N>
ds::array<T, N>::array() : m_size{N} {
    if (m_size == 0) {
        m_arr = nullptr;
    } else {
        m_arr = new T[m_size];
        for (int i = 0; i < m_size; ++i) {
            m_arr[i] = 0;
        }
    }
}
 
template <typename T, size_t N>
ds::array<T, N>::array(const ds::array<T, N>& rhs) {
    if (m_arr) {
        delete[] m_arr;
    }
    m_size = N;
    m_arr = new T[m_size];
    for (int i = 0; i < m_size; ++i) {
        m_arr[i] = rhs.m_arr[i];
    }
}
    
template <typename T, size_t N>
ds::array<T, N>::array(array<T, N>&& rhs) {
    m_size = N;
    m_arr = rhs.m_arr;
    rhs.m_arr = nullptr;
}

template <typename T, size_t N>
ds::array<T, N>::array(std::initializer_list<T> init) {
    if (init.size() != N) {
        throw std::runtime_error("Wrong initializer list size");
    }
    m_size = N;
    m_arr = new T[m_size];
    auto it = init.begin();
    for (int i = 0; i < m_size; ++i) {
        m_arr[i] = *it;
        ++it;
    }
} 

template <typename T, size_t N>
ds::array<T, N>::~array() {
    delete[] m_arr;
    m_arr = nullptr;
}

template <typename T, size_t N>
ds::array<T, N>& ds::array<T, N>::operator=(const ds::array<T, N>& rhs) {
    if (this == &rhs) {
        return *this;
    }
    if (m_arr) {
        delete[] m_arr;
    }
    m_size = N;
    m_arr = new T[m_size];
    for (int i = 0; i < m_size; ++i) {
        m_arr[i] = rhs.m_arr[i];
    }
    return *this;
}

template <typename T, size_t N>
ds::array<T, N>& ds::array<T, N>::operator=(ds::array<T, N>&& rhs) {
    if (this == &rhs) {
        return *this;
    } 
    m_size = N;
    m_arr = rhs.m_arr;
    rhs.m_arr = nullptr;
}

template <typename T, size_t N>
T& ds::array<T, N>::at(size_t pos) {
    if (pos < 0 or pos >= m_size) {
        throw std::runtime_error("Wrong position");
    }
    return m_arr[pos];
}

template <typename T, size_t N>
const T& ds::array<T, N>::at(size_t pos) const {
    if (pos < 0 or pos >= m_size) {
        throw std::runtime_error("Wrong position");
    }
    return m_arr[pos];
}

template <typename T, size_t N>
T& ds::array<T, N>::operator[](size_t pos) {
    return m_arr[pos];
}

template <typename T, size_t N>
const T& ds::array<T, N>::operator[](size_t pos) const {
    return m_arr[pos];
}

template <typename T, size_t N>
T& ds::array<T, N>::front() {
    return m_arr[0];
}

template <typename T, size_t N>
const T& ds::array<T, N>::front() const {
    return m_arr[0];
}

template <typename T, size_t N>
T& ds::array<T, N>::back() {
    return m_arr[m_size - 1];
}

template <typename T, size_t N>
const T& ds::array<T, N>::back() const {
    return m_arr[m_size - 1];
}

template <typename T, size_t N>
T* ds::array<T, N>::data() {
    if (m_size == 0) {
        return nullptr;
    }
    return m_arr;
}

template <typename T, size_t N>
const T* ds::array<T, N>::data() const noexcept {
    if (m_size == 0) {
        return nullptr;
    }
    return m_arr;
}

template <typename T, size_t N>
ds::array<T, N>::iterator::iterator() : m_ptr(nullptr) {}

template <typename T, size_t N>
ds::array<T, N>::iterator::iterator(T* ptr) : m_ptr(ptr) {}

template <typename T, size_t N>
ds::array<T, N>::iterator::iterator(const iterator& it) : m_ptr(it.m_ptr) {}

template <typename T, size_t N>
typename ds::array<T, N>::iterator& ds::array<T, N>::iterator::operator+=(difference_type rhs) {
    m_ptr += rhs;
    return *this;
}

template <typename T, size_t N>
typename ds::array<T, N>::iterator& ds::array<T, N>::iterator::operator-=(difference_type rhs) {
    m_ptr -= rhs;
    return *this;
}

template <typename T, size_t N>
T& ds::array<T, N>::iterator::operator*() {
    return *m_ptr;
}

template <typename T, size_t N>
T* ds::array<T, N>::iterator::operator->() {
    return m_ptr;
}

template <typename T, size_t N>
T& ds::array<T, N>::iterator::operator[](difference_type rhs) {
    return m_ptr[rhs];
}

template <typename T, size_t N>
typename ds::array<T, N>::iterator& ds::array<T, N>::iterator::operator++() {
    ++m_ptr;
    return *this;
}

template <typename T, size_t N>
typename ds::array<T, N>::iterator& ds::array<T, N>::iterator::operator--() {
    --m_ptr;
    return *this;
}

template <typename T, size_t N>
typename ds::array<T, N>::iterator& ds::array<T, N>::iterator::operator++(int) {
    iterator tmp(this);
    ++m_ptr;
    return tmp;
}

template <typename T, size_t N>
typename ds::array<T, N>::iterator& ds::array<T, N>::iterator::operator--(int) {
    iterator tmp(this);
    --m_ptr;
    return tmp;
}

template <typename T, size_t N>
typename ds::array<T, N>::iterator::difference_type ds::array<T, N>::iterator::operator-(const iterator& rhs) {
    return m_ptr - rhs.m_ptr;
}

template <typename T, size_t N>
typename ds::array<T, N>::iterator ds::array<T, N>::iterator::operator-(difference_type rhs) {
    return iterator(m_ptr - rhs);
}

template <typename T, size_t N>
typename ds::array<T, N>::iterator ds::array<T, N>::iterator::operator+(difference_type rhs) {
    return iterator(m_ptr + rhs);
}

template <typename T, size_t N>
bool ds::array<T, N>::iterator::operator==(const iterator& rhs) {
    return m_ptr == rhs.m_ptr;
}

template <typename T, size_t N>
bool ds::array<T, N>::iterator::operator!=(const iterator& rhs) {
    return m_ptr != rhs.m_ptr;
}

template <typename T, size_t N>
bool ds::array<T, N>::iterator::operator>=(const iterator& rhs) {
    return m_ptr >= rhs.m_ptr;
}

template <typename T, size_t N>
bool ds::array<T, N>::iterator::operator<=(const iterator& rhs) {
    return m_ptr <= rhs.m_ptr;
}

template <typename T, size_t N>
bool ds::array<T, N>::iterator::operator>(const iterator& rhs) {
    return m_ptr > rhs.m_ptr;
}

template <typename T, size_t N>
bool ds::array<T, N>::iterator::operator<(const iterator& rhs) {
    return m_ptr < rhs.m_ptr;
}

template <typename T, size_t N>
typename ds::array<T, N>::iterator ds::array<T, N>::begin() {
    return iterator(m_arr);
}

template <typename T, size_t N> 
typename ds::array<T, N>::iterator ds::array<T, N>::end() {
    return iterator(m_arr + m_size);
}

template <typename T, size_t N>
bool ds::array<T, N>::empty() const {
    return m_size == 0;
}

template <typename T, size_t N>
size_t ds::array<T, N>::size() const {
    return m_size;
}

template <typename T, size_t N>
void ds::array<T, N>::fill(const T& val) {
    for (int i = 0; i < m_size; ++i) {
        m_arr[i] = val;
    }
}

template <typename T, size_t N>
void ds::array<T, N>::swap(ds::array<T, N>& other) {
    T** tmp = &m_arr;
    m_arr = other.m_arr;
    other.m_arr = *tmp;
}