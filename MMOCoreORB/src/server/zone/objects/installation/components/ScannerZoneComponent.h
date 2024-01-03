/*
 * ScannerZoneComponent.h
 *
 *  Created on: Dec 17, 2012
 *      Author: root
 */

#ifndef SCANNERZONECOMPONENT_H_
#define SCANNERZONECOMPONENT_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/TreeEntry.h"


class ScannerZoneComponent : public GroundZoneComponent {

public:
	void notifyInsertToZone(SceneObject* sceneObject, Zone* zone) const;
	void notifyPositionUpdate(SceneObject* sceneObject, TreeEntry* entry) const;

};

#endif /* SCANNERZONECOMPONENT_H_ */
