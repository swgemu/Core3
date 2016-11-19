/*
 * PlayerZoneComponent.h
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#ifndef PLAYERZONECOMPONENT_H_
#define PLAYERZONECOMPONENT_H_

#include "server/zone/objects/scene/components/ZoneComponent.h"

class PlayerZoneComponent : public ZoneComponent {
public:
	void notifyInsert(SceneObject* sceneObject, QuadTreeEntry* entry) const;

	void notifyDissapear(SceneObject* sceneObject, QuadTreeEntry* entry) const;

	void switchZone(SceneObject* sceneObject, const String& newTerrainName, float newPostionX, float newPositionZ, float newPositionY, uint64 parentID = 0, bool toggleInvisibility = false) const;

	void notifyInsertToZone(SceneObject* sceneObject, Zone* newZone) const;

	void teleport(SceneObject* sceneObject, float newPositionX, float newPositionZ, float newPositionY, uint64 parentID = 0) const;

	/**
	 * Updates position of this object to the rest of in range objects
	 * @pre { this object is locked}
	 * @post { this object is locked, in range objects are updated with the new position }
	 * @param lightUpdate if true a standalone message is sent to the in range objects
	 */
	void updateZone(SceneObject* sceneObject, bool lightUpdate, bool sendPackets = true) const;

	/**
	 * Updates position and/or parent of this object and to the rest of in range objects
	 * @pre { this object is locked, newParent is a CellObject }
	 * @post {this object is locked, in range objects are updated of the new position and parent }
	 * @param newParent cellObject where this object is
	 * @param lightUpdate if true a standalone message is sent to the in range objects
	 */
	void updateZoneWithParent(SceneObject* sceneObject, SceneObject* newParent, bool lightUpdate, bool sendPackets = true) const;

};


#endif /* PLAYERZONECOMPONENT_H_ */
