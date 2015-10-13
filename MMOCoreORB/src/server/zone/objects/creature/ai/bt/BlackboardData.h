#ifndef BLACKBOARDDATA_H_
#define BLACKBOARDDATA_H_

#include <typeinfo>
#include <memory>
#include <cassert>

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

// Use partial specialization to account for variance in const types
template <typename T>
struct BlackboardType
{
    typedef T TYPE;
    typedef const T CONST;
    typedef T& REF;
    typedef const T& CONSTREF;
};

template <typename T>
struct BlackboardType<const T>
{
    typedef T TYPE;
    typedef const T CONST;
    typedef T& REF;
    typedef const T& CONSTREF;
};

template <typename T>
struct BlackboardType<T&>
{
    typedef T TYPE;
    typedef const T CONST;
    typedef T& REF;
    typedef const T& CONSTREF;
};

template <typename T>
struct BlackboardType<const T&>
{
    typedef T TYPE;
    typedef const T CONST;
    typedef T& REF;
    typedef const T& CONSTREF;
};

class BlackboardData : public Object
{
public:
    BlackboardData() : Object(), data(NULL) {}

    template <typename T>
    BlackboardData(T in)
        : Object(), data(new Data<typename BlackboardType<T>::TYPE>(in)) {}

    ~BlackboardData() {
        delete data;
    }
    
    template <typename T>
    typename BlackboardType<T>::REF get()
    {
        typedef typename BlackboardType<T>::TYPE TBASE;
        // TODO: turn these asserts into compile-time checks (will likely
        // require use of typeof and c++11 #if-checks)
        assert(typeid(Data<TBASE>) == typeid(*data));
        return static_cast<Data<TBASE>&>(*data).value;
    }
    
    template <typename T>
    typename BlackboardType<T>::CONSTREF get() const
    {
        typedef typename BlackboardType<T>::TYPE TBASE;
        assert(typeid(Data<TBASE>) == typeid(*data));
        return dynamic_cast<Data<TBASE>&>(*data).value;
    }
    
    template <typename T>
    void set(typename BlackboardType<T>::CONSTREF in)
    {
        delete data;
        data = new Data<typename BlackboardType<T>::TYPE>(in);
    }
    
private:
    class AbstractData
    {
    public:
        virtual ~AbstractData() {}
    };
    
    template <typename T>
    class Data : public AbstractData
    {
    public:
        Data(T in) : value(in) {}
        ~Data() {}
        T value;
    };
    
    AbstractData* data;
};

}
}
}
}
}
}

#endif // BLACKBOARDDATA_H_
