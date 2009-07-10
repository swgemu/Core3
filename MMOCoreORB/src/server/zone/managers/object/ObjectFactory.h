/*
 * ObjectFactory.h
 *
 *  Created on: 09/07/2009
 *      Author: TheAnswer
 */

#ifndef OBJECTFACTORY_H_
#define OBJECTFACTORY_H_

#include "engine/engine.h"

template <typename CtorSignature, typename UniqueIdType> class ObjectFactory;

namespace objectfactory {
	template<typename BaseClassType, typename Param1Type, typename Param2Type, typename ClassType>
	BaseClassType CreateObject(Param1Type param1, Param2Type param2) {
		return new ClassType(param1, param2);
	}
}

template<typename BaseClassType, typename Param1Type, typename Param2Type, typename UniqueIdType>
class ObjectFactory<BaseClassType (Param1Type, Param2Type), UniqueIdType>
{
protected:
   typedef BaseClassType (*CreateObjectFunc)(Param1Type, Param2Type);

public:
   template<typename ClassType> bool registerObject(UniqueIdType objectType) {
	   if (objectCreatorMap.contains(objectType))
		   return false;

	   objectCreatorMap.put(objectType, &objectfactory::CreateObject<BaseClassType, ClassType>);

	   return true;
   }

   bool unregisterObject(UniqueIdType objectType) {
	   return objectCreatorMap.drop(objectType);
   }

   BaseClassType createObject(UniqueIdType objectType, Param1Type param1, Param2Type param2) {
	   if (!objectCreatorMap.contains(objectType))
		   return NULL;
	   else
		   return (objectCreatorMap.get(objectType))(param1, param2);
   }

protected:
   VectorMap<unsigned int, CreateObjectFunc> objectCreatorMap;
};


#endif /* OBJECTFACTORY_H_ */
