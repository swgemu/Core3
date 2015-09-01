
#ifndef TAMECREATURETASK_H_
#define TAMECREATURETASK_H_

#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/creature/events/SpawnCreatureTask.h"
#include "engine/engine.h"

class TameCreatureTask : public Task {

private:
	enum Phase { INITIAL, SECOND, FINAL} currentPhase;
	int originalMask;
	ManagedReference<Creature*> creature;
	ManagedReference<CreatureObject*> player;
	bool force;
	bool adult;

public:
	TameCreatureTask(Creature* cre, CreatureObject* playo, int pvpMask, bool forced, bool adults) : Task() {
		currentPhase = INITIAL;
		creature = cre;
		player = playo;
		originalMask = pvpMask;
		force = forced;
		adult = adults;
	}

	void run() {
		Locker locker(creature);

		Locker _clocker(player, creature);

		player->removePendingTask("tame_pet");

		if (force) {
			success(adult);
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
			chatManager->broadcastMessage(player, "@hireling/hireling:taming_" + String::valueOf(System::random(4) + 1));
			player->doAnimation("");
			currentPhase = SECOND;
			player->addPendingTask("tame_pet", this, 10000);
			break;
		case SECOND:
			chatManager->broadcastMessage(player, "@hireling/hireling:taming_" + String::valueOf(System::random(4) + 1));
			currentPhase = FINAL;
			player->addPendingTask("tame_pet", this, 10000);
			break;
		case FINAL:
			float tamingChance = creature->getChanceToTame(player);

			if (tamingChance > System::random(100))
				success(false);
			else {
				player->sendSystemMessage("@hireling/hireling:taming_fail"); // You fail to tame the creature.
				creature->showFlyText("npc_reaction/flytext","fail", 204, 0, 0);  // You fail to tame the creature.
				resetStatus();

				int ferocity = creature->getFerocity();

				if (System::random(20 - ferocity) == 0) {
					CombatManager::instance()->startCombat(creature,player,true);
				}
			}

			break;
		}

		return;
	}

	void success(bool adult) {
		ZoneServer* zoneServer = player->getZoneServer();

		String objectString = creature->getControlDeviceTemplate();
		if (objectString == "")
			objectString = "object/intangible/pet/pet_control.iff";

		SceneObject* datapad = player->getSlottedObject("datapad");
		PlayerManager* playerManager = zoneServer->getPlayerManager();
		ObjectManager* objectManager = zoneServer->getObjectManager();

		if (datapad == NULL || playerManager == NULL || objectManager == NULL) {
			resetStatus();
			return;
		}

		ManagedReference<PetControlDevice*> controlDevice = zoneServer->createObject(objectString.hashCode(), 1).castTo<PetControlDevice*>();

		if (controlDevice == NULL) {
			resetStatus();
			return;
		}

		Locker deviceLocker(controlDevice);

		controlDevice->setControlledObject(creature);

		StringId s;
		s.setStringId(creature->getObjectName()->getFullPath());

		controlDevice->setObjectName(s, false);
		controlDevice->setPetType(PetManager::CREATUREPET);
		controlDevice->setMaxVitality(100);
		controlDevice->setVitality(100);
		controlDevice->setGrowthStage(1);
		controlDevice->updateStatus(1);
		controlDevice->setCustomObjectName(creature->getCustomObjectName(), true);

		if (!datapad->transferObject(controlDevice, -1)) {
			resetStatus();
			controlDevice->destroyObjectFromDatabase(true);
			return;
		}

		objectManager->persistSceneObjectsRecursively(creature, 1);

		if (adult) {
			controlDevice->growPet(player, true, true);
		}

		creature->setControlDevice(controlDevice);
		creature->setObjectMenuComponent("PetMenuComponent");
		creature->setCreatureLink(player);
		creature->setFaction(player->getFaction());

		if (player->getPvpStatusBitmask() & CreatureFlag::PLAYER)
			creature->setPvpStatusBitmask(player->getPvpStatusBitmask() - CreatureFlag::PLAYER, false);
		else
			creature->setPvpStatusBitmask(player->getPvpStatusBitmask(), false);

		creature->setBaby(false);

		if (creature->isAiAgent()) {
			AiAgent* agent = cast<AiAgent*>(creature.get());
			ManagedReference<SceneObject*> parent = player->getParent().get();

			float respawn = agent->getRespawnTimer() * 1000;

			if (respawn > 0 && agent->getHomeObject().get() == NULL) {

				if (agent->getRandomRespawn()) {
					respawn = System::random(respawn) + (respawn / 2.f);
				}

				uint32 tempCRC = 0;
				CreatureTemplate* crTemplate = agent->getCreatureTemplate();

				if (crTemplate != NULL)
					tempCRC = crTemplate->getTemplateName().hashCode();

				PatrolPoint* homeLoc = agent->getHomeLocation();

				Reference<Task*> task = new SpawnCreatureTask(tempCRC, agent->getRespawnTimer(), creature->getZone()->getZoneName(), homeLoc->getPositionX(), homeLoc->getPositionZ(), homeLoc->getPositionY(), agent->getParentID(), agent->getRandomRespawn());
				task->schedule(respawn);
			}

			agent->setFollowObject(player);
			agent->storeFollowObject();

			agent->setHomeLocation(player->getPositionX(), player->getPositionZ(), player->getPositionY(), (parent != NULL && parent->isCellObject()) ? parent : NULL);
			agent->setNextStepPosition(player->getPositionX(), player->getPositionZ(), player->getPositionY(), (parent != NULL && parent->isCellObject()) ? parent : NULL);
			agent->clearPatrolPoints();

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
