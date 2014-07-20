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

#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/conversation/ConversationObserver.h"
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
#include "components/AiDefaultComponent.h"
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
//#include "server/zone/managers/loot/LootManager.h"
//#include "server/zone/managers/templates/TemplateManager.h"
//#include "server/zone/objects/creature/ai/bt/Behavior.h"
//#include "server/zone/objects/creature/CreatureObject.h"
//#include "server/zone/packets/creature/CreatureObjectDeltaMessage4.h"
//#include "server/zone/packets/object/NpcConversationMessage.h"
//#include "server/zone/packets/object/StopNpcConversation.h"
//#include "server/zone/packets/object/StringList.h"
//#include "server/zone/packets/ui/CreateClientPathMessage.h"
//#include "server/zone/templates/appearance/FloorMesh.h"
//#include "server/zone/templates/appearance/PortalLayout.h"
#include "variables/CreatureAttackMap.h"
#include "variables/CreatureTemplateReference.h"
#include "variables/CurrentFoundPath.h"

#include "server/chat/ChatManager.h"
#include "server/zone/managers/creature/SpawnObserver.h"


//#define SHOW_WALK_PATH
//#define DEBUG
//#define SHOW_NEXT_POSITION

void AiAgentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	CreatureObjectImplementation::loadTemplateData(templateData);
}

int AiAgentImplementation::calculateAttackMinDamage(int level) {
	int minDmg = MAX(npcTemplate->getDamageMin(), 20 + (level * 5));

	return minDmg;
}

int AiAgentImplementation::calculateAttackMaxDamage(int level) {
	int dmg = MAX(npcTemplate->getDamageMax(), calculateAttackMinDamage(level) * 2);

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
	level = npcTemplate->getLevel();

	float minDmg = calculateAttackMinDamage(level);
	float maxDmg = calculateAttackMaxDamage(level);
	float speed = calculateAttackSpeed(level);

	Reference<WeaponObject*> defaultWeapon = getSlottedObject("default_weapon").castTo<WeaponObject*>();

	if (weapons.size() == 0) {
		Vector<String> wepgroups = npcTemplate->getWeapons();
		for (int i = 0; i < wepgroups.size(); ++i) {
			Vector<String> weptemps = CreatureTemplateManager::instance()->getWeapons(wepgroups.get(i));

			for (int i = 0; i < weptemps.size(); ++i) {
				uint32 crc = weptemps.get(i).hashCode();

				ManagedReference<WeaponObject*> weao = (server->getZoneServer()->createObject(crc, 0)).castTo<WeaponObject*>();

				if (weao != NULL) {
					weao->setMinDamage(minDmg * 0.5);
					weao->setMaxDamage(maxDmg * 0.5);
					weao->setAttackSpeed(speed);
					weapons.add(weao);

					if (i == 0)
						transferObject(weao, 4, false);
				} else {
					error("could not create weapon " + weptemps.get(i));
				}
			}
		}

		// add the default weapon for creatures
		if (isCreature()) {
			weapons.add(defaultWeapon);
		}
	}

	if (defaultWeapon != NULL) {
		// set the damage of the default weapon
		defaultWeapon->setMinDamage(minDmg);
		defaultWeapon->setMaxDamage(maxDmg);
		defaultWeapon->setAttackSpeed(speed);
	}

	int ham;
	baseHAM.removeAll();

	for (int i = 0; i < 9; ++i) {
		if (i % 3 == 0) {
			ham = System::random(npcTemplate->getBaseHAMmax() - npcTemplate->getBaseHAM()) + npcTemplate->getBaseHAM();
			baseHAM.add(ham);
		} else
			baseHAM.add(ham/100);
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

	if(npcTemplate->getGenerateRandomName())//generateRandomName
	{
		NameManager* nm = server->getNameManager();
		if(npcTemplate->getUseOnlyRandomName())
		{
			setCustomObjectName(nm->makeCreatureName(npcTemplate->getHasLastName()), false);
		}
		else
		{
			String newName = nm->makeCreatureName(npcTemplate->getHasLastName());
			newName += " (";
			newName += StringIdManager::instance()->getStringId(objectName.getFullPath().hashCode()).toString();
			StringIdManager::instance()->getStringId(objectName.getFullPath().hashCode()).toString();
			newName += ")";
			setCustomObjectName(newName, false);
		}
	}
	else// if(templateData->getCustomName().count != 0)//not nessicary.
	{
		setCustomObjectName(templateData->getCustomName(), false);
	}


	setHeight(templateData->getScale(), false);

	String currentLogName = getLoggingName();

	if (!currentLogName.contains(npcTemplate->getTemplateName())) {
		StringBuffer logName;
		logName << getLoggingName() << "[" << npcTemplate->getTemplateName() << "]";

		setLoggingName(logName.toString());
	}

	String pvpFaction = npcTemplate->getPvpFaction();

	if (!pvpFaction.isEmpty() && (pvpFaction == "imperial" || pvpFaction == "rebel")) {
		setFaction(pvpFaction.hashCode());
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

						ManagedReference<TangibleObject*> tano = (server->getZoneServer()->createObject(templ.hashCode(), 0)).castTo<TangibleObject*>();

						if (tano != NULL) {
							VectorMap<String, uint8>* cust = obj->getCustomizationVariables();

							for (int j = 0; j < cust->size(); ++j) {
								tano->setCustomizationVariable(cust->elementAt(j).getKey(), cust->elementAt(j).getValue());
							}

							transferObject(tano, 4, false);
						}

					}
				}
			} else {
				error("null outfit group " + outfit);
			}
		}
	}
}

void AiAgentImplementation::setLevel(int lvl, bool randomHam) {
	if (lvl == 0)
		return;

	CreatureObjectImplementation::setLevel(lvl);

	level = lvl;

	if (npcTemplate == NULL) {
		return;
	}

	int baseLevel = npcTemplate->getLevel();

	if (baseLevel == lvl)
		return;

	float minDmg = calculateAttackMinDamage(baseLevel);
	float maxDmg = calculateAttackMaxDamage(baseLevel);
	float speed = calculateAttackSpeed(lvl);

	Reference<WeaponObject*> defaultWeapon = getSlottedObject("default_weapon").castTo<WeaponObject*>();

	float ratio = ((float)lvl) / (float)baseLevel;

	minDmg *= ratio;
	maxDmg *= ratio;

	for (int i = 0; i < weapons.size(); ++i) {
		WeaponObject* weao = weapons.get(i);

		weao->setMinDamage(minDmg * 0.5);
		weao->setMaxDamage(maxDmg * 0.5);
		weao->setAttackSpeed(speed);
	}

	if (defaultWeapon != NULL) {
		defaultWeapon->setMinDamage(minDmg);
		defaultWeapon->setMaxDamage(maxDmg);
		defaultWeapon->setAttackSpeed(speed);
	}

	int baseHamMax = ((float)npcTemplate->getBaseHAMmax()) * ratio;
	int baseHam = ((float)npcTemplate->getBaseHAM()) * ratio;

	int ham;

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

	aiInterfaceComponents.add(ComponentManager::instance()->getComponent<AiDefaultComponent*>("AiDefaultComponent"));

}

void AiAgentImplementation::notifyPositionUpdate(QuadTreeEntry* entry) {
	for (int i = 0; i < aiInterfaceComponents.size(); i++) {
		AiInterfaceComponent* interface = aiInterfaceComponents.get(i);
		interface->notifyPositionUpdate(_this.getReferenceUnsafeStaticCast(), entry);
	}

	CreatureObjectImplementation::notifyPositionUpdate(entry);
}

void AiAgentImplementation::doAwarenessCheck(Coordinate& start, uint64 time, CreatureObject* target) {
	for (int i = 0; i < aiInterfaceComponents.size(); i++) {
		AiInterfaceComponent* interface = aiInterfaceComponents.get(i);
		interface->doAwarenessCheck(_this.getReferenceUnsafeStaticCast(), start, time, target);
	}
}

void AiAgentImplementation::doRecovery() {
	if (isDead() || getZone() == NULL)
		return;

	activateHAMRegeneration();
	activateStateRecovery();
	activatePostureRecovery();

	if (damageOverTimeList.hasDot() && damageOverTimeList.isNextTickPast()) {
		damageOverTimeList.activateDots(_this.get());
	}

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
	if (npcTemplate == NULL || npcTemplate->getAttacks() == NULL) {
		selectDefaultAttack();
		return;
	}

	CreatureAttackMap* attackMap = npcTemplate->getAttacks();
	selectSpecialAttack(attackMap->getRandomAttackNumber());
}

void AiAgentImplementation::selectSpecialAttack(int attackNum) {
	if (npcTemplate == NULL || npcTemplate->getAttacks() == NULL) {
		selectDefaultAttack();
		return;
	}

	CreatureAttackMap* attackMap = npcTemplate->getAttacks();

	if (attackNum >= 0 && attackNum < attackMap->size()) {
		String args = attackMap->getArguments(attackNum);
		nextActionCRC = attackMap->getCommand(attackNum).hashCode();
		nextActionArgs = attackMap->getArguments(attackNum);
	} else
		selectDefaultAttack();
}

void AiAgentImplementation::selectDefaultAttack() {
	if (npcTemplate == NULL)
		nextActionCRC = String("defaultattack").hashCode();
	else
		nextActionCRC = npcTemplate->getDefaultAttack().hashCode();

	nextActionArgs = "";
}

void AiAgentImplementation::enqueueAttack() {
	if (followObject != NULL) {
		enqueueCommand(nextActionCRC, 0, followObject->getObjectID(), nextActionArgs);
		nextActionCRC = 0;
		nextActionArgs = "";
	}
}

bool AiAgentImplementation::validateStateAttack() {
	if (followObject == NULL || !followObject->isCreatureObject())
		return false;

	return validateStateAttack(cast<CreatureObject*>(followObject.get()), nextActionArgs);
}

SceneObject* AiAgentImplementation::getTargetFromMap() {
	CreatureObject* target = getThreatMap()->getHighestThreatCreature();

	if (target != NULL && !defenderList.contains(target) && (!target->isDead() && !target->isIncapacitated()) && target->getDistanceTo(_this.get()) < 128.f && target->isAttackableBy(_this.get()) && lastDamageReceived.miliDifference() < 20000)
		addDefender(target);
	else if (target != NULL && defenderList.contains(target) && (target->isDead() || target->isIncapacitated() || !target->isInRange(_this.get(), 128) || !target->isAttackableBy(_this.get()))) {
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
				CreatureObject* targetCreature = cast<CreatureObject*>(tarObj);

				if (!targetCreature->isDead() && !targetCreature->isIncapacitated() && targetCreature->getDistanceTo(_this.get()) < 128.f && targetCreature->isAttackableBy(_this.get())) {
					target = targetCreature;

					break;
				} else {
					// if the object on the defender list is no longer attackable, remove it
					removeDefender(targetCreature);
				}
			} else if (tarObj != NULL && tarObj->isTangibleObject()) {
				TangibleObject* targetTano = cast<TangibleObject*>(tarObj);

				if (!targetTano->isDestroyed() && targetTano->getDistanceTo(_this.get()) < 128.f && targetTano->isAttackableBy(_this.get())) {
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
	if (followObject == NULL)
		return false;

	if (!followObject->isInRange(_this.get(), 128))
		return false;

	if (followObject->isCreatureObject() && (!cast<CreatureObject*>(followObject.get())->isAttackableBy(_this.get()) || cast<CreatureObject*>(followObject.get())->isDead() || cast<CreatureObject*>(followObject.get())->isIncapacitated()))
		return false;

	if (followObject->isTangibleObject() && (!cast<TangibleObject*>(followObject.get())->isAttackableBy(_this.get()) || cast<TangibleObject*>(followObject.get())->isDestroyed()))
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
			player->executeObjectControllerAction(String("loot").hashCode(), getObjectID(), "");

			return 0;
		case 36:
			getZoneServer()->getPlayerManager()->lootAll(player, _this.get());

			return 0;
		}
	}

	return CreatureObjectImplementation::handleObjectMenuSelect(player, selectedID);
}

void AiAgentImplementation::selectWeapon() {
	float dist = 5.f;

	if (followObject != NULL)
		dist = getDistanceTo(followObject.get());

	float diff = 1024.f;
	WeaponObject* finalWeap = getWeapon();

	for (int i = 0; i < weapons.size(); ++i) {
		WeaponObject* weap = weapons.get(i);

		float range = abs(weap->getIdealRange() - dist);

		if (range < diff) {
			diff = range;
			finalWeap = weap;
		}
	}

	ManagedReference<WeaponObject*> currentWeapon = getWeapon();
	ManagedReference<WeaponObject*> defaultWeapon = getSlottedObject("default_weapon").castTo<WeaponObject*>();

	// TODO (dannuic): this is an awful way to randomly not have a weapon. It would be far better to randomize the weapons vector on load in (based on some chance in the template lua)
/*	if ((dist < 6) && (finalWeap->isRangedWeapon() || (finalWeap->isMeleeWeapon() && System::random(10) == 0))) {
		float range = fabs(defaultWeapon->getIdealRange() - dist);

		if (range < diff) {
			finalWeap = defaultWeapon;
		}
	}*/

	if (currentWeapon != finalWeap) {
		if (currentWeapon != NULL && currentWeapon != defaultWeapon) {
			currentWeapon->destroyObjectFromWorld(false);

			//info("removed weapon " + currentWeapon->getDisplayedName(), true);
		}

		if (finalWeap != defaultWeapon) {

			//info("selected weapon " + finalWeap->getDisplayedName(), true);

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

bool AiAgentImplementation::validateStateAttack(CreatureObject* target, String& args) {
	StringTokenizer tokenizer(args);
	tokenizer.setDelimeter(";");

	while (tokenizer.hasMoreTokens()) {
		String singleArg;
		tokenizer.getStringToken(singleArg);

		if (singleArg.indexOf("Chance") != -1) {
			String stateName = singleArg.subString(0, args.indexOf("Chance"));
			uint64 state = CreatureState::instance()->getState(stateName);
			if (target->hasState(state) || (stateName == "postureDown" && target->isProne()) || (stateName == "knockdown" && target->isKnockedDown()) || (stateName == "postureUp" && target->isStanding())) {
				return false;

			}
		}
	}

	return true;
}

void AiAgentImplementation::setDespawnOnNoPlayerInRange(bool val) {
	if (despawnOnNoPlayerInRange == val)
		return;

	despawnOnNoPlayerInRange = val;

	if (val && numberOfPlayersInRange <= 0) {
		if (despawnEvent == NULL) {
			despawnEvent = new DespawnCreatureOnPlayerDissappear(_this.get());
		}

		if (!despawnEvent->isScheduled())
			despawnEvent->schedule(30000);
	}
}

bool AiAgentImplementation::tryRetreat() {
	return false;
	//TODO: fix this

	try {

		if(homeLocation.isInRange(_this.get(), 1.5))
			return false;

		if (homeLocation.getPositionX() == 0 && homeLocation.getPositionY() == 0 && homeLocation.getPositionZ() == 0)
			return false;

		CombatManager::instance()->forcePeace(_this.get());

		Locker locker(&targetMutex);

		setOblivious();

		//showFlyText("npc_reaction/flytext", "afraid", 0xFF, 0, 0);

		homeLocation.setReached(false);

		if (threatMap != NULL)
			threatMap->removeAll();

		patrolPoints.add(0, homeLocation);

		activateMovementEvent();
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

	return true;
}

void AiAgentImplementation::setDefender(SceneObject* defender) {
	setFollowObject(defender);

	CreatureObjectImplementation::setDefender(defender);

	if (isRetreating())
		homeLocation.setReached(true);

	activateRecovery();
}

void AiAgentImplementation::queueDizzyFallEvent() {
	if (System::random(10) == 1)
		CreatureObjectImplementation::queueDizzyFallEvent();
}

void AiAgentImplementation::addDefender(SceneObject* defender) {
	if (defenderList.size() == 0 && defender != NULL) {
		showFlyText("npc_reaction/flytext", "threaten", 0xFF, 0, 0);
		setFollowObject(defender);
	} else if (followState <= STALKING) {
		followState = FOLLOWING;
	}

	CreatureObjectImplementation::addDefender(defender);

	activateRecovery();
}

void AiAgentImplementation::removeDefender(SceneObject* defender) {
	CreatureObjectImplementation::removeDefender(defender);

	if (defender == NULL)
		return;

	if (defender->isCreatureObject())
		getThreatMap()->dropDamage(cast<CreatureObject*>(defender));

	if (followObject == defender) {
		CreatureObject* target = getThreatMap()->getHighestThreatCreature();

		if (target == NULL && defenderList.size() > 0) {
			SceneObject* tarObj = defenderList.get(0);
			if (tarObj != NULL && tarObj->isCreatureObject())
				target = cast<CreatureObject*>(tarObj);
		}

		if (target != NULL)
			setDefender(target);
		else
			setOblivious();
	}

	activateRecovery();
}

/**
 * Cleares the combat state
 * @pre { this object is locked }
 * @post { this object is locked, this object is not in a combat state }
 * @param clearDefenders if true the defender vector willl be emptied
 */
void AiAgentImplementation::clearCombatState(bool clearDefenders) {
	CreatureObjectImplementation::clearCombatState(clearDefenders);

	if (threatMap != NULL)
		threatMap->removeAll();

	//setOblivious();
}

void AiAgentImplementation::notifyInsert(QuadTreeEntry* entry) {
	SceneObject* scno = cast<SceneObject*>( entry);

	if (scno == _this.get())
		return;

	if (scno->isPlayerCreature()) {
		++numberOfPlayersInRange;
		activateMovementEvent();
	}
}

void AiAgentImplementation::clearDespawnEvent() {
	despawnEvent = NULL;
}

void AiAgentImplementation::respawn(Zone* zone, int level) {
	if (getZone() != NULL)
		return;

	setLevel(level);

	initializePosition(homeLocation.getPositionX(), homeLocation.getPositionZ(), homeLocation.getPositionY());

	SceneObject* cell = homeLocation.getCell();

	setNextPosition(homeLocation.getPositionX(), homeLocation.getPositionZ(), homeLocation.getPositionY());
	nextStepPosition.setPosition(homeLocation.getPositionX(), homeLocation.getPositionZ(), homeLocation.getPositionY());
	nextStepPosition.setCell(cell);

	Locker zoneLocker(zone);

	if (cell != NULL)
		cell->transferObject(_this.get(), -1);
	else
		zone->transferObject(_this.get(), -1, true);

	respawnCounter++;

	activateLoad("");
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

	for (int i = 0; i < movementMarkers.size(); ++i)
		movementMarkers.get(i)->destroyObjectFromWorld(false);

	SceneObject* creatureInventory = getSlottedObject("inventory");

	if (creatureInventory != NULL) {
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

	//_this.get()->printReferenceHolders();

	//printf("%d ref count\n", _this.get()->getReferenceCount());

	if (homeObject != NULL) {
		homeObject->notifyObservers(ObserverEventType::CREATUREDESPAWNED, _this.get());
		return;
	}

	if (respawnTimer == 0) {
		//zone->getCreatureManager()->addToReservePool(_this.get());
		return;
	}

	float respawn = respawnTimer * 1000;

	if (randomRespawn) {
		respawn = System::random(respawn) + (respawn / 2.f);
	}

	Reference<Task*> task = new RespawnCreatureTask(_this.get(), zone, level);
	task->schedule(respawn);
}

void AiAgentImplementation::scheduleDespawn(int timeToDespawn) {
	if (getPendingTask("despawn") != NULL)
		return;

	Reference<DespawnCreatureTask*> despawn = new DespawnCreatureTask(_this.get());
	addPendingTask("despawn", despawn, timeToDespawn * 1000);
}

void AiAgentImplementation::notifyDissapear(QuadTreeEntry* entry) {
	SceneObject* scno = cast<SceneObject*>( entry);

	if (scno == _this.get())
		return;

	if (entry == followObject.get())
		setFollowObject(NULL);

	if (scno->isPlayerCreature()) {
		if ((--numberOfPlayersInRange <= 0)  && despawnOnNoPlayerInRange && (despawnEvent == NULL) && !isPet()) {
			despawnEvent = new DespawnCreatureOnPlayerDissappear(_this.get());
			despawnEvent->schedule(30000);
		}

		activateMovementEvent();
	}
}

void AiAgentImplementation::activateAwarenessEvent(CreatureObject *target) {

#ifdef DEBUG
	info("Starting activateAwarenessEvent check", true);
#endif
	Locker locker(&awarenessEventMutex);

	if (awarenessEvent == NULL) {
		awarenessEvent = new AiAwarenessEvent(_this.get(), target);

		awarenessEvent->schedule(1000);

#ifdef DEBUG
		info("Scheduling new Awareness Event", true);
#endif
	}

	if (!awarenessEvent->isScheduled()) {
		awarenessEvent->setTarget(target);
		awarenessEvent->schedule(1000);

#ifdef DEBUG
		info("Rescheduling awareness event", true);
#endif
	}
}

void AiAgentImplementation::activateRecovery() {
	if (thinkEvent == NULL) {
		thinkEvent = new AiThinkEvent(_this.get());

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
	if (followObject == NULL)
		return;

	faceObject(followObject);

	if (!nextStepPosition.isReached()) {
		broadcastNextPositionUpdate(&nextStepPosition);
	} else {
		++movementCounter;

		if (parent != NULL && getParent().get()->isCellObject())
			updateZoneWithParent(getParent().get(), true, true);
		else
			updateZone(true, true);
	}
}

bool AiAgentImplementation::findNextPosition(float maxDistance, bool walk) {
	Locker locker(&targetMutex);

	Vector3 thisWorldPos = getWorldPosition();
	WorldCoordinates* nextPosition = new WorldCoordinates();

	//ManagedReference<SceneObject*> strongFollow = followObject.get();

	float newSpeed = runSpeed * 1.5f; // FIXME (dannuic): Why is this *1.5? Is that some magic number?
	if (walk && !(isRetreating() || isFleeing()))
		newSpeed = walkSpeed;

	if(hasState(CreatureState::IMMOBILIZED))
		newSpeed = newSpeed / 2.f;

	if(hasState(CreatureState::FROZEN))
		newSpeed = 0.01f;

	float updateTicks = float(UPDATEMOVEMENTINTERVAL) / 1000.f;
	//currentSpeed = newSpeed;

	newSpeed *= updateTicks; // now newSpeed is the distance able to travel in time updateTicks

	float newPositionX = 0, newPositionZ = 0, newPositionY = 0;
	PathFinderManager* pathFinder = PathFinderManager::instance();
	//float maxDist = MIN(maxDistance, newSpeed);
	float maxDist = newSpeed;

	bool found = false;
	float dist = 0;
	float dx = 0, dy = 0;
	ManagedReference<SceneObject*> cellObject;
	Zone* zone = getZone();

#ifdef SHOW_WALK_PATH
	CreateClientPathMessage* pathMessage = new CreateClientPathMessage();
	if (getParent() == NULL) {
		pathMessage->addCoordinate(getPositionX(), getZone()->getHeight(getPositionX(), getPositionY()), getPositionY());
	} else {
		pathMessage->addCoordinate(getPositionX(), getPositionZ(), getPositionY());
	}
#endif

	// setNextPosition will add a point to patrolPoints (at the beginning)
	while (!found && patrolPoints.size() != 0) {
		// the first position in patrolPoints is where we want to move to
		PatrolPoint* targetPosition = &patrolPoints.get(0);
		Reference<SceneObject*> targetCoordinateCell = targetPosition->getCell();

		if (targetPosition->getCell() == NULL && zone != NULL) {
			// We are not in a cell, so we need to calculate which Z we want to move to
			PlanetManager* planetManager = zone->getPlanetManager();

			targetMutex.unlock();

			IntersectionResults intersections;
			CollisionManager::getWorldFloorCollisions(targetPosition->getPositionX(), targetPosition->getPositionY(), zone, true, &intersections, (CloseObjectsVector*) this->getCloseObjects());
			targetPosition->setPositionZ(planetManager->findClosestWorldFloor(targetPosition->getPositionX(), targetPosition->getPositionY(), targetPosition->getPositionZ(), this->getSwimHeight(), &intersections, (CloseObjectsVector*) this->getCloseObjects()));

			targetMutex.lock();
		}

		Reference<Vector<WorldCoordinates>* > path;

		if (targetCoordinateCell != NULL && dynamic_cast<CellObject*>(targetCoordinateCell.get())) {
			// If we are in a cell, we can't just blindly use our pathFinder
			if (targetCellObject == targetCoordinateCell && currentFoundPath != NULL) {
				// We have previously found a path into the same target cell that we want to move into
				Vector<Triangle*>* nodes = NULL;

				if (targetCellObject == parent.get()) {
					// the target cell is our current cell
					CellObject* cell = dynamic_cast<CellObject*>(targetCoordinateCell.get());

					FloorMesh* floor = PathFinderManager::getFloorMesh(cell);

					pathFinder->getFloorPath(getPosition(), targetPosition->getCoordinates().getPoint(), floor, nodes);
				}

				if (nodes == NULL) {
					// there are no nodes from the pathFinder result, so put our current position at the beginning of the path
					WorldCoordinates curr(_this.get().get());
					path = currentFoundPath;

					path->set(0, curr);
				} else {
					// we have an actual path, so we have work to do
					delete nodes;

					if (currentFoundPath->get(currentFoundPath->size() - 1).getWorldPosition().distanceTo(targetPosition->getCoordinates().getWorldPosition()) > 3) {
						// Our target is far away, so we will need a new path with a new position in the first spot
						path = currentFoundPath = static_cast<CurrentFoundPath*>(pathFinder->findPath(_this.get().get(), targetPosition->getCoordinates()));
						targetCellObject = targetCoordinateCell.get();
					} else {
						// Our target is close, so our path begins where we are standing
						WorldCoordinates curr(_this.get().get());
						path = currentFoundPath;

						path->set(0, curr);
					}
				}
			} else {
				// our target cell is different than our current target's cell, so we need to automatically re-calculate the path (and we don't need to include our current location)
				path = currentFoundPath = static_cast<CurrentFoundPath*>(pathFinder->findPath(_this.get().get(), targetPosition->getCoordinates()));
				targetCellObject = targetCoordinateCell.get();
			}
		} else {
			// we are outside, just find a path, and set our calculation variables for cells to NULL
			path = pathFinder->findPath(_this.get().get(), targetPosition->getCoordinates());
			targetCellObject = NULL;
			currentFoundPath = NULL;
		}

		if (path == NULL) {
			// we weren't able to find a path, so remove this location from patrolPoints and try again with the next one
			PatrolPoint oldPoint = patrolPoints.remove(0);

			continue;
		}

		// Get rid of duplicate/invalid points in path
		pathFinder->filterPastPoints(path, _this.get().get());

		WorldCoordinates* oldCoord = NULL;
		float pathDistance = 0;

		bool remove = true;

		float targetDistance = targetPosition->getWorldPosition().distanceTo(getWorldPosition());

		if (targetDistance > maxDistance) // target position if farther away than the "radius" of approach
			maxDist = MIN(newSpeed, targetDistance - maxDistance);
		else { // we are already where we need to be, so we have no new position
			//activateMovementEvent();
			if (followState == AiAgent::PATROLLING) {
				PatrolPoint oldPoint = patrolPoints.remove(0);
			}

			if (isRetreating())
				homeLocation.setReached(true);

			if (isFleeing())
				fleeing = false;

			if (followObject == NULL)
				notifyObservers(ObserverEventType::DESTINATIONREACHED);

			currentSpeed = 0;

			if (followObject != NULL && !(isRetreating() || isFleeing()))
				checkNewAngle();

			return false;
		}

		for (int i = 1; i < path->size() && !found; ++i) { // i = 0 is our position
			// path cannot be empty, we must at least have our current position in it
			WorldCoordinates* coord = &path->get(i); // FIXME (dannuic): why don't we just directly use nextPosition? it will be set to this right before it ends anyway

			Vector3 nextWorldPos = coord->getWorldPosition();

#ifdef SHOW_WALK_PATH
			if (coord->getCell() == NULL)
				pathMessage->addCoordinate(nextWorldPos.getX(), getZone()->getHeight(nextWorldPos.getX(), nextWorldPos.getY()), nextWorldPos.getY());
			else
				pathMessage->addCoordinate(nextWorldPos.getX(), nextWorldPos.getZ(), nextWorldPos.getY());
#endif

			if (oldCoord == NULL) {
				// this is the first time through the loop, so set our previous position
				oldCoord = &path->get(0);
			}

			pathDistance += oldCoord->getWorldPosition().distanceTo(nextWorldPos);

			if (i == path->size() - 1 || pathDistance >= maxDist || coord->getCell() != parent.get()) {
				// This is the last point, or as far as we can go in one time step, or our target is in a different cell
				// this will always be called at least once, so nextPosition will get set
				cellObject = coord->getCell();

				dist = nextWorldPos.distanceTo(thisWorldPos);

				*nextPosition = *coord;
				found = true;

				if ((dist <= maxDistance && cellObject == parent.get())) {
					// we are within our "radius" of approach of the current point, so we don't need to move
					if (i == path->size() - 1) {
						// this is the last point in the path to the patrolPoint
						PatrolPoint oldPoint = patrolPoints.remove(0);
						// make sure the patrolPoint doesn't get removed twice (removing a new target position)
						remove = false;
					}

					found = false;
				} else {
					//lets convert source and target coordinates to model or world space
					Vector3 oldCoordinates = oldCoord->getPoint();

					if (coord->getCell() != NULL) { // target coord in cell
						if (oldCoord->getCell() == NULL)  // old coord not in cell -- convert old coord to model space
							oldCoordinates = PathFinderManager::transformToModelSpace(oldCoord->getPoint(), coord->getCell()->getParent().get());

					} else { // target coord in world
						oldCoordinates = oldCoord->getWorldPosition();
					}

					if (pathDistance > maxDist) {
						// this is farther than we can go in one timestep
						Vector3 oldWorldCoord = oldCoord->getWorldPosition();

						dist = oldWorldCoord.distanceTo(nextWorldPos);

						float distanceToTravel = dist - (pathDistance - maxDist);

						if (distanceToTravel <= 0) {
							// Stop here because we can get to this point in one time step
							newPositionX = nextPosition->getX();
							newPositionY = nextPosition->getY();
						} else {
							//float rest = Math::sqrt(distanceToTravel);

							float rest = distanceToTravel;

							//dist = Math::sqrt(dist);

							if (dist != 0 && !isnan(dist)) {
								// calculate how far between the points we can get, and set that as the new position
								dx = nextPosition->getX() - oldCoordinates.getX();
								dy = nextPosition->getY() - oldCoordinates.getY();

								newPositionX = oldCoordinates.getX() + (rest * (dx / dist));// (newSpeed * (dx / dist));
								newPositionY = oldCoordinates.getY() + (rest * (dy / dist)); //(newSpeed * (dy / dist));
							} else {
								// failsafe if dist is somehow 0 (or nan), which is basically only when pathDistance == maxDist
								newPositionX = nextPosition->getX();
								newPositionY = nextPosition->getY();
							}
						}

						// Now do cell checks to get the Z coordinate outside or inside
						if (nextPosition->getCell() == NULL) {
							

							if (zone != NULL) {
								targetMutex.unlock();

								IntersectionResults intersections;
								CollisionManager::getWorldFloorCollisions(newPositionX, newPositionY, zone, true, &intersections, (CloseObjectsVector*) this->getCloseObjects());
								newPositionZ = zone->getPlanetManager()->findClosestWorldFloor(newPositionX, newPositionY, targetPosition->getPositionZ(), this->getSwimHeight(), &intersections, (CloseObjectsVector*) this->getCloseObjects());

								targetMutex.lock();
							}
							//newPositionZ = nextPosition.getZ();
						} else {
							newPositionZ = nextPosition->getZ();
						}
					} else {
						// we can get this far in one timestep, set the next position and see if we can get to the next point
						//info("setting nextPosition point", true);
						newPositionX = nextPosition->getX();
						newPositionY = nextPosition->getY();
						newPositionZ = nextPosition->getZ();
					}
#ifdef SHOW_NEXT_POSITION
					if (showNextMovementPosition) {
						for (int i = 0; i < movementMarkers.size(); ++i)
							movementMarkers.get(i)->destroyObjectFromWorld(false);

						movementMarkers.removeAll();

						Reference<SceneObject*> movementMarker = getZoneServer()->createObject(String("object/path_waypoint/path_waypoint.iff").hashCode(), 0);

						movementMarker->initializePosition(newPositionX, newPositionZ, newPositionY);
						StringBuffer msg;
						msg << "Next Position: path distance: " << pathDistance << " maxDist:" << maxDist;
						movementMarker->setCustomObjectName(msg.toString(), false);

						if (cellObject != NULL) {
							cellObject->transferObject(movementMarker, -1, true);
						} else {
							getZone()->transferObject(movementMarker, -1, false);
						}

						movementMarkers.add(movementMarker);

						for (int i = 0; i < path->size(); ++i) {
							WorldCoordinates* coord = &path->get(i);
							SceneObject* coordCell = coord->getCell();

							movementMarker = getZoneServer()->createObject(String("object/path_waypoint/path_waypoint.iff").hashCode(), 0);
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
			}

			oldCoord = coord;
		}

		if (!found && remove) {
			// we were not able to find the next point to head to, and we haven't popped patrolPoints yet
			PatrolPoint oldPoint = patrolPoints.remove(0);
		}
	}

#ifdef SHOW_WALK_PATH
	broadcastMessage(pathMessage, false);
#endif

	nextPosition->setX(newPositionX);
	nextPosition->setY(newPositionY);
	nextPosition->setZ(newPositionZ);
	nextPosition->setCell(cellObject);

	if (found) {
		// Set the next place we will be -- requires that we have found a destination
		nextStepPosition.setPosition(nextPosition->getX(), nextPosition->getZ(), nextPosition->getY());
		nextStepPosition.setCell(nextPosition->getCell());

		nextStepPosition.setReached(false);
		Vector3 thisPos = getPosition();

		float directionangle = atan2(nextStepPosition.getPositionX() - thisPos.getX(), nextStepPosition.getPositionY() - thisPos.getY());

		if (directionangle < 0) {
			float a = M_PI + directionangle;
			directionangle = M_PI + a;
		}

		float err = fabs(directionangle - direction.getRadians());

		if (err >= 0.05)
			direction.setHeadingDirection(directionangle);

		// Tell the clients where to expect us next tick -- requires that we have found a destination
		broadcastNextPositionUpdate(&nextStepPosition);

		currentSpeed = MAX(0.1, nextStepPosition.getWorldPosition().distanceTo(getWorldPosition()) / ((float)UPDATEMOVEMENTINTERVAL / 1000.f));
	} else {
		if (isRetreating())
			homeLocation.setReached(true);

		if (isFleeing())
			fleeing = false;

		if (followObject == NULL)
			notifyObservers(ObserverEventType::DESTINATIONREACHED);

		currentSpeed = 0;
	}

	if (!(isRetreating() || isFleeing()))
		checkNewAngle();

	delete nextPosition;

	updateLocomotion();
	//activateMovementEvent();

	return found;
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
	patrolPoints.removeAll();

	for (int i = 0; i < num; i++) {
		PatrolPoint newPoint;
		newPoint.setPositionX(homeLocation.getPositionX() + (-1 * dist + (float)System::random((unsigned int)dist * 2)));
		newPoint.setPositionY(homeLocation.getPositionY() + (-1 * dist + (float)System::random((unsigned int)dist * 2)));
		newPoint.setPositionZ(homeLocation.getPositionZ());
		if (parent != NULL && getParent().get()->isCellObject()) {
			newPoint.setCell(getParent().get());
		}

		if (newPoint.getCell() == NULL && zone != NULL) {
			PlanetManager* planetManager = zone->getPlanetManager();
			IntersectionResults intersections;
			CollisionManager::getWorldFloorCollisions(newPoint.getPositionX(), newPoint.getPositionY(), zone, true, &intersections, (CloseObjectsVector*) this->getCloseObjects());
			newPoint.setPositionZ(planetManager->findClosestWorldFloor(newPoint.getPositionX(), newPoint.getPositionY(), newPoint.getPositionZ(), this->getSwimHeight(), &intersections, (CloseObjectsVector*) this->getCloseObjects()));
		}

		patrolPoints.add(newPoint);
	}

	if (patrolPoints.size() > 0) {
		followState = AiAgent::PATROLLING;
		return true;
	}

	return false;
}

float AiAgentImplementation::getMaxDistance() {
	if (isRetreating() || isFleeing()) // TODO (dannuic): this should end up as logic in BT luas
		return 0.5;

	switch (followState) {
	case AiAgent::PATROLLING:
		return 0.5;
		break;
	case AiAgent::STALKING:
		return 25;
		break;
	case AiAgent::FOLLOWING:
		// stop in weapons range
		if (followObject != NULL && !CollisionManager::checkLineOfSight(_this.get(), followObject)) {
			return 0.5;
		} else if (getWeapon() != NULL ) {
			float weapMaxRange = MIN(getWeapon()->getIdealRange(), getWeapon()->getMaxRange());
			return MAX(0.5, weapMaxRange - 2);
		}
		break;
	}

	return 5.f;
}

int AiAgentImplementation::setDestination() {
	switch (followState) { // TODO (dannuic): Move all or most of this to BT luas
	case AiAgent::OBLIVIOUS:
		if (followObject)
			setOblivious();

		if (!homeLocation.isInRange(_this.get(), 1.5)) {
			homeLocation.setReached(false);
			clearPatrolPoints();
			addPatrolPoint(homeLocation);
		} else {
			homeLocation.setReached(true);
			clearPatrolPoints();
		}

		break;
	case AiAgent::PATROLLING:
		break;
	case AiAgent::WATCHING:
		if (followObject == NULL) {
			setOblivious();
			return setDestination();
		}

		setNextPosition(getPositionX(), getPositionZ(), getPositionY(), getParent().get()); // sets patrolPoints[0] to current position
		checkNewAngle(); // sends update zone packet
		if (patrolPoints.size() > 0)
			updateCurrentPosition(&patrolPoints.get(0));
		break;
	case AiAgent::STALKING:
	case AiAgent::FOLLOWING:
		if (followObject == NULL) {
			setOblivious();
			return setDestination();
		}

		clearPatrolPoints();
		setNextPosition(followObject->getPositionX(), followObject->getPositionZ(), followObject->getPositionY(), followObject->getParent().get());
		break;
	default:
		setOblivious();
		break;
	}

	//activateMovementEvent();

	return patrolPoints.size();
}

bool AiAgentImplementation::completeMove() {
	updateCurrentPosition(&nextStepPosition);
	nextStepPosition.setReached(true);
	return true;
}

bool AiAgentImplementation::isScentMasked(CreatureObject* target) {
	return false;

	Locker locker(&targetMutex);

	// Check masked scent
	if (!target->hasState(CreatureState::MASKSCENT)) {
		if(camouflagedObjects.contains(target)) camouflagedObjects.removeElement(target);
		return false;
	}

	// Don't do anything if object is ignored (Camo / Masked Scent)
	if (camouflagedObjects.contains(target))
		return true;

	int camoSkill = target->getSkillMod("mask_scent");
	int creatureLevel = getLevel();

	bool success = false;

	if (System::random(100) <= (-1 * (1 / ((camoSkill / 100.0f) * 20)) * creatureLevel) + 100) {
		camouflagedObjects.add(target);
		success = true;
	}

	Reference<Task*> ct = new CamoTask(target, _this.get(), true, success);
	ct->execute();

	return success;
}

bool AiAgentImplementation::isConcealed(CreatureObject* target) {
	return false;

	Locker locker(&targetMutex);

	if (!target->hasState(CreatureState::MASKSCENT)) {
		if(camouflagedObjects.contains(target)) camouflagedObjects.removeElement(target);
		return false;
	}

	// Don't do anything if object is ignored (Camo / Masked Scent)
	if (camouflagedObjects.contains(target))
		return true;

	// Check if camo breaks
	int camoSkill = target->getSkillMod("private_conceal");
	int creatureLevel = getLevel();

	if (!isCreature())
		creatureLevel *= 2;

	bool success = false;

	if (System::random(100) < (-1 * (1 / ((camoSkill / 100.0f) * 20)) * creatureLevel) + 100) {
		camouflagedObjects.add(target);
		success = true;
	}

	Reference<Task*> ct = new CamoTask(target, _this.get(), false, success);
	ct->execute();

	return success;
}

void AiAgentImplementation::activateMovementEvent() {
	if (getZone() == NULL)
		return;

	Locker locker(&movementEventMutex);

	if (isWaiting() && moveEvent != NULL)
		moveEvent->cancel();

	if ((waitTime < 0 || numberOfPlayersInRange <= 0) && followObject == NULL && !isRetreating()) {
		if (moveEvent != NULL) {
			moveEvent->clearCreatureObject();
			moveEvent = NULL;
		}

		return;
	}

	if (moveEvent == NULL) {
		moveEvent = new AiMoveEvent(_this.get());

		moveEvent->schedule(waitTime > 0 ? waitTime : UPDATEMOVEMENTINTERVAL);
	}

	try {
		if (!moveEvent->isScheduled())
			moveEvent->schedule(waitTime > 0 ? waitTime : UPDATEMOVEMENTINTERVAL);
	} catch (IllegalArgumentException& e) {

	}
}

void AiAgentImplementation::activateWaitEvent() {
	if (getZone() == NULL)
		return;

	if (waitEvent == NULL) {
		waitEvent = new AiWaitEvent(_this.get());

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

void AiAgentImplementation::broadcastNextPositionUpdate(PatrolPoint* point) {
	BasePacket* msg = NULL;
	++movementCounter;

	if (point == NULL) {
		if (parent != NULL)
			msg = new UpdateTransformWithParentMessage(_this.get());
		else
			msg = new UpdateTransformMessage(_this.get());
	} else {
		if (point->getCell() != NULL)
			msg = new LightUpdateTransformWithParentMessage(_this.get(), point->getPositionX(), point->getPositionZ(), point->getPositionY(), point->getCell()->getObjectID());
		else
			msg = new LightUpdateTransformMessage(_this.get(), point->getPositionX(), point->getPositionZ(), point->getPositionY());
	}

	broadcastMessage(msg, false);
}

int AiAgentImplementation::notifyObjectDestructionObservers(TangibleObject* attacker, int condition) {
	if (isPet()) {
		PetManager* petManager = server->getZoneServer()->getPetManager();

		petManager->notifyDestruction(attacker, _this.get(), condition);

	} else {
		if (getZone() != NULL) {
			CreatureManager* creatureManager = getZone()->getCreatureManager();

			creatureManager->notifyDestruction(attacker, _this.get(), condition);
		}
	}

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
		CreatureObject* creature = cast<CreatureObject*>( attacker);

		if (damage > 0) {
			getThreatMap()->addDamage(creature, damage);

			if (System::random(5) == 1) {
				setDefender(creature);
			}
		}
	}

	return CreatureObjectImplementation::inflictDamage(attacker, damageType, damage, destroy, notifyClient);
}

int AiAgentImplementation::inflictDamage(TangibleObject* attacker, int damageType, float damage, bool destroy, const String& xp, bool notifyClient) {
	lastDamageReceived.updateToCurrentTime();

	activateRecovery();

	if (attacker->isCreatureObject()) {
		CreatureObject* creature = cast<CreatureObject*>( attacker);

		if (damage > 0) {
			getThreatMap()->addDamage(creature, damage, xp);

			if (System::random(5) == 1) {
				setDefender(creature);
			}
		}
	}

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

	if (getKinetic() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_kinetic", "100%");

	if (getEnergy() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_energy", "100%");

	if (getElectricity() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_electrical", "100%");

	if (getStun() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_stun", "100%");

	if (getBlast() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_blast", "100%");

	if (getHeat() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_heat", "100%");

	if (getCold() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_cold", "100%");

	if (getAcid() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_acid", "100%");

	if (getLightSaber() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_restraint", "100%");

	if (getKinetic() > 0 && getKinetic() < 100) {
		StringBuffer txt;
		txt << round(getKinetic()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_kinetic", txt.toString());
	}

	if (getEnergy() > 0 && getEnergy() < 100) {
		StringBuffer txt;
		txt << round(getEnergy()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_energy", txt.toString());
	}

	if (getElectricity() > 0 && getElectricity() < 100) {
		StringBuffer txt;
		txt << round(getElectricity()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_electrical", txt.toString());
	}

	if (getStun() > 0 && getStun() < 100) {
		StringBuffer txt;
		txt << round(getStun()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_stun", txt.toString());
	}

	if (getBlast() > 0 && getBlast() < 100) {
		StringBuffer txt;
		txt << round(getBlast()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_blast", txt.toString());
	}

	if (getHeat() > 0 && getHeat() < 100) {
		StringBuffer txt;
		txt << round(getHeat()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_heat", txt.toString());
	}

	if (getCold() > 0 && getCold() < 100) {
		StringBuffer txt;
		txt << round(getCold()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_cold", txt.toString());
	}

	if (getAcid() > 0 && getAcid() < 100) {
		StringBuffer txt;
		txt << round(getAcid()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_acid", txt.toString());
	}

	if (getLightSaber() > 0 && getLightSaber() < 100) {
		StringBuffer txt;
		txt << round(getLightSaber()) << "%";
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


void AiAgentImplementation::sendConversationStartTo(SceneObject* player) {
	if (!player->isPlayerCreature() || isDead() || npcTemplate == NULL || npcTemplate->getConversationTemplate() == 0)
		return;

	//Face player.
	faceObject(player);

	PatrolPoint current(coordinates.getPosition(), getParent().get());

	broadcastNextPositionUpdate(&current);

	CreatureObject* playerCreature = cast<CreatureObject*>( player);
	StartNpcConversation* conv = new StartNpcConversation(playerCreature, getObjectID(), "");
	player->sendMessage(conv);

	SortedVector<ManagedReference<Observer*> > observers = getObservers(ObserverEventType::STARTCONVERSATION);

	for (int i = 0;  i < observers.size(); ++i) {
		if (dynamic_cast<ConversationObserver*>(observers.get(i).get()) != NULL)
			return;
	}

	if (npcTemplate == NULL)
		return;
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
		return;
	}



}

bool AiAgentImplementation::isAggressiveTo(CreatureObject* target) {
	if (!isAttackableBy(target))
		return false;

	uint32 targetFaction = target->getFaction();

	PlayerObject* ghost = target->getPlayerObject();

	if (getFaction() != 0 && targetFaction != 0) {

		if (ghost == NULL && (targetFaction != getFaction()))
			return true;
		else if (ghost != NULL && (targetFaction != getFaction()) && ghost->getFactionStatus() != FactionStatus::ONLEAVE)
			return true;
	}

	String pvpFaction = getPvPFaction();

	if (!pvpFaction.isEmpty()) {
		if (target->isPlayerCreature() && ghost != NULL) {
			float targetsStanding = ghost->getFactionStanding(pvpFaction);

			if (targetsStanding <= -3000)
				return true;
			else if (targetsStanding >= 3000)
				return false;

		} else if (target->isAiAgent()) {
			AiAgent* targetAi = cast<AiAgent*>(target);

			if (targetAi != NULL) {
				if (FactionManager::instance()->isEnemy(pvpFaction, targetAi->getPvPFaction()))
					return true;
				else
					return false;
			}
		}
	}

	if (getPvpStatusBitmask() & CreatureFlag::AGGRESSIVE)
		return true;

	return false;
}

bool AiAgentImplementation::hasLoot(){
	SceneObject* inventory = getSlottedObject("inventory");

	if(inventory == NULL)
		return false;

	return inventory->getContainerObjectsSize() > 0;
}

void AiAgentImplementation::sendDefaultConversationTo(SceneObject* player) {
	/*if (!player->isPlayerCreature())
		return;

	faceObject(player);

	PatrolPoint current(coordinates.getPosition(), getParent());

	broadcastNextPositionUpdate(&current);

	CreatureObject* playerCreature = cast<CreatureObject*>( player);

	ManagedReference<PlayerObject*> ghost = playerCreature->getPlayerObject();

	if (npcTemplate != NULL) {
		uint32 convoTemplate = npcTemplate->getConversationTemplate();

		Reference<ConversationTemplate*> convo = CreatureTemplateManager::instance()->getConversationTemplate(convoTemplate);

		if (convo != NULL) {
			Reference<ConversationScreen*> initialScreen = convo->getInitialScreen();

			if (initialScreen == NULL)
				return;

			//ghost->setLastNpcConvMessStr(root->getID());

			StartNpcConversation* conv = new StartNpcConversation(playerCreature, getObjectID(), "");
			player->sendMessage(conv);

			initialScreen->sendTo(playerCreature);

			return;
		}
	}

	//player->setLastNpcConvStr(("npc_" + getFu().toString()));
	ghost->setLastNpcConvMessStr("0,init");

	StartNpcConversation* conv = new StartNpcConversation(playerCreature, getObjectID(), "");
	player->sendMessage(conv);

	String responseFile, responseAttitude;

	if (responseFile == "") {
		if (isImperial()) {
			responseFile = "npc_reaction/stormtrooper";
		} else if (isRebel()) {
			responseFile = "npc_reaction/military";
		} else {
			short file = System::random(2);
			if (file == 0)
				responseFile = "npc_reaction/fancy";
			else if (file == 1)
				responseFile = "npc_reaction/slang";
			else
				responseFile = "npc_reaction/townperson";
		}
	}

	if (responseAttitude == "") {
		short type = System::random(2);
		if (type == 0)
			responseAttitude = "mean";
		else if (type == 1)
			responseAttitude = "mid";
		else
			responseAttitude = "nice";
	}

	StringBuffer convoChoice;
	convoChoice << "hi_" <<  responseAttitude << "_" << (System::random(15) + 1);

	//TODO: Revisit NPC Conversation
	//NpcConversationMessage* initial = new NpcConversationMessage(
	//		playerCreature, responseFile, convoChoice.toString());
	//player->sendMessage(initial);

	// Parse and send the options:
	//StringList* slist = new StringList(playerCreature);

	//String test = "I'm looking for work";
	//slist->insertOption(test);

	//player->sendMessage(slist);

	//playerCreature->setLastNpcConvMessStr("chitchat");*/
}

void AiAgentImplementation::selectConversationOption(int option, SceneObject* obj) {
	/*if (!obj->isCreatureObject())
		return;

	CreatureObject* player = cast<CreatureObject*>( obj);

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	String chk = ghost->getLastNpcConvMessStr();

	if (npcTemplate != NULL) {
			uint32 convoTemplate = npcTemplate->getConversationTemplate(); //TODO: Consider storing reference to the convo on the template?

			Reference<ConversationTemplate*> convo = CreatureTemplateManager::instance()->getConversationTemplate(convoTemplate);

			if (convo != NULL) {
				Reference<ConversationScreen*> lastScreen = convo->getScreen(chk);

				if (lastScreen == NULL)
					lastScreen = convo->getInitialScreen();

				Reference<ConversationOption*> convoOption = lastScreen->getOption(option);

				if (convoOption == NULL || !convoOption->isLinked())
					return; //Stop Conversation if no option exists or this option isn't linked to another option.

				Reference<ConversationScreen*> nextScreen = convo->getScreen(convoOption->getLinkedScreenID());

				if (nextScreen == NULL)
					return; //Couldn't find the linked screen in this conversation template.

				nextScreen->sendTo(player);

				return;
			}
	}

	if (chk != "chitchat") {
		return;
	}

	UnicodeString saying = "";
	switch(System::random(5)) {
	case 0:
		saying = "Why the heck would you want to work when welfare is free.";
		break;
	case 1:
		saying = "Pfft, work in this economy?  I'm waiting for the government to bail me out.";
		break;
	case 2:
		saying = "Check the missions terminals, they are overflowing with work.";
		break;
	case 3:
		saying = "Huh, work?  Whats that?";
		break;
	case 4:
		saying = "Did you check the mission terminals?";
		break;
	case 5:
		saying = "Me too.";
		break;
	}

	NpcConversationMessage* response = new NpcConversationMessage(player, saying);
	player->sendMessage(response);

	// Parse and send the options:
	StringList* slist = new StringList(player);
	player->sendMessage(slist);*/
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

	behaviors.put("none", NULL);

	VectorMap<String, Vector<String> > parents; // id's keyed by parents
	parents.setAllowOverwriteInsertPlan();

	// first build the maps
	for (int i=0; i < treeTemplate->size(); i++) {
		LuaAiTemplate* temp = treeTemplate->get(i).get();
		if (temp == NULL) {
			error("Null AI template"); // FIXME (dannuic): Is this still happening?
			continue;
		}

		Behavior* behavior = AiMap::createNewInstance(_this.get(), temp->className, temp->classType);
		behavior->setID(temp->id);
		behaviors.put(temp->id, behavior);

		Vector<String> ids = parents.get(temp->parent);
		ids.add(temp->id);
		parents.put(temp->parent, ids);
	}

	// now set parents
	for (int i = 0; i < parents.size(); i++) {
		VectorMapEntry<String, Vector<String> > element = parents.elementAt(i);
		if (element.getKey() == "none") // this is the parent of the root node, just skip it.
			continue;

		Behavior* b = behaviors.get(element.getKey());

		if (b == NULL || !b->isComposite()) { // parent is not composite, this will probably break the tree
			error("Failed to load " + element.getKey() + " as a parent in tree: " + aiTemplate->getTemplateName());
			continue;
		}

		CompositeBehavior* par = cast<CompositeBehavior*>(b);

		Vector<String> ids = element.getValue();

		for (int j = 0; j < ids.size(); j++) {
			Behavior* child = behaviors.get(ids.get(j));

			if (child == NULL) {
				error("Failed to load " + ids.get(i) + " as a child in tree: " + aiTemplate->getTemplateName());
				continue;
			}

			addBehaviorToTree(child, par);
		}
	}

	// now tree is complete, set the root node as the current node
	Vector<String> roots = parents.get("none");
	if (roots.size() > 1) {
		error("Multiple root nodes in tree: " + aiTemplate->getTemplateName());
		return; // all References will be lost here
	} else if (roots.size() <= 0) {
		error("No root nodes in tree: " + aiTemplate->getTemplateName());
		return;
	}

	String rootString = roots.get(0);
	Behavior* rootBehavior = behaviors.get(rootString);
	if (rootBehavior == NULL) {
		error("Failed to get root instance in " + aiTemplate->getTemplateName());
		return;
	}

	setCurrentBehavior(rootString);
}

void AiAgentImplementation::setupBehaviorTree() {
	AiTemplate* getTarget = AiMap::instance()->getGetTargetTemplate(creatureBitmask);
	AiTemplate* selectAttack = AiMap::instance()->getSelectAttackTemplate(creatureBitmask);
	AiTemplate* combatMove = AiMap::instance()->getCombatMoveTemplate(creatureBitmask);
	AiTemplate* idle = AiMap::instance()->getIdleTemplate(creatureBitmask);

	setupBehaviorTree(getTarget, selectAttack, combatMove, idle);
}

void AiAgentImplementation::setupBehaviorTree(AiTemplate* getTarget, AiTemplate* selectAttack, AiTemplate* combatMove, AiTemplate* idle) {
	CompositeBehavior* rootSelector = cast<CompositeBehavior*>(AiMap::instance()->createNewInstance(_this.get(), "Composite", AiMap::SELECTORBEHAVIOR));
	CompositeBehavior* attackSequence = cast<CompositeBehavior*>(AiMap::instance()->createNewInstance(_this.get(), "Composite", AiMap::SEQUENCEBEHAVIOR));
	rootSelector->setID(String("root"));
	attackSequence->setID(String("attackSequence"));

	addBehaviorToTree(attackSequence, rootSelector);

	setupBehaviorTree(getTarget);
	addCurrentBehaviorToTree(attackSequence);

	setupBehaviorTree(selectAttack);
	addCurrentBehaviorToTree(attackSequence);

	setupBehaviorTree(combatMove);
	addCurrentBehaviorToTree(attackSequence);

	setupBehaviorTree(idle);
	addCurrentBehaviorToTree(rootSelector);

	behaviors.put("root", rootSelector);
	behaviors.put("attackSequence", attackSequence);

	resetBehaviorList();

	//info(behaviors.get(currentBehaviorID)->print(), true);
}

void AiAgentImplementation::setCurrentBehavior(const String& b) {
	currentBehaviorID = b;
	if (behaviors.get(currentBehaviorID) != NULL) {
		//activateMovementEvent();

		// This is for debugging:
/*		ZoneServer* zoneServer = ServerCore::getZoneServer();
		ChatManager* chatManager = zoneServer->getChatManager();

		chatManager->broadcastMessage(_this.get(), currentBehaviorID, 0, 0, 0);*/
	} else
		error("Null Behavior in " + currentBehaviorID);
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

		chatManager->broadcastMessage(_this.get(), String::valueOf(status), 0, 0, 0);*/
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

	currentBehaviorID = "root";
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

	currentBehaviorID = "";
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

	SortedVector<ManagedReference<QuadTreeEntry*> > closeAiAgents;

	try {
		if (closeobjects == NULL) {
			info("Null closeobjects vector in AiAgentImplementation::broadcastInterrupt", true);
			zone->getInRangeObjects(getPositionX(), getPositionY(), 192, &closeAiAgents, true);
		} else {
			closeAiAgents.removeAll(closeobjects->size(), 10);
			closeobjects->safeCopyTo(closeAiAgents);
		}
	} catch (Exception& e) {

	}

	for (int i = 0; i < closeAiAgents.size(); ++i) {
		AiAgent* agent = cast<AiAgent*>(closeAiAgents.get(i).get());

		if (_this.get() == agent || agent == NULL)
			continue;

		agent->activateInterrupt(_this.get(), msg);
	}
}

void AiAgentImplementation::setCombatState() {
	CreatureObjectImplementation::setCombatState();

	if (homeObject != NULL)
		homeObject->notifyObservers(ObserverEventType::AIMESSAGE, _this.get(), ObserverEventType::STARTCOMBAT);

	//broadcastInterrupt(ObserverEventType::STARTCOMBAT);

	activateInterrupt(_this.get(), ObserverEventType::STARTCOMBAT);
}

void AiAgentImplementation::activateInterrupt(SceneObject* source, int64 msg) {
	AiInterruptTask* task = new AiInterruptTask(_this.get(), source, msg);
	task->execute();
}

void AiAgentImplementation::activateLoad(const String& temp) {
	AiLoadTask* task = new AiLoadTask(_this.get(), temp);
	task->execute();
}
