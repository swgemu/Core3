/*
 * SceneObjectFactory.h
 *
 *  Created on: 28/07/2010
 *      Author: victor
 */

#ifndef SCENEOBJECTFACTORY_H_
#define SCENEOBJECTFACTORY_H_

#include "engine/engine.h"

namespace server {
 namespace zone {
  namespace managers {
   namespace object {

   template <typename CtorSignature, typename UniqueIdType> class SceneObjectFactory;

   template<typename BaseClassType, typename ClassType> BaseClassType CreateObject() {
	   return new ClassType();
   }

   template <typename TypeId, typename Value>
   class ObjectCreatorMap : public HashTable<TypeId, Value> {
	   int hash(const TypeId& k) const {
		   return (int)k;
	   }

   public:
	   ObjectCreatorMap() {
		   HashTable<TypeId, Value>::setNullValue(NULL);
	   }
   };

   template<typename BaseClassType, typename UniqueIdType>
   class SceneObjectFactory<BaseClassType (), UniqueIdType>
   {
   protected:
	   typedef BaseClassType (*CreateObjectFunc)();

   public:
	   BaseClassType createObject(UniqueIdType uniqueID) {
		   if (!objectCreator.containsKey(uniqueID))
			   return NULL;

		   return objectCreator.get(uniqueID)();
	   }

	   template<typename ClassType> bool registerObject(UniqueIdType uniqueID) {
		   if (objectCreator.containsKey(uniqueID))
			   return false;

		   objectCreator.put(uniqueID, &CreateObject<BaseClassType, ClassType>);

		   return true;
	   }

	   bool unregisterObject(UniqueIdType uniqueID) {
		   return objectCreator.drop(uniqueID);
	   }

	   bool containsObject(UniqueIdType uniqueID) {
		   return objectCreator.containsKey(uniqueID);
	   }

   protected:
	   ObjectCreatorMap<UniqueIdType, CreateObjectFunc> objectCreator;
   };

   }
  }
 }
}

using namespace server::zone::managers::object;

#endif /* SCENEOBJECTFACTORY_H_ */
