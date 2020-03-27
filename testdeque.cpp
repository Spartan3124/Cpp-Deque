#include <iostream>
#include <exception>
#include "Deque.h"

int main()
{
    
    Deque< int > dq;
    std::cout << dq << std::endl;
    dq.insert_head(5);
    std::cout << dq << std::endl;
    dq.insert_head(6);
    std::cout << dq << std::endl;
    dq.insert_tail(-1);
    std::cout << dq << std::endl;
    std::cout << dq.size() << std::endl;

    Deque< int > dq1(dq);
    std::cout << dq1 << std::endl;
    Deque< int > dq2;
    dq2 = dq;
    std::cout << dq2 << std::endl;
    dq = dq;
    std::cout << dq << std::endl;

    int head = dq.remove_head();
    std::cout << "head: " << head << std::endl;
    std::cout << dq << std::endl;
    int tail = dq.remove_tail();
    std::cout << "tail: " << tail << std::endl;
    std::cout << dq << std::endl;

    dq.clear();
    std::cout << dq << std::endl;
    std::cout << "is_empty: " << dq.is_empty() << std::endl;
    std::cout << dq << std::endl;
    try
    {
        dq.remove_head();
    }
    catch(const UnderflowError & e)
    {
        std::cout << "underflow error!" << std::endl;
    }

    //**************************************************************************
    //ONLY UNCOMMENT TO TEST OVERFLOW ERROR
    //**************************************************************************
    // try
    // {
    //     dq.resize(299999990);
    //     while (1)
    //     {
    //         dq.resize(dq.size() * 2);
    //         std::cout << "size: " << dq.size() << std::endl;
    //         dq.insert_tail(1); // to cause memory allocation error
    //     }
    // }
    // catch (const OverflowError & e)
    // {
    //     std::cout << "overflow error!" << std::endl;
    // }
    
    return 0;
}
