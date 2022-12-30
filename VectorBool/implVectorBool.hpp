#include "VectorBool.h"

VectorBool::Reference::Reference(size_t* p , size_t ind) : ptr{p} , index{ind} , val{}
{
    val = ptr[index / bitCount] & (1 << (index % bitCount));
}

void VectorBool::Reference::flip()
{
    if(val == 1)
    {
        ptr[index / bitCount] ^= (1 << (index % bitCount));
    }
    else
    {
        ptr[index / bitCount] |= (1 << (index % bitCount));
        val == true;
    }
}

VectorBool::Reference::Reference(const VectorBool::Reference& oth) : ptr{oth.ptr} , index{oth.index} , val{oth.val}
{}

VectorBool::Reference::Reference(VectorBool::Reference&& oth) : ptr{oth.ptr} , index{oth.index} , val{oth.val}
{
    delete[] oth.ptr;
    oth.ptr = nullptr;
    oth.val = 0;
    oth.index = 0;
}

VectorBool::Reference& VectorBool::Reference::operator=(const VectorBool::Reference& oth)
{
    if(val != oth.val)
    {
        flip();
    }
    return *this;
}

VectorBool::Reference::operator bool() const
{
    return val;
}

VectorBool::VectorBool() : m_capacity{bitCount} , m_size{}
{
    m_buf = new size_t[m_capacity];
}

VectorBool::VectorBool(const VectorBool& oth) : m_capacity{oth.m_capacity} , m_size{oth.m_size}
{
    m_buf = new size_t[m_capacity / bitCount];
    for(size_t i = 0; i < m_size; ++i)
    {
        m_buf[i] = oth.m_buf[i];
    }
}

VectorBool::VectorBool(std::initializer_list<bool> init) : m_size{init.size()} , m_capacity{} , m_buf{}
{
    if(init.size())
    {
        while(m_capacity < init.size())
        {
            m_capacity += bitCount;
        }
    }
    m_buf = new size_t[m_capacity];
    size_t i = 0 , bit = 1;
    for(auto iter = init.begin(); iter != init.end(); ++iter , ++i)
    {
        if(*iter)
        {
            m_buf[i / bitCount] |= (1 << (i % bitCount));
        }
        bit <<= 1;
    }
}

VectorBool::VectorBool(size_t count) : m_capacity{} , m_size{count} , m_buf{}
{
    if(count)
    {
        while(m_capacity < count)
        {
            m_capacity += bitCount;
        }
    }
    m_buf = new size_t[m_capacity];
}

VectorBool::VectorBool(size_t count , bool val) : m_capacity{} , m_size{count} , m_buf{}
{
    if(count)
    {
        while (m_capacity < count)
        {
            m_capacity += bitCount;
        }
        m_buf = new size_t[m_capacity];
    }
    if(val)
    {
        bool bit = 1;
        for(int i = 0; i < m_size; ++i)
        {
            m_buf[i] |= bit;
            bit <<= 1;
        }
    }
}

VectorBool::~VectorBool()
{
    delete[] m_buf;
    m_buf = nullptr; 
}

bool VectorBool::isEmpty() const
{
    return !m_size;
}

size_t VectorBool::size() const
{
    return m_size;
}

size_t VectorBool::capacity() const
{
    return m_capacity;
}

void VectorBool::insert(size_t pos , bool val)
{
    if(isEmpty())
    {
        m_capacity = bitCount;
        m_buf = new size_t[1];
        m_buf[m_size++] = val;
    }
}

void VectorBool::pop_back()
{
    --m_size;
}

void VectorBool::push_back(bool val)
{
    ++m_size;
    resize();
    size_t* tmp = new size_t[m_capacity];
    for(int i = 0; i < m_size; ++i)
    {
        tmp[i] = m_buf[i];
    }
    tmp[m_size - 1] = val;
    delete[] m_buf;
    m_buf = tmp;
    tmp = nullptr;

}

bool VectorBool::at(size_t index) const
{
    if(index >= m_size)
    {
        throw std::out_of_range("Wrong index ! At() function");
    }
    return m_buf[index];
}   

void VectorBool::resize()
{
    if(m_size == m_capacity)
    {
        m_capacity *= 2;
    }
}

void VectorBool::shrink_to_fit()
{
    if(m_capacity > m_size)
    {
        m_capacity = m_size;
    }
}

void VectorBool::clear()
{
    m_size = 0;
    delete[] m_buf;
    m_buf = new size_t[m_capacity];
}

void VectorBool::replace(size_t index , bool val)
{
    if(index >= m_size)
    {
        throw std::out_of_range("Wrong index , replace() function");
    }
    size_t* tmp = new size_t[m_capacity];
    for(int i = 0; i < m_size; i++)
    {
        tmp[i] = m_buf[i];
    }
    for(int i = 0; i < m_size; i++)
    {
        if(i != index)
        {
            continue;
        }
        else
        {
            tmp[i] = tmp[i + 1];
            tmp[index] = val;
        }
    }
    delete[] m_buf;
    m_buf = tmp;
    tmp = nullptr;
}