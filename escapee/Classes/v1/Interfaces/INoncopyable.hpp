#ifndef __INTERFACES_INONCOPYABLE_HPP__
#define __INTERFACES_INONCOPYABLE_HPP__

namespace Interfaces
{

class INoncopyable
{
protected:

    INoncopyable() = default;
    virtual ~INoncopyable() =default;

    INoncopyable( const INoncopyable& ) = delete;
    INoncopyable& operator=( const INoncopyable& ) = delete;
};

}

#endif