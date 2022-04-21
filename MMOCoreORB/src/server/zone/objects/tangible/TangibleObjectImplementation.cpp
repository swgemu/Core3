/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "engine/engine.h"

#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/skill/SkillModManager.h"
#include "server/zone/packets/tangible/TangibleObjectMessage3.h"
#include "server/zone/packets/tangible/TangibleObjectMessage6.h"
#include "server/zone/packets/tangible/TangibleObjectMessage7.h"
#include "server/zone/packets/tangible/TangibleObjectDeltaMessage3.h"
#include "server/zone/packets/tangible/TangibleObjectDeltaMessage6.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "templates/SharedTangibleObjectTemplate.h"
#include "templates/params/creature/CreatureFlag.h"
#include "server/zone/packets/tangible/UpdatePVPStatusMessage.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/factorycrate/FactoryCrate.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"
#include "server/zone/Zone.h"
#include "tasks/ClearDefenderListsTask.h"
#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"
#include "templates/tangible/tool/RepairToolTemplate.h"
#include "server/zone/objects/tangible/tool/repair/RepairTool.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/tangible/tool/antidecay/AntiDecayKit.h"
#include "server/zone/objects/player/events/StoreSpawnedChildrenTask.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "templates/faction/Factions.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/chat/ChatManager.h"

void TangibleObjectImplementation::initializeTransientMembers() {
	SceneObjectImplementation::initializeTransientMembers();

	threatMap = nullptr;

	setLoggingName("TangibleObject");

	if (faction !=  Factions::FACTIONREBEL && faction != Factions::FACTIONIMPERIAL) {
		faction = 0;
	}
}

void TangibleObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	SceneObjectImplementation::loadTemplateData(templateData);

	SharedTangibleObjectTemplate* tanoData = dynamic_cast<SharedTangibleObjectTemplate*>(templateData);

	if (tanoData == nullptr)
		return;

	targetable = tanoData->getTargetable();

	maxCondition = tanoData->getMaxCondition();

	invisible = tanoData->isInvisible();

	useCount = tanoData->getUseCount();

	optionsBitmask = tanoData->getOptionsBitmask();
	pvpStatusBitmask = tanoData->getPvpStatusBitmask();

	sliceable = tanoData->getSliceable();

	jediRobe = tanoData->isJediRobe();

	faction = tanoData->getFaction();

	junkDealerNeeded = tanoData->getJunkDealerNeeded();
	junkValue = tanoData->getJunkValue();

	threatMap = nullptr;
}

void TangibleObjectImplementation::notifyLoadFromDatabase() {
	SceneObjectImplementation::notifyLoadFromDatabase();

	if (activeAreas.size() > 0) {
		TangibleObject* tano = asTangibleObject();

		for (int i = activeAreas.size() - 1; i >= 0; i--) {
			auto& area = activeAreas.get(i);

			if (!area->isNavArea()) {
				area->notifyExit(tano);
				activeAreas.remove(i);
			}
		}
	}

	if (hasAntiDecayKit()) {
		AntiDecayKit* adk = antiDecayKitObject.castTo<AntiDecayKit*>();

		if (adk != nullptr) {
			if (!adk->isUsed()) {
				Locker locker(adk);
				adk->setUsed(true);
			}

			auto strongAdkParent = adk->getParent().get();

			if (strongAdkParent != nullptr) {
				error()
					<< "oid: " << getObjectID()
					<< " has AntiDecayKit(" << adk->getObjectID()
					<< ") with parent: " << strongAdkParent->getObjectID()
					<< ", removing from world."
					;
				Locker lock(adk);
				adk->destroyObjectFromWorld(true);
			}
		}
	}
}

void TangibleObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	if (hasAntiDecayKit()) {
		AntiDecayKit* adk = antiDecayKitObject.castTo<AntiDecayKit*>();

		if (adk != nullptr) {
			auto strongAdkParent = adk->getParent().get();
			error()
				<< "destroyObjectFromDatabase oid: " << getObjectID()
				<< " has AntiDecayKit(" << adk->getObjectID()
				<< ") with parent: " << (strongAdkParent != nullptr ? strongAdkParent->getObjectID() : 0)
				<< ", removing adk from database."
				;
			Locker lock(adk);
			adk->destroyObjectFromDatabase(true);
			antiDecayKitObject = nullptr;
		}
	}

	SceneObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

void TangibleObjectImplementation::sendBaselinesTo(SceneObject* player) {
	debug("sending tano baselines");

	TangibleObject* thisPointer = asTangibleObject();

	BaseMessage* tano3 = new TangibleObjectMessage3(thisPointer);
	player->sendMessage(tano3);

	BaseMessage* tano6 = new TangibleObjectMessage6(thisPointer);
	player->sendMessage(tano6);

	if (player->isPlayerCreature())
		sendPvpStatusTo(player->asCreatureObject());
}

void TangibleObjectImplementation::setFactionStatus(int status) {
	factionStatus = status;
	futureFactionStatus = -1;

	if (isPlayerCreature()) {
		CreatureObject* creature = asCreatureObject();

		if (creature == nullptr)
			return;

		PlayerObject* ghost = creature->getPlayerObject();

		if (ghost == nullptr)
			return;

		uint32 pvpStatusBitmask = creature->getPvpStatusBitmask();
		uint32 oldStatusBitmask = pvpStatusBitmask;

		if (factionStatus == FactionStatus::COVERT) {
			creature->sendSystemMessage("@faction_recruiter:covert_complete");

			if (pvpStatusBitmask & CreatureFlag::OVERT)
				pvpStatusBitmask &= ~CreatureFlag::OVERT;
		} else if (factionStatus == FactionStatus::OVERT) {
			if(!(pvpStatusBitmask & CreatureFlag::OVERT)) {
				int cooldown = 300;

				Zone* creoZone = creature->getZone();

				if (creoZone != nullptr) {
					GCWManager* gcwMan = creoZone->getGCWManager();

					if (gcwMan != nullptr)
						cooldown = gcwMan->getOvertCooldown();
				}

				creature->addCooldown("declare_overt_cooldown", cooldown * 1000);
				pvpStatusBitmask |= CreatureFlag::OVERT;

				creature->sendSystemMessage("@faction_recruiter:overt_complete");
			}

			if (ConfigManager::instance()->isPvpBroadcastChannelEnabled()) {
				ZoneServer* zoneServer = getZoneServer();

				if (zoneServer != nullptr) {
					ChatManager* chatManager = zoneServer->getChatManager();

					if (chatManager != nullptr) {
						ghost->addChatRoom(chatManager->getPvpBroadcastRoom()->getRoomID());
					}
				}
			}
		} else if (factionStatus == FactionStatus::ONLEAVE) {
			if (pvpStatusBitmask & CreatureFlag::OVERT)
				pvpStatusBitmask &= ~CreatureFlag::OVERT;

			if (creature->getFaction() != 0)
				creature->sendSystemMessage("@faction_recruiter:on_leave_complete");
		}

		if (oldStatusBitmask != CreatureFlag::NONE)
			creature->setPvpStatusBitmask(pvpStatusBitmask);
		else
			broadcastPvpStatusBitmask(); // Invuln players still need faction changes broadcasted even without the bitmask changing

		Vector<ManagedReference<CreatureObject*> > petsToStore;

		for (int i = 0; i < ghost->getActivePetsSize(); i++) {
			Reference<AiAgent*> pet = ghost->getActivePet(i);

			if (pet == nullptr)
				continue;

			const CreatureTemplate* creatureTemplate = pet->getCreatureTemplate();

			if (creatureTemplate != nullptr && creature->getFaction() != 0) {
				const auto& templateFaction = creatureTemplate->getFaction();

				if (!templateFaction.isEmpty() && factionStatus == FactionStatus::ONLEAVE) {
					petsToStore.add(pet.castTo<CreatureObject*>());
					creature->sendSystemMessage("You're no longer the right faction status for one of your pets, storing...");
					continue;
				}
			}
		}

		StoreSpawnedChildrenTask* task = new StoreSpawnedChildrenTask(creature, std::move(petsToStore));
		task->execute();

		ghost->updateInRangeBuildingPermissions();
	}

	notifyObservers(ObserverEventType::FACTIONCHANGED);
}

void TangibleObjectImplementation::sendPvpStatusTo(CreatureObject* player) {
	uint32 newPvpStatusBitmask = pvpStatusBitmask;

	bool attackable = isAttackableBy(player);
	bool aggressive = isAggressiveTo(player);

	if (attackable && !(newPvpStatusBitmask & CreatureFlag::ATTACKABLE)) {
		newPvpStatusBitmask |= CreatureFlag::ATTACKABLE;
	} else if (!attackable && newPvpStatusBitmask & CreatureFlag::ATTACKABLE) {
		newPvpStatusBitmask &= ~CreatureFlag::ATTACKABLE;
	}

	if (aggressive && !(newPvpStatusBitmask & CreatureFlag::AGGRESSIVE)) {
		newPvpStatusBitmask |= CreatureFlag::AGGRESSIVE;
	} else if (!aggressive && newPvpStatusBitmask & CreatureFlag::AGGRESSIVE) {
		newPvpStatusBitmask &= ~CreatureFlag::AGGRESSIVE;
	}

	if (newPvpStatusBitmask & CreatureFlag::TEF) {
		if (player != asTangibleObject())
			newPvpStatusBitmask &= ~CreatureFlag::TEF;
	}

	if (getFutureFactionStatus() == FactionStatus::OVERT)
		newPvpStatusBitmask |= CreatureFlag::WILLBEDECLARED;

	if (getFactionStatus() == FactionStatus::OVERT && getFutureFactionStatus() == FactionStatus::COVERT)
		newPvpStatusBitmask |= CreatureFlag::WASDECLARED;

	BaseMessage* pvp = new UpdatePVPStatusMessage(asTangibleObject(), player, newPvpStatusBitmask);
	player->sendMessage(pvp);
}

void TangibleObjectImplementation::broadcastPvpStatusBitmask() {
	if (closeobjects == nullptr) {
		return;
	}

	Zone* zone = getZoneUnsafe();

	if (zone == nullptr) {
		return;
	}

	CreatureObject* thisCreo = asCreatureObject();

	SortedVector<QuadTreeEntry*> closeObjects(closeobjects->size(), 10);

	closeobjects->safeCopyReceiversTo(closeObjects, CloseObjectsVector::CREOTYPE);

	for (int i = 0; i < closeObjects.size(); ++i) {
		SceneObject* obj = cast<SceneObject*>(closeObjects.get(i));

		if (obj == nullptr || !obj->isCreatureObject())
			continue;

		CreatureObject* creo = obj->asCreatureObject();

		if (creo->isPlayerCreature())
			sendPvpStatusTo(creo);

		if (thisCreo != nullptr && thisCreo->isPlayerCreature())
			creo->sendPvpStatusTo(thisCreo);
	}

	closeobjects->safeCopyReceiversTo(closeObjects, CloseObjectsVector::INSTALLATIONTYPE);

	for (int i = 0; i < closeObjects.size(); ++i) {
		SceneObject* obj = cast<SceneObject*>(closeObjects.get(i));

		if (obj != nullptr && obj->isInstallationObject() && thisCreo != nullptr) {
			obj->asTangibleObject()->sendPvpStatusTo(thisCreo);
		}
	}
}

void TangibleObjectImplementation::setFutureFactionStatus(int status) {
	futureFactionStatus = status;

	broadcastPvpStatusBitmask();
}

void TangibleObjectImplementation::setPvpStatusBitmask(uint32 bitmask, bool notifyClient) {
	pvpStatusBitmask = bitmask;

	broadcastPvpStatusBitmask();

	if (isPlayerCreature()) {
		PlayerObject* ghost = asCreatureObject()->getPlayerObject();

		if (ghost == nullptr)
			return;

		if (bitmask & CreatureFlag::PLAYER)
			bitmask &= ~CreatureFlag::PLAYER;

		for (int i = 0; i < ghost->getActivePetsSize(); i++) {
			Reference<AiAgent*> pet = ghost->getActivePet(i);

			if (pet == nullptr)
				continue;

			Locker clocker(pet, asTangibleObject());

			pet->setPvpStatusBitmask(bitmask);
		}
	}
}

void TangibleObjectImplementation::setIsCraftedEnhancedItem(bool value) {
	isCraftedEnhancedItem = value;
}

void TangibleObjectImplementation::setPvpStatusBit(uint32 pvpStatus, bool notifyClient) {
	if (!(pvpStatusBitmask & pvpStatus)) {
		setPvpStatusBitmask(pvpStatusBitmask | pvpStatus, notifyClient);
	}
}

void TangibleObjectImplementation::clearPvpStatusBit(uint32 pvpStatus, bool notifyClient) {
	if (pvpStatusBitmask & pvpStatus) {
		setPvpStatusBitmask(pvpStatusBitmask & ~pvpStatus, notifyClient);
	}
}

void TangibleObjectImplementation::synchronizedUIListen(CreatureObject* player, int value) {
	// Send TANO7 Baseline
	TangibleObjectMessage7* tano7 = new TangibleObjectMessage7(asTangibleObject());
	player->sendMessage(tano7);
}

void TangibleObjectImplementation::synchronizedUIStopListen(CreatureObject* player, int value) {

}

void TangibleObjectImplementation::setSerialNumber(const String& serial) {
	uint32 bitmask = getOptionsBitmask();
	bitmask |= OptionBitmask::HASSERIAL;
	setOptionsBitmask(bitmask);
	objectSerial = serial;
}

void TangibleObjectImplementation::addVisibleComponent(int value, bool notifyClient) {
	if (visibleComponents.contains(value))
		return;

	if (notifyClient) {
		TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(asTangibleObject());
		dtano3->startUpdate(0x05);

		visibleComponents.add(value, dtano3);

		dtano3->close();

		broadcastMessage(dtano3, true);
	} else {
		visibleComponents.add(value);
	}
}

void TangibleObjectImplementation::removeAllVisibleComponents(bool notifyClient) {
	if (notifyClient) {
		TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(asTangibleObject());
		dtano3->startUpdate(0x05);

		visibleComponents.removeAll(dtano3);

		dtano3->close();

		broadcastMessage(dtano3, true);
	} else {
		visibleComponents.removeAll();
	}
}

void TangibleObjectImplementation::removeVisibleComponent(int value, bool notifyClient) {
	if (!visibleComponents.contains(value))
		return;

	if (notifyClient) {
		TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(asTangibleObject());
		dtano3->startUpdate(0x05);

		visibleComponents.drop(value, dtano3);

		dtano3->close();

		broadcastMessage(dtano3, true);
	} else {
		visibleComponents.drop(value);
	}
}

void TangibleObjectImplementation::setDefender(SceneObject* defender) {
	if (defender == asTangibleObject())
		return;

	fatal(defender, "defender in setDefender null");

	if (defenderList.size() == 0) {
		addDefender(defender);
		return;
	}

	ManagedReference<SceneObject*> temp = nullptr;

	int i = 0;
	for (; i < defenderList.size(); i++) {
		if (defenderList.get(i) == defender) {
			if (i == 0) return;
			break;
		}
	}

	if (i == defenderList.size())
		addDefender(defender);

	temp = defenderList.get(0);

	TangibleObjectDeltaMessage6* dtano6 = new TangibleObjectDeltaMessage6(asTangibleObject());
	dtano6->startUpdate(0x01);

	defenderList.set(0, defender, dtano6, 2);
	defenderList.set(i, temp, dtano6, 0);

	dtano6->close();

	broadcastMessage(dtano6, true);
}

void TangibleObjectImplementation::addDefender(SceneObject* defender) {
	if (defender == asTangibleObject())
		return;

	fatal(defender, "defender in addDefender null");

	for (int i = 0; i < defenderList.size(); ++i) {
		if (defender == defenderList.get(i))
			return;
	}

	debug("adding defender");

	TangibleObjectDeltaMessage6* dtano6 = new TangibleObjectDeltaMessage6(asTangibleObject());
	dtano6->startUpdate(0x01);

	defenderList.add(defender, dtano6);

	dtano6->close();

	broadcastMessage(dtano6, true);

	setCombatState();

	notifyObservers(ObserverEventType::DEFENDERADDED, defender);
}

void TangibleObjectImplementation::removeDefenders() {
	debug("removing all defenders");

	if (defenderList.size() == 0) {
		debug("no defenders in list");
		return;
	}

	for (int i = 0; i < defenderList.size(); i++)
		notifyObservers(ObserverEventType::DEFENDERDROPPED, defenderList.get(i));

	TangibleObjectDeltaMessage6* dtano6 = new TangibleObjectDeltaMessage6(asTangibleObject());
	dtano6->startUpdate(0x01);

	defenderList.removeAll(dtano6);

	dtano6->close();

	broadcastMessage(dtano6, true);

	debug("removed all defenders");
}

void TangibleObjectImplementation::removeDefender(SceneObject* defender) {
	debug("trying to remove defender");

	for (int i = 0; i < defenderList.size(); ++i) {
		if (defenderList.get(i) == defender) {
			debug("removing defender");

			notifyObservers(ObserverEventType::DEFENDERDROPPED, defender);

			TangibleObjectDeltaMessage6* dtano6 = new TangibleObjectDeltaMessage6(asTangibleObject());

			dtano6->startUpdate(0x01);

			if (defenderList.size() == 1)
				defenderList.removeAll(dtano6);
			else
				defenderList.remove(i, dtano6);

			dtano6->close();

			broadcastMessage(dtano6, true);

			debug("defender found and removed");
			break;
		}
	}

	if (defenderList.size() == 0) {
		clearCombatState(false);
	}

	debug("finished removing defender");
}

void TangibleObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	SceneObjectImplementation::fillAttributeList(alm, object);

	if (maxCondition > 0) {
		StringBuffer cond;
		cond << (maxCondition-(int)conditionDamage) << "/" << maxCondition;

		auto config = ConfigManager::instance();

		if (isForceNoTrade()) {
			cond << config->getForceNoTradeMessage();
		} else if (antiDecayKitObject != nullptr && antiDecayKitObject->isForceNoTrade()) {
			cond << config->getForceNoTradeADKMessage();
		} else if (isNoTrade() || containsNoTradeObjectRecursive()) {
			cond << config->getNoTradeMessage();
		}

		alm->insertAttribute("condition", cond);
	}

	int volumeLimit = getContainerVolumeLimit();

	if (volumeLimit >= 1 && getContainerType() == ContainerType::VOLUME) {
		int objectCount = getCountableObjectsRecursive();

		StringBuffer contentsString;
		contentsString << objectCount << "/" << volumeLimit;

		alm->insertAttribute("volume", volume + objectCount);
		alm->insertAttribute("contents", contentsString);
	} else {
		alm->insertAttribute("volume", volume);
	}

	if (!craftersName.isEmpty()) {
		alm->insertAttribute("crafter", craftersName);
	}

	if (!objectSerial.isEmpty()) {
		alm->insertAttribute("serial_number", objectSerial);
	}

	if (useCount > 1) {
		if (gameObjectType == SceneObjectType::CRAFTINGTOOL)
			alm->insertAttribute("craft_tool_time", useCount);
		else
			alm->insertAttribute("quantity", useCount);
	}

	if (gameObjectType == SceneObjectType::PLAYERLOOTCRATE) {
		if (isSliceable()) {
			alm->insertAttribute( "lock_mechanism", "@obj_attr_n:slicable" );
		}
		else {
			alm->insertAttribute( "lock_mechanism", "@obj_attr_n:broken" );
		}
	}
}

void TangibleObjectImplementation::setCustomizationVariable(byte type, int16 value, bool notifyClient) {
	customizationVariables.setVariable(type, value);

	if (!notifyClient)
		return;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(asTangibleObject());
	dtano3->updateCustomizationString();
	dtano3->close();

	broadcastMessage(dtano3, true);
}

void TangibleObjectImplementation::setCustomizationVariable(const String& type, int16 value, bool notifyClient) {
	customizationVariables.setVariable(type, value);

	if(!notifyClient)
		return;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(asTangibleObject());
	dtano3->updateCustomizationString();
	dtano3->close();

	broadcastMessage(dtano3, true);

}

void TangibleObjectImplementation::setCountdownTimer(unsigned int newUseCount, bool notifyClient) {
	if (useCount == newUseCount)
		return;

	useCount = newUseCount;

	if (!notifyClient)
		return;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(asTangibleObject());
	dtano3->updateCountdownTimer();
	dtano3->close();

	broadcastMessage(dtano3, true);
}

void TangibleObjectImplementation::setUseCount(uint32 newUseCount, bool notifyClient) {
	if (useCount == newUseCount)
		return;

	setCountdownTimer(newUseCount, notifyClient);
}

void TangibleObjectImplementation::decreaseUseCount(unsigned int decrementAmount, bool notifyClient) {
	setUseCount(useCount - decrementAmount, notifyClient);

	if (useCount < 1 && !isCreatureObject()) {
		destroyObjectFromWorld(true);

		destroyObjectFromDatabase(true);

		return;
	}
}

void TangibleObjectImplementation::setMaxCondition(int maxCond, bool notifyClient) {
	if (maxCondition == maxCond)
		return;

	maxCondition = maxCond;

	if (!notifyClient)
		return;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(asTangibleObject());
	dtano3->updateMaxCondition();
	dtano3->close();

	broadcastMessage(dtano3, true);
}

void TangibleObjectImplementation::setConditionDamage(float condDamage, bool notifyClient) {
	if (conditionDamage == condDamage)
		return;

	conditionDamage = condDamage;

	if (!notifyClient)
		return;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(asTangibleObject());
	dtano3->updateConditionDamage();
	dtano3->close();

	broadcastMessage(dtano3, true);
}

int TangibleObjectImplementation::inflictDamage(TangibleObject* attacker, int damageType, float damage, bool destroy, bool notifyClient, bool isCombatAction) {
	if (hasAntiDecayKit())
		return 0;

	float newConditionDamage = conditionDamage + damage;

	if (!destroy && newConditionDamage >= maxCondition)
		newConditionDamage = maxCondition - 1;
	else if (newConditionDamage >= maxCondition)
		newConditionDamage = maxCondition;

	setConditionDamage(newConditionDamage, notifyClient);

	if (attacker->isCreatureObject()) {
		CreatureObject* creature = attacker->asCreatureObject();

		if (damage > 0 && attacker != asTangibleObject())
			getThreatMap()->addDamage(creature, (uint32)damage);
	}

	if (newConditionDamage >= maxCondition) {
		notifyObjectDestructionObservers(attacker, newConditionDamage, isCombatAction);
		notifyObservers(ObserverEventType::OBJECTDISABLED, attacker);
		setDisabled(true);
	}

	return 0;
}

int TangibleObjectImplementation::inflictDamage(TangibleObject* attacker, int damageType, float damage, bool destroy, const String& xp, bool notifyClient, bool isCombatAction) {
	if (hasAntiDecayKit())
		return 0;

	float newConditionDamage = conditionDamage + damage;

	if (!destroy && newConditionDamage >= maxCondition)
		newConditionDamage = maxCondition - 1;

	setConditionDamage(newConditionDamage, notifyClient);

	if (attacker->isCreatureObject()) {
		CreatureObject* creature = attacker->asCreatureObject();

		if (damage > 0 && attacker != asTangibleObject())
			getThreatMap()->addDamage(creature, (uint32)damage, xp);
	}

	if (newConditionDamage >= maxCondition) {
		notifyObjectDestructionObservers(attacker, newConditionDamage, isCombatAction);
		notifyObservers(ObserverEventType::OBJECTDISABLED, attacker);
		setDisabled(true);
	}

	return 0;
}

int TangibleObjectImplementation::notifyObjectDestructionObservers(TangibleObject* attacker, int condition, bool isCombatAction) {
	notifyObservers(ObserverEventType::OBJECTDESTRUCTION, attacker, condition);

	if (threatMap != nullptr)
		threatMap->removeAll();

	dropFromDefenderLists();

	attacker->removeDefender(asTangibleObject());

	return 1;
}

void TangibleObjectImplementation::dropFromDefenderLists() {
	if (defenderList.size() == 0) {
		return;
	}

	Reference<ClearDefenderListsTask*> task = new ClearDefenderListsTask(defenderList, asTangibleObject());
	Core::getTaskManager()->executeTask(task);

	clearCombatState(false);
}

int TangibleObjectImplementation::healDamage(TangibleObject* healer, int damageType, float damageToHeal, bool notifyClient) {
	float newConditionDamage = conditionDamage - damageToHeal;

	int returnValue = damageToHeal;

	if (newConditionDamage < 0)
		returnValue = damageToHeal + newConditionDamage;

	if (returnValue < 0)
		returnValue = 0;

	setConditionDamage(Math::max(0.f, newConditionDamage), notifyClient);

	return returnValue;
}

void TangibleObjectImplementation::setObjectName(const StringId& stringID, bool notifyClient) {
	objectName = stringID;

	if (!notifyClient)
		return;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(asTangibleObject());
	dtano3->updateObjectName(stringID);
	dtano3->close();

	broadcastMessage(dtano3, true);
}

void TangibleObjectImplementation::setCustomObjectName(const UnicodeString& name, bool notifyClient) {
	customName = name;

	if (isClientObject())
		setForceSend(true);

	if (!notifyClient)
		return;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(asTangibleObject());
	dtano3->updateCustomName(name);
	dtano3->close();

	broadcastMessage(dtano3, true);
}

void TangibleObjectImplementation::setOptionsBitmask(uint32 bitmask, bool notifyClient) {
	if (bitmask == optionsBitmask)
		return;

	optionsBitmask = bitmask;

	if (!notifyClient)
		return;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(asTangibleObject());
	dtano3->updateOptionsBitmask();
	dtano3->close();

	broadcastMessage(dtano3, true);
}

void TangibleObjectImplementation::setOptionBit(uint32 option, bool notifyClient) {
	if (!(optionsBitmask & option)) {
		setOptionsBitmask(optionsBitmask | option, notifyClient);
	}
}

void TangibleObjectImplementation::clearOptionBit(uint32 option, bool notifyClient) {
	if (optionsBitmask & option) {
		setOptionsBitmask(optionsBitmask & ~option, notifyClient);
	}
}

void TangibleObjectImplementation::updateCraftingValues(CraftingValues* values,
		bool firstUpdate) {
	/// I know its kind dirty, but we want generics to have quantities
	/// Without needing their own classes
	if (values->hasProperty("quantity")) {
		setUseCount(values->getCurrentValue("quantity"));
	}

	if (values->hasProperty("charges")) {
		setUseCount(values->getCurrentValue("charges"));
	}

	if (values->hasProperty("charge")) {
		setUseCount(values->getCurrentValue("charge"));
	}
}

Reference<FactoryCrate*> TangibleObjectImplementation::createFactoryCrate(int maxSize, String& factoryCrateType, bool insertSelf ) {
	ObjectManager* objectManager = ObjectManager::instance();

	String crateType = factoryCrateType;
	uint32 type = getGameObjectType();

	if (crateType == "") {
		if(type & SceneObjectType::ARMOR)
        		crateType = "object/factory/factory_crate_armor.iff";
    		else if(type == SceneObjectType::CHEMICAL || type == SceneObjectType::PHARMACEUTICAL || type == SceneObjectType::PETMEDECINE)
        		crateType = "object/factory/factory_crate_chemicals.iff";
    		else if(type & SceneObjectType::CLOTHING)
        		crateType = "object/factory/factory_crate_clothing.iff";
    		else if(type == SceneObjectType::ELECTRONICS)
        		crateType = "object/factory/factory_crate_electronics.iff";
    		else if(type == SceneObjectType::FOOD || type == SceneObjectType::DRINK)
        		crateType = "object/factory/factory_crate_food.iff";
    		else if(type == SceneObjectType::FURNITURE)
        		crateType = "object/factory/factory_crate_furniture.iff";
    		else if(type & SceneObjectType::INSTALLATION)
        		crateType = "object/factory/factory_crate_installation.iff";
    		else if(type & SceneObjectType::WEAPON)
        		crateType = "object/factory/factory_crate_weapon.iff";
    		else
        	crateType = "object/factory/factory_crate_generic_items.iff";
	}

	Reference<FactoryCrate*> crate = (getZoneServer()->createObject(crateType.hashCode(), 2)).castTo<FactoryCrate*>();

	if (crate == nullptr)
		return nullptr;

	Locker locker(crate);

	crate->setMaxCapacity(maxSize);


	if (insertSelf) {
		if (!crate->transferObject(asTangibleObject(), -1, false)) {
			crate->destroyObjectFromDatabase(true);
			return nullptr;
		}
	} else {
		ManagedReference<TangibleObject*> protoclone = cast<TangibleObject*>( objectManager->cloneObject(asTangibleObject()));

		if (protoclone == nullptr) {
			crate->destroyObjectFromDatabase(true);
			return nullptr;
		}

		/*
		* I really didn't want to do this this way, but I had no other way of making the text on the crate be white
		* if the item it contained has yellow magic bit set. So I stripped the yellow magic bit off when the item is placed inside
		* the crate here, and added it back when the item is extracted from the crate if it is a crafted enhanced item.
		*/
		if(protoclone->getIsCraftedEnhancedItem()) {
			protoclone->removeMagicBit(false);
		}

		protoclone->setParent(nullptr);
		if (!crate->transferObject(protoclone, -1, false)) {
			protoclone->destroyObjectFromDatabase(true);
			crate->destroyObjectFromDatabase(true);
			return nullptr;
		}
	}

	crate->setCustomObjectName(getCustomObjectName(), false);

	crate->setUseCount(1);

	return crate;
}

void TangibleObjectImplementation::addTemplateSkillMods(TangibleObject* targetObject) const {
	SharedTangibleObjectTemplate* tano = dynamic_cast<SharedTangibleObjectTemplate*>(templateObject.get());

	if (tano == nullptr)
		return;

	const VectorMap<String, int>* mods = tano->getSkillMods();

	for (int i = 0; i < mods->size(); ++i) {
		VectorMapEntry<String, int> entry = mods->elementAt(i);

		targetObject->addSkillMod(SkillModManager::TEMPLATE, entry.getKey(), entry.getValue());
	}
}

void TangibleObjectImplementation::removeTemplateSkillMods(TangibleObject* targetObject) const {
	const SharedTangibleObjectTemplate* tano = dynamic_cast<const SharedTangibleObjectTemplate*>(templateObject.get());

	if (tano == nullptr)
		return;

	const VectorMap<String, int>* mods = tano->getSkillMods();

	for (int i = 0; i < mods->size(); ++i) {
		const auto& entry = mods->elementAt(i);

		targetObject->removeSkillMod(SkillModManager::TEMPLATE, entry.getKey(), entry.getValue());
	}
}

const VectorMap<String, int>* TangibleObjectImplementation::getTemplateSkillMods() const {
	SharedTangibleObjectTemplate* tano = dynamic_cast<SharedTangibleObjectTemplate*>(templateObject.get());

	if (tano == nullptr)
		return nullptr;

	return tano->getSkillMods();
}

bool TangibleObjectImplementation::canRepair(CreatureObject* player) {
	if (player == nullptr || !isASubChildOf(player))
		return false;

	SceneObject* inventory = player->getSlottedObject("inventory");

	if (inventory == nullptr)
		return false;

	for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
		ManagedReference<SceneObject*> item = inventory->getContainerObject(i);
		if(item->isRepairTool()) {
			Reference<RepairToolTemplate*> repairTemplate = cast<RepairToolTemplate*>(item->getObjectTemplate());

			if (repairTemplate == nullptr) {
				error("No RepairToolTemplate for: " + String::valueOf(item->getServerObjectCRC()));

				continue;
			}

			if (repairTemplate->getRepairType() & getGameObjectType()) {
				return true;
			}
		}
	}

	return false;
}

void TangibleObjectImplementation::repair(CreatureObject* player, RepairTool * repairTool) {

	if(player == nullptr || player->getZoneServer() == nullptr)
		return;

	if (!isASubChildOf(player))
		return;

	if (getConditionDamage() == 0) {
		player->sendSystemMessage("That item is not in need of repair.");
		return;
	}

	//Condition is unrepairable
	if ((getMaxCondition() - getConditionDamage()) <= 0) {
		StringIdChatParameter cantrepair("error_message", "sys_repair_unrepairable");
		cantrepair.setTT(getDisplayedName());
		player->sendSystemMessage(cantrepair); //%TT's condition is beyond repair even for your skills.
		return;
	}

	Reference<RepairToolTemplate*> repairTemplate = nullptr;

	if (repairTool == nullptr) {
		SceneObject* inventory = player->getSlottedObject("inventory");

		if(inventory == nullptr) {
			return;
		}

		for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
			ManagedReference<SceneObject*> item = inventory->getContainerObject(i);

			if (item->isRepairTool()) {
				repairTemplate = cast<RepairToolTemplate*>(item->getObjectTemplate());

				if (repairTemplate == nullptr) {
					error("No RepairToolTemplate for: " + String::valueOf(item->getServerObjectCRC()));
					return;
				}

				if(repairTemplate->getRepairType() & getGameObjectType()) {
					repairTool = cast<RepairTool*>(item.get());
					break;
				}

				repairTemplate = nullptr;
			}
		}
	} else {
		repairTemplate = cast<RepairToolTemplate*>(repairTool->getObjectTemplate());

		if (!(repairTemplate->getRepairType() & getGameObjectType())) {
			error ("Given RepairTool can't repair this type of object");
			return;
		}
	}

	if (repairTool == nullptr) {
		error ("No RepairTool given or found. Aborting");
		return;
	}

	/// Luck Roll + Profession Mod(25) + Luck Tapes
	/// + Station Mod - BF

	/// Luck Roll
	int roll = System::random(100);
	int repairChance = roll;

	/// Profession Bonus
	if (player->hasSkill(repairTemplate->getSkill()))
		repairChance += 35;

	/// Get Skill mods
	repairChance += player->getSkillMod(repairTemplate->getSkillMod());
	repairChance += player->getSkillMod("crafting_repair");
	repairChance += player->getSkillMod("force_repair_bonus");

	/// use tool quality to lower chances if bad tool
	float quality = 1.f - (((100.f - repairTool->getQuality()) / 2) / 100.f);
	repairChance *= quality;

	ManagedReference<PlayerManager*> playerMan = player->getZoneServer()->getPlayerManager();

	/// Increase if near station
	if (playerMan->getNearbyCraftingStation(player, repairTemplate->getStationType()) != nullptr) {
		repairChance += 15;
	}

	/// Subtract battle fatigue
	repairChance -= (player->getShockWounds() / 2);

	/// Subtract complexity
	repairChance -= (getComplexity() / 3);

	/// 5% random failure
	if (getMaxCondition() < 20 || roll < 5)
		repairChance = 0;

	if (roll > 95)
		repairChance = 100;

	String result = repairAttempt(repairChance);

	Locker locker(repairTool);

	repairTool->decreaseUseCount(1, true);

	player->sendSystemMessage(result);
}

ThreatMap* TangibleObjectImplementation::getThreatMap() {
	if (threatMap == nullptr) {
		Reference<ThreatMap*> newMap = new ThreatMap(asTangibleObject());

		threatMap.compareAndSet(nullptr, newMap.get());
	}

	return threatMap;
}

bool TangibleObjectImplementation::isAttackableBy(TangibleObject* object) {
	if (object == nullptr)
		return  false;

	if (object->isCreatureObject())
		return isAttackableBy(object->asCreatureObject());

	return false;
}

bool TangibleObjectImplementation::isAttackableBy(CreatureObject* creature) {
	if (creature == nullptr)
		return false;

	// info(true) << "TangibleObjectImplementation::isAttackableBy Creature Check -- Object ID = " << getObjectID() << " by attacking Creature ID = " << creature->getObjectID();

	if (!(pvpStatusBitmask & CreatureFlag::ATTACKABLE))
		return false;

	for (int i = 0; i < activeAreas.size(); i++) {
		ActiveArea* area = activeAreas.get(i);

		if (area != nullptr && area->isNoCombatArea())
			return false;
	}

	// Attacking CreO is AiAgent
	if (creature->isAiAgent()) {
		AiAgent* ai = creature->asAiAgent();

		if (ai->getHomeObject().get() == asTangibleObject()) {
			return false;
		}

		if (ai->isPet()) {
			ManagedReference<PetControlDevice*> pcd = ai->getControlDevice().get().castTo<PetControlDevice*>();
			if (pcd != nullptr && pcd->getPetType() == PetManager::FACTIONPET && isNeutral()) {
				return false;
			}

			ManagedReference<CreatureObject*> owner = ai->getLinkedCreature().get();

			if (owner == nullptr)
				return false;

			return isAttackableBy(owner);
		}
	}

	// Attacking CreO is a player
	if (creature->isPlayerCreature()) {
		Reference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost != nullptr && ghost->hasCrackdownTefTowards(getFaction())) {
			return true;
		}

		if (isImperial() && (!creature->isRebel() || creature->getFactionStatus() == 0)) {
			return false;
		}

		if (isRebel() && (!creature->isImperial() || creature->getFactionStatus() == 0)) {
			return false;
		}
	}

	if (isImperial() && !(creature->isRebel())) {
		return false;
	} else if (isRebel() && !(creature->isImperial())) {
		return false;
	}

	// info(true) << "RanO isAttackable check return true";

	return pvpStatusBitmask & CreatureFlag::ATTACKABLE;
}

void TangibleObjectImplementation::addActiveArea(ActiveArea* area) {
	if (!area->isDeployed())
		area->deploy();

	Locker locker(&containerLock);

	activeAreas.put(area);
}

void TangibleObjectImplementation::sendTo(SceneObject* player, bool doClose, bool forceLoadContainer) {
	if (isInvisible() && player != asTangibleObject())
		return;

	SceneObjectImplementation::sendTo(player, doClose, forceLoadContainer);
}

bool TangibleObjectImplementation::isCityStreetLamp() const {
	return (templateObject != nullptr && templateObject->getFullTemplateString().contains("object/tangible/furniture/city/streetlamp"));
}

bool TangibleObjectImplementation::isCityStatue() const {
	return (templateObject != nullptr && templateObject->getFullTemplateString().contains("object/tangible/furniture/city/statue"));
}

bool TangibleObjectImplementation::isCityFountain() const {
	return (templateObject != nullptr && templateObject->getFullTemplateString().contains("object/tangible/furniture/city/fountain"));
}

bool TangibleObjectImplementation::isRebel() const {
	return faction == Factions::FACTIONREBEL;
}

bool TangibleObjectImplementation::isImperial() const {
	return faction == Factions::FACTIONIMPERIAL;
}

bool TangibleObjectImplementation::isNeutral() const {
	return faction == Factions::FACTIONNEUTRAL;
}

void TangibleObjectImplementation::setDisabled(bool disabled) {
	if (disabled)
		setOptionBit(OptionBitmask::DISABLED, true);
	else
		clearOptionBit(OptionBitmask::DISABLED, true);
}

bool TangibleObjectImplementation::isDisabled() const {
	return getOptionsBitmask() & OptionBitmask::DISABLED;
}

bool TangibleObjectImplementation::isInNavMesh() {
	for (int i = 0; i < activeAreas.size(); ++i) {
		const auto& area = activeAreas.get(i);

		if (area->isNavArea())
			return true;
	}

	return false;
}

TangibleObject* TangibleObject::asTangibleObject() {
	return this;
}

TangibleObject* TangibleObjectImplementation::asTangibleObject() {
	return _this.getReferenceUnsafeStaticCast();
}
