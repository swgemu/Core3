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

#include "../../../ZoneClientSession.h"
#include "../../player/Player.h"

#include "../../../packets/scene/AttributeListMessage.h"
#include "../../../packets/tangible/TangibleObjectMessage3.h"
#include "../../../packets/object/ObjectMenuResponse.h"

#include "Wearable.h"
#include "WearableImplementation.h"

#include "../../../managers/player/PlayerManager.h"

#include "../../../objects/draftschematic/DraftSchematicValuesImplementation.h"

WearableImplementation::WearableImplementation(uint64 objid, uint32 tempCRC, const UnicodeString& n, const String& tempn, bool eqp)
		: WearableSkillModMap() , WearableServant(objid, CLOTHING) {
	objectCRC = tempCRC;

	customName = n;

	stfFile = "wearables_name";
	stfName = tempn;

	equipped = eqp;
	init();
}

WearableImplementation::WearableImplementation(CreatureObject* creature, uint64 oid, uint32 tempCRC, const UnicodeString& n, const String& tempn, bool eqp)
	: WearableSkillModMap()	, WearableServant(oid, CLOTHING) {

	objectCRC = tempCRC;

	customName = n;

	stfFile = "wearables_name";
	stfName = tempn;

	if ((equipped = eqp))
		setParent(creature, 0x04);
	else
		setParent((TangibleObject*) creature->getInventory(), 0xFFFFFFFF);
	init();
}

WearableImplementation::WearableImplementation(CreatureObject* creature, uint32 tempCRC, const UnicodeString& n, const String& tempn, bool eqp)
	: WearableSkillModMap() , WearableServant(creature->getNewItemID(), CLOTHING) {
	//creature->getNewItemID();
	objectCRC = tempCRC;

	customName = n;

	stfFile = "wearables_name";
	stfName = tempn;

	if ((equipped = eqp))
		setParent(creature, 0x04);
	else
		setParent((TangibleObject*) creature->getInventory(), 0xFFFFFFFF);
	init();
}

void WearableImplementation::init() {

	EMPTY = "";

	socketCount = 0;

	setConditionDamage(0);
	setCondition(100,100);

	setHealthEncumbrance(0);
	setActionEncumbrance(0);
	setMindEncumbrance(0);

	wearableType = WearableImplementation::WEARABLECLOTHING;

}

void WearableImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;

	AttributeListMessage* alm = new AttributeListMessage((TangibleObject*) _this);

	addAttributes(alm);

	player->sendMessage(alm);

}

void WearableImplementation::addAttributes(AttributeListMessage* alm) {

	StringBuffer conditionStr;
	conditionStr << getCondition() << '/' << maxCondition;
	alm->insertAttribute("Condition", conditionStr);

	alm->insertAttribute("Volume", "1");

	if (socketsLeft() > 0)
		alm->insertAttribute("Sockets", socketsLeft());

	insertStatMods(alm);

	if (craftersName != "") {

		alm->insertAttribute("crafter", craftersName);
	}
	if (craftedSerial != "") {

		alm->insertAttribute("serial_number", craftedSerial);
	}
}

void WearableImplementation::parseItemAttributes() {

	maxCondition = itemAttributes->getMaxCondition();
	conditionDamage = maxCondition - itemAttributes->getCurrentCondition();

	String name = "socketCount";
	setMaxSockets(itemAttributes->getIntAttribute(name));

	name = "skillMods";
	makeSkillModMap(itemAttributes->getStringAttribute(name));

	name = "attachments";
	makeAttachmentMap(itemAttributes->getStringAttribute(name));

	name = "healthEncumberance";
	healthEncumbrance = itemAttributes->getIntAttribute(name);
	name = "actionEncumberance";
	actionEncumbrance = itemAttributes->getIntAttribute(name);
	name = "mindEncumberance";
	mindEncumbrance = itemAttributes->getIntAttribute(name);

	name = "craftedserial";
	craftedSerial = itemAttributes->getStringAttribute(name);

	name = "craftersname";
	craftersName = itemAttributes->getStringAttribute(name);

	rebuildActiveSkillModMap();
}

void WearableImplementation::saveSkillModMap() {

	String name, value;

	name = "attachments";
	value = getAttachmentString();
	itemAttributes->setStringAttribute(name, value);

	name = "skillMods";
	value = getSkillModString();
	itemAttributes->setStringAttribute(name, value);
}

void WearableImplementation::sendTo(Player* player, bool doClose) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::create(client);

	if (parent != NULL)
		link(client, parent);

	BaseMessage* tano3 = new TangibleObjectMessage3((TangibleObject*) _this);
	client->sendMessage(tano3);

	if (doClose)
		SceneObjectImplementation::close(client);

}

void WearableImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	if (player->getInventoryItem(getObjectID()) != NULL) {

		if (getConditionDamage() > 0)
			omr->addRadialParent(70, 3, "sui:repair");
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

void WearableImplementation::updateCraftingValues(DraftSchematic* draftSchematic){
	/*
	 * Values available:	Range:
	 * sockets				0-0(novice artisan) (Don't use)
	 * hitpoints			1000-1000 (Don't Use)
	 */
	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	if(firstCraftingUpdate) {
		generateSockets(draftSchematic);
		firstCraftingUpdate = false;
	}
}

void WearableImplementation::generateSockets(DraftSchematic* draftSchematic) {

	String assemblySkill = draftSchematic->getAssemblySkill();
	// Get assembly points from skill

	Player* player = draftSchematic->getCrafter();

	if (player == NULL) {

		setMaxSockets(0);

	} else {

		int skill = player->getSkillMod(assemblySkill) * 2; // 0 to 250 max
		int luck = System::random(player->getSkillMod("luck") + player->getSkillMod("force_luck")); //0 to 250
		int random = (System::random(750)) - 250; // -250 to 500

		float roll = System::random(skill + luck + random);

		int generatedCount = int(float(MAXSOCKETS * roll) / float(MAXSOCKETS * 100));

		if (generatedCount > MAXSOCKETS)
			generatedCount = MAXSOCKETS;
		if (generatedCount < 0)
			generatedCount = 0;

		setMaxSockets(generatedCount);
	}
}

String& WearableImplementation::getSkillModType(int i) {
	if (getActiveSkillModCount() >= i)
		return getActiveSkillModKey(i);
	else
		return EMPTY;
}

int WearableImplementation::getSkillModValue(String name) {
	return getActiveSkillModValue(name);
}

void WearableImplementation::applyAttachment(Player* player, Attachment* attachment) {

	if (hasEmptySocket() && attachmentMatches(attachment)) {

		 if (isEquipped())
			 unsetAttachmentMods(player);

		 AttachmentEntry* entry = new AttachmentEntry();

		 for(int i = 0; i < attachment->getSkillModCount(); ++i) {

			 String name = attachment->getSkillModName(i);
			 int value = attachment->getSkillModValue(name);

			 entry->add(name, value);
		}

		addAttachment(entry);

		saveSkillModMap();

		rebuildActiveSkillModMap();

		if (isEquipped())
			setAttachmentMods(player);

		attachment->remove(player);
		attachment->finalize();

		generateAttributes(player);
	}
}
void WearableImplementation::reclaimAttachments(Player* player) {

	 if (isEquipped()) {
		 player->sendSystemMessage("Cannot reclaim attachments while item is equipped");
		 return;
	 }

	AttachmentEntry* entry;
	Attachment* newAttachment = NULL;

	for (int i = 0; i < attachmentVector.size(); ++i) {
			entry = attachmentVector.get(i);
			newAttachment = new Attachment(player->getNewItemID(), wearableType);

			for(int j = 0; j < entry->size(); ++j) {
				String key = entry->getKey(j);
				int value = entry->get(key);
				newAttachment->addSkillMod(key, value);
			}

			player->addInventoryItem(newAttachment);

			newAttachment->sendTo(player, true);
	}
	newAttachment = NULL;
	attachmentVector.removeAll();

	saveSkillModMap();

	rebuildActiveSkillModMap();
}

/*
 * rebuildActiveSkillModMap build the active map for attachments based on known attachment rules
 */
void WearableImplementation::rebuildActiveSkillModMap() {

	activeSkillModMap.removeAll();
	AttachmentEntry* entry;
	String statName;
	int statValue;


	for(int i = 0; i < innateSkillModMap.size(); ++i) {

		statName = (&innateSkillModMap.elementAt(i))->getKey();
		statValue = innateSkillModMap.get(statName);

		if(activeSkillModMap.contains(statName) && statValue > activeSkillModMap.get(statName)) {
			activeSkillModMap.drop(statName);
			activeSkillModMap.put(statName, statValue);
		} else if (!activeSkillModMap.contains(statName)) {
			activeSkillModIndex.add(statName);
			activeSkillModMap.put(statName, statValue);
		}
	}

	for (int i = 0; i < attachmentVector.size(); ++i) {
		entry = attachmentVector.get(i);

		if (entry != NULL) {

			statName = "";

			getBestAttachmentSkillMod(statName, entry);

			if (statName != "") {
				statValue = entry->get(statName);

				activeSkillModIndex.add(statName);
				activeSkillModMap.put(statName, statValue);
			}
		}
	}
}


void WearableImplementation::getBestAttachmentSkillMod(String& valueName, AttachmentEntry* entry) {
	String key = "";
	int value;

	int maxValue = -26;

	for(int i = 0; i < entry->size(); ++i) {

		key = entry->getKey(i);
		value = entry->get(key);

		if (value > maxValue) {
			if((!activeSkillModMap.contains(key)))
				valueName = key;
			else
				if(value > activeSkillModMap.get(key))
					valueName = key;
		}
	}
}

bool WearableImplementation::attachmentMatches(Attachment* attachment) {

	if((wearableType == WearableImplementation::WEARABLECLOTHING &&
			attachment->getAttachmentType() == AttachmentImplementation::CLOTHINGATTACHMENT)  ||
			(wearableType == WearableImplementation::WEARABLEARMOR &&
			attachment->getAttachmentType() == AttachmentImplementation::ARMORATTACHMENT))
		return true;
	else
		return false;
}

void WearableImplementation::setAttachmentMods(Player* player) {

	for (int i = 0; i < getActiveSkillModCount(); ++i) {

		String name = getActiveSkillModKey(i);
		int value = getActiveSkillModValue(name);

		player->addSkillModBonus(name, value, true);
	}
}

void WearableImplementation::unsetAttachmentMods(Player* player) {

	for (int i = 0; i < getActiveSkillModCount(); ++i) {

		String name = getActiveSkillModKey(i);
		int value = getActiveSkillModValue(name);

		player->addSkillModBonus(name, -value, true);
	}
}

void WearableImplementation::onEquip(Player* player) {

	setAttachmentMods(player);

}
void WearableImplementation::onUnequip(Player* player) {

	unsetAttachmentMods(player);

}
void WearableImplementation::onBroken(Player* player) {

}
