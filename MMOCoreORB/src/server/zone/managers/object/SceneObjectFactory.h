/*
 * SceneObjectFactory.h
 *
 *  Created on: 28/07/2010
 *      Author: victor
 */

#ifndef SCENEOBJECTFACTORY_H_
#define SCENEOBJECTFACTORY_H_

#include "system/lang.h"

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
		   uint32 a = k;
		   a = (a+0x7ed55d16) + (a<<12);
		   a = (a^0xc761c23c) ^ (a>>19);
		   a = (a+0x165667b1) + (a<<5);
		   a = (a+0xd3a2646c) ^ (a<<9);
		   a = (a+0xfd7046c5) + (a<<3);
		   a = (a^0xb55a4f09) ^ (a>>16);

		   return a;
	   }

   public:
	   ObjectCreatorMap() {
		   HashTable<TypeId, Value>::setNullValue(nullptr);
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
			   return nullptr;

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

	   bool containsObject(UniqueIdType uniqueID) const {
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
