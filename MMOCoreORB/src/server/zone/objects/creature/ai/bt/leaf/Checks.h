#ifndef CHECKS_H_
#define CHECKS_H_

#include "server/zone/objects/creature/ai/bt/Behavior.h"
#include "server/zone/objects/creature/CreaturePosture.h"
#include "server/zone/managers/creature/PetManager.h"

// helper macro to re-implement all the necessary constructors
// this is unneccesary in c++11 with access to a smarter using,
// but since we can't guarantee c++11, this will do.
// in the future, if we guarantee c++11, all we need to do is 
// 'using Behavior::Behavior'
#define _CHECK(class_name, check, check_op, val_type) \
class class_name : public Behavior \
{ \
public: \
    class_name(const String& className, const uint32 id, const String& argString = "") \
        : Behavior(className, id, argString), checkVar((val_type)(0)) {} \
    class_name(const class_name& c) \
        : Behavior(c) { checkVar = c.checkVar; } \
    class_name& operator=(const class_name& c) { \
        if (this == &c) \
            return *this; \
        Behavior::operator=(c); \
        checkVar = c.checkVar; \
        return *this; \
    } \
    Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const { \
        return checkArg<val_type, check_op>()(agent->check, checkVar) ? \
                            SUCCESS : FAILURE; \
    } \
    void parseArgs(const String& argString) { \
        VectorMap<String, String> args = Behavior::fillArgs(argString); \
        checkVar = getArg<val_type>()(args.get("condition")); \
    } \
private: \
    val_type checkVar; \
};

#define _ARGPAIR(bigT, converter) \
template <> \
struct getArg<bigT> { \
    bigT operator()(const String& val) { \
        return converter::valueOf(val); \
    } \
};

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
namespace leaf {
	
template <typename T> struct getArg {};
_ARGPAIR(int32, Integer)
_ARGPAIR(uint32, UnsignedInteger)
_ARGPAIR(int64, Long)
_ARGPAIR(uint64, UnsignedLong)
_ARGPAIR(float, Float)
_ARGPAIR(double, Double)

template <typename T, char O> struct checkArg {};

template <typename T>
struct checkArg<T, '='> {
    bool operator() (T a, T b) { return a == b; }
};

template <typename T>
struct checkArg<T, '>'> {
    bool operator() (T a, T b) { return a > b; }
};

_CHECK(CheckPosture,     getPosture(),     '=', uint32)
_CHECK(CheckDestination, setDestination(), '>', int32)
_CHECK(CheckFollowState, getFollowState(), '=', int32)
//_CHECK(CheckLastCommand, getLastCommand(), '=', uint32) // TODO: implement pet checks

}
}
}
}
}
}
}

#endif // CHECKS_H_