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

