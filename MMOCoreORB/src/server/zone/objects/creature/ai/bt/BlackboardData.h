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

class BlackboardData
{
public:
    template <typename T>
    BlackboardData(T in) : data(new Data<typename BlackboardType<T>::TYPE>(in)) {}
    
    template <typename T>
    typename BlackboardType<T>::REF get()
    {
        typedef typename BlackboardType<T>::TYPE TBASE;
        // TODO: turn these asserts into compile-time checks (will likely require use of typeof)
        assert(typeid(Data<TBASE>) == typeid(*data.get()));
        return static_cast<Data<TBASE>&>(*data.get()).value;
    }
    
    template <typename T>
    typename BlackboardType<T>::CONSTREF get() const
    {
        typedef typename BlackboardType<T>::TYPE TBASE;
        assert(typeid(Data<TBASE>) == typeid(*data.get()));
        return dynamic_cast<Data<TBASE>&>(*data.get()).value;
    }
    
    template <typename T>
    void set(typename BlackboardType<T>::CONSTREF in)
    {
        data.reset(new Data<typename BlackboardType<T>::TYPE>(in));
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
    
    std::auto_ptr<AbstractData> data;
};

}
}
}
}
}
}

#endif // BLACKBOARDDATA_H_