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
#include "server/zone/objects/scene/components/SceneObjectComponent.h"
#include "engine/util/u3d/QuadTreeEntry.h"


class DetectorZoneComponent : public ZoneComponent {

public:
	void notifyPositionUpdate(SceneObject* sceneObject, QuadTreeEntry* entry);

};





#endif /* DETECTORZONECOMPONENT_H_ */
