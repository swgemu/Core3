/*
 * DeadEyePrototypeImplementation.h
 *
 * Created on: 6/24/2022
 * Author: H
 */

#include "server/zone/objects/tangible/misc/DeadEyePrototype.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

void DeadEyePrototypeImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (player == nullptr)
		return;
}

int DeadEyePrototypeImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (player == nullptr)
		return 0;

	if (!isASubChildOf(player))
		return 0;

	if (selectedID != 20) {
		return 0;
	}

	if (player->isDead() || player->isIncapacitated())
		return 0;

	uint32 buffCRC = STRING_HASHCODE("dead_eye");

	if (player->hasBuff(buffCRC)) {
		player->sendSystemMessage("@combat_effects:dead_eye_already"); //You are already under the effects of Dead Eye.
		return 0;
	}

	if (!player->checkCooldownRecovery("dead_eye")) {
		player->sendSystemMessage("@combat_effects:dead_eye_wait"); // You took Dead Eye too recently. An overdose could cause neurological damage.
		return 0;
	}

	Reference<Buff*> buff = new Buff(player, buffCRC, duration, BuffType::SKILL);

	Locker locker(buff);

	buff->setSkillModifier("dead_eye", effectiveness);

	player->addBuff(buff);

	// 2 hour cooldown
	player->addCooldown("dead_eye", 7200 * 1000);

	// Send message to player
	player->sendSystemMessage("@combat_effects:dead_eye_active"); // The chemical infusion immediately begins to heighten your awareness, agility, and visual acuity.

	//Consume a charge from the item
	decreaseUseCount();

	return 1;
}

void DeadEyePrototypeImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player) {
		if (player == nullptr)
			return;

		int volume = getContainerVolumeLimit();
		alm->insertAttribute("volume", volume);

		String crafter = getCraftersName();
		alm->insertAttribute("crafter", crafter);

		String serial = getSerialNumber();
		alm->insertAttribute("serial_number", serial);

		// Effectiveness
		StringBuffer effectivenessBuffer;

		effectivenessBuffer << effectiveness << "%";
		alm->insertAttribute("effectiveness", effectivenessBuffer.toString());

		// Duration
		StringBuffer durationstring;

		int minutes = (int) floor(duration / 60.0f);
		int seconds = Math::getPrecision(duration % 60, 2);

		durationstring << minutes << ":" << seconds;

		alm->insertAttribute("duration", durationstring.toString());
}
