/*
 * SaberInventoryContainerComponent.h
 *
 *  Created on: Apr 14, 2012
 *      Author: katherine
 */

#ifndef SABERINVENTORYCONTAINERCOMPONENT_H_
#define SABERINVENTORYCONTAINERCOMPONENT_H_

#include "server/zone/objects/scene/components/ContainerComponent.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace scene {
    class SceneObject;
   }

   namespace creature {
    class CreatureObject;
   }
  }

  class Zone;
 }
}

using namespace server::zone::objects::scene;
using namespace server::zone::objects::creature;


class SaberInventoryContainerComponent : public ContainerComponent {
public:

	/**
	 * Evaluates if this object has the necessary free slots to be able to add the specified SceneObject
	 * @pre { this object is locked, object is locked }
	 * @post {this object is locked, object is locked }
	 * @param object SceneObject that will be checked
	 * @param error error string that the player will receive on error
	 * @return returns 0 on success, or error code
	 */
	virtual int canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription);

	/**
	 * Is called when this object has been inserted with an object
	 * @param object object that has been inserted
	 */
	virtual int notifyObjectInserted(SceneObject* sceneObject, SceneObject* object);

	/**
	 * Is called when an object was removed
	 * @param object object that has been inserted
	 */
	virtual int notifyObjectRemoved(SceneObject* sceneObject, SceneObject* object, SceneObject* destination);

};



#endif /* SABERINVENTORYCONTAINERCOMPONENT_H_ */
