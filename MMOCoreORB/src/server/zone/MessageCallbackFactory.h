/*
 * MessageCallbackFactory.h
 *
 *  Created on: 28/07/2010
 *      Author: victor
 */

#ifndef MESSAGECALLBACKFACTORY_H_
#define MESSAGECALLBACKFACTORY_H_


#include "engine/engine.h"

namespace server {
 namespace zone {

 template <typename TypeId, typename Value>
 class ObjectCreatorMap : public HashTable<TypeId, Value> {
	 int hash(const TypeId& k) {
		 return (int)k;
	 }

 public:
	 ObjectCreatorMap() {
		 HashTable<TypeId, Value>::setNullValue(NULL);
	 }
 };

 template <typename CtorSignature, typename UniqueIdType> class MessageCallbackFactory;

 template<typename BaseClassType, typename Param1Type, typename ClassType> BaseClassType CreateObject(Param1Type param1) {
	 return new ClassType(param1);
 }

 template<typename BaseClassType, typename Param1Type, typename UniqueIdType>
 class MessageCallbackFactory<BaseClassType (Param1Type), UniqueIdType>
 {
 protected:
	 typedef BaseClassType (*CreateObjectFunc)(Param1Type);

 public:
	 BaseClassType createObject(UniqueIdType uniqueID, Param1Type param1) {
		 if (!objectCreator.containsKey(uniqueID))
			 return NULL;

		 return objectCreator.get(uniqueID)(param1);
	 }

	 template<typename ClassType> bool registerObject(UniqueIdType uniqueID) {
		 if (objectCreator.containsKey(uniqueID))
			 return false;

		 objectCreator.put(uniqueID, &CreateObject<BaseClassType, Param1Type, ClassType>);

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

 template<typename BaseClassType, typename Param1Type, typename Param2Type, typename ClassType> BaseClassType CreateObject(Param1Type param1, Param2Type param2) {
	 return new ClassType(param1, param2);
 }

 template<typename BaseClassType, typename Param1Type, typename Param2Type, typename UniqueIdType>
 class MessageCallbackFactory<BaseClassType (Param1Type, Param2Type), UniqueIdType>
 {
 protected:
	 typedef BaseClassType (*CreateObjectFunc)(Param1Type, Param2Type);

 public:
	 BaseClassType createObject(UniqueIdType uniqueID, Param1Type param1, Param2Type param2) {
		 CreateObjectFunc func = objectCreator.get(uniqueID);

		 if (func != NULL)
			 return func(param1, param2);
		 else
			 return NULL;
	 }

	 template<typename ClassType> bool registerObject(UniqueIdType uniqueID) {
		 objectCreator.put(uniqueID, &CreateObject<BaseClassType, Param1Type, Param2Type, ClassType>);

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

using namespace server::zone;


#endif /* MESSAGECALLBACKFACTORY_H_ */
