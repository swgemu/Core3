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

#ifndef WEARABLEIMPLEMENTATION_H_
#define WEARABLEIMPLEMENTATION_H_

#include "../../creature/CreatureObject.h"

#include "Wearable.h"
#include "../attachment/Attachment.h"
#include "../attachment/AttachmentImplementation.h"

#include "WearableSkillModMap.h"

/*
 * WearableImplementation is a class the represents Armor and Clothing
 */
class WearableImplementation: public WearableSkillModMap, public WearableServant {
protected:

	int socketCount;

	int healthEncumbrance;
	int actionEncumbrance;
	int mindEncumbrance;

	int wearableType;

	String EMPTY;

public:

	const static int MAXSOCKETS = 4;
	const static int MAXSKILLMODS = 3;

	const static int WEARABLECLOTHING = 0x01;
	const static int WEARABLEARMOR = 0x02;
	const static int WEARABLEPSG = 0x03;

	const static bool REMOVABLEATTACHMENTS = true;

public:

	/*
	 * Constructor
	 */
	WearableImplementation(uint64 objid, uint32 tempCRC,
			const UnicodeString& n, const String& tempn, bool eqp = false);
	/*
	 * Constructor
	 */
	WearableImplementation(CreatureObject* creature, uint64 oid,
			uint32 tempCRC, const UnicodeString& n, const String& tempn,
			bool eqp = false);
	/*
	 * Constructor
	 */
	WearableImplementation(CreatureObject* creature, uint32 tempCRC,
			const UnicodeString& n, const String& tempn, bool eqp = false);

	/*
	 * init Initializes values
	 */
	void init();
	/*
	 * generateAttributes is called when the client requests the items properties
	 */
	void generateAttributes(SceneObject* obj);
	/*
	 * addAttributes add properties to the bazaar and generateAttributes
	 */
	void addAttributes(AttributeListMessage* alm);
	/*
	 * parseItemAttributes changes ItemAttributes into the values fot the Wearable
	 */
	void parseItemAttributes();
	/*
	 * makeSkillModAttributeString makes a string from skillModMap to save as an ItemAttribute
	 */
	void saveSkillModMap();
	/*
	 * sendTo sends this baseline to the player
	 */
	void sendTo(Player* player, bool doClose = true);
	/*
	 * sendRadialResponseTo radials
	 */
	void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr);
	/*
	 * updateCraftingValues is called during the crafting process
	 * for the object to have access to the values created
	 */
	void updateCraftingValues(DraftSchematic* draftSchematic);
	/*
	 * generateSockets creates a random number of sockets based on the max value
	 */
	void generateSockets(DraftSchematic* draftSchematic);

	void getBestAttachmentSkillMod(String& valueName, AttachmentEntry* entry);

	void rebuildActiveSkillModMap();

	bool hasSkillMod(String skillModName) {
		return contains(skillModName);
	}

	inline void setHealthEncumbrance(int healthEnc) {
		healthEncumbrance = healthEnc;
		String name = "healthEncumberance";
		itemAttributes->setIntAttribute(name, healthEnc);
	}

	inline void setActionEncumbrance(int actionEnc) {
		actionEncumbrance = actionEnc;
		String name = "actionEncumberance";
		itemAttributes->setIntAttribute(name, actionEnc);
	}

	inline void setMindEncumbrance(int mindEnc) {
		mindEncumbrance = mindEnc;
		String name = "mindEncumberance";
		itemAttributes->setIntAttribute(name, mindEnc);
	}

	inline void setMaxSockets(int socket) {
		socketCount = socket;
		String key = "socketCount";
		itemAttributes->setIntAttribute(key, socket);
	}

	inline int socketsLeft() {
		return socketCount - socketsUsed();
	}

	int getMaxSockets() {
		return socketCount;
	}

	int socketsUsed() {
		return getUsedSocketCount();
	}

	inline int getHealthEncumbrance() {
		return healthEncumbrance;
	}

	inline int getActionEncumbrance() {
		return actionEncumbrance;
	}

	inline int getMindEncumbrance() {
		return mindEncumbrance;
	}

	inline bool hasEmptySocket() {
		return socketsLeft() > 0;
	}

	void conditionReduction(float damage) {
		conditionDamage += damage;
	}

	bool attachmentMatches(Attachment* attachment);

	void setAttachmentMods(Player* player);
	void unsetAttachmentMods(Player* player);

	String& getSkillModType(int i);
	int getSkillModValue(String name);
	void applyAttachment(Player* player, Attachment* attachment);
	void reclaimAttachments(Player* player);


	// Events
	void onEquip(Player* player);
	void onUnequip(Player* player);
	void onBroken(Player* player);

};

#endif /*WEARABLEIMPLEMENTATION_H_*/
