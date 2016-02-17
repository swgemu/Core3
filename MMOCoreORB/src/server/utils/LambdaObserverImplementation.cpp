#include "LambdaObserver.h"

int LambdaObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable *observable, ManagedObject *arg1, long arg2) {
	if(function.getLambda() != NULL)
	return functiongetLambda()(eventType, observable, arg1, arg2);
}
