/*
 * ZoneComponent.h
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#ifndef ZONECOMPONENT_H_
#define ZONECOMPONENT_H_

#include "engine/engine.h"

#include "SceneObjectComponent.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace scene {
    class SceneObject;
   }

   namespace building {
    class BuildingObject;
   }
  }

  class Zone;
 }
}

using namespace server::zone::objects::scene;
using namespace server::zone::objects::building;
using namespace server::zone;

#include "engine/util/u3d/QuadTreeEntry.h"

class ZoneComponent : public SceneObjectComponent, public Logger {
	//protected Zone zone;

public:



	virtual void notifyInsert(SceneObject* sceneObject, QuadTreeEntry* entry) {

	}

	virtual void notifyDissapear(SceneObject* sceneObject, QuadTreeEntry* entry) {

	}

	/**
	 * Inserts this object into zone
	 * @pre { this object is locked }
	 * @post { this object is locked and inserted into zone }
	 * @param zone Zone object where this object will be inserted
	 */
	virtual void insertToZone(SceneObject* sceneObject, Zone* zone);

	/**
	 * Inserts this object into the building, this method is only to be called from insertToZone
	 * @pre { this object is locked, zone is locked }
	 * @post { this object is in the building, this object is locked, zone is locked }
	 * @param building BuildingObject where this object will be inserted
	 */
	virtual void insertToBuilding(SceneObject* sceneObject, BuildingObject* building);

	/**
	 * Switches zone and position of this object
	 * @pre { this object is locked }
	 * @post { this object is locked, is in the new zone and in the new position }
	 * @param newZoneID new zone id where the object will be inserted
	 * @param newPositionX new position X
	 * @param newPositionZ new position Z
	 * @param newPositionY new position Y
	 */
	virtual void switchZone(SceneObject* sceneObject, const String& newTerrainName, float newPostionX, float newPositionZ, float newPositionY, uint64 parentID = 0);

	virtual void teleport(SceneObject* sceneObject, float newPositionX, float newPositionZ, float newPositionY, uint64 parentID = 0);

	/**
	 * Removes object from zone
	 * @pre { this object is locked }
	 * @post { this object is locked and not in zone}
	 */
	virtual void removeFromZone(SceneObject* sceneObject);

	/**
	 * Removes this object from the building, this method is only to be called from removeFromZone
	 * @pre { this object is locked, zone is locked }
	 * @post { this object is not in the building, this object is locked, zone is locked }
	 * @param building BuildingObject from where this object will be removed
	 */
	virtual void removeFromBuilding(SceneObject* sceneObject, BuildingObject* building);

	/**
	 * Updates position of this object to the rest of in range objects
	 * @pre { this object is locked}
	 * @post { this object is locked, in range objects are updated with the new position }
	 * @param lightUpdate if true a standalone message is sent to the in range objects
	 */
	virtual void updateZone(SceneObject* sceneObject, bool lightUpdate, bool sendPackets = true);

	/**
	 * Updates position and/or parent of this object and to the rest of in range objects
	 * @pre { this object is locked, newParent is a CellObject }
	 * @post {this object is locked, in range objects are updated of the new position and parent }
	 * @param newParent cellObject where this object is
	 * @param lightUpdate if true a standalone message is sent to the in range objects
	 */
	virtual void updateZoneWithParent(SceneObject* sceneObject, SceneObject* newParent, bool lightUpdate, bool sendPackets = true);


};


#endif /* ZONECOMPONENT_H_ */
