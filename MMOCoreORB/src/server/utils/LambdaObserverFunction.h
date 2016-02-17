/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#ifndef LAMBDAOBSERVERFUNCTION_H_
#define LAMBDAOBSERVERFUNCTION_H_

#include "engine/util/Observable.h"
#include <functional>
#include "engine/core/LambdaFunction.h"

/*
 * Usage:
registerObserver(ObserverEventType::CREATUREREVIVED, new LambdaObserver(
		new LambdaObserverFunction([newPosture](uint32 eventType, Observable *observable, ManagedObject *arg1, uint64 arg2) ->int {
	return 1;
}, "TestObserver")));
*/
  
class LambdaObserverFunction : public Object {
	LambdaFunction<std::function<int(uint32, Observable*, ManagedObject*, uint64)> > function;

public:
	template<class L>
	LambdaObserverFunction(L&& l, const char* name) : function(std::forward<L>(l), name) {

	}

	int notifyObserverEvent(uint32 eventType, Observable* obs, ManagedObject* arg1, uint64 arg2) {
	  return function.getLambda()(eventType, obs, arg1, arg2);
	}

};

#endif
