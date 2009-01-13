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

#include "../../../managers/item/ItemManager.h"
#include "CampSite.h"

#include "../TangibleObject.h"

#include "engine/engine.h"

#include "CampKitImplementation.h"
#include "events/CampSpawnEvent.h"

#include "../../../packets.h"
CampKitImplementation::CampKitImplementation(unsigned long long oid, unsigned int tempCRC, const UnicodeString& n, const String& tempn)
	: CampKitServant(oid, CAMPKIT) {
		objectCRC = tempCRC;

		templateTypeName = "obj_n";
		templateName = tempn;

		name = n;

		setUsesRemaining(5);
		setXP(320);
		setDuration(60);
		setCampType(0);

		setEquipped(false);

}
CampKitImplementation::CampKitImplementation(Player* player, unsigned int tempCRC, const UnicodeString& n, const String& tempn)
: CampKitServant(player->getNewItemID(), CAMPKIT) {
	objectCRC = tempCRC;

	templateTypeName = "obj_n";
	templateName = tempn;

	name = n;

	setUsesRemaining(5);
	setXP(320);
	setDuration(60);
	setCampType(0);
	setEquipped(false);

	setContainer((TangibleObject*) player->getInventory(), 0xFFFFFFFF);

    setEquipped(false);

}

/*
 * Uses the object.
 * \param player The player using the object.
 */
int CampKitImplementation::useObject(Player* player) {
	if (!isUsefull(player))
		return 1;
	CampSite* campSite = new CampSite(player, player->getNewItemID(), _this);
	campSite->setZoneProcessServer(player->getZoneProcessServer());
	campSite->initializePosition(player->getPositionX(), player->getPositionZ(), player->getPositionY());
	campSite->setDirection(0,0,0,0);

	//	campSite->insertToZone(player->getZone()); // need to do a temp structure
	//	campSite->createCampArea();

	player->setCamp(campSite);
	player->sendSystemMessage("@camp:starting_camp");
	CampSpawnEvent* event = new CampSpawnEvent(campSite,5000);
	player->getZoneProcessServer()->addEvent(event);

	return 1;
}

bool CampKitImplementation::isUsefull(Player* player) {
	if (player->isInANoBuildArea()) {
		player->sendSystemMessage("@camp:error_nobuild");
		return false;
	} else if (player->hasCamp()) {
		player->sendSystemMessage("@camp:sys_already_camping");
		return false;
	} else if (!player->isStanding()) {
		player->sendSystemMessage("@camp:error_cmd_fail");
		return false;
	}/* else if (!player->isInCombat()) {
		player->sendSystemMessage("@camp:sys_not_in_combat");
		return false;
	} */else if (player->isInCamp()) {
		player->sendSystemMessage("@camp:error_camp_too_close");
		return false;
	} else {
		return true;
	}
}

/*
 * Uses a charge oh the camo kit. If 0 uses are left, it is removed from the inventory.
 * \param player The player that uses the camo kit.
 */
void CampKitImplementation::useCharge(Player* player) {
	if (usesRemaining <= 0) {
		remove(player);
		return;
	}

	setUsesRemaining(getUsesRemaining() - 1);
	updated = true;

	if (usesRemaining == 0)
		remove(player);
}



/*
 * Removes the camo kit from the inventory.
 * \param player The player.
 */
void CampKitImplementation::remove(Player* player) {
	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();

	itemManager->deletePlayerItem(player, _this, false);

	player->removeInventoryItem(objectID);

	BaseMessage* msg = new SceneObjectDestroyMessage(objectID);
	player->sendMessage(msg);
}

void CampKitImplementation::sendDeltas(Player* player) {
	TangibleObjectDeltaMessage3 * dtano3 = new TangibleObjectDeltaMessage3((TangibleObject*)_this);
	dtano3->addIntUpdate(7, (getUsesRemaining() == 1) ? 0 : getUsesRemaining()); //Update the number of charges on the pack in inventory.
	dtano3->close();
	player->sendMessage(dtano3);
}

void CampKitImplementation::addHeaderAttributes(AttributeListMessage* alm) {
	alm->insertAttribute("volume", "1");
	alm->insertAttribute("counter_uses_remaining", getUsesRemaining());

	if(craftersName != ""){
		alm->insertAttribute("crafter", craftersName);
	}

	if(craftedSerial != ""){
		alm->insertAttribute("serial_number", craftedSerial);
	}
}

void CampKitImplementation::addFooterAttributes(AttributeListMessage* alm) {
	//alm->insertAttribute("healing_ability", getPlanet());
}

void CampKitImplementation::addAttributes(AttributeListMessage* alm) {
	addHeaderAttributes(alm);
	addFooterAttributes(alm);
}

void CampKitImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;
	AttributeListMessage* alm = new AttributeListMessage((TangibleObject*) _this);

	addAttributes(alm);

	player->sendMessage(alm);
}

void CampKitImplementation::parseItemAttributes() {
	String attr = "uses";
	setUsesRemaining(itemAttributes->getIntAttribute(attr));
	attr = "exp";
	setXP(itemAttributes->getIntAttribute(attr));
	attr = "duration";
	setDuration(itemAttributes->getIntAttribute(attr));
	attr = "campType";
	setCampType(itemAttributes->getIntAttribute(attr));
}

