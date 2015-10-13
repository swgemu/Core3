#ifndef NOTBEHAVIOR_H_
#define NOTBEHAVIOR_H_

#include "Behavior.h"
class NotBehavior : public Behavior
{
    NotBehavior(AiAgent* _agent, const String& className)
        : Behavior(_agent, className) {}
    
    NotBehavior(const NotBehavior& b)
        : Behavior(b) {}
    
    NotBehavior& operator=(const NotBehavior& b)
    {
        Behavior::operator=(b);
        return *this;
    }
};

#endif // NOTBEHAVIOR_H_
