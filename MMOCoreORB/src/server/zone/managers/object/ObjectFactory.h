/*
 * ObjectFactory.h
 *
 *  Created on: 09/07/2009
 *      Author: TheAnswer
 */

#ifndef OBJECTFACTORY_H_
#define OBJECTFACTORY_H_

#include "engine/engine.h"

//#include <map>

namespace objectfactory {
	template<typename BaseClassType, typename ClassType>
	BaseClassType* CreateObject(LuaObject* templ, BaseClassType* parent) {
	   return new ClassType(templ, parent);
	}
}

template<typename BaseClassType> class ObjectFactory {
	VectorMap<uint32, BaseClassType*(*)(LuaObject*, BaseClassType*)> objectMap;
public:
	//~ObjectFactory<BaseClassType>() { }

	template<typename ClassType>
	bool registerObject(uint32 str) {
		if (objectMap.contains(str))
			return false;

		objectMap.put(str, &objectfactory::CreateObject<BaseClassType, ClassType>);

		return true;
	}

	void unregisterObject(uint32 str) {
		return objectMap.drop(str);
	}

	BaseClassType* createObject(uint32 str, LuaObject* templ, BaseClassType* parent) {
		if (!objectMap.contains(str))
			return NULL;
		else
			return objectMap.get(str)(templ, parent);
	}

public:
	//ObjectFactory<BaseClassType>(void) { }
};


#endif /* OBJECTFACTORY_H_ */
