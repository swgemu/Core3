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
#include "server/zone/objects/scene/components/SceneObjectComponent.h"
#include "engine/util/u3d/QuadTreeEntry.h"


class MinefieldZoneComponent : public ZoneComponent {

public:
	void notifyPositionUpdate(SceneObject* sceneObject, QuadTreeEntry* entry);

};


#endif /* MINEFIELDZONECOMPONENT_H_ */
