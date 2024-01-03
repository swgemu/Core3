/*
 * MinefieldZoneComponent.h
 *
 *  Created on: Dec 17, 2012
 *      Author: root
 */

#ifndef MINEFIELDZONECOMPONENT_H_
#define MINEFIELDZONECOMPONENT_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/TreeEntry.h"

class MinefieldZoneComponent : public GroundZoneComponent {

public:
	void notifyPositionUpdate(SceneObject* sceneObject, TreeEntry* entry) const;
	void notifyInsertToZone(SceneObject* sceneObject, Zone* zne) const;
	void notifyDissapear(SceneObject* sceneObject, TreeEntry* entry) const;
};


#endif /* MINEFIELDZONECOMPONENT_H_ */
