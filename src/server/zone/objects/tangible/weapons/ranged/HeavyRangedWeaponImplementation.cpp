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
#include "engine/engine.h"

#include "HeavyRangedWeaponImplementation.h"
#include "../../../player/Player.h"
#include "../../../../managers/item/ItemManager.h"
#include "../../TangibleObject.h"
#include "../../../../packets.h"

HeavyRangedWeaponImplementation::HeavyRangedWeaponImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn, bool eqp)
		: HeavyRangedWeaponServant(objid, tempcrc, n, tempn, HEAVYWEAPON, eqp) {
	init();
}

HeavyRangedWeaponImplementation::HeavyRangedWeaponImplementation(CreatureObject* creature, const String& temp, const UnicodeString& n, const String& tempn, bool eqp)
		: HeavyRangedWeaponServant(creature, temp, n, tempn, HEAVYWEAPON, eqp) {
	init();
}

void HeavyRangedWeaponImplementation::init() {
	setAttackSpeed(7.1f);

	setMinDamage(678);
	setMaxDamage(1217);
	setWoundsRatio(36);

	setPointBlankAccuracy(-100);
	setPointBlankRange(0);

	setIdealAccuracy(22);
	setIdealRange(48);

	setMaxRangeAccuracy(21);
	setMaxRange(64);

	setHealthAttackCost(114);
	setActionAttackCost(75);
	setMindAttackCost(65);

	setObjectSubType(TangibleObjectImplementation::HEAVYWEAPON);
	setUsesRemaining(50);
	setCategory(TangibleObjectImplementation::HEAVYWEAPON);

	switch(objectCRC) {
		case 0xB4202597:
			setType(HEAVYROCKETLAUNCHER);
			setDamageType(BLAST);
			setArmorPiercing(HEAVY);
			setSpeedSkillMod("heavy_rocket_launcher_speed");

			setSkill("firerocketlauncher");
			setCert("cert_heavy_rocket_launcher");
			setArea(8.0f);
			break;
		case 0x3FF5F042:
			setType(HEAVYLIGHTNINGBEAM);
			setDamageType(ENERGY);
			setArmorPiercing(HEAVY);
			setSpeedSkillMod("heavy_lightning_beam_speed");

			setSkill("firelightningbeam");
			setCert("cert_heavy_lightning_beam");
			setArea(8.0f);
			break;
		case 0x1419A31E:
			setType(HEAVYACIDBEAM);
			setDamageType(ACID);
			setArmorPiercing(MEDIUM);
			setSpeedSkillMod("heavy_acid_beam_speed");

			setSkill("fireacidbeam");
			setCert("cert_heavy_acid_beam");
			setArea(8.0f);
			break;
		case 0x55FD0A8C:
			setType(HEAVYPARTICLEBEAM);
			setDamageType(ENERGY);
			setArmorPiercing(MEDIUM);
			setSpeedSkillMod("heavy_particle_beam_speed");

			setSkill("fireparticlebeam");
			setCert("cert_heavy_particle_beam");
			setArea(8.0f);
			break;
	}
	setXpType();
}

int HeavyRangedWeaponImplementation::useObject(Player* player) {
	SceneObject* obj = player->getTarget();

	if (obj == NULL) {
		player->sendSystemMessage("Invalid target");
		return 0;
	}

	if (!obj->isPlayer() && !obj->isNonPlayerCreature()) {
		player->sendSystemMessage("Invalid target");
		return 0;
	}

	StringBuffer cmd;
	cmd << "/fireheavyweapon "<< getObjectID();
	ExecuteConsoleCommand* msg =  new ExecuteConsoleCommand(cmd.toString());
	player->sendMessage(msg);
	/*player->doCombatAnimation((CreatureObject*)obj, 0x683374B3, true);

	int healthDmg = System::random((int)maxDamage - (int)minDamage) + (int)minDamage;
	int actionDmg = System::random((int)maxDamage - (int)minDamage) + (int)minDamage;
	int mindDmg = System::random((int)maxDamage - (int)minDamage) + (int)minDamage;

	((CreatureObject*)obj)->changeHAMBars(-healthDmg, -actionDmg, -mindDmg, true);

	if (!decreaseUsesRemaining()) {
		//remove(player, false);
		return 0;
	}
	 */
	return 0;
}

void HeavyRangedWeaponImplementation::remove(Player* player) {
	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();

	itemManager->deletePlayerItem(player, _this, false);

	player->removeInventoryItem(objectID);

	BaseMessage* msg = new SceneObjectDestroyMessage(objectID);
	player->sendMessage(msg);
}

void HeavyRangedWeaponImplementation::activateSkill(Player* player) {
	System::out << "activate skill\n";
	player->fireHeavyWeapon((TangibleObject*)_this, getSkillCRC());
}

void HeavyRangedWeaponImplementation::setSkill(const String& sk) {
	skillName = sk;
	String attr = "skillName";
	itemAttributes->setStringAttribute(attr,skillName);
	setSkillCRC(skillName.hashCode());
}
String& HeavyRangedWeaponImplementation::getSkill() {
	return skillName;
}

uint32 HeavyRangedWeaponImplementation::getSkillCRC() {
	return skill;
}

void HeavyRangedWeaponImplementation::setSkillCRC(const uint32 sk) {
	skill = sk;
}

void HeavyRangedWeaponImplementation::parseItemAttributes() {
	WeaponImplementation::parseItemAttributes();
	String attr = "skillName";
	setSkill(itemAttributes->getStringAttribute(attr));
}

void HeavyRangedWeaponImplementation::useCharge(Player* player) {

	decreaseUsesRemaining();
	updated = true;

	if (getUsesRemaining() == 0)
		remove(player);
	else
		sendDeltas(player);
}

void HeavyRangedWeaponImplementation::sendDeltas(Player* player) {
	TangibleObjectDeltaMessage3 * dtano3 = new TangibleObjectDeltaMessage3((TangibleObject*)_this);
	dtano3->addIntUpdate(7, getUsesRemaining()); //Update the number of charges on the pack in inventory.
	dtano3->close();
	player->sendMessage(dtano3);
}
