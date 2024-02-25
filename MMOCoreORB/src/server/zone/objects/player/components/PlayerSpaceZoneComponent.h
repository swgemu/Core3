/*
 * PlayerZoneComponent.h
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#ifndef PLAYERSPACEZONECOMPONENT_H_
#define PLAYERSPACEZONECOMPONENT_H_

#include "server/zone/objects/scene/components/SpaceZoneComponent.h"
#include "server/zone/TreeEntry.h"

class PlayerSpaceZoneComponent : public SpaceZoneComponent{
public:
	PlayerSpaceZoneComponent() {
		setLoggingName("PlayerSpaceZoneComponent");
	}

	void notifyInsert(SceneObject* sceneObject, TreeEntry* entry) const;

	void notifyDissapear(SceneObject* sceneObject, TreeEntry* entry) const;

	void switchZone(SceneObject* sceneObject, const String& newTerrainName, float newPostionX, float newPositionZ, float newPositionY, uint64 parentID = 0, bool toggleInvisibility = false, int playerArrangement = -1) const;

	void notifyInsertToZone(SceneObject* sceneObject, SpaceZone* newZone) const;

	void teleport(SceneObject* sceneObject, float newPositionX, float newPositionZ, float newPositionY, uint64 parentID = 0) const;

	void updateZone(SceneObject* sceneObject, bool lightUpdate, bool sendPackets = true) const;

	void updateZoneWithParent(SceneObject* sceneObject, SceneObject* newParent, bool lightUpdate, bool sendPackets = true) const;

};


#endif /* PLAYERSPACEZONECOMPONENT_H_ */
