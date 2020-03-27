#ifndef DEQUE_H
#define DEQUE_H
// Filename: Deque.h
//Name: Caleb Fischer
#include <iostream>
#include <exception>
class UnderflowError {}; // this is thrown when removing a value from an
// empty deque
class OverflowError {}; // this is thrown when a value cannot be added
// (when memory cannot be allocated)

template < typename T >
class Deque
{
public:
    Deque();
    Deque(const Deque & c);
    ~Deque();
    Deque operator=(const Deque & d);
    T operator[](int i) const;
    
    void resize(int size);
    Deque insert_head(const int n);
    Deque insert_tail(const int n);
    T remove_head();
    T remove_tail();
    
    int size();
    void clear();
    bool is_empty();
    
private:
    T * x_;
    int size_;
    int capacity_;
};

template< class T >
std::ostream & operator<<(std::ostream & cout, const Deque <T> & d);

template < typename T >
Deque<T>::Deque()
    : size_(0), capacity_(0), x_(new T[0])
{}


template < typename T >
Deque<T>::Deque(const Deque & c)
    : x_(new T[c.capacity_]), size_(c.size_), capacity_(c.capacity_)
{
    for (int i = 0; i < size_; ++i)
    {
        x_[i] = c.x_[i];
    }
}


template < typename T>
Deque<T>::~Deque()
{
    delete [] x_;
}


template < typename T >
void Deque<T>::resize(int size)
{
    if ((size > this->capacity_) || (size < this->capacity_ / 3))
    {
        int * q = new T[size * 2];
        
        for (int i = 0; i < (size < this->size_ ? size : this->size_); ++i)
        {
            //std::cout << "p_[i]" << p_[i] << std::endl;
            q[i] = this->x_[i];
        }
        delete [] x_;
        capacity_ = size * 2;
        this->x_ = q;
        //x equals address of q
    }
    this->size_ = size;
}


template < typename T >
Deque<T> Deque<T>::insert_head(const int n)
{
    try
    {
        this->resize(this->size_ + 1);
        int newVal = n;
        int oldVal;
        for (int i = 0; i < this->size_; ++i)
        {
            oldVal = this->x_[i];
            this->x_[i] = newVal;
            newVal = oldVal;  
        }
        
        return (*this);
    }
    catch (std::bad_alloc & e)
    {
        throw OverflowError();
    }
}


template < typename T >
Deque<T> Deque<T>::insert_tail(const int n)
{
    try
    {
        //std::cout << "size: " << size_ + 1 << std::endl;
        this->resize(this->size_ + 1);
        this->x_[this->size_ - 1] = n;
        return (*this);
    }
    catch (std::bad_alloc & e)
    {
        throw OverflowError();
    }
}


template < typename T >
T Deque<T>::remove_head()
{
    if (this->size_ == 0)
    {
        throw UnderflowError();
    }
    
    T ret = this->x_[0];
    int newVal;
    for (int i = 0; i < this->size_ - 1; ++i)
    {
        newVal = this->x_[i + 1];
        this->x_[i] = newVal;
    }
    this->resize((this->size_ - 1));
    return (ret);
}


template < typename T >
T Deque<T>::remove_tail()
{
    if (this->size_ == 0)
    {
        throw UnderflowError();
    }
    
    T ret = this->x_[this->size_ - 1];
    this->resize((this->size_ - 1));
    return (ret);
}


template < typename T >
Deque<T> Deque<T>::operator=(const Deque & d)
{
    if (this != &d)
    {
        if (this->capacity_ < d.size_)
        {
            delete [] x_;
            x_ = new int[d.size_];
        }
        
        for (int i = 0; i < d.size_; ++i)
        {
            x_[i] = d.x_[i];
        }
        
        capacity_ = d.capacity_;
        size_ = d.size_;
    }
    return (*this);
}


template < typename T >
T Deque<T>::operator[](int i) const
{
    return (x_[i]);
}


template < typename T >
int Deque<T>::size()
{
    return (this->size_);
}



template < typename T >
void Deque<T>::clear()
{
    this->size_ = 0;
    this->capacity_ = 0;
    delete [] x_;
    x_ = new T[0];
}


template < typename T >
bool Deque<T>::is_empty()
{
    return (this->size_ == 0);
}


template< typename T >
std::ostream & operator<<(std::ostream & cout, Deque <T> & d)
{
    cout << '[';
    for (int i = 0; i < d.size(); ++i)
    {
        cout << d[i];
        if (i < d.size() - 1) cout << ", ";
    }
    cout << ']';
    return cout;
}

#endif
