/*
 * SurveyDroidMenuComponent.cpp
 *
 *  Created on: 08/11/2014
 *      Author: washu
 */

#include "SurveyDroidMenuComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sessions/InterplanetarySurveyDroidSession.h"

void SurveyDroidMenuComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	if (droidObject == NULL || !droidObject->isTangibleObject() || player == NULL) {
		return;
	}

	TangibleObjectMenuComponent::fillObjectMenuResponse(droidObject, menuResponse, player);
}

int SurveyDroidMenuComponent::handleObjectMenuSelect(SceneObject* droidObject, CreatureObject* player, byte selectedID) const {
	if (!droidObject->isTangibleObject()) {
		return 0;
	}

	if (!player->isPlayerCreature()) {
		return 0;
	}
	TangibleObject* tano = cast<TangibleObject*>( droidObject);

	if (selectedID == 20) { // Use radial menu
		// check for inventory
		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
		if (inventory == NULL)
			return 0;
		PlayerObject* playerObject = player->getPlayerObject();
		// Check for appropiate skill (survey)
		if (!playerObject->hasAbility("survey")) {
			player->sendSystemMessage("@pet/droid_modules:survey_no_survey_skill");
			return 0;
		}
		if (player->containsActiveSession(SessionFacadeType::INTERPLANETARYSURVEYDROID)) {
			return 0;
		}
		ManagedReference<InterplanetarySurveyDroidSession*> session = new InterplanetarySurveyDroidSession(player);
		player->addActiveSession(SessionFacadeType::INTERPLANETARYSURVEYDROID,session);
		session->initalizeDroid(tano);
		return 0;
	} else {
		return TangibleObjectMenuComponent::handleObjectMenuSelect(droidObject, player, selectedID);
	}
}
