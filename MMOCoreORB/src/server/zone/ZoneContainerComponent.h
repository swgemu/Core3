/*
 * ZoneContainerComponent.h
 *
 *  Created on: 03/09/2011
 *      Author: TheAnswer
 */

#ifndef ZONECONTAINERCOMPONENT_H_
#define ZONECONTAINERCOMPONENT_H_

#include "server/zone/objects/scene/components/ContainerComponent.h"

namespace server {
	namespace zone {
		class Zone;

		namespace objects {
			namespace area {
				class ActiveArea;
			}
		}
	}
}

using namespace server::zone;
using namespace server::zone::objects::area;

class ZoneContainerComponent : public ContainerComponent {
protected:
	bool insertActiveArea(Zone* zone, ActiveArea* activeArea) const;
	bool removeActiveArea(Zone* zone, ActiveArea* activeArea) const;
public:
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
	//virtual int canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription);

	/**
	 * Is called when this object has been inserted with an object
	 * @param object object that has been inserted
	 */
	//virtual int notifyObjectInserted(SceneObject* sceneObject, SceneObject* object);

	/**
	 * Is called when an object was removed
	 * @param object object that has been inserted
	 */
	//virtual int notifyObjectRemoved(SceneObject* sceneObject, SceneObject* object);

};

#endif /* ZONECONTAINERCOMPONENT_H_ */
