/*
 * ThrowableWeaponImplementaton.cpp
 *
 *  Created on: Oct 23, 2008
 *      Author: swgdev
 */

#include "ThrowableWeaponImplementation.h"
#include "../../player/Player.h"
#include "../../../managers/item/ItemManager.h"
#include "../TangibleObject.h"
#include "engine/engine.h"
#include "../../../packets.h"

ThrowableWeaponImplementation::ThrowableWeaponImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn, const int tp, bool eqp)
		: ThrowableWeaponServant(objid, tempcrc, n, tempn, tp, false) {
	initialize();
}

ThrowableWeaponImplementation::ThrowableWeaponImplementation(CreatureObject* creature, const String& temp, const UnicodeString& n, const String& tempn, const int tp, bool eqp)
			: ThrowableWeaponServant(creature, temp, n, tempn, tp, false) {
	initialize();
}


void ThrowableWeaponImplementation::initialize() {
	objectSubType = TangibleObjectImplementation::TRAP;

	setType(TRAP);
	setCategory(ALL);

	setDamageType(KINETIC);
	setMinDamage(89);
	setMaxDamage(232);

	setAttackSpeed(1.0f);

	setRange(45);

	setPointBlankAccuracy(-30);
	setPointBlankRange(0);

	setIdealAccuracy(60);
	setIdealRange(30);

	setMaxRangeAccuracy(-85);
	setMaxRange(32);
	setArmorPiercing(NONE);

	setHealthAttackCost(17);
	setActionAttackCost(30);
	setMindAttackCost(17);

	setEquipped(false);
}

void ThrowableWeaponImplementation::remove(Player* player) {
	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();

	itemManager->deletePlayerItem(player, _this, false);

	player->removeInventoryItem(objectID);

	BaseMessage* msg = new SceneObjectDestroyMessage(objectID);
	player->sendMessage(msg);
}

int ThrowableWeaponImplementation::useObject(Player* player) {

	if (!isUsefull(player)) {
		player->sendSystemMessage("No Skill, Not Certified");
		return 0;
	}

	player->queueThrow((TangibleObject*)_this, getSkillCRC());

	return 1;
}

void ThrowableWeaponImplementation::setSkill(const String& sk) {
	setSkillCRC(sk.hashCode());
}

int ThrowableWeaponImplementation::getSkillCRC() {
	return skill;
}

void ThrowableWeaponImplementation::setSkillCRC(const int sk) {
	skill = sk;
	String attr = "skill";
	itemAttributes->setIntAttribute(attr,skill);
}

void ThrowableWeaponImplementation::parseItemAttributes() {
//	cout << "parse trap\n";
	WeaponImplementation::parseItemAttributes();
	String attr = "skill";
	setSkillCRC(itemAttributes->getIntAttribute(attr));
}

bool ThrowableWeaponImplementation::isUsefull(Player* player) {
	return true;
}

