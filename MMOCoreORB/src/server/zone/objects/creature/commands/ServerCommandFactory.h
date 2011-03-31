/*
 * ServerCommandFactory.h
 *
 *  Created on: 31/03/2011
 *      Author: victor
 */

#ifndef SERVERCOMMANDFACTORY_H_
#define SERVERCOMMANDFACTORY_H_

#include "engine/engine.h"

template<typename KeyType, typename ParamType1, typename ParamType2, typename ParamType3> class MethodFactory;

template<typename ClassType, typename ParamType1, typename ParamType2, typename ParamType3> int RunMethod(ParamType1 param1, ParamType2 param2, ParamType3 param3) {
	return ClassType::executeCommand(param1, param2, param3);
}

template<typename KeyType, typename ParamType1, typename ParamType2, typename ParamType3>
class MethodFactory
{
protected:
	typedef int (*RunMethodFunc)(ParamType1, ParamType2, ParamType3);

public:
	int runMethod(KeyType uniqueID, ParamType1 param1, ParamType2 param2, ParamType3 param3) {
		if (!methodFactory.containsKey(uniqueID))
			return -1;

		return methodFactory.get(uniqueID)(param1, param2, param3);
	}

	template<typename ClassType> bool registerMethod(KeyType uniqueID) {
		if (methodFactory.containsKey(uniqueID))
			return false;

		methodFactory.put(uniqueID, &RunMethod<ClassType>);

		return true;
	}

	bool unregisterMethod(KeyType uniqueID) {
		return methodFactory.drop(uniqueID);
	}

	bool containsMethod(KeyType uniqueID) {
		return methodFactory.containsKey(uniqueID);
	}

protected:
	HashTable<KeyType, RunMethodFunc> methodFactory;
};



#endif /* SERVERCOMMANDFACTORY_H_ */
