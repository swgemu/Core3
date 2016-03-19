/*
 * LuaContainerComponent.h
 *
 *  Created on: 05/02/2012
 *      Author: Elvaron
 */

#ifndef LUACONTAINERCOMPONENT_H_
#define LUACONTAINERCOMPONENT_H_

#include "ContainerComponent.h"

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


class LuaContainerComponent : public ContainerComponent {
	String luaClassName;

public:
	LuaContainerComponent(const String& className);
	~LuaContainerComponent();

	/**
	 * Tries to add/link object
	 * @pre { this object is locked, object is locked }
	 * @post {this object is locked, object is locked }
	 * @param object SceneObject that will be added to the current object
	 * @param containmentType arrangement type that will be used to add the object
	 * @param notifyClient if true in range objects will be updated with the change
	 * @return returns true if the object has been successfully added
	 */
	virtual bool transferObject(SceneObject* sceneObject, SceneObject* object, int containmentType, bool notifyClient = false, bool allowOverflow = false, bool notifyRoot = true) const;

	/**
	 * Tries to remove/unlink object
	 * @pre { this object is locked, object is locked }
	 * @post {this object is locked, object is locked }
	 * @param object SceneObject that will be removed from the current object
	 * @param notifyClient not used currently
	 * @return returns true if the object has been successfully removed
	 */
	virtual bool removeObject(SceneObject* sceneObject, SceneObject* object, SceneObject* destination, bool notifyClient) const;

	/**
	 * Evaluates if this object has the necessary free slots to be able to add the specified SceneObject
	 * @pre { this object is locked, object is locked }
	 * @post {this object is locked, object is locked }
	 * @param object SceneObject that will be checked
	 * @param error error string that the player will receive on error
	 * @return returns 0 on success, or error code
	 */
	virtual int canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) const;

	/**
	 * Is called when this object has been inserted with an object
	 * @param object object that has been inserted
	 */
	virtual int notifyObjectInserted(SceneObject* sceneObject, SceneObject* object) const;

	/**
	 * Is called when an object was removed
	 * @param object object that has been inserted
	 */
	virtual int notifyObjectRemoved(SceneObject* sceneObject, SceneObject* object, SceneObject* destination) const;

};

#endif /* LUACONTAINERCOMPONENT_H_ */
