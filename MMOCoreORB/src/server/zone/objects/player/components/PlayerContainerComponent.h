/*
 * PlayerContainerComponent.h
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#include "server/zone/objects/scene/components/ContainerComponent.h"
#include "server/zone/objects/player/PlayerCreature.h"

class PlayerContainerComponent : public ContainerComponent {
public:
	/**
	 * Evaluates if this object has the necessary free slots to be able to add the specified SceneObject
	 * @pre { this object is locked, object is locked }
	 * @post {this object is locked, object is locked }
	 * @param object SceneObject that will be checked
	 * @param error error string that the player will receive on error
	 * @return returns 0 on success, or error code
	 */
	int canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription);


};
