/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#ifndef LAMBDAOBSERVERFUNCTION_H_
#define LAMBDAOBSERVERFUNCTION_H_

#include "engine/util/Observable.h"
#include <functional>

class LambdaObserverFunction : public Object {
	std::function<int(uint32, Observable*, ManagedObject*, uint64)> func;
public:

  int notifyObserverEvent(uint32 eventType, Observable* obs, ManagedObject* arg1, uint64 arg2) {
	  return func(eventType, obs, arg1, arg2);
  }
  LambdaObserverFunction(std::function<int(uint32, Observable*, ManagedObject*, uint64)> f) : func(f) { }

  LambdaObserverFunction(const LambdaObserverFunction& rhs) : Object(rhs) {
	  func = rhs.func;
  }
};

#endif
