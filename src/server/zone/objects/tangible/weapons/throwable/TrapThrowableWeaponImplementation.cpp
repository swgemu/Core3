/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
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

/*
 * Uses the object.
 * \param player The player using the object.
 */
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


	if (!player->hasCooldownExpired(getSkill())) {
		player->sendSystemMessage("trap/trap", "sys_not_ready");
		return 0;
	}

	ManagedReference<SceneObject> obj = player->getTarget();
	if (obj == NULL || !obj->isNonPlayerCreature()) {
		player->sendSystemMessage("trap/trap", "sys_cannot_throw");
		return 0;
	}

	Creature* target = (Creature*) obj.get();
	if (!target->isCreature()) {
		player->sendSystemMessage("trap/trap", "sys_creatures_only");
		return 0;
	}

	useCharge(player);
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

/*
 * Uses a charge of the object. Ramoves the object if 0 charges left
 * \param player The player.
 */
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

/*
 * Parses the items attributes.
 */
void TrapThrowableWeaponImplementation::parseItemAttributes() {
//	cout << "parse trap\n";
	ThrowableWeaponImplementation::parseItemAttributes();
}

/*
 * Checks if the object is usefull.
 * \param player The player using the object.
 */
bool TrapThrowableWeaponImplementation::isUsefull(Player* player) {
//	cout << "is usefull: " <<  player->hasSkill(getSkillCRC()) << "\n";
	return player->hasSkill(getSkillCRC());
}

void TrapThrowableWeaponImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	if (player->getInventoryItem(getObjectID()) != NULL) {

	/*	if (!isSliced() && player->getSlicingAbility() >= 2)
			omr->addRadialItem(0, 69, 3, "Slice");

		omr->addRadialItem(0, 70, 3, "Repair");

		if (hasPowerup())
			omr->addRadialItem(0, 71, 3, "Remove Powerup");*/
	}

	//TODO:Cell permission check
	if (_this->getParent() != NULL) {
		bool cellPermission = true;

		if (_this->getParent()->isCell() && cellPermission) {
			omr->addRadialItem(0, 10, 3, "Pickup");
		}
	}

	omr->finish();

	player->sendMessage(omr);

}
