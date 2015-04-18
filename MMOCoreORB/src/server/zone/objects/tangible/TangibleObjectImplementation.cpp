/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "server/zone/objects/tangible/TangibleObject.h"
#include "variables/SkillModMap.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/skill/SkillModManager.h"
#include "server/zone/objects/scene/variables/CustomizationVariables.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/tangible/TangibleObjectMessage3.h"
#include "server/zone/packets/tangible/TangibleObjectMessage6.h"
#include "server/zone/packets/tangible/TangibleObjectMessage7.h"
#include "server/zone/packets/tangible/TangibleObjectDeltaMessage3.h"
#include "server/zone/packets/tangible/TangibleObjectDeltaMessage6.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/templates/SharedTangibleObjectTemplate.h"
#include "server/zone/objects/creature/CreatureFlag.h"
#include "server/zone/packets/tangible/UpdatePVPStatusMessage.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/managers/crafting/CraftingManager.h"
#include "server/zone/objects/tangible/component/Component.h"
#include "server/zone/objects/factorycrate/FactoryCrate.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"
#include "server/zone/Zone.h"
#include "tasks/ClearDefenderListsTask.h"
#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"
#include "server/zone/objects/manufactureschematic/ingredientslots/ComponentSlot.h"
#include "server/zone/templates/tangible/tool/RepairToolTemplate.h"
#include "server/zone/objects/tangible/tool/repair/RepairTool.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/tangible/wearables/WearableObject.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "engine/engine.h"


void TangibleObjectImplementation::initializeTransientMembers() {
	SceneObjectImplementation::initializeTransientMembers();

	threatMap = NULL;

	setLoggingName("TangibleObject");

	if (faction !=  0x16148850 && faction != 0xDB4ACC54) {
		faction = 0;
	}
}

void TangibleObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	SceneObjectImplementation::loadTemplateData(templateData);

	SharedTangibleObjectTemplate* tanoData = dynamic_cast<SharedTangibleObjectTemplate*>(templateData);

	if (tanoData == NULL)
		return;

	targetable = tanoData->getTargetable();

	maxCondition = tanoData->getMaxCondition();

	useCount = tanoData->getUseCount();

	optionsBitmask = tanoData->getOptionsBitmask();
	pvpStatusBitmask = tanoData->getPvpStatusBitmask();

	sliceable = tanoData->getSliceable();

	faction = tanoData->getFaction();

	threatMap = NULL;
}

void TangibleObjectImplementation::notifyLoadFromDatabase() {
	SceneObjectImplementation::notifyLoadFromDatabase();

	for (int i = 0; i < activeAreas.size(); ++i) {
		activeAreas.get(i)->notifyExit(_this.get());
	}

	activeAreas.removeAll();
}

void TangibleObjectImplementation::sendBaselinesTo(SceneObject* player) {
	info("sending tano baselines");

	Reference<TangibleObject*> thisPointer = _this.get();

	BaseMessage* tano3 = new TangibleObjectMessage3(thisPointer);
	player->sendMessage(tano3);

	BaseMessage* tano6 = new TangibleObjectMessage6(thisPointer);
	player->sendMessage(tano6);

	if (player->isPlayerCreature())
		sendPvpStatusTo(cast<CreatureObject*>(player));
}

void TangibleObjectImplementation::sendPvpStatusTo(CreatureObject* player) {
	uint32 newPvpStatusBitmask = pvpStatusBitmask;

	if (!(newPvpStatusBitmask & CreatureFlag::ATTACKABLE)) {
		if (isAttackableBy(player))
			newPvpStatusBitmask |= CreatureFlag::ATTACKABLE;
	} else if (!isAttackableBy(player))
		newPvpStatusBitmask -= CreatureFlag::ATTACKABLE;

	if (!(newPvpStatusBitmask & CreatureFlag::AGGRESSIVE)) {
		if (isAggressiveTo(player))
			newPvpStatusBitmask |= CreatureFlag::AGGRESSIVE;
	} else if (!isAggressiveTo(player))
		newPvpStatusBitmask -= CreatureFlag::AGGRESSIVE;

	BaseMessage* pvp = new UpdatePVPStatusMessage(_this.get(), newPvpStatusBitmask);
	player->sendMessage(pvp);
}

void TangibleObjectImplementation::broadcastPvpStatusBitmask(){
	if (getZone() == NULL)
			return;

	if (closeobjects != NULL) {
		Zone* zone = getZone();

		//Locker locker(zone);

		CreatureObject* thisCreo = cast<CreatureObject*>(_this.get().get());

		SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects(closeobjects->size(), 10);

		closeobjects->safeCopyTo(closeObjects);

		for (int i = 0; i < closeObjects.size(); ++i) {
			SceneObject* obj = cast<SceneObject*>(closeObjects.get(i).get());

			if (obj != NULL && obj->isCreatureObject()) {
				CreatureObject* creo = cast<CreatureObject*>(obj);

				sendPvpStatusTo(creo);

				if (thisCreo != NULL)
					creo->sendPvpStatusTo(thisCreo);
			}

		}
	}
}

void TangibleObjectImplementation::setPvpStatusBitmask(int bitmask, bool notifyClient) {
	pvpStatusBitmask = bitmask;

	broadcastPvpStatusBitmask();

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

void TangibleObjectImplementation::synchronizedUIListen(SceneObject* player, int value) {
	// Send TANO7 Baseline
	TangibleObjectMessage7* tano7 = new TangibleObjectMessage7(_this.get());
	player->sendMessage(tano7);
}

void TangibleObjectImplementation::synchronizedUIStopListen(SceneObject* player, int value) {

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
		TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this.get());
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
		TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this.get());
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
		TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this.get());
		dtano3->startUpdate(0x05);

		visibleComponents.drop(value, dtano3);

		dtano3->close();

		broadcastMessage(dtano3, true);
	} else {
		visibleComponents.drop(value);
	}
}

void TangibleObjectImplementation::setDefender(SceneObject* defender) {
	if (defender == _this.get())
		return;

	assert(defender);

	if (defenderList.size() == 0) {
		addDefender(defender);
		return;
	}

	ManagedReference<SceneObject*> temp = NULL;

	int i = 0;
	for (; i < defenderList.size(); i++) {
		if (defenderList.get(i) == defender) {
			if (i == 0)
				return;

			temp = defenderList.get(0);

			TangibleObjectDeltaMessage6* dtano6 = new TangibleObjectDeltaMessage6(_this.get());
			dtano6->startUpdate(0x01);

			defenderList.set(0, defender, dtano6, 2);
			defenderList.set(i, temp, dtano6, 0);

			dtano6->close();

			broadcastMessage(dtano6, true);

			break;
		}
	}

	if (i == defenderList.size())
		addDefender(defender);
	else
		setCombatState();
}

void TangibleObjectImplementation::addDefender(SceneObject* defender) {
	if (defender == _this.get())
		return;

	assert(defender);

	for (int i = 0; i < defenderList.size(); ++i) {
		if (defender == defenderList.get(i))
			return;
	}

	//info("adding defender");

	TangibleObjectDeltaMessage6* dtano6 = new TangibleObjectDeltaMessage6(_this.get());
	dtano6->startUpdate(0x01);

	defenderList.add(defender, dtano6);

	dtano6->close();

	broadcastMessage(dtano6, true);

	setCombatState();

	notifyObservers(ObserverEventType::DEFENDERADDED, defender);
}

void TangibleObjectImplementation::removeDefenders() {
	//info("removing all defenders");
	if (defenderList.size() == 0) {
		//info("no defenders in list");
		return;
	}

	for (int i = 0; i < defenderList.size(); i++)
		notifyObservers(ObserverEventType::DEFENDERDROPPED, defenderList.get(i));

	TangibleObjectDeltaMessage6* dtano6 = new TangibleObjectDeltaMessage6(_this.get());
	dtano6->startUpdate(0x01);

	defenderList.removeAll(dtano6);

	dtano6->close();

	broadcastMessage(dtano6, true);

	//info("removed all defenders");
}

void TangibleObjectImplementation::removeDefender(SceneObject* defender) {
	//info("trying to remove defender");
	for (int i = 0; i < defenderList.size(); ++i) {
		if (defenderList.get(i) == defender) {
			info("removing defender");

			notifyObservers(ObserverEventType::DEFENDERDROPPED, defender);

			TangibleObjectDeltaMessage6* dtano6 = new TangibleObjectDeltaMessage6(_this.get());

			dtano6->startUpdate(0x01);

			if (defenderList.size() == 1)
				defenderList.removeAll(dtano6);
			else
				defenderList.remove(i, dtano6);

			dtano6->close();

			broadcastMessage(dtano6, true);

			//info("defender found and removed");
			break;
		}
	}

	if (defenderList.size() == 0)
		clearCombatState(false);

	//info("finished removing defender");
}

void TangibleObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	SceneObjectImplementation::fillAttributeList(alm, object);

	if (maxCondition > 0) {
		StringBuffer cond;
		cond << (maxCondition-(int)conditionDamage) << "/" << maxCondition;

		alm->insertAttribute("condition", cond);
	}

	alm->insertAttribute("volume", volume);

	if (!craftersName.isEmpty()) {

		alm->insertAttribute("crafter", craftersName);
	}
	if (!objectSerial.isEmpty()) {

		alm->insertAttribute("serial_number", objectSerial);
	}

	if(useCount > 1)
		alm->insertAttribute("quantity", useCount);

	if (gameObjectType == SceneObjectType::PLAYERLOOTCRATE) {
		if( isSliceable() ){
			alm->insertAttribute( "lock_mechanism", "@obj_attr_n:slicable" );
		}
		else{
			alm->insertAttribute( "lock_mechanism", "@obj_attr_n:broken" );
		}
	}
}

void TangibleObjectImplementation::setCustomizationVariable(byte type, int16 value, bool notifyClient) {
	customizationVariables.setVariable(type, value);

	if (!notifyClient)
		return;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this.get());
	dtano3->updateCustomizationString();
	dtano3->close();

	broadcastMessage(dtano3, true);
}

void TangibleObjectImplementation::setCustomizationVariable(const String& type, int16 value, bool notifyClient) {
	customizationVariables.setVariable(type, value);

	if(!notifyClient)
		return;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this.get());
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

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this.get());
	dtano3->updateCountdownTimer();
	dtano3->close();

	broadcastMessage(dtano3, true);
}

void TangibleObjectImplementation::setUseCount(uint32 newUseCount, bool notifyClient) {
	if (useCount == newUseCount)
		return;

	setCountdownTimer(newUseCount, notifyClient);

	if (useCount < 1 && !isCreatureObject()) {
		destroyObjectFromWorld(true);

		destroyObjectFromDatabase(true);

		return;
	}
}

void TangibleObjectImplementation::decreaseUseCount() {
	setUseCount(useCount - 1, true);
}

void TangibleObjectImplementation::setMaxCondition(int maxCond, bool notifyClient) {
	if (maxCondition == maxCond)
		return;

	maxCondition = maxCond;

	if (!notifyClient)
		return;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this.get());
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

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this.get());
	dtano3->updateConditionDamage();
	dtano3->close();

	broadcastMessage(dtano3, true);
}

int TangibleObjectImplementation::inflictDamage(TangibleObject* attacker, int damageType, float damage, bool destroy, bool notifyClient) {
	if(hasAntiDecayKit())
		return 0;

	float newConditionDamage = conditionDamage + damage;

	if (!destroy && newConditionDamage >= maxCondition)
		newConditionDamage = maxCondition - 1;
	else if (newConditionDamage >= maxCondition)
		newConditionDamage = maxCondition;

	setConditionDamage(newConditionDamage, notifyClient);

	if (attacker->isCreatureObject()) {
		CreatureObject* creature = cast<CreatureObject*>( attacker);

		if (damage > 0 && attacker != _this.get())
			getThreatMap()->addDamage(creature, (uint32)damage);
	}

	if (newConditionDamage >= maxCondition)
		notifyObjectDestructionObservers(attacker, newConditionDamage);

	return 0;
}

int TangibleObjectImplementation::inflictDamage(TangibleObject* attacker, int damageType, float damage, bool destroy, const String& xp, bool notifyClient) {
	if(hasAntiDecayKit())
		return 0;

	float newConditionDamage = conditionDamage + damage;

	if (!destroy && newConditionDamage >= maxCondition)
		newConditionDamage = maxCondition - 1;

	setConditionDamage(newConditionDamage, notifyClient);

	if (attacker->isCreatureObject()) {
		CreatureObject* creature = cast<CreatureObject*>( attacker);

		if (damage > 0 && attacker != _this.get())
			getThreatMap()->addDamage(creature, (uint32)damage, xp);
	}

	if (newConditionDamage >= maxCondition)
		notifyObjectDestructionObservers(attacker, newConditionDamage);

	return 0;
}

int TangibleObjectImplementation::notifyObjectDestructionObservers(TangibleObject* attacker, int condition) {
	notifyObservers(ObserverEventType::OBJECTDESTRUCTION, attacker, condition);

	if (threatMap != NULL)
		threatMap->removeAll();

	dropFromDefenderLists(attacker);

	return 1;
}

void TangibleObjectImplementation::dropFromDefenderLists(TangibleObject* destructor) {
	if (defenderList.size() == 0)
		return;

	Reference<ClearDefenderListsTask*> task = new ClearDefenderListsTask(defenderList, _this.get());
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

	setConditionDamage(MAX(0, newConditionDamage), notifyClient);

	return returnValue;
}

void TangibleObjectImplementation::setCustomObjectName(const UnicodeString& name, bool notifyClient) {
	customName = name;

	if (!notifyClient)
		return;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this.get());
	dtano3->updateName(name);
	dtano3->close();

	broadcastMessage(dtano3, true);
}

void TangibleObjectImplementation::setOptionsBitmask(uint32 bitmask, bool notifyClient) {
	if (bitmask == optionsBitmask)
		return;

	optionsBitmask = bitmask;

	if (!notifyClient)
		return;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this.get());
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

Reference<FactoryCrate*> TangibleObjectImplementation::createFactoryCrate(bool insertSelf) {
	String file;
	uint32 type = getGameObjectType();

	if(type & SceneObjectType::ARMOR)
		file = "object/factory/factory_crate_armor.iff";
	else if(type == SceneObjectType::CHEMICAL || type == SceneObjectType::PHARMACEUTICAL || type == SceneObjectType::PETMEDECINE)
		file = "object/factory/factory_crate_chemicals.iff";
	else if(type & SceneObjectType::CLOTHING)
		file = "object/factory/factory_crate_clothing.iff";
	else if(type == SceneObjectType::ELECTRONICS)
		file = "object/factory/factory_crate_electronics.iff";
	else if(type == SceneObjectType::FOOD || type == SceneObjectType::DRINK)
		file = "object/factory/factory_crate_food.iff";
	else if(type == SceneObjectType::FURNITURE)
		file = "object/factory/factory_crate_furniture.iff";
	else if(type & SceneObjectType::INSTALLATION)
		file = "object/factory/factory_crate_installation.iff";
	else if(type & SceneObjectType::WEAPON)
		file = "object/factory/factory_crate_weapon.iff";
	else
		file = "object/factory/factory_crate_generic_items.iff";

	SharedTangibleObjectTemplate* tanoData = dynamic_cast<SharedTangibleObjectTemplate*>(templateObject.get());

	if (tanoData == NULL)
		return NULL;

	ObjectManager* objectManager = ObjectManager::instance();

	Reference<FactoryCrate*> crate = (getZoneServer()->createObject(file.hashCode(), 2)).castTo<FactoryCrate*>();

	if (crate == NULL)
		return NULL;

	crate->setMaxCapacity(tanoData->getFactoryCrateSize());

	if (insertSelf) {
		if (!crate->transferObject(_this.get(), -1, false)) {
			crate->destroyObjectFromDatabase(true);
			return NULL;
		}
	} else {

		ManagedReference<TangibleObject*> protoclone = cast<TangibleObject*>( objectManager->cloneObject(_this.get()));

		if (protoclone == NULL) {
			crate->destroyObjectFromDatabase(true);
			return NULL;
		}

		protoclone->setParent(NULL);
		if (!crate->transferObject(protoclone, -1, false)) {
			protoclone->destroyObjectFromDatabase(true);
			crate->destroyObjectFromDatabase(true);
			return NULL;
		}
	}

	crate->setCustomObjectName(getCustomObjectName(), false);

	crate->setUseCount(1);

	return crate;
}

void TangibleObjectImplementation::addTemplateSkillMods(TangibleObject* targetObject) {
	SharedTangibleObjectTemplate* tano = dynamic_cast<SharedTangibleObjectTemplate*>(templateObject.get());

	if (tano == NULL)
		return;

	VectorMap<String, int>* mods = tano->getSkillMods();

	for (int i = 0; i < mods->size(); ++i) {
		VectorMapEntry<String, int> entry = mods->elementAt(i);

		targetObject->addSkillMod(SkillModManager::TEMPLATE, entry.getKey(), entry.getValue());
	}
}

void TangibleObjectImplementation::removeTemplateSkillMods(TangibleObject* targetObject) {
	SharedTangibleObjectTemplate* tano = dynamic_cast<SharedTangibleObjectTemplate*>(templateObject.get());

	if (tano == NULL)
		return;

	VectorMap<String, int>* mods = tano->getSkillMods();

	for (int i = 0; i < mods->size(); ++i) {
		VectorMapEntry<String, int> entry = mods->elementAt(i);

		targetObject->removeSkillMod(SkillModManager::TEMPLATE, entry.getKey(), entry.getValue());
	}
}

VectorMap<String, int>* TangibleObjectImplementation::getTemplateSkillMods() {
	SharedTangibleObjectTemplate* tano = dynamic_cast<SharedTangibleObjectTemplate*>(templateObject.get());

	if (tano == NULL)
		return NULL;

	return tano->getSkillMods();
}

bool TangibleObjectImplementation::canRepair(CreatureObject* player) {
	if (player == NULL || !isASubChildOf(player))
		return false;

	SceneObject* inventory = player->getSlottedObject("inventory");

	if (inventory == NULL)
		return false;

	for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
		ManagedReference<SceneObject*> item = inventory->getContainerObject(i);
		if(item->isRepairTool()) {
			Reference<RepairToolTemplate*> repairTemplate = cast<RepairToolTemplate*>(item->getObjectTemplate());

			if (repairTemplate == NULL) {
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

void TangibleObjectImplementation::repair(CreatureObject* player) {

	if(player == NULL || player->getZoneServer() == NULL)
		return;

	if(!isASubChildOf(player))
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

	SceneObject* inventory = player->getSlottedObject("inventory");
	if(inventory == NULL)
		return;

	ManagedReference<RepairTool*> repairTool = NULL;
	Reference<RepairToolTemplate*> repairTemplate = NULL;

	for(int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
		ManagedReference<SceneObject*> item = inventory->getContainerObject(i);
		if(item->isRepairTool()) {
			repairTemplate = cast<RepairToolTemplate*>(item->getObjectTemplate());

			if (repairTemplate == NULL) {
				error("No RepairToolTemplate for: " + String::valueOf(item->getServerObjectCRC()));
				return;
			}

			if(repairTemplate->getRepairType() & getGameObjectType()) {
				repairTool = cast<RepairTool*>(item.get());
				break;
			}
			repairTemplate = NULL;
		}
	}

	if(repairTool == NULL)
		return;

	/// Luck Roll + Profession Mod(25) + Luck Tapes
	/// + Station Mod - BF

	/// Luck Roll
	int roll = System::random(100);
	int repairChance = roll;

	/// Profession Bonus
	if(player->hasSkill(repairTemplate->getSkill()))
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
	if(playerMan->getNearbyCraftingStation(player, repairTemplate->getStationType()) != NULL) {
		repairChance += 15;
	}

	/// Subtract battle fatigue
	repairChance -= (player->getShockWounds() / 2);

	/// Subtract complexity
	repairChance -= (getComplexity() / 3);

	/// 5% random failure
	if(getMaxCondition() < 20 || roll < 5)
		repairChance = 0;

	if(roll > 95)
		repairChance = 100;

	String result = repairAttempt(repairChance);
	repairTool->destroyObjectFromWorld(true);
	repairTool->destroyObjectFromDatabase(true);

	player->sendSystemMessage(result);
}

ThreatMap* TangibleObjectImplementation::getThreatMap() {
	if (threatMap == NULL) {
		Reference<ThreatMap*> newMap = new ThreatMap(_this.get());

		threatMap.compareAndSet(NULL, newMap.get());
	}

	return threatMap;
}

bool TangibleObjectImplementation::isAttackableBy(CreatureObject* object) {
	if (isImperial() && !(object->isRebel())) {
		return false;
	} else if (isRebel() && !(object->isImperial())) {
		return false;
	} else if (object->isPlayerCreature() && object->getPlayerObject()) {
		if (isImperial() && (object->getPlayerObject())->getFactionStatus() == 0) {
			return false;
		}

		if (isRebel() && (object->getPlayerObject())->getFactionStatus() == 0) {
			return false;
		}

	} else if (object->isAiAgent()) {
		AiAgent* ai = cast<AiAgent*>(object);

		if (ai->getHomeObject() == _this.get()) {
			return false;
		}

		if (ai->isPet()) {
			ManagedReference<PetControlDevice*> pcd = ai->getControlDevice().get().castTo<PetControlDevice*>();
			if (pcd != NULL && pcd->getPetType() == PetManager::FACTIONPET && isNeutral()) {
				return false;
			}
		}
	}

	return pvpStatusBitmask & CreatureFlag::ATTACKABLE;
}

void TangibleObjectImplementation::addActiveArea(ActiveArea* area) {
	if (!area->isDeplyoed())
		area->deploy();

	activeAreas.put(area);
}

bool TangibleObjectImplementation::isCityStreetLamp(){
	return (templateObject != NULL && templateObject->getFullTemplateString().contains("object/tangible/furniture/city/streetlamp"));
}

bool TangibleObjectImplementation::isCityStatue(){
	return (templateObject != NULL && templateObject->getFullTemplateString().contains("object/tangible/furniture/city/statue"));
}

bool TangibleObjectImplementation::isCityFountain(){
	return (templateObject != NULL && templateObject->getFullTemplateString().contains("object/tangible/furniture/city/fountain"));
}
