/*
 * ContainerObjectsMap.h
 *
 *  Created on: 13/10/2012
 *      Author: victor
 */

#ifndef CONTAINEROBJECTSMAP_H_
#define CONTAINEROBJECTSMAP_H_

#include "engine/engine.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace scene {
   	   class SceneObject;

   	class ContainerObjectsMap : public Variable {
   		int operationMode;

   		VectorMap<uint64, ManagedReference<SceneObject*> > containerObjects;
   		VectorMap<uint64, uint64>* oids;

   		Mutex loadMutex;
   	public:
   		enum {NORMAL_LOAD = 0, DELAYED_LOAD };

   	private:
   		void copyData(const ContainerObjectsMap& c);

   	public:
   		ContainerObjectsMap();
   		~ContainerObjectsMap();
   		ContainerObjectsMap(const ContainerObjectsMap& c);

   		ContainerObjectsMap& operator=(const ContainerObjectsMap& c);

   		VectorMap<uint64, ManagedReference<SceneObject*> >* getContainerObjects();

   		bool toBinaryStream(ObjectOutputStream* stream);
   		bool parseFromBinaryStream(ObjectInputStream* stream);

   		void notifyLoadFromDatabase();

   		void loadObjects();

   		void removeAll();
   		void removeElementAt(int index);

   		bool contains(uint64 oid);
   		int size();

   		ManagedReference<SceneObject*> get(int index);
   		ManagedReference<SceneObject*> get(uint64 oid);

   		void put(uint64 oid, SceneObject* object);
   		void drop(uint64 oid);

   		void setDelayedLoadOperationMode() {
   			operationMode = DELAYED_LOAD;
   		}

   		bool hasDelayedLoadOperationMode() {
   			return operationMode == DELAYED_LOAD;
   		}
   	};
   }
  }
 }
}

using namespace server::zone::objects::scene;

#endif /* CONTAINEROBJECTSMAP_H_ */
