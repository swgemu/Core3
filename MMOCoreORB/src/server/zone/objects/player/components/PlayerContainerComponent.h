/*
 * PlayerContainerComponent.h
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#include "server/zone/objects/scene/components/ContainerComponent.h"

namespace server {
namespace zone {
namespace objects {
namespace scene {
class SceneObject;
}  // namespace scene
}  // namespace objects
}  // namespace zone
}  // namespace server
namespace sys {
namespace lang {
class String;
}  // namespace lang
}  // namespace sys

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
	int canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) const;

	/**
	 * Is called when this object has been inserted with an object
	 * @param object object that has been inserted
	 */
	int notifyObjectInserted(SceneObject* sceneObject, SceneObject* object) const;

	/**
	 * Is called when an object was removed
	 * @param object object that has been inserted
	 */
	int notifyObjectRemoved(SceneObject* sceneObject, SceneObject* object, SceneObject* destination) const;

};
