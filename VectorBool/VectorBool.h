#ifndef VECTORBOOL_H
#define VECTORBOOL_H
#include <iostream>
#include <initializer_list>

enum{bitCount = 8 * sizeof(size_t)};

class VectorBool
{
    public : 

    VectorBool();
    VectorBool(const VectorBool&);
    VectorBool(VectorBool&&);
    VectorBool(std::initializer_list<bool>);
    VectorBool(size_t);
    VectorBool(size_t , bool);
    ~VectorBool();

    public :

    void erase();
    void insert(size_t , bool);
    void push_back(bool);
    void pop_back();
    void resize();
    void shrink_to_fit();
    void clear();
    void replace(size_t , bool);

    public :

    bool isEmpty() const;
    bool at(size_t) const;
    size_t size() const;
    size_t capacity() const;

    public :

    class Reference
    {
        public :

        Reference(size_t* , size_t);
        Reference(const Reference&);
        Reference(Reference&&);
        Reference& operator = (const Reference&);
        operator bool() const;
        void flip();

        private :
        size_t* ptr;
        size_t index;
        bool val;
    };

    public :

    const size_t operator [](size_t index) const
    {
        if(index < 0 || index >= m_size)
        {
            throw std::out_of_range("Wrong index");
        }
        return m_buf[index];
    }

    friend std::ostream& operator << (std::ostream& print , const VectorBool& ob)
    {
        print << "Your VectorBool contains : ";
        for(int i = 0; i < ob.size(); ++i)
        {
            print << ob[i] << "  ";
        }
        print << std::endl;
        return print;
    } 

    private :

    size_t m_size;
    size_t m_capacity;
    size_t* m_buf;
};

#include "implVectorBool.hpp"
#endif