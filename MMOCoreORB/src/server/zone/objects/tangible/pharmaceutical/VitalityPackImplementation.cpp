/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/objects/tangible/pharmaceutical/VitalityPack.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/managers/creature/PetManager.h"

void VitalityPackImplementation::fillAttributeList(AttributeListMessage* msg, CreatureObject* player){
	TangibleObjectImplementation::fillAttributeList(msg, player);

	msg->insertAttribute("power", effectiveness);
}

int VitalityPackImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {

	if (player == NULL)
		return 0;

	if (!isASubChildOf(player))
		return 0;

	if (selectedID != 20)
		return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);

	uint64 targetID = player->getTargetID();
	ZoneServer* server = player->getZoneServer();
	if (server == NULL)
		return 0;

	// Target must be a pet
	ManagedReference<TangibleObject*> target = server->getObject(targetID, true).castTo<TangibleObject*>();
	if (target == NULL || !target->isPet()) {
		player->sendSystemMessage("You can only use this to restore vitality to pets");
		return 0;
	}

	ManagedReference<AiAgent*> pet = cast<AiAgent*>(target.get());
	if (pet == NULL)
		return 0;

	ManagedReference<PetControlDevice*> controlDevice = pet->getControlDevice().get().castTo<PetControlDevice*>();
	if (controlDevice == NULL)
		return 0;

	// Check pet type
	Locker crossLock(controlDevice, _this.getReferenceUnsafeStaticCast());

	if (controlDevice->getPetType() == PetManager::FACTIONPET) {
		player->sendSystemMessage("You cannot use this to restore vitality to that type of pet");
		return 0;
	}

	// Check owner
	uint64 ownerID = pet->getCreatureLinkID();
	if (ownerID != player->getObjectID()) {
		player->sendSystemMessage("You cannot revitalize another player's pet");
		return 0;
	}

	// Check pet and player states
	if (pet->isInCombat() || pet->isDead() || pet->isIncapacitated() || player->isInCombat() || player->isDead() || player->isIncapacitated()) {
		player->sendSystemMessage("You can't restore vitality to your pet right now");
		return 0;
	}

	// Check that some vitality has been lost
	if (controlDevice->getVitality() >= controlDevice->getMaxVitality()) {
		player->sendSystemMessage("Pet is already at maximum vitality");
		return 0;
	}

	// Calculate vitality loss
	int vitalityLost = controlDevice->getMaxVitality() - controlDevice->getVitality();
	int vitalityLoss = 1;

	if (effectiveness < 45) {
		vitalityLoss += (vitalityLost / 9) + (vitalityLost / 13);
	} else if (effectiveness < 75) {
		vitalityLoss += (vitalityLost / 19) + (vitalityLost / 28);
	} else {
		vitalityLoss += (vitalityLost / 29) + (vitalityLost / 43);
	}

	vitalityLoss *= ((vitalityLost - 1) / (effectiveness > 0 ? effectiveness : 1)) + 1;

	if (vitalityLoss >= controlDevice->getMaxVitality()) {
		vitalityLoss = controlDevice->getMaxVitality() - 1;
	}

	// Reduce max vitality
	controlDevice->setMaxVitality(controlDevice->getMaxVitality() - vitalityLoss);

	// Restore vitality to new max
	controlDevice->setVitality(controlDevice->getMaxVitality());

	// Use a charge
	decreaseUseCount();

	player->sendSystemMessage("You restore your pet to " + String::valueOf(controlDevice->getMaxVitality()) +
							  " vitality but it permanently lost " + String::valueOf(vitalityLoss) + " vitality.");

	return 0;

}
