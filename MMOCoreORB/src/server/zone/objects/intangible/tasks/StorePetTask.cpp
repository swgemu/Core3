#include "StorePetTask.h"

#include "templates/params/creature/CreatureAttribute.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/group/GroupManager.h"
#include "server/zone/managers/creature/PetManager.h"

StorePetTask::StorePetTask(CreatureObject* player, AiAgent* pet) {
	this->play = player;
	this->pt = pet;
}

void StorePetTask::run() {
	ManagedReference<CreatureObject*> player = play.get();
	ManagedReference<AiAgent*> pet = pt.get();

	if (player == nullptr || pet == nullptr)
		return;

	ZoneServer* zoneServer = player->getZoneServer();

	if (zoneServer == nullptr || zoneServer->isServerLoading()) {
		schedule(10000 + System::random(5000));
		return;
	}

	Locker locker(player);
	Locker clocker(pet, player);

	if (pet->containsPendingTask("droid_power"))
		pet->removePendingTask("droid_power");

	if (pet->containsPendingTask("droid_skill_mod"))
		pet->removePendingTask("droid_skill_mod");

	if (pet->containsPendingTask("store_pet"))
		pet->removePendingTask("store_pet");

	if (pet->getHAM(CreatureAttribute::HEALTH) < 1)
		pet->setHAM(CreatureAttribute::HEALTH, 1);
	if (pet->getHAM(CreatureAttribute::ACTION) < 1)
		pet->setHAM(CreatureAttribute::ACTION, 1);
	if (pet->getHAM(CreatureAttribute::MIND) < 1)
		pet->setHAM(CreatureAttribute::MIND, 1);

	pet->setPosture(CreaturePosture::UPRIGHT, true);
	pet->clearState(CreatureState::SWIMMING);
	pet->clearCombatState(true);
	pet->setOblivious();
	pet->storeFollowObject();
	if (pet->isDroidObject()) {
		DroidObject* droid = cast<DroidObject*>(pet.get());
		if (droid != nullptr) {
			droid->onStore();
			droid->unloadSkillMods(player);
		}
	}

	pet->destroyObjectFromWorld(true);
	pet->setCreatureLink(nullptr);

	ManagedReference<PetControlDevice*> controlDevice = pet->getControlDevice().get().castTo<PetControlDevice*>();
	if (controlDevice != nullptr) {
		Locker deviceLocker(controlDevice);
		controlDevice->updateStatus(0);
		controlDevice->setLastCommandTarget(nullptr);
		controlDevice->setLastCommand(PetManager::FOLLOW);
	}


	const CreatureTemplate* creoTemp = pet->getCreatureTemplate();

	if (creoTemp != nullptr) {
		pet->setFaction(creoTemp->getFaction().hashCode());
		pet->setPvpStatusBitmask(creoTemp->getPvpBitmask(), false);
	}
	else {
		pet->setFaction(0);
		pet->setPvpStatusBitmask(0, false);
	}

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
	ghost->removeFromActivePets(pet);

	ManagedReference<GroupObject*> group = pet->getGroup();

	locker.release();

	if (group != nullptr)
		GroupManager::instance()->leaveGroup(group, pet);

}