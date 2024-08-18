/*
 * CreatureImplementation.cpp
 *
 *  Created on: 10/23/2010
 *      Author: Kyle
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/ai/Creature.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/creature/events/DespawnCreatureTask.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

//#define DEBUG

void CreatureImplementation::initializeTransientMembers() {
	milkState = CreatureManager::NOTMILKED;
	dnaState = CreatureManager::HASDNA;
	dnaSampleCount = 0;
	AiAgentImplementation::initializeTransientMembers();
}

void CreatureImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	AiAgentImplementation::fillObjectMenuResponse(menuResponse, player);

	if (canMilkMe(player)) {

		menuResponse->addRadialMenuItem(112, 3, "@pet/pet_menu:milk_me");

	} else if (canHarvestMe(player)) {

		menuResponse->addRadialMenuItem(112, 3, "@sui:harvest_corpse");

		if (getMeatType() != "")
			menuResponse->addRadialMenuItemToRadialID(112, 234, 3, "@sui:harvest_meat");

		if (getHideType() != "")
			menuResponse->addRadialMenuItemToRadialID(112, 235, 3, "@sui:harvest_hide");

		if (getBoneType() != "")
			menuResponse->addRadialMenuItemToRadialID(112, 236, 3, "@sui:harvest_bone");
	}

	if (canTameMe(player) && player->hasSkill("outdoors_creaturehandler_novice") && getChanceToTame(player) >= 15) {
		menuResponse->addRadialMenuItem(159, 3, "@pet/pet_menu:menu_tame");
	}
}

int CreatureImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	auto zone = getZone();

	if (zone == nullptr)
		return 0;

	if (!(_this.getReferenceUnsafeStaticCast()->isDead())) {
		if (selectedID == 112) {
			zone->getCreatureManager()->milk(_this.getReferenceUnsafeStaticCast(), player);
		}
	} else {
		if ((selectedID == 112 || selectedID == 234 || selectedID == 235 || selectedID == 236)) {
			zone->getCreatureManager()->harvest(_this.getReferenceUnsafeStaticCast(), player, selectedID);

			return 0;
		}
	}

	if (selectedID == 159) {
		zone->getCreatureManager()->tame(_this.getReferenceUnsafeStaticCast(), player);
	}

	return AiAgentImplementation::handleObjectMenuSelect(player, selectedID);
}

void CreatureImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player) {
	AiAgentImplementation::fillAttributeList(alm, player);

	int creaKnowledge = player != nullptr ?  player->getSkillMod("creature_knowledge") : 100;

	if (getHideType().isEmpty() && getBoneType().isEmpty() && getMeatType().isEmpty()) {
		if(!isPet()) // we do want to show this for pets
			return;
	}

	if (creaKnowledge >= 5) {
		if (player != nullptr && isAggressiveTo(player))
			alm->insertAttribute("aggro", "yes");
		else
			alm->insertAttribute("aggro", "no");
		if (isStalker())
			alm->insertAttribute("stalking", "yes");
		else
			alm->insertAttribute("stalking", "no");
	}

	if (creaKnowledge >= 10) {
		if (getTame() > 0.0f)
			alm->insertAttribute("tamable", "yes");
		else
			alm->insertAttribute("tamable", "no");
	}

	if (creaKnowledge >= 20 && !isPet()) {
		if (!getHideType().isEmpty()) {
			StringBuffer hideName;
			hideName << "@obj_attr_n:" << getHideType();
			alm->insertAttribute("res_hide", hideName.toString());
		} else
			alm->insertAttribute("res_hide", "---");
		if (!getBoneType().isEmpty()) {
			StringBuffer boneName;
			boneName << "@obj_attr_n:" << getBoneType();
			alm->insertAttribute("res_bone", boneName.toString());
		} else
			alm->insertAttribute("res_bone", "---");
		if (!getMeatType().isEmpty()) {
			StringBuffer meatName;
			meatName << "@obj_attr_n:" << getMeatType();
			alm->insertAttribute("res_meat", meatName.toString());
		} else
			alm->insertAttribute("res_meat", "---");
	}

	if (creaKnowledge >= 30) {
		if (isKiller())
			alm->insertAttribute("killer", "yes");
		else
			alm->insertAttribute("killer", "no");
	}

	if (creaKnowledge >= 40) {
		alm->insertAttribute("ferocity", (int) getFerocity());
	}

	if (creaKnowledge >= 45)
		alm->insertAttribute("challenge_level", getAdultLevel());

	//int skillNum = skillCommands.size();
	const CreatureAttackMap* attackMap = getAttackMap();
	int skillNum = 0;
	if (attackMap != nullptr)
		skillNum = attackMap->size();
	if (creaKnowledge >= 70) {
		String skillname = "";
		if (skillNum >= 1)
			skillname = attackMap->getCommand(0);

		if (skillname == "creatureareaattack")
			skillname = "unknown_attack";
		else if (skillname.isEmpty())
			skillname = "none";

		StringBuffer skillMsg;
		skillMsg << "@combat_effects:" << skillname;

		alm->insertAttribute("pet_command_18", skillMsg.toString());
	}

	if (creaKnowledge >= 80) {
		String skillname = "";
		if (skillNum >= 2)
			skillname = attackMap->getCommand(1);

		if (skillname == "creatureareaattack")
			skillname = "unknown_attack";
		else if (skillname.isEmpty())
			skillname = "none";

		StringBuffer skillMsg;
		skillMsg << "@combat_effects:" << skillname;

		alm->insertAttribute("pet_command_19", skillMsg.toString());
	}

	if (creaKnowledge >= 90)
		alm->insertAttribute("basetohit", getChanceHit());

	if (creaKnowledge >= 100) {
		StringBuffer damageMsg;
		damageMsg << getDamageMin() << "-" << getDamageMax();
		alm->insertAttribute("cat_wpn_damage", damageMsg.toString());
	}
}

bool CreatureImplementation::hasOrganics() {
	return ((getHideMax() + getBoneMax() + getMeatMax()) > 0);
}

bool CreatureImplementation::hasDNA() {
	if (isBaby()) {
		return false;
	}
	if (isPet() && !hasPetDeed()) {
		return false;
	}
	// skip droids and anything that doesnt have organic bits or it doesnt eat
	if (isDroidObject() || !hasOrganics() || getDiet() == ObjectFlag::NONE) {
		return false;
	}
	return (dnaState == CreatureManager::HASDNA);
}


bool CreatureImplementation::hasMilk() {
	if (isBaby())
		return false;

	return (getMilk() > 0);
}

void CreatureImplementation::addAlreadyHarvested(CreatureObject* player) {
	alreadyHarvested.put(player->getObjectID());
}

void CreatureImplementation::setMilkState(short milk) {
	milkState = milk;
}
void CreatureImplementation::setDnaState(short dna){
	dnaState = dna;
}
void CreatureImplementation::notifyDespawn(Zone* zone) {
	alreadyHarvested.removeAll();
	dnaState = CreatureManager::HASDNA;
	dnaSampleCount = 0;
	milkState = CreatureManager::NOTMILKED;
	baby = false;
	AiAgentImplementation::notifyDespawn(zone);
}

bool CreatureImplementation::canHarvestMe(CreatureObject* player) {

	if(!player->isInRange(_this.getReferenceUnsafeStaticCast(), 10.0f) || player->isInCombat() || !player->hasSkill("outdoors_scout_novice")
			|| player->isDead() || player->isIncapacitated() || isPet())
		return false;

	if (!hasOrganics())
		return false;

	if (player->getSkillMod("creature_harvesting") < 1)
		return false;

	if (alreadyHarvested.contains(player->getObjectID()))
		return false;

	SceneObject* creatureInventory = getSlottedObject("inventory");

	if (creatureInventory == nullptr)
		return false;

	uint64 lootOwnerID = creatureInventory->getContainerPermissions()->getOwnerID();

	if (player->getObjectID() == lootOwnerID || (player->isGrouped() && player->getGroupID() == lootOwnerID))
		return true;

	return false;
}
bool CreatureImplementation::canDroidHarvestMe(CreatureObject* player,CreatureObject* droid) {

	// droid should be able to harvest if in range, with current AI
	if(!droid->isInRange(_this.getReferenceUnsafeStaticCast(), (10.0f + droid->getTemplateRadius() + getTemplateRadius())) || droid->isInCombat() || !player->hasSkill("outdoors_scout_novice")
			|| droid->isDead() || droid->isIncapacitated() || isPet()) {
		return false;
	}

	if (!hasOrganics()) {
		return false;
	}

	if (player->getSkillMod("creature_harvesting") < 1) {
		return false;
	}

	if (alreadyHarvested.contains(player->getObjectID())) {
		return false;
	}

	SceneObject* creatureInventory = getSlottedObject("inventory");

	if (creatureInventory == nullptr) {
		return false;
	}

	uint64 lootOwnerID = creatureInventory->getContainerPermissions()->getOwnerID();

	if (player->getObjectID() == lootOwnerID || (player->isGrouped() && player->getGroupID() == lootOwnerID))
		return true;
	return false;
}

bool CreatureImplementation::hasSkillToHarvestMe(CreatureObject* player) {

	if(!player->hasSkill("outdoors_scout_novice"))
		return false;

	if (!hasOrganics())
		return false;

	if (player->getSkillMod("creature_harvesting") < 1)
		return false;

	if (alreadyHarvested.contains(player->getObjectID()))
		return false;

	if (dnaState == CreatureManager::DNADEATH)
		return false;
	return true;
}

bool CreatureImplementation::canTameMe(CreatureObject* player) {
	if (!isBaby() || _this.getReferenceUnsafeStaticCast()->isInCombat() || _this.getReferenceUnsafeStaticCast()->isDead() || isPet())
		return false;

	if(player->isInCombat() || player->isDead() || player->isIncapacitated() || player->isRidingMount())
		return false;

	return true;
}

float CreatureImplementation::getChanceToTame(CreatureObject* player) {
	int skill = player->getSkillMod("tame_bonus");
	int cl = npcTemplate->getLevel();
	int ferocity = getFerocity();
	float tamingChance = getTame() * 100.0f;

	if (isVicious())
		skill += player->getSkillMod("tame_aggro");
	else
		skill += player->getSkillMod("tame_non_aggro");

	float chanceToTame = tamingChance + skill - (cl + ferocity);

	return chanceToTame;
}

bool CreatureImplementation::isVicious() {
	CreatureTemplate* creatureTemplate = npcTemplate.get();

	return creatureTemplate->getPvpBitmask() & ObjectFlag::AGGRESSIVE;
}

bool CreatureImplementation::canMilkMe(CreatureObject* player) {
	if (player == nullptr)
		return false;

	if (!hasMilk() || milkState != CreatureManager::NOTMILKED  || _this.getReferenceUnsafeStaticCast()->isInCombat() || _this.getReferenceUnsafeStaticCast()->isDead() || isPet())
		return false;

	if(!player->isInRange(_this.getReferenceUnsafeStaticCast(), 7.0f) || player->isInCombat() || player->isDead() || player->isIncapacitated() || !(player->hasState(CreatureState::MASKSCENT)))
		return false;

	return true;
}

bool CreatureImplementation::hasBeenMilked() const {
	return milkState == CreatureManager::ALREADYMILKED;
}

bool CreatureImplementation::hasSkillToSampleMe(CreatureObject* player) {

	if(!player->hasSkill("outdoors_bio_engineer_novice"))
		return false;

	if (!hasDNA())
		return false;

	int skillMod = player->getSkillMod("dna_harvesting");
	int cl = _this.getReferenceUnsafeStaticCast()->getLevel();
	// Skill Mod Check, you need atleast x skill points to be able to sample x level unless creature > 13k ham or CL 75 (we only generated values to 75)
	if (skillMod < 1 || cl > skillMod + 15)
		return false;

	if (dnaState == CreatureManager::DNASAMPLED)
		return false;

	return true;
}

bool CreatureImplementation::canCollectDna(CreatureObject* player) {
	if (!hasDNA() ||  _this.getReferenceUnsafeStaticCast()->isInCombat() || _this.getReferenceUnsafeStaticCast()->isDead() || !player->hasSkill("outdoors_bio_engineer_novice")){
		return false;
	}
	if (player->getSkillMod("dna_harvesting") < 1)
		return false;

	if (_this.getReferenceUnsafeStaticCast()->isNonPlayerCreatureObject()) {
		return false;
	}
	if(!player->isInRange(_this.getReferenceUnsafeStaticCast(), 16.0f) || player->isInCombat() || player->isDead() || player->isIncapacitated() ){
		return false;
	}

	return true;
}

void CreatureImplementation::loadTemplateDataForBaby(CreatureTemplate* templateData) {
	loadTemplateData(templateData);

	setCustomObjectName(getDisplayedName() + " (baby)", false);

	setHeight(templateData->getScale() * 0.46, false);

	int newLevel = level / 10;
	if (newLevel < 1)
		newLevel = 1;

	setLevel(newLevel, false);

	setBaby(true);

	clearPvpStatusBit(ObjectFlag::AGGRESSIVE, false);
	clearPvpStatusBit(ObjectFlag::ENEMY, false);
	addObjectFlag(ObjectFlag::BABY);

	/*
	auto inventory = getInventory();
	int invSize  = inventory->getContainerObjectsSize();

	if (invSize > 1) {
		StringBuffer msg;
		msg << "\033[32m" << getDisplayedName() << " ID: " << getObjectID() << " Inventory size: " << inventory->getContainerObjectsSize() << endl;


		for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
			auto object = inventory->getContainerObject(i);

			msg << getDisplayedName() << " ID: " << getObjectID() << "Inventory - #" << i << " Item: " << object->getObjectNameStringIdName() << " -- " << object->getObjectTemplate()->getTemplateFileName() << " ID: " << object->getObjectID() << endl;
		}

		info(true) << msg.toString() << "\033[0m";
	}
	*/
}

void CreatureImplementation::setPetLevel(int newLevel) {
	if (newLevel == 0)
		return;

	int oldLevel = level;

	CreatureObjectImplementation::setLevel(newLevel);

	if (getCreatureTemplate() == nullptr) {
		return;
	}

	Creature* thisCreature = _this.getReferenceUnsafeStaticCast();

	clearBuffs(false, false);

	int baseLevel = getTemplateLevel();

	float minDmg = calculateAttackMinDamage(baseLevel);
	float maxDmg = calculateAttackMaxDamage(baseLevel);

	float ratio = ((float)newLevel) / (float)baseLevel;
	minDmg *= ratio;
	maxDmg *= ratio;

	ManagedReference<WeaponObject*> defaultWeap = getDefaultWeapon();
	ManagedReference<WeaponObject*> primaryWeap = getPrimaryWeapon();

	if (primaryWeap != nullptr && primaryWeap != defaultWeap) {
		Locker primLock(primaryWeap, thisCreature);

		float mod = 1.f - 0.1f*float(primaryWeap->getArmorPiercing());

		primaryWeap->setMinDamage(minDmg * mod);
		primaryWeap->setMaxDamage(maxDmg * mod);
	}

	if (defaultWeap != nullptr) {
		Locker defLock(defaultWeap, thisCreature);

		defaultWeap->setMinDamage(minDmg);
		defaultWeap->setMaxDamage(maxDmg);
	}

	int ham = 0;

	for (int i = 0; i < 9; ++i) {
		if (i % 3 == 0) {
			ham = (getBaseHAM(i) / oldLevel) * newLevel;
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

int CreatureImplementation::getAdultLevel() {
	auto creatureDeed = getPetDeed();

	// Pet Deed is not null, use the level from that
	if (creatureDeed != nullptr) {
		return creatureDeed->getLevel();
	}

	if (npcTemplate != nullptr) {
		return npcTemplate->getLevel();
	}

	// Just use the creatures level
	return getLevel();
}

bool CreatureImplementation::isMount() {
	if (!isPet())
		return false;

	ManagedReference<PetControlDevice*> pcd = getControlDevice().get().castTo<PetControlDevice*>();
	if (pcd == nullptr)
		return false;

	if (pcd->isTrainedAsMount())
		return true;

	return false;
}

void CreatureImplementation::sendMessage(BasePacket* msg) {
	if (!isMount()) {
#ifdef LOCKFREE_BCLIENT_BUFFERS
		if (!msg->getReferenceCount())
#endif
		delete msg;
		return;
	}

	ManagedReference<CreatureObject* > linkedCreature = this->linkedCreature.get();

	if (linkedCreature != nullptr && linkedCreature->getParent().get() == _this.getReferenceUnsafeStaticCast())
		linkedCreature->sendMessage(msg);
	else {
#ifdef LOCKFREE_BCLIENT_BUFFERS
		if (!msg->getReferenceCount())
#endif
		delete msg;
	}
}
