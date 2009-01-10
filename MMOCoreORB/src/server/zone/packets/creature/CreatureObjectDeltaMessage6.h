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

#include "../../packets/DeltaMessage.h"

#include "../../objects/creature/CreatureObject.h"

#include "../../objects/creature/CreatureAttribute.h"

class CreatureObjectDeltaMessage6 : public DeltaMessage {
	CreatureObject* creo;

public:
	CreatureObjectDeltaMessage6(CreatureObject* cr)
	: DeltaMessage(cr->getObjectID(), 0x4352454F, 6) {
		creo = cr;
	}

	void startDefenderUpdate(int updates) {
		startUpdate(0x01);

		uint32 counter = creo->getNewDefenderUpdateCounter(updates);
		startList(updates, counter);
	}

	void addDefender(uint16 index, uint64 defenderID) {
		insertByte(1);
		insertShort(index);
		insertLong(defenderID);
	}

	void setDefender(uint16 idx, uint64 defenderID) {
		insertByte(2);
		insertShort(idx);
		insertLong(defenderID);
	}

	void removeDefender(uint16 index) {
		insertByte(0);
		insertShort(index);
	}

	void removeDefenders() {
		insertByte(4);
	}

	void updateWeapon() {
		addLongUpdate(0x05, creo->getWeaponID());
	}

	void updateGroupID() {
		addLongUpdate(0x06, creo->getGroupID());
	}

	void updateInviterId() {
		startUpdate(0x07);

		insertLong(creo->getGroupInviterID());
		insertLong(creo->getNewGroupInviteCounter());
	}

	void updateTarget() {
		addLongUpdate(0x09, creo->getTargetID());
	}


	/*void updateMaximumHAMBars() {
		we need to send full creo6 here intead of deltas to avoid counter corruption
	}

	void updateHAMBars() {
		we need to send full creo6 here intead of deltas to avoid counter corruption
	}*/

	void updateMaximumPrimaryBars(int32 health, int32 action, int32 mind) {
		startUpdate(0x0E);

		uint8 h = 0, a = 0, m = 0;

		if (creo->getHealthMax() != health)
			h = 1;

		if (creo->getActionMax() != action)
			a = 1;

		if (creo->getMindMax() != mind)
			m = 1;

		uint32 updatecount = creo->getNewHAMMaxUpdateCounter(h + a + m);
		startList((h + a + m), updatecount);

		if (h) {
			int32 healthCreo = creo->getHealthMax();
			addBar(0, healthCreo, health);

			creo->setHealthMax(healthCreo);
		}

		if (a) {
			int32 actionCreo = creo->getActionMax();
			addBar(3, actionCreo, action);

			creo->setActionMax(actionCreo);
		}

		if (m) {
			int32 mindCreo = creo->getMindMax();
			addBar(6, mindCreo, mind);

			creo->setMindMax(mindCreo);
		}
	}

	void updatePrimaryBars(int32 health, int32 action, int32 mind) {
		startUpdate(0x0D);

		uint8 h = 0, a = 0, m = 0;

		if (creo->getHealth() != health)
			h = 1;

		if (creo->getAction() != action)
			a = 1;

		if (creo->getMind() != mind)
			m = 1;

		uint32 updatecount = creo->getNewHAMUpdateCounter(h + a + m);
		startList((h+a+m), updatecount);

		if (h) {
			int32 healthCreo = creo->getHealth();
			addBar(0, healthCreo, health);

			creo->setHealth(healthCreo);
		}

		if (a) {
			int32 actionCreo = creo->getAction();
			addBar(3, actionCreo, action);

			creo->setAction(actionCreo);
		}

		if (m) {
			int32 mindCreo = creo->getMind();
			addBar(6, mindCreo, mind);

			creo->setMind(mindCreo);
		}
	}

	void updateAttributeBar(uint8 attribute, int32 value) {
		int32 creoValue = creo->getAttribute(attribute);

		if (value == creoValue) {
			creo->error("mhmm update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);
		uint32 updatecount = creo->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		addBar(attribute, creoValue, value);

		creo->setAttribute(attribute, creoValue);
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
		int32 creoAttributeMax = creo->getAttributeMax(attribute);

		/*if (value == creoAttributeMax) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}*/

		startUpdate(0x0E);

		uint32 updatecount = creo->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		addBar(attribute, creoAttributeMax, value);

		creo->setAttributeMax(attribute, creoAttributeMax);
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
			creo->error("oh hi update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);

		uint32 updatecount = creo->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		creo->changeAttribute(attribute, value);
		int32 creoValue = creo->getAttribute(attribute);
		addBar(attribute, creoValue);
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
			creo->error("u there update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0E);

		uint32 updatecount = creo->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		creo->changeAttributeMax(attribute, value);
		int32 creoAttributeMax = creo->getAttributeMax(attribute);
		addBar(attribute, MAX(1, creoAttributeMax));
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
	}

	void updateMoodID() {
		addByteUpdate(0x0A, creo->getMoodID());
	}

	void updateMoodStr() {
		addAsciiUpdate(0x04, creo->getMoodStr());
	}

	void updatePerformanceAnimation(String pAnimation) {
		startUpdate(0x03);
		insertAscii(pAnimation);
	}

	void updatePerformanceCounter(uint32 pCounter) {
		startUpdate(0x0B);
		insertInt(pCounter);
	}

	void updateInstrumentID(int value) {
		startUpdate(0x0C);
		insertInt(value);
	}

	void updateMoodAnimation(String value) {
		startUpdate(0x04);
		insertAscii(value);
	}

	void updateGuild(uint32 value) {
		startUpdate(0x08);
		insertInt(value);
	}

	void updateTemplateString() {
		startUpdate(0x10);
		insertAscii(creo->getTemplateString());
	}

	void setFrozen(bool frozen) {
		startUpdate(0x11);
		if (frozen) {
			insertByte(0x01);
		} else {
			insertByte(0);
		}
	}

	void updateLevel(uint16 value) {
		startUpdate(0x02);
		insertShort(value);
	}
};

#endif /*CREATUREOBJECTDELTAMESSAGE6_H_*/
