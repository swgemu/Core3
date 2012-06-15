/*
 * FleeStateComponent.h
 *
 *  Created on: May 17, 2012
 *      Author: da
 */

#ifndef FLEESTATECOMPONENT_H_
#define FLEESTATECOMPONENT_H_

#include "AiStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/templates/appearance/PortalLayout.h"
#include "server/zone/templates/appearance/FloorMesh.h"
#include "server/zone/templates/appearance/PathGraph.h"
#include "server/zone/templates/appearance/PathNode.h"

class FleeStateComponent : public AiStateComponent {
public:

	uint16 onEnter(AiActor* actor);

	uint16 doRecovery(AiActor* actor);

	uint16 doMovement(AiActor* actor);

	float getSpeed(CreatureObject* host);

	PatrolPoint getFleeLocation(CreatureObject* host, SceneObject* followObject);
};


#endif /* FLEESTATECOMPONENT_H_ */
