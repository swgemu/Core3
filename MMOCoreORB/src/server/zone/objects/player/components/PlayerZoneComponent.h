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
	void notifyInsert(SceneObject* sceneObject, QuadTreeEntry* entry);

	void notifyDissapear(SceneObject* sceneObject, QuadTreeEntry* entry);

	void switchZone(SceneObject* sceneObject, const String& newTerrainName, float newPostionX, float newPositionZ, float newPositionY, uint64 parentID = 0);

	void notifyInsertToZone(SceneObject* sceneObject, Zone* newZone);

	void teleport(SceneObject* sceneObject, float newPositionX, float newPositionZ, float newPositionY, uint64 parentID = 0);

	/**
	 * Updates position of this object to the rest of in range objects
	 * @pre { this object is locked}
	 * @post { this object is locked, in range objects are updated with the new position }
	 * @param lightUpdate if true a standalone message is sent to the in range objects
	 */
	void updateZone(SceneObject* sceneObject, bool lightUpdate, bool sendPackets = true);

	/**
	 * Updates position and/or parent of this object and to the rest of in range objects
	 * @pre { this object is locked, newParent is a CellObject }
	 * @post {this object is locked, in range objects are updated of the new position and parent }
	 * @param newParent cellObject where this object is
	 * @param lightUpdate if true a standalone message is sent to the in range objects
	 */
	void updateZoneWithParent(SceneObject* sceneObject, SceneObject* newParent, bool lightUpdate, bool sendPackets = true);

	/**
	 * Inserts this object into the building, this method is only to be called from insertToZone
	 * Includes a trigger to BuildingObject::onEnter
	 * @pre { this object is locked, zone is locked }
	 * @post { this object is in the building, building->onEnter has been triggered,
	 * 		   this object is locked, zone is locked }
	 * @param building BuildingObject where this object will be inserted
	 */
	void insertToBuilding(SceneObject* sceneObject, BuildingObject* building);

	/**
	 * Removes this object from the building, this method is only to be called from removeFromZone
	 * Includes a trigger to BuildingObject::onExit
	 * @pre { this object is locked, zone is locked }
	 * @post { this object is not in the building, building->onExit has been triggered,
	 * 		   this object is locked, zone is locked }
	 * @param building BuildingObject from where this object will be removed
	 */
	void removeFromBuilding(SceneObject* sceneObject, BuildingObject* building);

	void notifySelfPositionUpdate(SceneObject* sceneObject);

};


#endif /* PLAYERZONECOMPONENT_H_ */
