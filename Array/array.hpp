#ifndef DS_ARRAY_HPP
#define DS_ARRAY_HPP

#include <iostream>
#include <stdexcept>

namespace ds {
    template <typename T, size_t N>
    class array {
    public: // special member functions
        array(); 
        array(const array<T, N>&); 
        array(array<T, N>&&); 
        array(std::initializer_list<T>);
		~array();

        array& operator=(const array<T, N>&);
        array& operator=(array<T, N>&&);

    public: // element access
        T& at(size_t);
        const T& at(size_t) const;

        T& operator[](size_t);
        const T& operator[](size_t) const;

        T& front();
        const T& front() const;

        T& back();
        const T& back() const;

        T* data();
        const T* data() const noexcept;

    public:
        class iterator : public std::iterator<std::random_access_iterator_tag, T> {
        public:
            using difference_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
        
        public:
            iterator();
            iterator(T*);
            iterator(const iterator&);

        public:
            iterator& operator+=(difference_type);
            iterator& operator-=(difference_type);
            T& operator*();
            T* operator->();
            T& operator[](difference_type);
        
        public:
            iterator& operator++();
            iterator& operator--();
            iterator& operator++(int);
            iterator& operator--(int);

        public:
            difference_type operator-(const iterator&);
            iterator operator+(difference_type);
            iterator operator-(difference_type);

        public:
            bool operator==(const iterator&);
            bool operator!=(const iterator&);
            bool operator>=(const iterator&);
            bool operator<=(const iterator&);
            bool operator>(const iterator&);
            bool operator<(const iterator&);

        private:
            T* m_ptr;
        };

        iterator begin();
        iterator end();

    public: // capacity
        bool empty() const;
        size_t size() const;

    public: // operations
        void fill(const T&);
        void swap(array<T, N>&);

    public: // non-member functions
        template <typename X, size_t Y>
        friend bool operator==(const array<X, Y>& lhs, const array<X, Y>& rhs) {
            for (int i = 0; i < lhs.size(); ++i) {
                if (lhs.m_arr[i] != rhs.m_arr[i]) {
                    return false;
                }
            }
            return true;
        }

        template <typename X, size_t Y>
        friend bool operator!=(const array<X, Y>& lhs, const array<X, Y>& rhs) {
            return !(lhs == rhs);
        }

        template <typename X, size_t Y>
        friend bool operator>(const array<X, Y>& lhs, const array<X, Y>& rhs) {
            for (int i = 0; i < lhs.size(); ++i) {
                if (!(lhs.m_arr[i] > rhs.m_arr[i])) {
                    return false;
                }
            }
            return true;
        }

        template <typename X, size_t Y>
        friend bool operator>=(const array<X, Y>& lhs, const array<X, Y>& rhs) {
            return (lhs > rhs) || (lhs == rhs);
        }

        template <typename X, size_t Y>
        friend bool operator<(const array<X, Y>& lhs, const array<X, Y>& rhs) {
            for (int i = 0; i < lhs.size(); ++i) {
                if (!(lhs.m_arr[i] < rhs.m_arr[i])) {
                    return false;
                }
            }
            return true;
        }

        template <typename X, size_t Y>
        friend bool operator<=(const array<X, Y>& lhs, const array<X, Y>& rhs) {
            return (lhs < rhs) || (lhs == rhs);
        }

        template <typename X, size_t Y>
        friend std::ostream& operator<<(std::ostream& os, const array<X, Y>& arr) {
            for (int i = 0; i < arr.size(); ++i) {
                os << arr[i] << "  "; 
            }
            return os;
        }

    private:
        T* m_arr; 
        size_t m_size; 
    };
};
#include "array.tpp"
#endif // DS_ARRAY_HPP
