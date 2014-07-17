
#ifndef TAMECREATURETASK_H_
#define TAMECREATURETASK_H_

#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/chat/ChatManager.h"
#include "engine/engine.h"

class TameCreatureTask : public Task {

private:
	enum Phase { INITIAL, SECOND, THIRD, FOURTH, FINAL} currentPhase;
	int originalMask;
	ManagedReference<Creature*> creature;
	ManagedReference<CreatureObject*> player;
	bool force;

public:
	TameCreatureTask(Creature* cre, CreatureObject* playo, int pvpMask, bool forced) : Task() {
		currentPhase = INITIAL;
		creature = cre;
		player = playo;
		originalMask = pvpMask;
		force = forced;
	}

	void run() {
		Locker locker(creature);

		Locker _clocker(player, creature);

		player->removePendingTask("tame_pet");

		if (force) {
			success();
			return;
		}

		if (!creature->isInRange(player, 8.0f)) {
			player->sendSystemMessage("@hireling/hireling:taming_toofar"); // You are too far away to continue taming.
			creature->showFlyText("npc_reaction/flytext","toofar", 204, 0, 0);  // You are too far away to tame the creature.
			resetStatus();
			return;
		}

		if (!creature->canTameMe(player)) {
			player->sendSystemMessage("@pet/pet_menu:sys_cant_tame"); // You can't tame that
			resetStatus();
			return;
		}

		ChatManager* chatManager = player->getZoneServer()->getChatManager();

		switch (currentPhase) {
		case INITIAL:
			chatManager->broadcastMessage(player, "@hireling/hireling:taming_2"); // Steady.
			player->doAnimation("");
			currentPhase = SECOND;
			player->addPendingTask("tame_pet", this, 8000);
			break;
		case SECOND:
			chatManager->broadcastMessage(player, "@hireling/hireling:taming_3"); // Don't be scared.
			currentPhase = THIRD;
			player->addPendingTask("tame_pet", this, 8000);
			break;
		case THIRD:
			chatManager->broadcastMessage(player, "@hireling/hireling:taming_4"); // Don't bite me.
			currentPhase = FOURTH;
			player->addPendingTask("tame_pet", this, 8000);
			break;
		case FOURTH:
			chatManager->broadcastMessage(player, "@hireling/hireling:taming_5"); // Good... er... boy?
			currentPhase = FINAL;
			player->addPendingTask("tame_pet", this, 8000);
			break;
		case FINAL:
			float tamingChance = creature->getChanceToTame(player);

			if (tamingChance > System::random(100))
				success();
			else {
				player->sendSystemMessage("@hireling/hireling:taming_fail"); // You fail to tame the creature.
				creature->showFlyText("npc_reaction/flytext","fail", 204, 0, 0);  // You fail to tame the creature.
				resetStatus();

				int ferocity = creature->getFerocity();
				if (System::random(20 - ferocity) == 0)
					_clocker.release();
					CombatManager::instance()->startCombat(creature,player,true);
			}

			break;
		}

		return;
	}

	void success() {
		ZoneServer* zoneServer = player->getZoneServer();

		String objectString = creature->getControlDeviceTemplate();
		if (objectString == "")
			objectString = "object/intangible/pet/pet_control.iff";

		ManagedReference<PetControlDevice*> controlDevice = zoneServer->createObject(objectString.hashCode(), 1).castTo<PetControlDevice*>();

		if (controlDevice == NULL) {
			resetStatus();
			return;
		}

		SceneObject* datapad = player->getSlottedObject("datapad");
		PlayerManager* playerManager = zoneServer->getPlayerManager();
		ObjectManager* objectManager = zoneServer->getObjectManager();

		if (datapad == NULL || playerManager == NULL || objectManager == NULL) {
			resetStatus();
			return;
		}

		controlDevice->setControlledObject(creature);

		StringId s;
		s.setStringId(creature->getObjectName()->getFullPath());

		controlDevice->setObjectName(s);
		controlDevice->setPetType(PetManager::CREATUREPET);
		controlDevice->setMaxVitality(100);
		controlDevice->setVitality(100);
		controlDevice->setGrowthStage(1);
		controlDevice->updateStatus(1);
		controlDevice->setCustomObjectName(creature->getCustomObjectName(), true);

		datapad->transferObject(controlDevice, -1);
		objectManager->persistSceneObjectsRecursively(creature, 1);

		creature->setControlDevice(controlDevice);
		creature->setObjectMenuComponent("PetMenuComponent");
		creature->setCreatureLink(player);
		creature->setFaction(player->getFaction());

		if (player->getPvpStatusBitmask() & CreatureFlag::PLAYER)
			creature->setPvpStatusBitmask(player->getPvpStatusBitmask() - CreatureFlag::PLAYER, false);
		else
			creature->setPvpStatusBitmask(player->getPvpStatusBitmask(), false);

		creature->setBaby(false);
		creature->setFollowObject(player);

		if (creature->isAiAgent()) {
			AiAgent* agent = cast<AiAgent*>(creature.get());
			agent->setCreatureBitmask(CreatureFlag::PET);
			agent->activateLoad("");
		}

		creature->getZone()->broadcastObject(creature, true);
		datapad->broadcastObject(controlDevice, true);

		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
		ghost->addToActivePets(creature);

		CreatureTemplate* creatureTemplate = creature->getCreatureTemplate();

		if (creatureTemplate != NULL)
			playerManager->awardExperience(player, "creaturehandler", 20 * creatureTemplate->getLevel());
		else
			playerManager->awardExperience(player, "creaturehandler", 20 * creature->getLevel());

		player->sendSystemMessage("@hireling/hireling:taming_success"); // You successfully tame the creature.
		creature->showFlyText("npc_reaction/flytext","success", 0, 204, 0);  // You tame the creature.
	}

	void resetStatus() {
		creature->setPvpStatusBitmask(originalMask, true);
		if (creature->isAiAgent()) {
			AiAgent* agent = cast<AiAgent*>(creature.get());
			agent->activateLoad("");
		}
	}
};

#endif /* TAMECREATURETASK_H_ */
