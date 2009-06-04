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

#ifndef CREATUREOBJECTDELTAMESSAGE6_H_
#define CREATUREOBJECTDELTAMESSAGE6_H_

#include "../tangible/TangibleObjectDeltaMessage6.h"
#include "../../objects/tangible/creature/CreatureObject.h"

class CreatureObjectDeltaMessage6 : public TangibleObjectDeltaMessage6 {
protected:
	CreatureObject* creature;

	void addAttributeUpdate(uint16 attribute, int32 value) {
		insertShort(attribute);
		insertInt(value);
	}

public:
	CreatureObjectDeltaMessage6(CreatureObject* creo)
			: TangibleObjectDeltaMessage6(creo, 0x4352454F) {
		creature = creo;
	}

	void updateLevel(uint16 level) {
		startUpdate(0x02);
		insertShort(level);
	}

	void updatePerformanceName(const String& performancename) {
		startUpdate(0x03);
		insertAscii(performancename);
	}

	void updateMoodName(const String& moodname) {
		startUpdate(0x04);
		insertAscii(moodname);
	}

	void updateWeaponID(uint64 weaponid) {
		startUpdate(0x05);
		insertLong(weaponid);
	}

	void updateGroupID(uint64 groupid) {
		startUpdate(0x06);
		insertLong(groupid);
	}

	void updateGroupInviterID(uint64 inviterid, uint64 invitecounter) {
		startUpdate(0x07);
		insertLong(inviterid);
		insertLong(invitecounter);
	}

	void updateGuildID(uint64 guildid) {
		startUpdate(0x08);
		insertLong(guildid);
	}

	void updateTargetID(uint64 targetid) {
		startUpdate(0x09);
		insertLong(targetid);
	}

	void updateMoodID(uint8 moodid) {
		startUpdate(0x0A);
		insertByte(moodid);
	}

	void updatePerformanceCounter(uint32 performancecounter) {
		startUpdate(0x0B);
		insertInt(performancecounter);
	}

	void updatePerformanceID(uint32 performanceid) {
		startUpdate(0x0C);
		insertInt(performanceid);
	}

	void updateAttributes(int32* attributechanges, uint32 counter) {
		startUpdate(0x0D);

		insertInt(3); //Attributes List Size TODO: Find a way to update this with list size.
		insertInt(counter); //Attributes Update Counter

		insertByte(0x02); //Update type
		for (int i = 0; i < 9; i++) {
			if (attributechanges[i] != 0)
				addAttributeUpdate(i, attributechanges[i]);
		}

	}

	void updateAttributesMax(uint32* attributechanges, uint32 counter) {
		startUpdate(0x0E);
		insertInt(3); //Attributes Max List Size
		insertInt(counter); //Attributes Max Update Counter

		insertByte(0x02); //Update type
		for (int i = 0; i < 9; i++) {
			if (attributechanges[i] != 0)
				addAttributeUpdate(i, attributechanges[i]);
		}
	}

	//0x0F = Equipment List
	void updateEquipmentList() {
		//TODO: This needs research
		startUpdate(0x0F);
		insertInt(0); //Equipment List Size
		insertInt(0); //Equipment List Update Counter

		//for (int i = 0; i < equipmentList.size(); i++) {
			//TangibleObject* equipment = equipmentList.get(i);
			//insertCustomizationString(equipment->getCustomizationString());
			//insertInt(equipment->getWHATEVERTHISISLOL());
			//insertLong(equipment->getObjectID());
			//insertInt(equipment->getObjectCRC());
		//}
	}

	void updateTemplatePath(const String& templatepath) {
		startUpdate(0x10);
		insertAscii(templatepath);
	}

	void updateStationaryFlag(bool stationary) {
		startUpdate(0x11);
		insertByte((uint8) stationary);
	}


	/*void updateMaximumHAMBars() {
		we need to send full creo6 here intead of deltas to avoid counter corruption
		TODO: Perhaps there is another alternative...
	}

	void updateHAMBars() {
		we need to send full creo6 here intead of deltas to avoid counter corruption
	}

	void updateHAMPrimaryMaximum(int32 health, int32 action, int32 mind) {
		startUpdate(0x0E);

		uint8 h = 0, a = 0, m = 0;

		if (creature->getHealthMax() != health)
			h = 1;

		if (creature->getActionMax() != action)
			a = 1;

		if (creature->getMindMax() != mind)
			m = 1;

		uint32 updatecount = creature->getNewHAMMaxUpdateCounter(h + a + m);
		startList((h + a + m), updatecount);

		if (h) {
			int32 healthCreo = creature->getHealthMax();
			addBar(0, healthCreo, health);

			creature->setHealthMax(healthCreo);
		}

		if (a) {
			int32 actionCreo = creature->getActionMax();
			addBar(3, actionCreo, action);

			creature->setActionMax(actionCreo);
		}

		if (m) {
			int32 mindCreo = creature->getMindMax();
			addBar(6, mindCreo, mind);

			creature->setMindMax(mindCreo);
		}
	}

	void updatePrimaryBars(int32 health, int32 action, int32 mind) {
		startUpdate(0x0D);

		uint8 h = 0, a = 0, m = 0;

		if (creature->getHealth() != health)
			h = 1;

		if (creature->getAction() != action)
			a = 1;

		if (creature->getMind() != mind)
			m = 1;

		uint32 updatecount = creature->getNewHAMUpdateCounter(h + a + m);
		startList((h+a+m), updatecount);

		if (h) {
			int32 healthCreo = creature->getHealth();
			addBar(0, healthCreo, health);

			creature->setHealth(healthCreo);
		}

		if (a) {
			int32 actionCreo = creature->getAction();
			addBar(3, actionCreo, action);

			creature->setAction(actionCreo);
		}

		if (m) {
			int32 mindCreo = creature->getMind();
			addBar(6, mindCreo, mind);

			creature->setMind(mindCreo);
		}
	}

	void updateAttributeBar(uint8 attribute, int32 value) {
		int32 creatureValue = creature->getAttribute(attribute);

		if (value == creatureValue) {
			creature->error("mhmm update creature delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);
		uint32 updatecount = creature->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		addBar(attribute, creatureValue, value);

		creature->setAttribute(attribute, creatureValue);
	}

	void updateHealthBar(int32 value) {
		updateAttributeBar(CreatureAttribute::HEALTH, value);
	}

	void updateStrengthBar(int32 value) {
		updateAttributeBar(CreatureAttribute::STRENGTH, value);
	}

	void updateConstitutionBar(int32 value) {
		updateAttributeBar(CreatureAttribute::CONSTITUTION, value);
	}

	void updateActionBar(int32 value) {
		updateAttributeBar(CreatureAttribute::ACTION, value);
	}

	void updateQuicknessBar(int32 value) {
		updateAttributeBar(CreatureAttribute::QUICKNESS, value);
	}

	void updateStaminaBar(int32 value) {
		updateAttributeBar(CreatureAttribute::STAMINA, value);
	}

	void updateMindBar(int32 value) {
		updateAttributeBar(CreatureAttribute::MIND, value);
	}

	void updateFocusBar(int32 value) {
		updateAttributeBar(CreatureAttribute::FOCUS, value);
	}

	void updateWillpowerBar(int32 value) {
		updateAttributeBar(CreatureAttribute::WILLPOWER, value);
	}

	void updateMaxAttributeBar(uint8 attribute, int32 value) {
		int32 creatureAttributeMax = creature->getAttributeMax(attribute);


		startUpdate(0x0E);

		uint32 updatecount = creature->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		addBar(attribute, creatureAttributeMax, value);

		creature->setAttributeMax(attribute, creatureAttributeMax);
	}

	void updateMaxHealthBar(int32 value) {
		updateMaxAttributeBar(CreatureAttribute::HEALTH, value);
	}

	void updateMaxStrengthBar(int32 value) {
		updateMaxAttributeBar(CreatureAttribute::STRENGTH, value);
	}

	void updateMaxConstitutionBar(int32 value) {
		updateMaxAttributeBar(CreatureAttribute::CONSTITUTION, value);
	}

	void updateMaxActionBar(int32 value) {
		updateMaxAttributeBar(CreatureAttribute::ACTION, value);
	}

	void updateMaxQuicknessBar(int32 value) {
		updateMaxAttributeBar(CreatureAttribute::QUICKNESS, value);
	}

	void updateMaxStaminaBar(int32 value) {
		updateMaxAttributeBar(CreatureAttribute::STAMINA, value);
	}

	void updateMaxMindBar(int32 value) {
		updateMaxAttributeBar(CreatureAttribute::MIND, value);
	}

	void updateMaxFocusBar(int32 value) {
		updateMaxAttributeBar(CreatureAttribute::FOCUS, value);
	}

	void updateMaxWillpowerBar(int32 value) {
		updateMaxAttributeBar(CreatureAttribute::WILLPOWER, value);
	}

	void changeAttributeBar(uint8 attribute, int32 value) {
		if (value == 0) {
			creature->error("oh hi update creature delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);

		uint32 updatecount = creature->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		creature->changeAttribute(attribute, value);
		int32 creatureValue = creature->getAttribute(attribute);
		addBar(attribute, creatureValue);
	}

	void changeHealthBar(int32 value) {
		changeAttributeBar(CreatureAttribute::HEALTH, value);
	}

	void changeStrengthBar(int32 value) {
		changeAttributeBar(CreatureAttribute::STRENGTH, value);
	}

	void changeConstitutionBar(int32 value) {
		changeAttributeBar(CreatureAttribute::CONSTITUTION, value);
	}

	void changeActionBar(int32 value) {
		changeAttributeBar(CreatureAttribute::ACTION, value);
	}

	void changeQuicknessBar(int32 value) {
		changeAttributeBar(CreatureAttribute::QUICKNESS, value);
	}

	void changeStaminaBar(int32 value) {
		changeAttributeBar(CreatureAttribute::STAMINA, value);
	}

	void changeMindBar(int32 value) {
		changeAttributeBar(CreatureAttribute::MIND, value);
	}

	void changeFocusBar(int32 value) {
		changeAttributeBar(CreatureAttribute::FOCUS, value);
	}

	void changeWillpowerBar(int32 value) {
		changeAttributeBar(CreatureAttribute::WILLPOWER, value);
	}

	void changeMaxAttributeBar(uint8 attribute, int32 value) {
		if (value == 0) {
			creature->error("u there update creature delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0E);

		uint32 updatecount = creature->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		creature->changeAttributeMax(attribute, value);
		int32 creatureAttributeMax = creature->getAttributeMax(attribute);
		addBar(attribute, MAX(1, creatureAttributeMax));
	}

	void changeMaxHealthBar(int32 value) {
		changeMaxAttributeBar(CreatureAttribute::HEALTH, value);
	}

	void changeMaxStrengthBar(int32 value) {
		changeMaxAttributeBar(CreatureAttribute::STRENGTH, value);
	}

	void changeMaxConstitutionBar(int32 value) {
		changeMaxAttributeBar(CreatureAttribute::CONSTITUTION, value);
	}

	void changeMaxActionBar(int32 value) {
		changeMaxAttributeBar(CreatureAttribute::ACTION, value);
	}

	void changeMaxQuicknessBar(int32 value) {
		changeMaxAttributeBar(CreatureAttribute::QUICKNESS, value);
	}

	void changeMaxStaminaBar(int32 value) {
		changeMaxAttributeBar(CreatureAttribute::STAMINA, value);
	}

	void changeMaxMindBar(int32 value) {
		changeMaxAttributeBar(CreatureAttribute::MIND, value);
	}

	void changeMaxFocusBar(int32 value) {
		changeMaxAttributeBar(CreatureAttribute::FOCUS, value);
	}

	void changeMaxWillpowerBar(int32 value) {
		changeMaxAttributeBar(CreatureAttribute::WILLPOWER, value);
	}

	void addBar(uint16 index, int32& value, int32 nvalue) {
		removeListIntElement(index, value = nvalue);
	}

	void addBar(uint16 index, int32 value) {
		removeListIntElement(index, value);
	}*/
};

#endif /*CREATUREOBJECTDELTAMESSAGE6_H_*/
