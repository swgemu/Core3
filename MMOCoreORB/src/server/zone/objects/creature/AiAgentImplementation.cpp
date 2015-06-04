/*
 * AiAgentImplementation.cpp
 *
 *  Created on: 13/07/2010
 *      Author: victor
 */

#include <engine/core/ManagedReference.h>
#include <engine/core/ManagedWeakReference.h>
#include <engine/util/Singleton.h>
#include <engine/util/u3d/CloseObjectsVector.h>
#include <engine/util/u3d/Coordinate.h>
#include <engine/util/u3d/Quaternion.h>
#include <engine/util/u3d/Triangle.h>
#include <engine/util/u3d/Vector3.h>
#include <system/io/StringTokenizer.h>
#include <system/lang/IllegalArgumentException.h>
#include <system/lang/ref/Reference.h>
#include <system/lang/ref/WeakReference.h>
#include <system/lang/String.h>
#include <system/lang/StringBuffer.h>
#include <system/lang/System.h>
#include <system/lang/Time.h>
#include <system/lang/UnicodeString.h>
#include <system/platform.h>
#include <system/thread/Locker.h>
#include <system/thread/Mutex.h>
#include <system/thread/ReadLocker.h>
#include <system/util/ArrayList.h>
#include <system/util/SortedVector.h>
#include <system/util/Vector.h>
#include <system/util/VectorMap.h>
#include <cmath>
#include <cstdlib>

#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/reaction/ReactionManager.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/Creature.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/creature/conversation/ConversationObserver.h"
#include "server/zone/objects/creature/commands/CombatQueueCommand.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/collision/PathFinderManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/components/ComponentManager.h"
#include "server/zone/managers/conversation/ConversationManager.h"
#include "server/zone/managers/creature/AiMap.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/managers/faction/FactionManager.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/packets/object/StartNpcConversation.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/packets/scene/LightUpdateTransformMessage.h"
#include "server/zone/packets/scene/LightUpdateTransformWithParentMessage.h"
#include "server/zone/packets/scene/UpdateTransformMessage.h"
#include "server/zone/packets/scene/UpdateTransformWithParentMessage.h"
#include "server/zone/templates/AiTemplate.h"
#include "server/zone/templates/mobile/CreatureTemplate.h"
#include "server/zone/templates/mobile/MobileOutfit.h"
#include "server/zone/templates/mobile/MobileOutfitGroup.h"
#include "server/zone/templates/SharedObjectTemplate.h"
#include "server/zone//ZoneReference.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/objects/scene/ObserverEventType.h"
#include "server/zone/objects/scene/variables/DeltaVector.h"
#include "server/zone/objects/scene/variables/StringId.h"
#include "server/zone/objects/scene/WorldCoordinates.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"
#include "ai/bt/CompositeBehavior.h"
#include "CreatureAttribute.h"
#include "CreatureFlag.h"
#include "CreaturePosture.h"
#include "CreatureState.h"
#include "damageovertime/DamageOverTimeList.h"
#include "events/AiAwarenessEvent.h"
#include "events/AiMoveEvent.h"
#include "events/AiThinkEvent.h"
#include "events/AiWaitEvent.h"
#include "events/AiInterruptTask.h"
#include "events/AiLoadTask.h"
#include "events/CamoTask.h"
#include "events/DespawnCreatureOnPlayerDissappear.h"
#include "events/DespawnCreatureTask.h"
#include "events/RespawnCreatureTask.h"
#include "PatrolPoint.h"
#include "PatrolPointsVector.h"
#include "variables/CreatureAttackMap.h"
#include "variables/CreatureTemplateReference.h"
#include "variables/CurrentFoundPath.h"

#include "server/chat/ChatManager.h"
#include "server/zone/managers/creature/SpawnObserver.h"
#include "server/zone/managers/creature/DynamicSpawnObserver.h"


//#define SHOW_WALK_PATH
//#define DEBUG
//#define SHOW_NEXT_POSITION

void AiAgentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	CreatureObjectImplementation::loadTemplateData(templateData);
}

int AiAgentImplementation::calculateAttackMinDamage(int level) {
	int minDmg = MAX(getDamageMin(), 20 + (level * 5));
	if (petDeed != NULL) {
		minDmg = petDeed->getMinDamage();
		if (level < petDeed->getLevel()) {
			// reduce by level range
			float percent = (float)level/(float)petDeed->getLevel();
			minDmg *= percent;
		}
	}
	if (isDroidObject()) {
		minDmg = getDamageMin();
	}
	return minDmg;
}

int AiAgentImplementation::calculateAttackMaxDamage(int level) {
	int dmg = MAX(getDamageMax(), calculateAttackMinDamage(level) * 2);
	if (petDeed != NULL) {
		dmg = petDeed->getMaxDamage();
		if (level < petDeed->getLevel()) {
			float percent = (float)level/(float)petDeed->getLevel();
			dmg *= percent;
		}
	}
	if (isDroidObject()) {
		dmg = getDamageMax();
	}
	return dmg;
}
float AiAgentImplementation::calculateAttackSpeed(int level) {
	float speed = 3.5f - ((float)level / 100.f);
	return speed;
}

void AiAgentImplementation::loadTemplateData(CreatureTemplate* templateData) {
	npcTemplate = templateData;

	setPvpStatusBitmask(npcTemplate->getPvpBitmask());
	if (npcTemplate->getPvpBitmask() == 0)
		closeobjects = NULL;

	optionsBitmask = npcTemplate->getOptionsBitmask();
	creatureBitmask = npcTemplate->getCreatureBitmask();
	level = getTemplateLevel();

	float minDmg = npcTemplate->getDamageMin();
	float maxDmg = npcTemplate->getDamageMax();
	float speed = calculateAttackSpeed(level);
	bool allowedWeapon = true;
	if (petDeed != NULL) {
		allowedWeapon = petDeed->getRanged();
	}

	Vector<WeaponObject*> weapons;
	Vector<String> wepgroups = npcTemplate->getWeapons();
	if (allowedWeapon) {
		for (int i = 0; i < wepgroups.size(); ++i) {
			Vector<String> weptemps = CreatureTemplateManager::instance()->getWeapons(wepgroups.get(i));

			for (int i = 0; i < weptemps.size(); ++i) {
				uint32 crc = weptemps.get(i).hashCode();

				ManagedReference<WeaponObject*> weao = (server->getZoneServer()->createObject(crc, getPersistenceLevel())).castTo<WeaponObject*>();

				if (weao != NULL) {
					float mod = 1 - 0.1*weao->getArmorPiercing();
					weao->setMinDamage(minDmg * mod);
					weao->setMaxDamage(maxDmg * mod);

					SharedWeaponObjectTemplate* weaoTemp = cast<SharedWeaponObjectTemplate*>(weao->getObjectTemplate());
					if (weaoTemp != NULL && weaoTemp->getPlayerRaces()->size() > 0) {
						weao->setAttackSpeed(speed);
					} else if (petDeed != NULL) {
						weao->setAttackSpeed(petDeed->getAttackSpeed());
					}

					weapons.add(weao);

					if (i == 0)
						transferObject(weao, 4, false);
				} else {
					error("could not create weapon " + weptemps.get(i));
				}
			}
		}
	}

	if (weapons.size() > 0)
		readyWeapon =  weapons.get(System::random(weapons.size() - 1));
	else
		readyWeapon = NULL;

	Reference<WeaponObject*> defaultWeapon = getSlottedObject("default_weapon").castTo<WeaponObject*>();
	if (defaultWeapon != NULL) {
		// set the damage of the default weapon
		defaultWeapon->setMinDamage(minDmg);
		defaultWeapon->setMaxDamage(maxDmg);

		if (petDeed != NULL) {
			defaultWeapon->setAttackSpeed(petDeed->getAttackSpeed());
		} else if(isPet()){
			defaultWeapon->setAttackSpeed(speed);
		}
	}



	CreatureAttackMap* fullAttackMap;
	if (petDeed != NULL)
		fullAttackMap = petDeed->getAttacks();
	else
		fullAttackMap = npcTemplate->getAttacks();

	ZoneServer* zoneServer;
	ObjectController* objectController;
	if ((zoneServer = getZoneServer()) != NULL && (objectController = zoneServer->getObjectController()) != NULL) {
		attackMap = new CreatureAttackMap();
		defaultAttackMap = new CreatureAttackMap();

		for (int i = 0; i < fullAttackMap->size(); i++) {
			CombatQueueCommand* attack = cast<CombatQueueCommand*>(objectController->getQueueCommand(fullAttackMap->getCommand(i)));
			if (attack == NULL)
				continue;

			if (readyWeapon != NULL && (attack->getWeaponType() & readyWeapon->getWeaponBitmask())) {
				attackMap->add(fullAttackMap->get(i));

			}

			if (defaultWeapon != NULL && (attack->getWeaponType() & defaultWeapon->getWeaponBitmask())) {
				defaultAttackMap->add(fullAttackMap->get(i));
			}
		}

		// if we didn't get any attacks or the weapon is NULL, drop the reference to the attack maps
		if (attackMap->isEmpty())
			attackMap = NULL;

		if (defaultAttackMap->isEmpty())
			defaultAttackMap = NULL;

	} else {
		attackMap = NULL;
		defaultAttackMap = NULL;
	}

	int ham;
	baseHAM.removeAll();
	if (petDeed == NULL) {
		for (int i = 0; i < 9; ++i) {
			if (i % 3 == 0) {
				ham = System::random(getHamMaximum() - getHamBase()) + getHamBase();
				if (isDroidObject() && isPet())
					ham = getHamMaximum();
				baseHAM.add(ham);
			} else
				baseHAM.add(ham/10);
		}
	} else {
		int health = petDeed->getHealth();
		baseHAM.add(health);
		baseHAM.add(health/10);
		baseHAM.add(health/10);
		int action = petDeed->getAction();
		baseHAM.add(action);
		baseHAM.add(action/10);
		baseHAM.add(action/10);
		int mind = petDeed->getMind();
		baseHAM.add(mind);
		baseHAM.add(mind/10);
		baseHAM.add(mind/10);
	}
	hamList.removeAll();
	for (int i = 0; i < 9; ++i) {
		hamList.add(baseHAM.get(i));
	}

	maxHamList.removeAll();
	for (int i = 0; i < 9; ++i) {
		maxHamList.add(baseHAM.get(i));
	}


	objectName = npcTemplate->getObjectName();

	if(npcTemplate->getRandomNameType() != NameManagerType::TAG) {
		NameManager* nm = server->getNameManager();

		if(npcTemplate->getRandomNameType() % 2 == 1) {
			setCustomObjectName(nm->makeCreatureName(npcTemplate->getRandomNameType()), false);
		} else {
			String newName = nm->makeCreatureName(npcTemplate->getRandomNameType());
			newName += " (";

			if (objectName == "")
				newName += templateData->getCustomName();
			else
				newName += StringIdManager::instance()->getStringId(objectName.getFullPath().hashCode()).toString();

			newName += ")";
			setCustomObjectName(newName, false);
		}
	} else {
		setCustomObjectName(templateData->getCustomName(), false);
	}

	setHeight(templateData->getScale(), false);

	String currentLogName = getLoggingName();

	if (!currentLogName.contains(npcTemplate->getTemplateName())) {
		StringBuffer logName;
		logName << getLoggingName() << "[" << npcTemplate->getTemplateName() << "]";

		setLoggingName(logName.toString());
	}

	String factionString = npcTemplate->getFaction();

	if (!factionString.isEmpty() && (factionString == "imperial" || factionString == "rebel")) {
		setFaction(factionString.hashCode());
	}

	if (!loadedOutfit) {
		loadedOutfit = true;
		String outfit = npcTemplate->getOutfit();

		if (!outfit.isEmpty()) {
			MobileOutfitGroup* group = CreatureTemplateManager::instance()->getMobileOutfitGroup(outfit);

			if (group != NULL) {
				Vector<MobileOutfit>* outfits = group->getOutfits();

				int num = System::random(outfits->size() - 1);

				if (num > -1) {
					MobileOutfit* clothes = &outfits->get(num);

					Vector<OutfitTangibleObject>* objects = clothes->getObjects();

					for (int i = 0; i < objects->size(); ++i) {
						OutfitTangibleObject* obj = &objects->get(i);

						String templ = obj->getObjectTemplate();

						ManagedReference<TangibleObject*> tano = (server->getZoneServer()->createObject(templ.hashCode(), getPersistenceLevel())).castTo<TangibleObject*>();

						if (tano != NULL) {
							Locker objLocker(tano);

							VectorMap<String, uint8>* cust = obj->getCustomizationVariables();

							for (int j = 0; j < cust->size(); ++j) {
								tano->setCustomizationVariable(cust->elementAt(j).getKey(), cust->elementAt(j).getValue());
							}

							if (!transferObject(tano, 4, false) && tano->isPersistent()) {
								tano->destroyObjectFromDatabase(true);
							}
						}

					}
				}
			} else {
				error("null outfit group " + outfit);
			}
		}
	}

	String conTemp = npcTemplate->getContainerComponentTemplate();
	if (!conTemp.isEmpty()) {
		containerComponent = cast<ContainerComponent*>(ComponentManager::instance()->getComponent<SceneObjectComponent*>(conTemp));
	}
}

void AiAgentImplementation::setLevel(int lvl, bool randomHam) {
	if (lvl <= 0)
		return;

	CreatureObjectImplementation::setLevel(lvl);

	level = lvl;

	if (npcTemplate == NULL) {
		return;
	}

	int baseLevel = getTemplateLevel();

	if (baseLevel == lvl)
		return;

	float minDmg = calculateAttackMinDamage(baseLevel);
	float maxDmg = calculateAttackMaxDamage(baseLevel);
	float speed = calculateAttackSpeed(lvl);

	float ratio = ((float)lvl) / (float)baseLevel;

	minDmg *= ratio;
	maxDmg *= ratio;

	if (readyWeapon != NULL) {
		float mod = 1 - 0.1*readyWeapon->getArmorPiercing();
		readyWeapon->setMinDamage(minDmg * mod);
		readyWeapon->setMaxDamage(maxDmg * mod);

		SharedWeaponObjectTemplate* weaoTemp = cast<SharedWeaponObjectTemplate*>(readyWeapon->getObjectTemplate());
		if (weaoTemp != NULL && weaoTemp->getPlayerRaces()->size() > 0) {
			readyWeapon->setAttackSpeed(speed);
		} else if (petDeed != NULL) {
			readyWeapon->setAttackSpeed(petDeed->getAttackSpeed());
		}
	}

	Reference<WeaponObject*> defaultWeapon = getSlottedObject("default_weapon").castTo<WeaponObject*>();
	if (defaultWeapon != NULL) {
		defaultWeapon->setMinDamage(minDmg);
		defaultWeapon->setMaxDamage(maxDmg);
		if(petDeed != NULL)
			defaultWeapon->setAttackSpeed(petDeed->getAttackSpeed());
		else if(isPet())
			defaultWeapon->setAttackSpeed(speed);
	}

	int baseHamMax = ((float)getHamMaximum()) * ratio;
	int baseHam = ((float)getHamBase()) * ratio;

	int ham = 0;

	for (int i = 0; i < 9; ++i) {
		if (i % 3 == 0) {
			if (randomHam)
				ham = System::random(baseHamMax - baseHam) + baseHam;
			else
				ham = ((baseHamMax - baseHam) / 2) + baseHam;

			setBaseHAM(i, ham);
		} else
			setBaseHAM(i, ham / 100);
	}

	for (int i = 0; i < 9; ++i) {
		setHAM(i, baseHAM.get(i));
	}

	for (int i = 0; i < 9; ++i) {
		setMaxHAM(i, baseHAM.get(i));
	}
}

void AiAgentImplementation::initializeTransientMembers() {
	CreatureObjectImplementation::initializeTransientMembers();

	rescheduleTrackingTask();
}

void AiAgentImplementation::notifyPositionUpdate(QuadTreeEntry* entry) {
	CreatureObjectImplementation::notifyPositionUpdate(entry);
}

void AiAgentImplementation::doAwarenessCheck() {
	if (numberOfPlayersInRange.get() <= 0)
		return;

	CloseObjectsVector* vec = (CloseObjectsVector*) getCloseObjects();
	if (vec == NULL)
		return;

	SortedVector<ManagedReference<QuadTreeEntry* > > closeObjects;
	vec->safeCopyTo(closeObjects);

	Behavior* current = behaviors.get(currentBehaviorID);

	if (current != NULL) {
		AiAgent* thisObject = asAiAgent();

		for (int i = 0; i < closeObjects.size(); ++i) {
			CreatureObject* target = cast<CreatureObject*>(closeObjects.get(i).get());

			if (thisObject == target || target == NULL)
				continue;

			if (target->isVehicleObject() || target->hasRidingCreature())
				continue;

			//Locker crossLocker(target, thisObject); lets do dirty reads

			if (current->doAwarenessCheck(target)) {
				interrupt(target, ObserverEventType::OBJECTINRANGEMOVED);
			}
		}
	}

	if (numberOfPlayersInRange.get() > 0) {
		activateAwarenessEvent();
	}
}

void AiAgentImplementation::doRecovery() {
	if (isDead() || getZone() == NULL)
		return;

	activateHAMRegeneration();
	activateStateRecovery();
	activatePostureRecovery();

	// we only want to activate recovery if we need to -- it will restart when we need it
	if (defenderList.size() > 0 || damageOverTimeList.hasDot()
			|| getHAM(CreatureAttribute::HEALTH) < getMaxHAM(CreatureAttribute::HEALTH)
			|| getHAM(CreatureAttribute::ACTION) < getMaxHAM(CreatureAttribute::ACTION)
			|| getHAM(CreatureAttribute::MIND) < getMaxHAM(CreatureAttribute::MIND)
			|| getWounds(CreatureAttribute::CONSTITUTION) > 0 || getWounds(CreatureAttribute::STRENGTH) > 0
			|| getWounds(CreatureAttribute::QUICKNESS) > 0 || getWounds(CreatureAttribute::STAMINA) > 0
			|| getWounds(CreatureAttribute::FOCUS) > 0 || getWounds(CreatureAttribute::WILLPOWER) > 0)
		activateRecovery();
}

void AiAgentImplementation::selectSpecialAttack() {
	CreatureAttackMap* attackMap = getAttackMap();

	if (attackMap == NULL) {
		selectDefaultAttack();
		return;
	}

	selectSpecialAttack(attackMap->getRandomAttackNumber());
}

void AiAgentImplementation::selectSpecialAttack(int attackNum) {
	CreatureAttackMap* attackMap = getAttackMap();
	if (attackMap == NULL) {
		selectDefaultAttack();
		return;
	}

	if (attackNum >= 0 && attackNum < attackMap->size()) {
		String cmd = attackMap->getCommand(attackNum);

		if (cmd.isEmpty()) {
			selectDefaultAttack();
		} else {
			nextActionCRC = cmd.hashCode();
			nextActionArgs = attackMap->getArguments(attackNum);

			ZoneServer* zoneServer = getZoneServer();
			if (zoneServer == NULL) {
				selectDefaultAttack();
				return;
			}

			ObjectController* objectController = zoneServer->getObjectController();
			if (objectController == NULL) {
				selectDefaultAttack();
				return;
			}

			QueueCommand* queueCommand = getZoneServer()->getObjectController()->getQueueCommand(nextActionCRC);
			ManagedReference<SceneObject*> followCopy = getFollowObject();
			if (queueCommand == NULL || followCopy == NULL
					|| (queueCommand->getMaxRange() > 0 && !followCopy->isInRange(asAiAgent(), queueCommand->getMaxRange() + getTemplateRadius() + followCopy->getTemplateRadius()))
					|| (queueCommand->getMaxRange() <= 0 && !followCopy->isInRange(asAiAgent(), getWeapon()->getMaxRange() + getTemplateRadius() + followCopy->getTemplateRadius()))) {
				selectDefaultAttack();
			}
		}
	} else {
		selectDefaultAttack();
	}
}

void AiAgentImplementation::selectDefaultAttack() {
	if (npcTemplate == NULL)
		nextActionCRC = STRING_HASHCODE("defaultattack");
	else
		nextActionCRC = npcTemplate->getDefaultAttack().hashCode();

	nextActionArgs = "";
}

void AiAgentImplementation::enqueueAttack(int priority) {
	ManagedReference<SceneObject*> followCopy = getFollowObject();

	if (followCopy != NULL) {
		enqueueCommand(nextActionCRC, 0, followCopy->getObjectID(), nextActionArgs, priority);
		nextActionCRC = 0;
		nextActionArgs = "";
	}
}

bool AiAgentImplementation::validateStateAttack() {
	ManagedReference<SceneObject*> followCopy = getFollowObject();

	if (followCopy == NULL || !followCopy->isCreatureObject())
		return false;

	return validateStateAttack(followCopy->asCreatureObject(), nextActionCRC);
}

SceneObject* AiAgentImplementation::getTargetFromMap() {
	CreatureObject* target = getThreatMap()->getHighestThreatCreature();

	if (target != NULL && !defenderList.contains(target) && (!target->isDead() && !target->isIncapacitated()) && target->getDistanceTo(asAiAgent()) < 128.f && target->isAttackableBy(asAiAgent()) && lastDamageReceived.miliDifference() < 20000)
		addDefender(target);
	else if (target != NULL && defenderList.contains(target) && (target->isDead() || target->isIncapacitated() || !target->isInRange(asAiAgent(), 128) || !target->isAttackableBy(asAiAgent()))) {
		removeDefender(target);
		target = NULL;
	}

	return target;
}

SceneObject* AiAgentImplementation::getTargetFromDefenders() {
	SceneObject* target = NULL;

	if (defenderList.size() > 0) {
		for (int i = 0; i < defenderList.size(); ++i) {
			SceneObject* tarObj = defenderList.get(i);

			if (tarObj != NULL && tarObj->isCreatureObject()) {
				CreatureObject* targetCreature = tarObj->asCreatureObject();

				if (!targetCreature->isDead() && !targetCreature->isIncapacitated() && targetCreature->getDistanceTo(asAiAgent()) < 128.f && targetCreature->isAttackableBy(asAiAgent())) {
					target = targetCreature;

					break;
				} else {
					// if the object on the defender list is no longer attackable, remove it
					removeDefender(targetCreature);
				}
			} else if (tarObj != NULL && tarObj->isTangibleObject()) {
				TangibleObject* targetTano = cast<TangibleObject*>(tarObj);

				if (!targetTano->isDestroyed() && targetTano->getDistanceTo(asAiAgent()) < 128.f && targetTano->isAttackableBy(asAiAgent())) {
					target = targetTano;
					break;
				} else {
					removeDefender(targetTano);
				}
			}
		}
	}

	return target;
}

bool AiAgentImplementation::validateTarget() {
	ManagedReference<SceneObject*> followCopy = getFollowObject();

	return validateTarget(followCopy);
}

bool AiAgentImplementation::validateTarget(SceneObject* target) {
	if (target == NULL)
		return false;

	if (!target->isInRange(asAiAgent(), 128))
		return false;

	CreatureObject* targetCreatureObject = target->asCreatureObject();

	if (targetCreatureObject != NULL && (!targetCreatureObject->isAttackableBy(asAiAgent()) || targetCreatureObject->isDead() || targetCreatureObject->isIncapacitated()))
		return false;

	TangibleObject* targetTangibleObject = target->asTangibleObject();

	if (targetTangibleObject != NULL && (!targetTangibleObject->isAttackableBy(asAiAgent()) || targetTangibleObject->isDestroyed()))
		return false;

	return true;
}

int AiAgentImplementation::notifyAttack(Observable* observable) {
	// TODO: add reaction attacks
	return 0;
}

int AiAgentImplementation::notifyCallForHelp(Observable* observable, ManagedObject* arg1) {
	// TODO: add aggroing
	return 0;
}

int AiAgentImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (isDead() && !isPet()) {
		switch (selectedID) {
		case 35:
			player->executeObjectControllerAction(STRING_HASHCODE("loot"), getObjectID(), "");

			return 0;
		case 36:
			player->executeObjectControllerAction(STRING_HASHCODE("loot"), getObjectID(), "all");

			return 0;
		}
	}

	return CreatureObjectImplementation::handleObjectMenuSelect(player, selectedID);
}

void AiAgentImplementation::selectWeapon() {
	ManagedReference<SceneObject*> followCopy = getFollowObject();
	float dist = 5.f;

	if (followCopy != NULL)
		dist = getDistanceTo(followCopy) - followCopy->getTemplateRadius() - getTemplateRadius();

	WeaponObject* finalWeap = NULL;
	ManagedReference<WeaponObject*> defaultWeapon = getSlottedObject("default_weapon").castTo<WeaponObject*>();

	float readyWeaponRangeDiff = -1.f;
	float defaultWeaponRangeDiff = 100.f;

	if (readyWeapon != NULL) {
		finalWeap = readyWeapon;
		readyWeaponRangeDiff = fabs(readyWeapon->getIdealRange() - dist);
	}

	if (defaultWeapon != NULL && defaultWeapon->getMaxRange() >= dist) {
		defaultWeaponRangeDiff = fabs(defaultWeapon->getIdealRange() - dist);
	}

	if (finalWeap == NULL || readyWeaponRangeDiff > defaultWeaponRangeDiff)
		finalWeap = defaultWeapon;

	ManagedReference<WeaponObject*> currentWeapon = getWeapon();

	if (currentWeapon != finalWeap) {
		if (currentWeapon != NULL && currentWeapon != defaultWeapon) {
			Locker locker(currentWeapon);

			currentWeapon->destroyObjectFromWorld(false);

			//info("removed weapon " + currentWeapon->getDisplayedName(), true);
		}

		if (finalWeap != NULL && finalWeap != defaultWeapon) {

			//info("selected weapon " + finalWeap->getDisplayedName(), true);
			Locker locker(finalWeap);

			transferObject(finalWeap, 4, false);
			broadcastObject(finalWeap, false);
		}
	}

	//setWeapon(finalWeap, true);
}

void AiAgentImplementation::selectDefaultWeapon() {
	ManagedReference<WeaponObject*> currentWeapon = getWeapon();
	ManagedReference<WeaponObject*> defaultWeapon = getSlottedObject("default_weapon").castTo<WeaponObject*>();

	if (currentWeapon != NULL && currentWeapon != defaultWeapon)
		currentWeapon->destroyObjectFromWorld(false);
}

bool AiAgentImplementation::validateStateAttack(CreatureObject* target, unsigned int actionCRC) {
	ManagedReference<ObjectController*> objectController = getZoneServer()->getObjectController();
	CombatQueueCommand* queueCommand = cast<CombatQueueCommand*>(objectController->getQueueCommand(actionCRC));

	VectorMap<uint8, StateEffect>* effects = queueCommand->getStateEffects();

	if (effects->size() == 0) {
		return true;
	}

	for (int i = 0; i < effects->size(); i++) {
		uint8 effectType = effects->elementAt(i).getKey();

		switch (effectType) {
		case CommandEffect::BLIND:
			if (!target->hasState(CreatureState::BLINDED)) {
				return true;
			}
			break;
		case CommandEffect::DIZZY:
			if (!target->hasState(CreatureState::DIZZY)) {
				return true;
			}
			break;
		case CommandEffect::INTIMIDATE:
			if (!target->hasState(CreatureState::INTIMIDATED)) {
				return true;
			}
			break;
		case CommandEffect::STUN:
			if (!target->hasState(CreatureState::STUNNED)) {
				return true;
			}
			break;
		case CommandEffect::KNOCKDOWN:
			if (!target->isKnockedDown() && target->checkKnockdownRecovery()) {
				return true;
			}
			break;
		case CommandEffect::POSTUREUP:
			if (!target->isStanding() && target->checkPostureUpRecovery()) {
				return true;
			}
			break;
		case CommandEffect::POSTUREDOWN:
			if (!target->isProne() && target->checkPostureDownRecovery()) {
				return true;
			}
			break;
		case CommandEffect::NEXTATTACKDELAY:
			if (!target->hasAttackDelay()) {
				return true;
			}
			break;
		default:
			break;
		}
	}

	return false;
}

void AiAgentImplementation::setDespawnOnNoPlayerInRange(bool val) {
	if (despawnOnNoPlayerInRange == val)
		return;

	despawnOnNoPlayerInRange = val;

	if (val && numberOfPlayersInRange <= 0) {
		if (despawnEvent == NULL) {
			despawnEvent = new DespawnCreatureOnPlayerDissappear(asAiAgent());
		}

		if (!despawnEvent->isScheduled())
			despawnEvent->schedule(30000);
	}
}

void AiAgentImplementation::runAway(CreatureObject* target, float range) {
	ManagedReference<SceneObject*> followCopy = getFollowObject();
	if (target == NULL || getZone() == NULL || followCopy == NULL) {
		setOblivious();
		return;
	}

	setTargetObject(target);

	// TODO (dannuic): do we need to check threatmap for other players in range at this point, or just have the mob completely drop aggro?
	if (threatMap != NULL)
		threatMap->removeAll();
	// try to peace out while running away since we removed all threat targets see above note
	CombatManager::instance()->attemptPeace(asAiAgent());
	clearPatrolPoints();

	showFlyText("npc_reaction/flytext", "afraid", 0xFF, 0, 0);
	notifyObservers(ObserverEventType::FLEEING, target);
	sendReactionChat(ReactionManager::FLEE);

	setFollowState(AiAgent::FLEEING);
	fleeRange = range;

	if (!homeLocation.isInRange(asAiAgent(), 128)) {
		homeLocation.setReached(false);
		setNextPosition(homeLocation.getPositionX(), homeLocation.getPositionZ(), homeLocation.getPositionY(), homeLocation.getCell());
	} else {
		Vector3 runTrajectory(getPositionX() - followCopy->getPositionX(), getPositionY() - followCopy->getPositionY(), 0);
		runTrajectory = runTrajectory * (fleeRange / runTrajectory.length());
		runTrajectory += getPosition();

		setNextPosition(runTrajectory.getX(), getZone()->getHeight(runTrajectory.getX(), runTrajectory.getY()), runTrajectory.getY(), getParent().get());
	}
}

void AiAgentImplementation::leash() {
	setFollowState(AiAgent::LEASHING);
	setTargetObject(NULL);
	storeFollowObject();

	clearPatrolPoints();

	CombatManager::instance()->forcePeace(asAiAgent());

	if (!homeLocation.isInRange(asAiAgent(), 1.5)) {
		homeLocation.setReached(false);
		addPatrolPoint(homeLocation);
	} else {
		homeLocation.setReached(true);
	}
}

void AiAgentImplementation::setDefender(SceneObject* defender) {
	setFollowObject(defender);

	CreatureObjectImplementation::setDefender(defender);

	if (isRetreating())
		homeLocation.setReached(true);

	activateRecovery();
}

void AiAgentImplementation::queueDizzyFallEvent() {
	if (isNonPlayerCreatureObject())
		CreatureObjectImplementation::queueDizzyFallEvent();
}

void AiAgentImplementation::addDefender(SceneObject* defender) {
	unsigned int stateCopy = getFollowState();

	if ((defenderList.size() == 0 || getFollowObject() == NULL) && defender != NULL) {
		showFlyText("npc_reaction/flytext", "threaten", 0xFF, 0, 0);
		setFollowObject(defender);
		if (defender->isCreatureObject() && threatMap != NULL)
			threatMap->addAggro(defender->asCreatureObject(), 1);
	} else if (stateCopy <= STALKING) {
		setFollowState(AiAgent::FOLLOWING);
	}

	CreatureObjectImplementation::addDefender(defender);

	activateRecovery();
}

void AiAgentImplementation::removeDefender(SceneObject* defender) {
	CreatureObjectImplementation::removeDefender(defender);

	if (defender == NULL)
		return;

	if (defender->isCreatureObject())
		getThreatMap()->dropDamage(defender->asCreatureObject());

	if (getFollowObject() == defender) {
		CreatureObject* target = getThreatMap()->getHighestThreatCreature();

		if (target == NULL && defenderList.size() > 0) {
			SceneObject* tarObj = defenderList.get(0);
			if (tarObj != NULL && tarObj->isCreatureObject())
				target = tarObj->asCreatureObject();
		}

		if (target != NULL)
			setDefender(target);
		else
			restoreFollowObject();
	}

	activateRecovery();
}

/**
 * Clears the combat state
 * @pre { this object is locked }
 * @post { this object is locked, this object is not in a combat state }
 * @param clearDefenders if true the defender vector will be emptied
 */
void AiAgentImplementation::clearCombatState(bool clearDefenders) {
	CreatureObjectImplementation::clearCombatState(clearDefenders);

	if (threatMap != NULL)
		threatMap->removeAll();

	notifyObservers(ObserverEventType::PEACE);
	sendReactionChat(ReactionManager::CALM);
}

void AiAgentImplementation::notifyInsert(QuadTreeEntry* entry) {
	SceneObject* scno = static_cast<SceneObject*>( entry);

	if (scno == asAiAgent())
		return;

	if (scno == NULL)
		return;

	CreatureObject* creo = scno->asCreatureObject();
	if (creo != NULL && !creo->isInvisible() && creo->isPlayerCreature()) {
		int newValue = (int) numberOfPlayersInRange.increment();
		activateMovementEvent();

		if (newValue == 1) {
			uint64 delay = 500 + System::random(1000);
			activateAwarenessEvent(delay);
		}
	}
}

void AiAgentImplementation::clearDespawnEvent() {
	despawnEvent = NULL;
}

void AiAgentImplementation::respawn(Zone* zone, int level) {
	if (getZone() != NULL)
		return;

	CreatureManager* creatureManager = zone->getCreatureManager();

	if (npcTemplate != NULL && creatureManager != NULL && isCreature()) {
		int chance = 2000;
		int babiesSpawned = 0;

		if (homeObject != NULL) {
			SortedVector<ManagedReference<Observer*> > observers = homeObject->getObservers(ObserverEventType::CREATUREDESPAWNED);
			DynamicSpawnObserver* observer = NULL;

			for (int i = 0; i < observers.size(); i++) {
				observer = observers.get(i).castTo<DynamicSpawnObserver*>();

				if (observer != NULL) {
					break;
				}
			}

			if (observer != NULL) {
				chance = 500;
				babiesSpawned = observer->getBabiesSpawned();
			}
		}

		if (creatureManager->checkSpawnAsBaby(npcTemplate->getTame(), babiesSpawned, chance)) {
			Creature* creature = cast<Creature*>(asAiAgent());

			if (creature) {
				creature->loadTemplateDataForBaby(npcTemplate);
			} else {
				error("object is not a Creature but returned true to spawn as a baby");
			}
		}
	} else {
		setLevel(level);
	}

	resetBehaviorList();
	clearCombatState(true);

	initializePosition(homeLocation.getPositionX(), homeLocation.getPositionZ(), homeLocation.getPositionY());

	SceneObject* cell = homeLocation.getCell();

	setNextPosition(homeLocation.getPositionX(), homeLocation.getPositionZ(), homeLocation.getPositionY());
	nextStepPosition.setPosition(homeLocation.getPositionX(), homeLocation.getPositionZ(), homeLocation.getPositionY());
	nextStepPosition.setCell(cell);

	Locker zoneLocker(zone);

	if (cell != NULL)
		cell->transferObject(asAiAgent(), -1);
	else
		zone->transferObject(asAiAgent(), -1, true);

	respawnCounter++;

	activateMovementEvent();
}

void AiAgentImplementation::sendBaselinesTo(SceneObject* player) {
	ReadLocker locker(&despawnMutex);

	CreatureObjectImplementation::sendBaselinesTo(player);
}

void AiAgentImplementation::notifyDespawn(Zone* zone) {
	Locker mLocker(&movementEventMutex);
	if (moveEvent != NULL) {
		moveEvent->cancel();
		moveEvent->clearCreatureObject();
		moveEvent = NULL;
	}

	mLocker.release();

	for (int i = 0; i < movementMarkers.size(); ++i) {
		ManagedReference<SceneObject*> marker = movementMarkers.get(i);
		Locker clocker(marker, asAiAgent());
		marker->destroyObjectFromWorld(false);
	}

	SceneObject* creatureInventory = getSlottedObject("inventory");

	if (creatureInventory != NULL) {
		Locker clocker(creatureInventory, asAiAgent());
		creatureInventory->setContainerOwnerID(0);
	}

	if (npcTemplate == NULL)
		return;

	int oldLevel = level;

	Locker locker(&despawnMutex);

	loadTemplateData(templateObject);
	loadTemplateData(npcTemplate);

	if (oldLevel != level)
		setLevel(level);

	stateBitmask = 0;

	setPosture(CreaturePosture::UPRIGHT, false);

	shockWounds = 0;

	if (threatMap != NULL)
		threatMap->removeAll();

	locker.release();

	//Delete all loot out of inventory
	ManagedReference<SceneObject*> inventory = getSlottedObject("inventory");

	if (inventory != NULL) {
		while (inventory->getContainerObjectsSize() > 0) {
			ManagedReference<SceneObject*> obj = inventory->getContainerObject(0);
			inventory->removeFromContainerObjects(0);
			obj->destroyObjectFromWorld(false);
			obj->destroyObjectFromDatabase(true);
		}
	}

	setTargetObject(NULL);
	setFollowObject(NULL);

	//asAiAgent()->printReferenceHolders();

	//printf("%d ref count\n", asAiAgent()->getReferenceCount());

	if (homeObject != NULL) {
		homeObject->notifyObservers(ObserverEventType::CREATUREDESPAWNED, asAiAgent());
		return;
	}

	if (respawnTimer == 0) {
		//zone->getCreatureManager()->addToReservePool(asAiAgent());
		return;
	}

	float respawn = respawnTimer * 1000;

	if (randomRespawn) {
		respawn = System::random(respawn) + (respawn / 2.f);
	}

	Reference<Task*> task = new RespawnCreatureTask(asAiAgent(), zone, level);
	task->schedule(respawn);
}

void AiAgentImplementation::scheduleDespawn(int timeToDespawn) {
	if (getPendingTask("despawn") != NULL)
		return;

	Reference<DespawnCreatureTask*> despawn = new DespawnCreatureTask(asAiAgent());
	addPendingTask("despawn", despawn, timeToDespawn * 1000);
}

void AiAgentImplementation::notifyDissapear(QuadTreeEntry* entry) {
	SceneObject* scno = static_cast<SceneObject*>( entry);

	if (scno == asAiAgent())
		return;

	if (scno == getFollowObject()) {
			ManagedReference<AiAgent*> ai = asAiAgent();
			ManagedReference<SceneObject*> sceno = scno;

			EXECUTE_TASK_2(ai, sceno, {
				Locker locker(ai_p);
				Locker clocker(sceno_p, ai_p);

				if (sceno_p == ai_p->getFollowObject()) {
					ai_p->restoreFollowObject();
				}
			});
	}

	if (scno->isPlayerCreature()) {
		CreatureObject* creo = scno->asCreatureObject();
		if (!creo->isInvisible()) {
			int32 newValue = (int32) numberOfPlayersInRange.decrement();

			if (newValue == 0) {
				if (despawnOnNoPlayerInRange && (despawnEvent == NULL) && !isPet()) {
					despawnEvent = new DespawnCreatureOnPlayerDissappear(asAiAgent());
					despawnEvent->schedule(30000);
				}

				if (awarenessEvent != NULL) {
					awarenessEvent->cancel();
					awarenessEvent = NULL;
				}
			} else if (newValue < 0) {
				error("numberOfPlayersInRange below 0");
			}

			activateMovementEvent();
		}
	}
}

void AiAgentImplementation::activateAwarenessEvent(uint64 delay) {

#ifdef DEBUG
	info("Starting activateAwarenessEvent check", true);
#endif
	Locker locker(&awarenessEventMutex);

	if (awarenessEvent == NULL) {
		awarenessEvent = new AiAwarenessEvent(asAiAgent());

#ifdef DEBUG
		info("Creating new Awareness Event", true);
#endif
	}

	if (!awarenessEvent->isScheduled()) {
		awarenessEvent->schedule(delay);

#ifdef DEBUG
		info("Scheduling awareness event", true);
#endif
	}
}

void AiAgentImplementation::activateRecovery() {
	if (thinkEvent == NULL) {
		thinkEvent = new AiThinkEvent(asAiAgent());

		thinkEvent->schedule(2000);
	}

	if (!thinkEvent->isScheduled())
		thinkEvent->schedule(2000);
}

void AiAgentImplementation::activatePostureRecovery() {
	if (isProne() || isKnockedDown() || isKneeling())
		executeObjectControllerAction(0xA8A25C79); // stand
}

void AiAgentImplementation::updateCurrentPosition(PatrolPoint* pos) {
	PatrolPoint* nextPosition = pos;

	setPosition(nextPosition->getPositionX(), nextPosition->getPositionZ(),
			nextPosition->getPositionY());

	SceneObject* cell = nextPosition->getCell();

	/*StringBuffer reachedPosition;
	reachedPosition << "(" << positionX << ", " << positionY << ")";
	info("reached " + reachedPosition.toString(), true);*/

	if (getZone() == NULL)
		return;

	if (cell != NULL && cell->getParent() != NULL)
		updateZoneWithParent(cell, false, false);
	else
		updateZone(false, false);
}


void AiAgentImplementation::checkNewAngle() {
	ManagedReference<SceneObject*> followCopy = getFollowObject();
	if (followCopy == NULL)
		return;

	faceObject(followCopy);

	if (!nextStepPosition.isReached()) {
		broadcastNextPositionUpdate(&nextStepPosition);
	} else {
		if (getZone() == NULL)
			return;

		broadcastNextPositionUpdate(NULL);
		/*
		Locker clocker(getZone(), asAiAgent());

		++movementCounter;

		ManagedReference<SceneObject*> strongParent = getParent().get();
		if (strongParent != NULL && strongParent->isCellObject())
			updateZoneWithParent(getParent().get(), true, true);
		else
			updateZone(true, true);

			*/
	}
}

// It is important to know that the return of this function determines whether
// or not an AI should try to continue finding positions next tick. If true,
// the AI has not reached the first patrolPoint in their queue and if false,
// they have and that patrolPoint has been popped (and saved if necessary).
bool AiAgentImplementation::findNextPosition(float maxDistance, bool walk) {
	/*
	 * SETUP: Calculate and initialize situational variables
	 */

	Locker locker(&targetMutex);

	WorldCoordinates nextPosition;

	float newSpeed = runSpeed; // Is this *1.5? Is that some magic number?
	if (walk && !(isRetreating() || isFleeing()))
		newSpeed = walkSpeed;

	if(hasState(CreatureState::IMMOBILIZED))
		newSpeed = newSpeed / 2.f;

	if(hasState(CreatureState::FROZEN))
		newSpeed = 0.01f;

	float updateTicks = float(UPDATEMOVEMENTINTERVAL) / 1000.f;

	float maxSpeed = newSpeed*updateTicks; // now maxSpeed is the distance able to travel in time updateTicks

	PathFinderManager* pathFinder = PathFinderManager::instance();
	float maxDist = maxSpeed;

	bool found = false;

#ifdef SHOW_WALK_PATH
	CreateClientPathMessage* pathMessage = new CreateClientPathMessage();
	if (getParent() == NULL) {
		pathMessage->addCoordinate(getPositionX(), getZone()->getHeight(getPositionX(), getPositionY()), getPositionY());
	} else {
		pathMessage->addCoordinate(getPositionX(), getPositionZ(), getPositionY());
	}
#endif

	// setNextPosition will add a point to patrolPoints (at the beginning)
	while (!found && getPatrolPointSize() != 0) {
		// the first position in patrolPoints is where we want to move to
		PatrolPoint targetPosition = getNextPosition();
		ManagedReference<SceneObject*> targetCoordinateCell = targetPosition.getCell();

		/*
		 * PRE-STEP: calculate z if we need to for our target location
		 */

		if (targetCoordinateCell == NULL && targetPosition.getPositionZ() == 0) {
			// We are not in a cell, so we need to calculate which Z we want to move to
			targetMutex.unlock();
			targetPosition.setPositionZ(getWorldZ(targetPosition.getWorldPosition()));
			targetMutex.lock();
		}

		/*
		 *  STEP 1: Find a path (or reuse our previous path)
		 */

		Reference<Vector<WorldCoordinates>* > path;

		if (targetCellObject == targetCoordinateCell && currentFoundPath != NULL) {
			// We have previously found a path into the same target cell that we want to move into
			SceneObject* currentCell = getParent().get();
			if (currentCell != NULL && !currentCell->isCellObject())
				currentCell = NULL;
				
			// Don't recalculate path if mob hasn't entered the target cell yet (we already checked to make sure the target is still in the same cell)
			if (currentCell == targetCoordinateCell && currentFoundPath->get(currentFoundPath->size() - 1).getWorldPosition().distanceTo(targetPosition.getCoordinates().getWorldPosition()) > 3) {
				// Our target has moved, so we will need a new path with a new position.
				path = currentFoundPath = static_cast<CurrentFoundPath*>(pathFinder->findPath(asAiAgent(), targetPosition.getCoordinates()));
			} else {
				// Our target is close to where it was before, so our path begins where we are standing
				WorldCoordinates curr(asAiAgent());
				path = currentFoundPath;

				path->set(0, curr);
			}
		} else {
			// either our target cell is different than the current path cell or we don't have a current path,
			// so we need to automatically re-calculate the path (and we don't need to include our current location)
			path = currentFoundPath = static_cast<CurrentFoundPath*>(pathFinder->findPath(asAiAgent(), targetPosition.getCoordinates()));
			targetCellObject = targetCoordinateCell;
		}

		if (path == NULL || path->size() == 0) {
			// we weren't able to find a path, so remove this location from patrolPoints and try again with the next one
			PatrolPoint oldPoint = patrolPoints.remove(0);

			if (getFollowState() == AiAgent::PATROLLING)
				savedPatrolPoints.add(oldPoint);

			if (isRetreating())
				homeLocation.setReached(true);

			if (getPatrolPointSize() == 0) {
				CellObject* sourceCell = getParent().get().castTo<CellObject*>();
				error("NULL or empty path in AiAgent::findNextPosition. Source was " + getPosition().toString() + " in " + String::valueOf(sourceCell != NULL ? sourceCell->getCellNumber() : 0) + ". Destination was " + oldPoint.toString());
				nextPosition = oldPoint.getCoordinates();
				found = true;
			}

			continue;
		}

		// Get rid of duplicate/invalid points in path
		pathFinder->filterPastPoints(path, asAiAgent());

		/*
		 * STEP 2: Calculate distance to travel
		 */

		float targetDistance = targetPosition.getWorldPosition().distanceTo(getWorldPosition());

		if (targetDistance > maxDistance)
			// this is the actual "distance we can travel" calculation. We only want to
			// go to the edge of the maxDistance radius and stop, so select the minimum
			// of either our max travel distance (maxSpeed) or the distance from the
			// maxDistance radius
			maxDist = MIN(maxSpeed, targetDistance - maxDistance + 0.1);
		else
			// We are already at or inside the maxDistance radius, so we have reached this
			// patrolPoint. We want to stop at every patrolPoint exactly once, so we will
			// return from this function here because we are done.
			break;

		/*
		 * STEP 3: Calculate the next position along the path
		 */

		if (path->size() < 2) {
			// we know path size is at least one, so somehow we got a one-position path (this shouldn't happen)
			// just use the one position as our next point don't set found because this is our current position
			nextPosition = path->get(0);
		} else {
			// the farthest we will move is one point in the path, and the movement update time will change to reflect that
			nextPosition = path->get(1);
			found = true;

			float dist = fabs(nextPosition.getWorldPosition().distanceTo(getWorldPosition()));
			if (dist > maxDist && dist > 0) {
				// okay, we can't go that far in one update (since we've capped update times)
				// calculate the distance we can go and set nextPosition
				Vector3 thisPos = getWorldPosition();
				if (nextPosition.getCell() != NULL)
					thisPos = PathFinderManager::transformToModelSpace(thisPos, nextPosition.getCell()->getParent().get());

				float dx = nextPosition.getX() - thisPos.getX();
				float dy = nextPosition.getY() - thisPos.getY();
				float dz = nextPosition.getZ() - thisPos.getZ();

				nextPosition.setX(thisPos.getX() + (maxDist * (dx / dist)));
				nextPosition.setZ(thisPos.getZ() + (maxDist * (dz / dist)));
				nextPosition.setY(thisPos.getY() + (maxDist * (dy / dist)));

				// Now do cell checks to get the Z coordinate outside
				if (nextPosition.getCell() == NULL) {
					targetMutex.unlock();
					nextPosition.setZ(getWorldZ(nextPosition.getWorldPosition()));
					targetMutex.lock();
				}
			}
		}

#ifdef SHOW_WALK_PATH
		for (int i = 1; i < path->size(); ++i) { // i = 0 is our position
			WorldCoordinates nextPositionDebug = path->get(i);

			Vector3 nextWorldPos = nextPositionDebug.getWorldPosition();

			if (nextPositionDebug.getCell() == NULL)
				pathMessage->addCoordinate(nextWorldPos.getX(), getZone()->getHeight(nextWorldPos.getX(), nextWorldPos.getY()), nextWorldPos.getY());
			else
				pathMessage->addCoordinate(nextWorldPos.getX(), nextWorldPos.getZ(), nextWorldPos.getY());

#ifdef SHOW_NEXT_POSITION
			if (showNextMovementPosition) {
				for (int i = 0; i < movementMarkers.size(); ++i) {
					ManagedReference<SceneObject*> marker = movementMarkers.get(i);
					Locker clocker(marker, asAiAgent());
					marker->destroyObjectFromWorld(false);
				}

				movementMarkers.removeAll();

				Reference<SceneObject*> movementMarker = getZoneServer()->createObject(STRING_HASHCODE("object/path_waypoint/path_waypoint.iff"), 0);

				Locker clocker(movementMarker, asAiAgent());

				movementMarker->initializePosition(nextPositionDebug.getX(), nextPositionDebug.getZ(), nextPositionDebug.getY());
				StringBuffer msg;
				msg << "Next Position: path distance: " << nextPositionDebug.getWorldPosition().distanceTo(getWorldPosition()) << " maxDist:" << maxDist;
				movementMarker->setCustomObjectName(msg.toString(), false);

				CellObject* cellObject = dynamic_cast<CellObject*>(nextPositionDebug.getCell());

				if (cellObject != NULL) {
					cellObject->transferObject(movementMarker, -1, true);
				} else {
					getZone()->transferObject(movementMarker, -1, false);
				}

				movementMarkers.add(movementMarker);

				clocker.release();

				for (int i = 0; i < path->size(); ++i) {
					WorldCoordinates* coord = &path->get(i);
					SceneObject* coordCell = coord->getCell();

					movementMarker = getZoneServer()->createObject(STRING_HASHCODE("object/path_waypoint/path_waypoint.iff"), 0);

					Locker clocker(movementMarker, asAiAgent());

					movementMarker->initializePosition(coord->getPoint().getX(), coord->getPoint().getZ(), coord->getPoint().getY());

					if (coordCell != NULL) {
						coordCell->transferObject(movementMarker, -1, true);
					} else {
						getZone()->transferObject(movementMarker, -1, false);
					}

					movementMarkers.add(movementMarker);
				}
			}
#endif
		}
#endif
	}

#ifdef SHOW_WALK_PATH
	broadcastMessage(pathMessage, false);
#endif

	/*
	 * STEP 4: Finish the update tick
	 */

	if (found) {
		// Set the next place we will be if we are to move
		nextStepPosition.setPosition(nextPosition.getX(), nextPosition.getZ(), nextPosition.getY());
		nextStepPosition.setCell(nextPosition.getCell());

		nextStepPosition.setReached(false);

		Vector3 thisWorldPos = getWorldPosition();
		Vector3 nextWorldPos = nextStepPosition.getWorldPosition();

		float directionangle = atan2(nextWorldPos.getX() - thisWorldPos.getX(), nextWorldPos.getY() - thisWorldPos.getY());

		if (directionangle < 0) {
			float a = M_PI + directionangle;
			directionangle = M_PI + a;
		}

		float err = fabs(directionangle - direction.getRadians());

		if (err >= 0.05)
			direction.setHeadingDirection(directionangle);

		// Tell the clients where to expect us next tick -- requires that we have found a destination
		broadcastNextPositionUpdate(&nextStepPosition);

		float dist = fabs(thisWorldPos.distanceTo(nextWorldPos));
		if (dist > 0 && newSpeed > 0.1) {
			nextMovementInterval = MIN((int)((MIN(dist, maxDist)/newSpeed)*1000 + 0.5), UPDATEMOVEMENTINTERVAL);
			currentSpeed = newSpeed;
		} else
			currentSpeed = 0;
	} else {
		PatrolPoint oldPoint = patrolPoints.remove(0);

		if (getFollowState() == AiAgent::PATROLLING)
			savedPatrolPoints.add(oldPoint);

		ManagedReference<SceneObject*> followCopy = getFollowObject();
		if (followCopy == NULL)
			notifyObservers(ObserverEventType::DESTINATIONREACHED);

		if (isRetreating())
			homeLocation.setReached(true);

		currentFoundPath = NULL;
		targetCellObject = NULL;
		currentSpeed = 0;
	}

	if (!(isRetreating() || isFleeing())) {
		targetMutex.unlock();
		checkNewAngle();
		targetMutex.lock();
	}

	updateLocomotion();

	return getFollowState() == AiAgent::WATCHING || getFollowState() == AiAgent::FLEEING || found;
}

float AiAgentImplementation::getWorldZ(const Vector3& position) {
	Zone* zone = getZone();
	if (zone == NULL)
		return 0.f;

	SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects;

	if (closeobjects != NULL) {
		closeobjects->safeCopyTo(closeObjects);
	} else {
		zone->info("Null closeobjects vector in AiAgentImplementation::getWorldZ", true);

		Vector3 worldPosition = getWorldPosition();
		zone->getInRangeObjects(worldPosition.getX(), worldPosition.getY(), 128, &closeObjects, true);
	}

	IntersectionResults intersections;
	CollisionManager::getWorldFloorCollisions(position.getX(), position.getY(), zone, &intersections, closeObjects);
	return zone->getPlanetManager()->findClosestWorldFloor(position.getX(), position.getY(), position.getZ(), getSwimHeight(), &intersections, NULL);
}

// TODO (dannuic): All of the AI goes into the movement cycle, the recovery cycle is only for HAM/status recovery
void AiAgentImplementation::doMovement() {
	//info("doMovement", true);

	// Do pre-checks (these should remain hard-coded)
	if (isDead() || isIncapacitated() || (getZone() == NULL)) {
		setFollowObject(NULL);
		return;
	}

/*	Time startTime;
	startTime.updateToCurrentTime();*/

	if (isWaiting())
		stopWaiting();

	//info("Performing action ID: " + currentBehaviorID, true);
	// activate AI
	Behavior* current = behaviors.get(currentBehaviorID);
	if (current != NULL)
		current->doAction(true);

/*	Time endTime;
	endTime.updateToCurrentTime();*/

	//info("doMovement took " + String::valueOf(endTime.getMiliTime() - startTime.getMiliTime()) + "ms to complete.", true);
}

bool AiAgentImplementation::generatePatrol(int num, float dist) {
	clearPatrolPoints();
	clearSavedPatrolPoints();

	SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects;

	Zone* zone = getZone();

	if (zone == NULL)
		return false;

	if (closeobjects != NULL) {
		closeobjects->safeCopyTo(closeObjects);
	} else {
		zone->info("Null closeobjects vector in AiAgentImplementation::generatePatrol", true);

		Vector3 worldPosition = getWorldPosition();
		zone->getInRangeObjects(worldPosition.getX(), worldPosition.getY(), 128, &closeObjects, true);
	}

	for (int i = 0; i < num; i++) {
		PatrolPoint newPoint;
		newPoint.setPositionX(homeLocation.getPositionX() + (-1 * dist + (float)System::random((unsigned int)dist * 2)));
		newPoint.setPositionY(homeLocation.getPositionY() + (-1 * dist + (float)System::random((unsigned int)dist * 2)));
		newPoint.setPositionZ(homeLocation.getPositionZ());

		ManagedReference<SceneObject*> strongParent = getParent().get();
		if (strongParent != NULL && strongParent->isCellObject()) {
			newPoint.setCell(strongParent);
		}

		if (newPoint.getCell() == NULL && zone != NULL) {
			PlanetManager* planetManager = zone->getPlanetManager();
			IntersectionResults intersections;

			CollisionManager::getWorldFloorCollisions(newPoint.getPositionX(), newPoint.getPositionY(), zone, &intersections, closeObjects);

			newPoint.setPositionZ(planetManager->findClosestWorldFloor(newPoint.getPositionX(), newPoint.getPositionY(), newPoint.getPositionZ(), this->getSwimHeight(), &intersections, (CloseObjectsVector*) this->getCloseObjects()));
		}

		addPatrolPoint(newPoint);
	}

	if (getPatrolPointSize() > 0) {
		setFollowState(AiAgent::PATROLLING);
		return true;
	}

	return false;
}

float AiAgentImplementation::getMaxDistance() {
	if (isRetreating() || isFleeing())
		return 0.1f;

	ManagedReference<SceneObject*> followCopy = getFollowObject();
	unsigned int stateCopy = getFollowState();

	switch (stateCopy) {
	case AiAgent::PATROLLING:
	case AiAgent::LEASHING:
		return 0.1f;
		break;
	case AiAgent::STALKING:
		return followCopy != NULL ? getAggroRadius()*2 : 25;
		break;
	case AiAgent::FOLLOWING:
		if (followCopy == NULL)
			return 0.1f;

		if (isInCombat()) {
			// stop in weapons range
			if (!CollisionManager::checkLineOfSight(asAiAgent(), followCopy)) {
				return 0.1f;
			} else if (getWeapon() != NULL ) {
				float weapMaxRange = MIN(getWeapon()->getIdealRange(), getWeapon()->getMaxRange());
				return MAX(0.1f, weapMaxRange + getTemplateRadius() + followCopy->getTemplateRadius() - 2);
			}
		} else {
			return 1 + getTemplateRadius() + followCopy->getTemplateRadius();
		}
		break;
	}

	return 5.f;
}

int AiAgentImplementation::setDestination() {
	ManagedReference<SceneObject*> followCopy = getFollowObject();
	unsigned int stateCopy = getFollowState();
	switch (stateCopy) {
	case AiAgent::OBLIVIOUS:
		if (followCopy != NULL)
			setOblivious();
		clearPatrolPoints();

		if (!homeLocation.isInRange(asAiAgent(), 1.5)) {
			homeLocation.setReached(false);
			addPatrolPoint(homeLocation);
		} else {
			homeLocation.setReached(true);
		}

		break;
	case AiAgent::FLEEING:
		// TODO (dannuic): do we need to check threatmap for other players in range at this point? also, is this too far? alsoalso, is this time too static?
		if (!isRetreating() && (followCopy == NULL || !isInRange(followCopy, fleeRange))) {
			clearCombatState(true);
			setWatchObject(followCopy);
			alertedTime.updateToCurrentTime();
			alertedTime.addMiliTime(10000);
			return setDestination();
		}

		break;
	case AiAgent::LEASHING:
		if (!isRetreating()) {
			setOblivious();
			return setDestination();
		}

		break;
	case AiAgent::PATROLLING:
		if (getPatrolPointSize() == 0) {
			setPatrolPoints(savedPatrolPoints);
			clearSavedPatrolPoints();
		}

		break;
	case AiAgent::WATCHING:
		if (followCopy == NULL || getAlertedTime() == NULL || getAlertedTime()->isPast()) {
			setOblivious();
			return setDestination();
		}

		setNextPosition(getPositionX(), getPositionZ(), getPositionY(), getParent().get()); // sets patrolPoints[0] to current position
		checkNewAngle(); // sends update zone packet
		if (getPatrolPointSize() > 0) {
			PatrolPoint patrolPoint = getNextPosition();
			updateCurrentPosition(&patrolPoint);
		}
		break;
	case AiAgent::STALKING:
		if (getAlertedTime() == NULL || getAlertedTime()->isPast()) {
			setOblivious();
			return setDestination();
		}
	case AiAgent::FOLLOWING:
		if (followCopy == NULL) {
			setOblivious();
			return setDestination();
		}

		clearPatrolPoints();
		setNextPosition(followCopy->getPositionX(), followCopy->getPositionZ(), followCopy->getPositionY(), followCopy->getParent().get());
		break;
	default:
		setOblivious();
		break;
	}

	//activateMovementEvent();

	return getPatrolPointSize();
}

bool AiAgentImplementation::completeMove() {
	updateCurrentPosition(&nextStepPosition);
	nextStepPosition.setReached(true);
	return true;
}

bool AiAgentImplementation::isScentMasked(CreatureObject* target) {
	Locker locker(&targetMutex);
	CreatureObject* effectiveTarget = target;
	// Check masked scent
	if (target->isVehicleObject() || target->isMount()) {
		effectiveTarget = target->getLinkedCreature().get();
	}
	if (effectiveTarget == NULL) {
		return false;
	}
	if (!effectiveTarget->hasBuff(STRING_HASHCODE("skill_buff_mask_scent_self"))) {
		if(camouflagedObjects.contains(effectiveTarget)) camouflagedObjects.removeElement(effectiveTarget);
		return false;
	}
	if (isNonPlayerCreatureObject() || isDroidObject())
		return false;

	// Step 1. Check for break
	bool success = false;
	int camoSkill = effectiveTarget->getSkillMod("mask_scent");
	int creatureLevel = getLevel();

	int mod = 100;
	if (effectiveTarget->isKneeling() || effectiveTarget->isSitting())
		mod -= 10;
	if (effectiveTarget->isStanding())
		mod -= 15;
	if (effectiveTarget->isRunning() || effectiveTarget->isRidingMount() )
		mod -= 35;

	if (System::random(100) <= (-1 * (1 / ((camoSkill / 100.0f) * 20)) * creatureLevel) + mod) {
		success = true;
	}
	// first time through we award, second time on same mob if successful we dont
	if (success && camouflagedObjects.contains(effectiveTarget))
		return true;
	else if (success){
		camouflagedObjects.add(effectiveTarget); // add to award
	} else {
		if(camouflagedObjects.contains(effectiveTarget)) camouflagedObjects.removeElement(effectiveTarget);
	}

	Reference<Task*> ct = new CamoTask(effectiveTarget, asAiAgent(), true, success);
	ct->execute();

	return success;
}

bool AiAgentImplementation::isConcealed(CreatureObject* target) {
	Locker locker(&targetMutex);
	CreatureObject* effectiveTarget = target;
	// Check masked scent
	if (target->isVehicleObject() || target->isMount()) {
		effectiveTarget = target->getLinkedCreature().get();
	}
	if (effectiveTarget == NULL) {
		return false;
	}

	if (!effectiveTarget->hasBuff(STRING_HASHCODE("skill_buff_mask_scent"))) {
		if(camouflagedObjects.contains(effectiveTarget)) camouflagedObjects.removeElement(effectiveTarget);
		return false;
	}
	if (isDroidObject())
		return false;

	bool success = false;
	int camoSkill = effectiveTarget->getSkillMod("private_conceal");
	int creatureLevel = getLevel();

	int mod = 100;
	if (effectiveTarget->isKneeling() || effectiveTarget->isSitting())
		mod -= 10;
	if (effectiveTarget->isStanding())
		mod -= 15;
	if (effectiveTarget->isRunning() || effectiveTarget->isRidingMount() )
		mod -= 35;

	// Check if camo breaks
	if (!isCreature())
		creatureLevel *= 2;

	if (System::random(100) <= (-1 * (1 / ((camoSkill / 100.0f) * 20)) * creatureLevel) + mod) {
		success = true;
	}

	if (success && camouflagedObjects.contains(effectiveTarget))
		return true;
	else if (success){
		camouflagedObjects.add(effectiveTarget); // add to award
	} else {
		if(camouflagedObjects.contains(effectiveTarget)) camouflagedObjects.removeElement(effectiveTarget);
	}

	Reference<Task*> ct = new CamoTask(effectiveTarget, asAiAgent(), false, success);
	ct->execute();

	return success;
}

void AiAgentImplementation::activateMovementEvent() {
	if (getZone() == NULL)
		return;

	Locker locker(&movementEventMutex);

	if (isWaiting() && moveEvent != NULL)
		moveEvent->cancel();

	if ((waitTime < 0 || numberOfPlayersInRange.get() <= 0) && getFollowObject() == NULL && !isRetreating()) {
		if (moveEvent != NULL) {
			moveEvent->clearCreatureObject();
			moveEvent = NULL;
		}

		return;
	}

	if (moveEvent == NULL) {
		moveEvent = new AiMoveEvent(asAiAgent());

		moveEvent->schedule(waitTime > 0 ? waitTime : nextMovementInterval);
	}

	try {
		if (!moveEvent->isScheduled())
			moveEvent->schedule(waitTime > 0 ? waitTime : nextMovementInterval);
	} catch (IllegalArgumentException& e) {

	}

	nextMovementInterval = UPDATEMOVEMENTINTERVAL;
}

void AiAgentImplementation::activateWaitEvent() {
	if (getZone() == NULL)
		return;

	if (waitEvent == NULL) {
		waitEvent = new AiWaitEvent(asAiAgent());

		waitEvent->schedule(UPDATEMOVEMENTINTERVAL * 10);
	}

	if (!waitEvent->isScheduled())
		waitEvent->schedule(UPDATEMOVEMENTINTERVAL * 10);
}

void AiAgentImplementation::setNextPosition(float x, float z, float y, SceneObject* cell) {
	Locker locker(&targetMutex);

	PatrolPoint point(x, z, y, cell);

	patrolPoints.add(0, point);
}

void AiAgentImplementation::setNextStepPosition(float x, float z, float y, SceneObject* cell) {
	Locker locker(&targetMutex);

	PatrolPoint point(x, z, y, cell);

	nextStepPosition = point;
}

void AiAgentImplementation::broadcastNextPositionUpdate(PatrolPoint* point) {
	BasePacket* msg = NULL;
	++movementCounter;

	if (point == NULL) {
		if (parent.get() != NULL)
			msg = new UpdateTransformWithParentMessage(asAiAgent());
		else
			msg = new UpdateTransformMessage(asAiAgent());
	} else {
		if (point->getCell() != NULL)
			msg = new LightUpdateTransformWithParentMessage(asAiAgent(), point->getPositionX(), point->getPositionZ(), point->getPositionY(), point->getCell()->getObjectID());
		else
			msg = new LightUpdateTransformMessage(asAiAgent(), point->getPositionX(), point->getPositionZ(), point->getPositionY());
	}

	broadcastMessage(msg, false);
}

int AiAgentImplementation::notifyObjectDestructionObservers(TangibleObject* attacker, int condition) {
	if (isPet()) {
		PetManager* petManager = server->getZoneServer()->getPetManager();

		petManager->notifyDestruction(attacker, asAiAgent(), condition);

	} else {
		if (getZone() != NULL) {
			CreatureManager* creatureManager = getZone()->getCreatureManager();

			creatureManager->notifyDestruction(attacker, asAiAgent(), condition);
		}
	}

	sendReactionChat(ReactionManager::DEATH);

	return CreatureObjectImplementation::notifyObjectDestructionObservers(attacker, condition);
}

int AiAgentImplementation::notifyConverseObservers(CreatureObject* converser) {
	notifyObservers(ObserverEventType::CONVERSE, converser);

	return 1;
}

int AiAgentImplementation::inflictDamage(TangibleObject* attacker, int damageType, float damage, bool destroy, bool notifyClient) {
	lastDamageReceived.updateToCurrentTime();

	activateRecovery();
	
	if (attacker->isCreatureObject()) {
		CreatureObject* creature = attacker->asCreatureObject();

		if (damage > 0) {
			getThreatMap()->addDamage(creature, damage);
		}
	}
	activateInterrupt(attacker, ObserverEventType::DAMAGERECEIVED);
	return CreatureObjectImplementation::inflictDamage(attacker, damageType, damage, destroy, notifyClient);
}

int AiAgentImplementation::inflictDamage(TangibleObject* attacker, int damageType, float damage, bool destroy, const String& xp, bool notifyClient) {
	lastDamageReceived.updateToCurrentTime();

	activateRecovery();

	if (attacker->isCreatureObject()) {
		CreatureObject* creature = attacker->asCreatureObject();

		if (damage > 0) {
			getThreatMap()->addDamage(creature, damage, xp);
		}
	}
	activateInterrupt(attacker, ObserverEventType::DAMAGERECEIVED);
	return CreatureObjectImplementation::inflictDamage(attacker, damageType, damage, destroy, notifyClient);
}


void AiAgentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player) {

	if (isDead()) {
		return;
	}

	if (getArmor() == 0)
		alm->insertAttribute("armorrating", "None");
	else if (getArmor() == 1)
		alm->insertAttribute("armorrating", "Light");
	else if (getArmor() == 2)
		alm->insertAttribute("armorrating", "Medium");
	else if (getArmor() == 3)
		alm->insertAttribute("armorrating", "Heavy");

	if (isSpecialProtection(WeaponObject::KINETIC)) {
		StringBuffer txt;
		txt << Math::getPrecision(getKinetic(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_kinetic", txt.toString());
	}

	if (isSpecialProtection(WeaponObject::ENERGY)) {
		StringBuffer txt;
		txt << Math::getPrecision(getEnergy(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_energy", txt.toString());
	}

	if (isSpecialProtection(WeaponObject::ELECTRICITY)) {
		StringBuffer txt;
		txt << Math::getPrecision(getElectricity(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_electrical", txt.toString());
	}

	if (isSpecialProtection(WeaponObject::STUN)) {
		StringBuffer txt;
		txt << Math::getPrecision(getStun(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_stun", txt.toString());
	}

	if (isSpecialProtection(WeaponObject::BLAST)) {
		StringBuffer txt;
		txt << Math::getPrecision(getBlast(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_blast", txt.toString());
	}

	if (isSpecialProtection(WeaponObject::HEAT)) {
		StringBuffer txt;
		txt << Math::getPrecision(getHeat(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_heat", txt.toString());
	}

	if (isSpecialProtection(WeaponObject::COLD)) {
		StringBuffer txt;
		txt << Math::getPrecision(getCold(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_cold", txt.toString());
	}

	if (isSpecialProtection(WeaponObject::ACID)) {
		StringBuffer txt;
		txt << Math::getPrecision(getAcid(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_acid", txt.toString());
	}

	if (isSpecialProtection(WeaponObject::LIGHTSABER)) {
		StringBuffer txt;
		txt << Math::getPrecision(getLightSaber(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_restraint", txt.toString());
	}

	if (getKinetic() > 0 && !isSpecialProtection(WeaponObject::KINETIC)) {
		StringBuffer txt;
		txt << Math::getPrecision(getKinetic(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_kinetic", txt.toString());
	}

	if (getEnergy() > 0 && !isSpecialProtection(WeaponObject::ENERGY)) {
		StringBuffer txt;
		txt << Math::getPrecision(getEnergy(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_energy", txt.toString());
	}

	if (getElectricity() > 0 && !isSpecialProtection(WeaponObject::ELECTRICITY)) {
		StringBuffer txt;
		txt << Math::getPrecision(getElectricity(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_electrical", txt.toString());
	}

	if (getStun() > 0 && !isSpecialProtection(WeaponObject::STUN)) {
		StringBuffer txt;
		txt << Math::getPrecision(getStun(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_stun", txt.toString());
	}

	if (getBlast() > 0 && !isSpecialProtection(WeaponObject::BLAST)) {
		StringBuffer txt;
		txt << Math::getPrecision(getBlast(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_blast", txt.toString());
	}

	if (getHeat() > 0 && !isSpecialProtection(WeaponObject::HEAT)) {
		StringBuffer txt;
		txt << Math::getPrecision(getHeat(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_heat", txt.toString());
	}

	if (getCold() > 0 && !isSpecialProtection(WeaponObject::COLD)) {
		StringBuffer txt;
		txt << Math::getPrecision(getCold(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_cold", txt.toString());
	}

	if (getAcid() > 0 && !isSpecialProtection(WeaponObject::ACID)) {
		StringBuffer txt;
		txt << Math::getPrecision(getAcid(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_acid", txt.toString());
	}

	if (getLightSaber() > 0 && !isSpecialProtection(WeaponObject::LIGHTSABER)) {
		StringBuffer txt;
		txt << Math::getPrecision(getLightSaber(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_restraint", txt.toString());
	}

	if (getKinetic() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_kinetic", "-");

	if (getEnergy() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_energy", "-");

	if (getElectricity() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_electrical", "-");

	if (getStun() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_stun", "-");

	if (getBlast() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_blast", "-");

	if (getHeat() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_heat", "-");

	if (getCold() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_cold", "-");

	if (getAcid() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_acid", "-");

	if (getLightSaber() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_restraint", "-");

	if (isPet())
	{
		ManagedReference<CreatureObject*> owner = getLinkedCreature().get();

		if (owner != NULL)
		{
			StringBuffer fullName;
			fullName << owner->getFirstName();
			if(!owner->getLastName().isEmpty())
				fullName << " " << owner->getLastName();

			alm->insertAttribute("@obj_attr_n:owner", fullName.toString());
		}
	}

	if (player->getPlayerObject() && player->getPlayerObject()->isPrivileged()) {
		if (homeObject != NULL) {
			int type = 0;
			if (homeObject->getObserverCount(ObserverEventType::OBJECTDESTRUCTION) > 0)
				type = ObserverEventType::OBJECTDESTRUCTION;
			else if (homeObject->getObserverCount(ObserverEventType::CREATUREDESPAWNED) > 0)
				type = ObserverEventType::CREATUREDESPAWNED;

			if (type != 0) {
				ManagedReference<SpawnObserver*> spawnObserver = NULL;
				SortedVector<ManagedReference<Observer*> > observers = homeObject->getObservers(type);

				for (int i = 0; i < observers.size(); i++) {
					spawnObserver = cast<SpawnObserver*>(observers.get(i).get());
					if (spawnObserver != NULL)
						break;
				}

				if (spawnObserver) {
					String name = spawnObserver->getLairTemplateName();
					alm->insertAttribute("blank_entry" , "");
					alm->insertAttribute("object_type" , name);
					alm->insertAttribute("blank_entry" , "");
				}
			}
		}
	}
}

bool AiAgentImplementation::sendConversationStartTo(SceneObject* player) {
	if (!player->isPlayerCreature() || isDead() || npcTemplate == NULL || npcTemplate->getConversationTemplate() == 0)
		return false;

	//Face player.
	faceObject(player);

	PatrolPoint current(coordinates.getPosition(), getParent().get());

	broadcastNextPositionUpdate(&current);

	if (npcTemplate == NULL)
		return false;

	CreatureObject* playerCreature = cast<CreatureObject*>( player);

	ConversationTemplate* conversationTemplate = CreatureTemplateManager::instance()->getConversationTemplate(npcTemplate->getConversationTemplate());
	if (conversationTemplate != NULL && conversationTemplate->getConversationTemplateType() == ConversationTemplate::ConversationTemplateTypeTrainer) {
		ManagedReference<CityRegion*> city = player->getCityRegion();

		if (city != NULL && !city->isClientRegion() && city->isBanned(player->getObjectID())) {
			playerCreature->sendSystemMessage("@city/city:banned_services"); // You are banned from using this city's services.
			return false;
		}
	}

	StartNpcConversation* conv = new StartNpcConversation(playerCreature, getObjectID(), "");
	player->sendMessage(conv);

	SortedVector<ManagedReference<Observer*> > observers = getObservers(ObserverEventType::STARTCONVERSATION);

	for (int i = 0;  i < observers.size(); ++i) {
		if (dynamic_cast<ConversationObserver*>(observers.get(i).get()) != NULL)
			return true;
	}

	//Create conversation observer.
	ConversationObserver* conversationObserver = ConversationManager::instance()->getConversationObserver(npcTemplate->getConversationTemplate());

	if (conversationObserver != NULL) {
		//Register observers.
		registerObserver(ObserverEventType::CONVERSE, conversationObserver);
		registerObserver(ObserverEventType::STARTCONVERSATION, conversationObserver);
		registerObserver(ObserverEventType::SELECTCONVERSATION, conversationObserver);
		registerObserver(ObserverEventType::STOPCONVERSATION, conversationObserver);
	} else {
		error("Could not create conversation observer.");
		return false;
	}

	return true;
}

bool AiAgentImplementation::isAggressiveTo(CreatureObject* target) {
	if (!isAttackableBy(target) || target->isVehicleObject())
		return false;

	// grab the GCW faction
	uint32 targetFaction = target->getFaction();
	PlayerObject* ghost = target->getPlayerObject();

	// check the GCW factions if both entities have one
	if (getFaction() != 0 && targetFaction != 0) {

		// this is basically the isEnemy check, but with the GCW faction (they should both return the same thing)
		if (ghost == NULL && (targetFaction != getFaction()))
			return true;
		// this is the same thing, but ensures that if the target is a player, that they aren't on leave
		else if (ghost != NULL && (targetFaction != getFaction()) && ghost->getFactionStatus() != FactionStatus::ONLEAVE)
			return true;
	}

	// now grab the generic faction (which could include imp/reb)
	String factionString = getFactionString();

	if (!factionString.isEmpty()) {
		// for players, we are only an enemy if the standing is less than -3000, but we are
		// forced to non-aggressive status if the standing is over 3000, otherwise use the
		// pvpStatusBitmask to determine aggressiveness
		if (target->isPlayerCreature() && ghost != NULL) {
			float targetsStanding = ghost->getFactionStanding(factionString);

			if (targetsStanding <= -3000)
				return true;
			else if (targetsStanding >= 3000)
				return false;

		// AI can check the enemy strings directly vs other AI (since they don't have a
		// standing)
		} else if (target->isAiAgent()) {
			AiAgent* targetAi = target->asAiAgent();

			if (targetAi != NULL && FactionManager::instance()->isEnemy(factionString, targetAi->getFactionString()))
				return true;
		}
	}

	// if we've made it this far then the target is a valid target, but we will only be aggressive based on the pvpStatusBitmask
	return getPvpStatusBitmask() & CreatureFlag::AGGRESSIVE;
}

bool AiAgentImplementation::hasLoot(){
	SceneObject* inventory = getSlottedObject("inventory");

	if(inventory == NULL)
		return false;

	return inventory->getContainerObjectsSize() > 0;
}

void AiAgentImplementation::sendDefaultConversationTo(SceneObject* player) {
}

void AiAgentImplementation::selectConversationOption(int option, SceneObject* obj) {
}

bool AiAgentImplementation::isEventMob() {

	if (getDisplayedName().contains(" (event)"))
		return true;

	return false;
}

void AiAgentImplementation::setupBehaviorTree(AiTemplate* aiTemplate) {
	if (aiTemplate == NULL) {
		error("Invalid aiTemplate in AiAgent::setupBehaviorTree");
		return;
	}

	Vector<Reference<LuaAiTemplate*> >* treeTemplate = aiTemplate->getTree();

	stopWaiting();
	setWait(0);

	behaviors.put(0, NULL);

	VectorMap<uint32, Vector<uint32> > parents; // id's keyed by parents
	parents.setAllowOverwriteInsertPlan();

	// first build the maps
	for (int i=0; i < treeTemplate->size(); i++) {
		LuaAiTemplate* temp = treeTemplate->get(i).get();
		if (temp == NULL) {
			error("Null AI template, contact dannuic if this occurs"); // FIXME (dannuic): Is this still happening?
			continue;
		}

		Behavior* behavior = AiMap::createNewInstance(asAiAgent(), temp->className, temp->classType);
		behavior->setID(temp->id);
		behaviors.put(temp->id, behavior);

		Vector<uint32> ids = parents.get(temp->parent);
		ids.add(temp->id);
		parents.put(temp->parent, ids);
	}

	// now set parents
	for (int i = 0; i < parents.size(); i++) {
		VectorMapEntry<uint32, Vector<uint32> >& element = parents.elementAt(i);
		if (element.getKey() == STRING_HASHCODE("none")) // this is the parent of the root node, just skip it.
			continue;

		Behavior* b = behaviors.get(element.getKey());

		if (b == NULL || !b->isComposite()) { // parent is not composite, this will probably break the tree
			error("Failed to load " + String::valueOf(element.getKey()) + " as a parent in tree: " + aiTemplate->getTemplateName());
			continue;
		}

		CompositeBehavior* par = cast<CompositeBehavior*>(b);

		Vector<uint32>& ids = element.getValue();

		for (int j = 0; j < ids.size(); j++) {
			Behavior* child = behaviors.get(ids.get(j));

			if (child == NULL) {
				error("Failed to load " + String::valueOf(ids.get(i)) + " as a child in tree: " + aiTemplate->getTemplateName());
				continue;
			}

			addBehaviorToTree(child, par);
		}
	}

	// now tree is complete, set the root node as the current node
	Vector<uint32>& roots = parents.get(STRING_HASHCODE("none"));
	if (roots.size() > 1) {
		error("Multiple root nodes in tree: " + aiTemplate->getTemplateName());
		return; // all References will be lost here
	} else if (roots.size() <= 0) {
		error("No root nodes in tree: " + aiTemplate->getTemplateName());
		return;
	}

	uint32 rootID = roots.get(0);
	Behavior* rootBehavior = behaviors.get(rootID);
	if (rootBehavior == NULL) {
		error("Failed to get root instance in " + aiTemplate->getTemplateName());
		return;
	}

	setCurrentBehavior(rootID);
}

void AiAgentImplementation::setupBehaviorTree() {
	AiTemplate* getTarget = AiMap::instance()->getGetTargetTemplate(creatureBitmask);
	AiTemplate* selectAttack = AiMap::instance()->getSelectAttackTemplate(creatureBitmask);
	AiTemplate* combatMove = AiMap::instance()->getCombatMoveTemplate(creatureBitmask);
	AiTemplate* idle = AiMap::instance()->getIdleTemplate(creatureBitmask);

	setupBehaviorTree(getTarget, selectAttack, combatMove, idle);
}

void AiAgentImplementation::setupBehaviorTree(AiTemplate* getTarget, AiTemplate* selectAttack, AiTemplate* combatMove, AiTemplate* idle) {
	String name = "CompositeDefault";
	if (creatureBitmask & CreatureFlag::DROID_PET)
		name = "CompositeDroidPet";
	else if (creatureBitmask & CreatureFlag::FACTION_PET)
		name = "CompositeFactionPet";
	else if (creatureBitmask & CreatureFlag::PET)
		name = "CompositeCreaturePet";
	else if (creatureBitmask & CreatureFlag::PACK)
		name = "CompositePack";

	CompositeBehavior* rootSelector = cast<CompositeBehavior*>(AiMap::instance()->createNewInstance(asAiAgent(), name, AiMap::SELECTORBEHAVIOR));
	CompositeBehavior* attackSequence = cast<CompositeBehavior*>(AiMap::instance()->createNewInstance(asAiAgent(), name, AiMap::SEQUENCEBEHAVIOR));
	rootSelector->setID(STRING_HASHCODE("root"));
	attackSequence->setID(STRING_HASHCODE("attackSequence"));

	addBehaviorToTree(attackSequence, rootSelector);

	setupBehaviorTree(getTarget);
	addCurrentBehaviorToTree(attackSequence);

	setupBehaviorTree(selectAttack);
	addCurrentBehaviorToTree(attackSequence);

	setupBehaviorTree(combatMove);
	addCurrentBehaviorToTree(attackSequence);

	setupBehaviorTree(idle);
	addCurrentBehaviorToTree(rootSelector);

	behaviors.put(STRING_HASHCODE("root"), rootSelector);
	behaviors.put(STRING_HASHCODE("attackSequence"), attackSequence);

	resetBehaviorList();

	//info(behaviors.get(currentBehaviorID)->print(), true);
}

void AiAgentImplementation::setCurrentBehavior(uint32 b) {
	currentBehaviorID = b;
	if (behaviors.get(currentBehaviorID) != NULL) {
		//activateMovementEvent();

		//info(currentBehaviorID, true);
		// This is for debugging:
/*		ZoneServer* zoneServer = ServerCore::getZoneServer();
		ChatManager* chatManager = zoneServer->getChatManager();

		chatManager->broadcastMessage(asAiAgent(), currentBehaviorID, 0, 0, 0);*/
	} else
		error("Null Behavior in " + String::valueOf(currentBehaviorID));
}

int AiAgentImplementation::getBehaviorStatus() {
	Behavior* b = behaviors.get(currentBehaviorID);
	if (b == NULL)
		return AiMap::INVALID;

	return b->getStatus();
}

void AiAgentImplementation::setBehaviorStatus(int status) {
	Behavior* b = behaviors.get(currentBehaviorID);
	if (b != NULL) {
		b->setStatus((uint8)status);

		// This is for debugging:
/*		ZoneServer* zoneServer = ServerCore::getZoneServer();
		ChatManager* chatManager = zoneServer->getChatManager();

		chatManager->broadcastMessage(asAiAgent(), String::valueOf(status), 0, 0, 0);*/
	}
}

void AiAgentImplementation::addBehaviorToTree(Behavior* b, CompositeBehavior* par) {
	if (b)
		b->setParent(par);
	if (par)
		par->addChild(b);
}

void AiAgentImplementation::addCurrentBehaviorToTree(CompositeBehavior* par) {
	Behavior* b = behaviors.get(currentBehaviorID);
	addBehaviorToTree(b, par);
}

/**
 * move the tree back to the root node
 */
void AiAgentImplementation::resetBehaviorList() {
	Behavior* b = behaviors.get(currentBehaviorID);
	if (b != NULL)
		b->end();

	currentBehaviorID = STRING_HASHCODE("root");
	b = behaviors.get(currentBehaviorID);
	if (b == NULL)
		return;

	b->setStatus(AiMap::SUSPEND);

	stopWaiting();
	setWait(0);

	if (moveEvent != NULL)
		moveEvent->cancel();
	//info(root->print(), true);
}

void AiAgentImplementation::clearBehaviorList() {
	for (int i = 0; i < behaviors.size(); i++) {
		Behavior* b = behaviors.get(i);
		if (b != NULL) {
			delete b;
			b = NULL;
		}
	}

	currentBehaviorID = 0;
	behaviors.removeAll();
}

int AiAgentImplementation::interrupt(SceneObject* source, int64 msg) {
	Behavior* b = behaviors.get(currentBehaviorID);

	if (b == NULL)
		return 1;

	return b->interrupt(source, msg);
}

void AiAgentImplementation::broadcastInterrupt(int64 msg) {
	if (zone == NULL)
		return;

	Reference<AiAgent*> aiAgent = asAiAgent();

	EXECUTE_TASK_2(aiAgent, msg, {
			SortedVector<ManagedReference<QuadTreeEntry*> > closeAiAgents;

			CloseObjectsVector* closeobjects = (CloseObjectsVector*) aiAgent_p->getCloseObjects();
			Zone* zone = aiAgent_p->getZone();

			if (zone == NULL)
				return;

			try {
				if (closeobjects == NULL) {
					aiAgent_p->info("Null closeobjects vector in AiAgentImplementation::broadcastInterrupt", true);
					zone->getInRangeObjects(aiAgent_p->getPositionX(), aiAgent_p->getPositionY(), 192, &closeAiAgents, true);
				} else {
					closeAiAgents.removeAll(closeobjects->size(), 10);
					closeobjects->safeCopyTo(closeAiAgents);
				}
			} catch (Exception& e) {

			}

			for (int i = 0; i < closeAiAgents.size(); ++i) {
				AiAgent* agent = cast<AiAgent*>(closeAiAgents.get(i).get());

				if (aiAgent_p == agent || agent == NULL)
					continue;

				Locker locker(agent);

				Locker crossLocker(aiAgent_p, agent);

				agent->interrupt(aiAgent_p, msg_p);
			}
	});

}

void AiAgentImplementation::setCombatState() {
	CreatureObjectImplementation::setCombatState();

	if (homeObject != NULL)
		homeObject->notifyObservers(ObserverEventType::AIMESSAGE, asAiAgent(), ObserverEventType::STARTCOMBAT);

	ManagedReference<SceneObject*> followCopy = getFollowObject();
	if (followCopy != NULL && followCopy->isTangibleObject()) {
		ManagedReference<TangibleObject*> target = cast<TangibleObject*>(followCopy.get());
		ManagedReference<AiAgent*> ai = asAiAgent();

		EXECUTE_TASK_2(ai, target, {
			Locker locker(ai_p);
			Locker clocker(target_p, ai_p);

			if (target_p->hasDefender(ai_p))
				ai_p->sendReactionChat(ReactionManager::ATTACKED);
		});

	}

	//broadcastInterrupt(ObserverEventType::STARTCOMBAT);

	activateInterrupt(asAiAgent(), ObserverEventType::STARTCOMBAT);
}

void AiAgentImplementation::activateInterrupt(SceneObject* source, int64 msg) {
	AiInterruptTask* task = new AiInterruptTask(asAiAgent(), source, msg);
	task->execute();
}

void AiAgentImplementation::activateLoad(const String& temp) {
	AiLoadTask* task = new AiLoadTask(asAiAgent(), temp);
	task->execute();
}

bool AiAgentImplementation::hasRangedWeapon() {
	Reference<WeaponObject*> defaultWeapon = getSlottedObject("default_weapon").castTo<WeaponObject*>();

	return (defaultWeapon != NULL && defaultWeapon->isRangedWeapon()) || (readyWeapon != NULL && readyWeapon->isRangedWeapon());
}

bool AiAgentImplementation::hasSpecialAttack(int num) {
	CreatureAttackMap* attackMap = getAttackMap();
	if (attackMap == NULL) {
		return false;
	}

	if (num == 0 || (num > attackMap->size())) {
		return false;
	}

	String cmd = attackMap->getCommand(num - 1);

	if (cmd.isEmpty()) {
		return false;
	}

	return true;
}

bool AiAgentImplementation::isAttackableBy(CreatureObject* object) {
	if (object == NULL || object == asAiAgent()) {
		return false;
	}

	if (isDead() || isIncapacitated() || getFollowState() == AiAgent::LEASHING) {
		return false;
	}

	if (isPet()) {
		ManagedReference<PetControlDevice*> pcd = getControlDevice().get().castTo<PetControlDevice*>();
		if (pcd != NULL && pcd->getPetType() == PetManager::FACTIONPET && object->isNeutral()) {
			return false;
		}

		ManagedReference<CreatureObject*> owner = getLinkedCreature().get();

		if (owner == NULL) {
			return false;
		}

		return owner->isAttackableBy(object);
	}

	if (object->isPet() || object->isVehicleObject()) {
		ManagedReference<PetControlDevice*> pcd = object->getControlDevice().get().castTo<PetControlDevice*>();
		if (pcd != NULL && pcd->getPetType() == PetManager::FACTIONPET && isNeutral()) {
			return false;
		}

		ManagedReference<CreatureObject*> owner = object->getLinkedCreature().get();

		if (owner == NULL) {
			return false;
		}

		return isAttackableBy(owner);
	}

	if (pvpStatusBitmask == 0) {
		return false;
	}

	unsigned int targetFaction = object->getFaction();

	if (targetFaction != 0 && getFaction() != 0) {
		if (targetFaction == getFaction()) {
			return false;
		}

		PlayerObject* ghost = object->getPlayerObject();

		if (ghost != NULL && ghost->getFactionStatus() == FactionStatus::ONLEAVE) {
			return false;
		}

	} else if (targetFaction == 0 && getFaction() != 0) {
		return false;
	}

	if (object->isAiAgent()) {
		AiAgent* ai = object->asAiAgent();

		CreatureTemplate* targetTemplate = ai->getCreatureTemplate();
		if ((npcTemplate.get() != NULL && targetTemplate != NULL) && (npcTemplate->getTemplateName() == targetTemplate->getTemplateName())) {
			return false;
		}

		String targetSocialGroup = ai->getSocialGroup().toLowerCase();
		if (!targetSocialGroup.isEmpty() && targetSocialGroup != "self" && targetSocialGroup == getSocialGroup().toLowerCase()) {
			return false;
		}
	}

	return true;
}

void AiAgentImplementation::restoreFollowObject() {
	Locker locker(&targetMutex);
	ManagedReference<SceneObject*> obj = followStore.get();
	locker.release();
	if (obj == NULL) {
		setOblivious();
	} else if (getCloseObjects() != NULL && !getCloseObjects()->contains(obj.get())) {
		setOblivious();
	} else if (obj->isCreatureObject() && obj->asCreatureObject()->isInvisible()) {
		setOblivious();
	} else {
		setFollowObject(obj);
	}
}
String AiAgentImplementation::getPersonalityStf() {
	if (npcTemplate == NULL)
		return "";
	else
		return npcTemplate->getPersonalityStf();
}

void AiAgentImplementation::sendReactionChat(int type, int state, bool force) {
	if (!getCooldownTimerMap()->isPast("reaction_chat") || getZone() == NULL) {
		return;
	}

	ReactionManager* reactionManager = getZoneServer()->getReactionManager();

	if (reactionManager != NULL)
		reactionManager->sendChatReaction(asAiAgent(), type, state, force);
}

float AiAgentImplementation::getEffectiveResist() {
	if (!isSpecialProtection(WeaponObject::ACID) && getAcid() > 0)
		return getAcid();
	if (!isSpecialProtection(WeaponObject::BLAST) && getBlast() > 0)
		return getBlast();
	if (!isSpecialProtection(WeaponObject::COLD) && getCold() > 0)
		return getCold();
	if (!isSpecialProtection(WeaponObject::ELECTRICITY) && getElectricity() > 0)
		return getElectricity();
	if (!isSpecialProtection(WeaponObject::ENERGY) && getEnergy() > 0)
		return getEnergy();
	if (!isSpecialProtection(WeaponObject::HEAT) && getHeat() > 0)
		return getHeat();
	if (!isSpecialProtection(WeaponObject::KINETIC) && getKinetic() > 0)
		return getKinetic();
	if (!isSpecialProtection(WeaponObject::LIGHTSABER) && getLightSaber() > 0)
		return getLightSaber();
	if (!isSpecialProtection(WeaponObject::STUN) && getStun() > 0)
		return getStun();
	return 0;
}

void AiAgentImplementation::setPatrolPoints(PatrolPointsVector& pVector) {
	Locker locker(&targetMutex);
	patrolPoints = pVector;
}

AiAgent* AiAgentImplementation::asAiAgent() {
	return _this.getReferenceUnsafeStaticCast();
}

AiAgent* AiAgent::asAiAgent() {
	return this;
}

