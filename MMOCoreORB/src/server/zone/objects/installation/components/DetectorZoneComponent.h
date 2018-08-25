/*
 * DetectorZoneComponent.h
 *
 *  Created on: Dec 17, 2012
 *      Author: root
 */

#ifndef DETECTORZONECOMPONENT_H_
#define DETECTORZONECOMPONENT_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/QuadTreeEntry.h"


class DetectorZoneComponent : public ZoneComponent {

public:
	void notifyPositionUpdate(SceneObject* sceneObject, QuadTreeEntry* entry) const;

};

#endif /* DETECTORZONECOMPONENT_H_ */
