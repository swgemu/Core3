/*
 * FishingPoleObjectImplementation.cpp
 *
 *  Created on: Apr 12, 2010
 *      Author: swgemu
 */

#include "FishingPoleObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/scene/variables/CustomizationVariables.h"
#include "server/zone/objects/scene/TransferErrorCode.h"

void FishingPoleObjectImplementation::fillAttributeList(AttributeListMessage* alm, PlayerCreature* object) {
	TangibleObjectImplementation::fillAttributeList(alm,object);

	alm->insertAttribute("quality", String::valueOf(quality));
}


int FishingPoleObjectImplementation::canAddObject(SceneObject* object, String& errorDescription) {
	if (object->isFishingBait()) {
		return TangibleObjectImplementation::canAddObject(object, errorDescription);
	}

	errorDescription = "@fishing:bait_only";

	return TransferErrorCode::BAITONLY;
}
