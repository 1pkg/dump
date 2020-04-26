#ifndef __NON_COPYABLE_HPP__
#define __NON_COPYABLE_HPP__

namespace ThirdParty
{

class noncopyable
{
protected:

    noncopyable() = default;
    ~noncopyable() = default;

    noncopyable( const noncopyable& ) = delete;
    noncopyable& operator=( const noncopyable& ) = delete;
};

}

#endif