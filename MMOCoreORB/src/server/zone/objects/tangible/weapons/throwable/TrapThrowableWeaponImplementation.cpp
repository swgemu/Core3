/*
 * ThrowableWeaponImplementaton.cpp
 *
 *  Created on: Oct 23, 2008
 *      Author: swgdev
 */

#include "TrapThrowableWeaponImplementation.h"
#include "../../../player/Player.h"
#include "../../../creature/Creature.h"
#include "../../../../managers/item/ItemManager.h"
#include "../../TangibleObject.h"
#include "engine/engine.h"
#include "../../../../packets.h"

TrapThrowableWeaponImplementation::TrapThrowableWeaponImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn, bool eqp)
		: TrapThrowableWeaponServant(objid, tempcrc, n, tempn, TangibleObjectImplementation::TRAP,false) {
	initialize();
}

TrapThrowableWeaponImplementation::TrapThrowableWeaponImplementation(CreatureObject* creature, const String& temp, const UnicodeString& n, const String& tempn, bool eqp)
			: TrapThrowableWeaponServant(creature, temp, n, tempn, TangibleObjectImplementation::TRAP, false) {
	initialize();
}


void TrapThrowableWeaponImplementation::initialize() {
	objectSubType = TangibleObjectImplementation::TRAP;

	setType(TRAP);
	setCategory(ALL);

	setXpType();

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

int TrapThrowableWeaponImplementation::useObject(Player* player) {

	String skillBox = "outdoors_scout_novice";

	if (!player->hasSkillBox(skillBox)) {
		player->sendSystemMessage("trap/trap", "trap_no_skill");
		return 0;
	}

	if (!isUsefull(player)) {
		player->sendSystemMessage("trap/trap", "trap_no_skill_this");
		return 0;
	}

	Creature* target = (Creature*) player->getTarget();

	if(target == NULL) {
		player->sendSystemMessage("trap/trap", "sys_cannot_throw");
		return 0;
	}

	if(!target->isCreature()) {
		player->sendSystemMessage("trap/trap", "sys_creatures_only");
		return 0;
	}

	player->queueThrow((TangibleObject*)_this, getSkillCRC());

	return 1;
}

void TrapThrowableWeaponImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;
	AttributeListMessage* alm = new AttributeListMessage((TangibleObject*) _this);

	addAttributes(alm);

	player->sendMessage(alm);
}
void TrapThrowableWeaponImplementation::addAttributes(AttributeListMessage* alm) {
	addHeaderAttributes(alm);
	addFooterAttributes(alm);
}

void TrapThrowableWeaponImplementation::addHeaderAttributes(AttributeListMessage* alm) {
	alm->insertAttribute("volume", "1");
	alm->insertAttribute("counter_uses_remaining", getUsesRemaining());

	if(craftersName != ""){
		alm->insertAttribute("crafter", craftersName);
	}

	if(craftedSerial != ""){
		alm->insertAttribute("serial_number", craftedSerial);
	}
}

void TrapThrowableWeaponImplementation::useCharge(Player* player) {

	decreaseUsesRemaining();
	updated = true;

	if (getUsesRemaining() == 0)
		remove(player);
	else
		sendDeltas(player);
}

void TrapThrowableWeaponImplementation::addFooterAttributes(AttributeListMessage* alm) {
	//alm->insertAttribute("healing_ability", getPlanet());
}

void TrapThrowableWeaponImplementation::sendDeltas(Player* player) {
	TangibleObjectDeltaMessage3 * dtano3 = new TangibleObjectDeltaMessage3((TangibleObject*)_this);
	dtano3->addIntUpdate(7, getUsesRemaining()); //Update the number of charges on the pack in inventory.
	dtano3->close();
	player->sendMessage(dtano3);
}
void TrapThrowableWeaponImplementation::parseItemAttributes() {
//	cout << "parse trap\n";
	WeaponImplementation::parseItemAttributes();
	String attr = "skill";
	setSkillCRC(itemAttributes->getIntAttribute(attr));
}

bool TrapThrowableWeaponImplementation::isUsefull(Player* player) {
//	cout << "is usefull: " <<  player->hasSkill(getSkillCRC()) << "\n";
	return player->hasSkill(getSkillCRC());
}
