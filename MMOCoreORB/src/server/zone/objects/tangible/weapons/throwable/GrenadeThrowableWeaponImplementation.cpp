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

#include "GrenadeThrowableWeaponImplementation.h"
#include "../../../player/Player.h"
#include "../../../creature/Creature.h"
#include "../../../../managers/item/ItemManager.h"
#include "../../TangibleObject.h"
#include "engine/engine.h"
#include "../../../../packets.h"

GrenadeThrowableWeaponImplementation::GrenadeThrowableWeaponImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn, bool eqp)
		: GrenadeThrowableWeaponServant(objid, tempcrc, n, tempn, TangibleObjectImplementation::TRAP,false) {
	init();
}

GrenadeThrowableWeaponImplementation::GrenadeThrowableWeaponImplementation(CreatureObject* creature, const String& temp, const UnicodeString& n, const String& tempn, bool eqp)
			: GrenadeThrowableWeaponServant(creature, temp, n, tempn, TangibleObjectImplementation::TRAP, false) {
	init();
}


void GrenadeThrowableWeaponImplementation::init() {
	objectSubType = TangibleObjectImplementation::THROWNWEAPON;

	setType(GRENADE);
	setCategory(ALL);

	setDamageType(ENERGY);
	setMinDamage(89);
	setMaxDamage(232);

	setAttackSpeed(4.0f);

	setRange(35);
	setArea(8.0f);
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
	setCertified(false);

	switch(objectCRC) {
		case 0xA943F10B:
			setArmorPiercing(NONE);
			setDamageType(ENERGY);
			setSkill("throwgrenade");
			break;
		case 0xA255B24C:
			setArmorPiercing(LIGHT);
			setDamageType(ENERGY);
			setSkill("throwgrenadefragmentation");
			setCert("cert_grenade_fragmentation");
			break;
		case 0x7F8BC760:
			setArmorPiercing(LIGHT);
			setDamageType(COLD);
			setSkill("throwgrenadecryoban");
			setCert("cert_grenade_cryoban");
			break;
		case 0x2382F2AD:
			setArmorPiercing(NONE);
			setDamageType(ACID);
			setSkill("throwgrenadeglop");
			setCert("cert_grenade_glop");
			break;
		case 0xF0940F10:
			setArmorPiercing(LIGHT);
			setDamageType(BLAST);
			setSkill("throwimperialdetonator");
			setCert("cert_grenade_imperial_detonator");
			break;
		case 0xF4107AED:
			setArmorPiercing(MEDIUM);
			setDamageType(BLAST);
			setCert("cert_grenade_thermal_detonator");
			setSkill("throwthermaldetonator");
			break;
		case 0x35E29637:
			setArmorPiercing(LIGHT);
			setDamageType(HEAT);
			setSkill("throwgrenadeproton");
			setCert("cert_grenade_proton");
			break;
		default:
			break;
		}
}

/*
 * Recieves the values from crafting.
 * \param DraftSchematic - the recently crafting schematic with value data
 */
void GrenadeThrowableWeaponImplementation::updateCraftingValues(DraftSchematic* draftSchematic){
	// Incoming values available
	//
	// unitIntegrity (Range: 1000 - 1000)
	// quality      (Range: 1 - 100)
	//***********************************

	setUsesRemaining(5);
	setArea(8.0f);
}

/*
 * Uses the object.
 * \param player The player using the object.
 */
int GrenadeThrowableWeaponImplementation::useObject(Player* player) {
	SceneObject* target = player->getTarget();

	if(target == NULL) {
		return 0;
	}

	if (!player->checkCertification(getCert())) {
		player->sendSystemMessage("This grenade is not certified");
		return 0;
	}

	if (!player->hasCooldownExpired(getSkill())) {
		player->sendSystemMessage("This grenade is not ready to be used again");
		return 0;
	}

	if (!player->isInRange(target,getRange())) {
		player->sendSystemMessage("Your target is too far away.");
		return 0;
	}

	//useCharge(player);
	StringBuffer cmd;
	cmd << "/throwgrenade "<< getObjectID();
	ExecuteConsoleCommand* msg =  new ExecuteConsoleCommand(cmd.toString());

	player->sendMessage(msg);
	//player->queueThrow((TangibleObject*)_this, getSkillCRC());
	//useCharge(player);
	return 1;
}

void GrenadeThrowableWeaponImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;
	AttributeListMessage* alm = new AttributeListMessage((TangibleObject*) _this);

	addAttributes(alm);
	player->sendMessage(alm);
}
void GrenadeThrowableWeaponImplementation::addAttributes(AttributeListMessage* alm) {
	//addHeaderAttributes(alm);
	WeaponImplementation::addAttributes(alm);

	addFooterAttributes(alm);
}

void GrenadeThrowableWeaponImplementation::addHeaderAttributes(AttributeListMessage* alm) {
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
void GrenadeThrowableWeaponImplementation::useCharge(Player* player) {

	decreaseUsesRemaining();
	updated = true;

	if (getUsesRemaining() == 0)
		remove(player);
	else
		sendDeltas(player);
}

void GrenadeThrowableWeaponImplementation::addFooterAttributes(AttributeListMessage* alm) {
	//alm->insertAttribute("healing_ability", getPlanet());
}

void GrenadeThrowableWeaponImplementation::sendDeltas(Player* player) {
	TangibleObjectDeltaMessage3 * dtano3 = new TangibleObjectDeltaMessage3((TangibleObject*)_this);
	dtano3->addIntUpdate(7, getUsesRemaining()); //Update the number of charges on the pack in inventory.
	dtano3->close();
	player->sendMessage(dtano3);
}

/*
 * Parses the items attributes.
 */
void GrenadeThrowableWeaponImplementation::parseItemAttributes() {
//	cout << "parse trap\n";
	ThrowableWeaponImplementation::parseItemAttributes();
	String attr = "area";
	setArea(itemAttributes->getFloatAttribute(attr));
}

void GrenadeThrowableWeaponImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
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
			omr->addRadialParent(10, 3, "@ui_radial:item_pickup");
		}
	}

	omr->finish();

	player->sendMessage(omr);

}

/*
 * Checks if the object is usefull.
 * \param player The player using the object.
 */
bool GrenadeThrowableWeaponImplementation::isUsefull(Player* player) {
//	cout << "is usefull: " <<  player->hasSkill(getSkillCRC()) << "\n";
	return player->hasSkill(getSkillCRC());
}
