/*
 * FishingPoleObjectImplementation.cpp
 *
 *  Created on: Apr 12, 2010
 *      Author: swgemu
 */

#include "FishingPoleObject.h"
#include "../TangibleObject.h"
#include "../../scene/SceneObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "../../scene/variables/CustomizationVariables.h"

void FishingPoleObjectImplementation::fillAttributeList(AttributeListMessage* alm, PlayerCreature* object) {
	TangibleObjectImplementation::fillAttributeList(alm,object);

	StringBuffer qual;
	qual << quality;
	alm->insertAttribute("quality", qual);
}
