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

	void updateMaximumPrimaryBars(uint32 health, uint32 action, uint32 mind) {
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
			uint32 healthCreo = creo->getHealthMax();
			addBar(0, healthCreo, health);

			creo->setHealthMax(healthCreo);
		}

		if (a) {
			uint32 actionCreo = creo->getActionMax();
			addBar(3, actionCreo, action);

			creo->setActionMax(actionCreo);
		}

		if (m) {
			uint32 mindCreo = creo->getMindMax();
			addBar(6, mindCreo, mind);

			creo->setMindMax(mindCreo);
		}
	}

	void updatePrimaryBars(uint32 health, uint32 action, uint32 mind) {
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
			uint32 healthCreo = creo->getHealth();
			addBar(0, healthCreo, health);

			creo->setHealth(healthCreo);
		}

		if (a) {
			uint32 actionCreo = creo->getAction();
			addBar(3, actionCreo, action);

			creo->setAction(actionCreo);
		}

		if (m) {
			uint32 mindCreo = creo->getMind();
			addBar(6, mindCreo, mind);

			creo->setMind(mindCreo);
		}
	}

	void updateHealthBar(uint32 health) {
		uint32 healthCreo = creo->getHealth();

		if (health == healthCreo) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);
		uint32 updatecount = creo->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		addBar(0, healthCreo, health);

		creo->setHealth(healthCreo);
	}

	void updateMaxHealthBar(uint32 health) {
		uint32 healthCreoMax = creo->getHealthMax();

		if (health == healthCreoMax) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0E);

		uint32 updatecount = creo->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		addBar(0, healthCreoMax, health);

		creo->setHealthMax(healthCreoMax);
	}

	void updateStrengthBar(uint32 strength) {
		uint32 strengthCreo = creo->getStrength();

		if (strength == strengthCreo) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);

		uint32 updatecount = creo->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		addBar(1, strengthCreo, strength);

		creo->setStrength(strengthCreo);
	}

	void updateMaxStrengthBar(uint32 strength) {
		uint32 strengthCreoMax = creo->getStrengthMax();

		if (strength == strengthCreoMax) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0E);

		uint32 updatecount = creo->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		addBar(1, strengthCreoMax, strength);
		creo->setStrengthMax(strengthCreoMax);
	}

	void updateConstitutionBar(uint32 constitution) {
		uint32 constitutionCreo = creo->getConstitution();

		if (constitution == constitutionCreo) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);

		uint32 updatecount = creo->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		addBar(2, constitutionCreo, constitution);
		creo->setConstitution(constitutionCreo);
	}

	void updateMaxConstitutionBar(uint32 constitution) {
		uint32 constitutionCreoMax = creo->getConstitutionMax();

		if (constitution == constitutionCreoMax) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0E);

		uint32 updatecount = creo->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		addBar(2, constitutionCreoMax, constitution);
		creo->setConstitutionMax(constitutionCreoMax);
	}

	void updateActionBar(uint32 action) {
		uint32 actionCreo = creo->getAction();

		if (actionCreo == action) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);

		uint32 updatecount = creo->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		addBar(3, actionCreo, action);
		creo->setAction(actionCreo);
	}

	void updateMaxActionBar(uint32 action) {
		uint32 actionCreoMax = creo->getActionMax();

		if (actionCreoMax == action) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0E);

		uint32 updatecount = creo->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		addBar(3, actionCreoMax, action);
		creo->setActionMax(actionCreoMax);
	}

	void updateQuicknessBar(uint32 quickness) {
		uint32 quicknessCreo = creo->getQuickness();

		if (quicknessCreo == quickness) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);

		uint32 updatecount = creo->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		addBar(4, quicknessCreo, quickness);
		creo->setQuickness(quicknessCreo);
	}

	void updateMaxQuicknessBar(uint32 quickness) {
		uint32 quicknessCreoMax = creo->getQuicknessMax();

		if (quicknessCreoMax == quickness) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0E);

		uint32 updatecount = creo->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		addBar(4, quicknessCreoMax, quickness);
		creo->setQuicknessMax(quicknessCreoMax);
	}

	void updateStaminaBar(uint32 stamina) {
		uint32 staminaCreo = creo->getStamina();

		if (staminaCreo == stamina) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);

		uint32 updatecount = creo->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		addBar(5, staminaCreo, stamina);
		creo->setStamina(staminaCreo);
	}

	void updateMaxStaminaBar(uint32 stamina) {
		uint32 staminaCreoMax = creo->getStaminaMax();

		if (staminaCreoMax == stamina) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0E);

		uint32 updatecount = creo->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		addBar(5, staminaCreoMax, stamina);
		creo->setStaminaMax(staminaCreoMax);
	}

	void updateMindBar(uint32 mind) {
		uint32 mindCreo = creo->getMind();

		if (mindCreo == mind) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);

		uint32 updatecount = creo->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		addBar(6, mindCreo, mind);
		creo->setMind(mindCreo);
	}

	void updateMaxMindBar(uint32 mind) {
		uint32 mindCreoMax = creo->getMindMax();

		if (mindCreoMax == mind) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0E);

		uint32 updatecount = creo->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		addBar(6, mindCreoMax, mind);
		creo->setMindMax(mindCreoMax);
	}

	void updateFocusBar(uint32 focus) {
		uint32 focusCreo = creo->getFocus();

		if (focusCreo == focus) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);

		uint32 updatecount = creo->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		addBar(7, focusCreo, focus);
		creo->setFocus(focusCreo);
	}

	void updateMaxFocusBar(uint32 focus) {
		uint32 focusCreoMax = creo->getFocusMax();

		if (focusCreoMax == focus) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0E);

		uint32 updatecount = creo->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		addBar(7, focusCreoMax, focus);
		creo->setFocusMax(focusCreoMax);
	}

	void updateWillpowerBar(uint32 willpower) {
		uint32 willpowerCreo = creo->getWillpower();

		if (willpowerCreo == willpower) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);

		uint32 updatecount = creo->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		addBar(8, willpowerCreo, willpower);
		creo->setWillpower(willpowerCreo);
	}

	void updateMaxWillpowerBar(uint32 willpower) {
		uint32 willpowerCreoMax = creo->getWillpowerMax();

		if (willpowerCreoMax == willpower) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0E);

		uint32 updatecount = creo->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		addBar(8, willpowerCreoMax, willpower);
		creo->setWillpowerMax(willpowerCreoMax);
	}

	void changeHealthBar(int32 health) {
		if (health == 0) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);

		uint32 updatecount = creo->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		creo->changeHealth(health);
		uint32 healthCreo = creo->getHealth();
		addBar(0, healthCreo);
	}

	void changeMaxHealthBar(int32 health) {
		if (health == 0) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0E);

		uint32 updatecount = creo->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		creo->changeHealthMax(health);
		uint32 healthCreoMax = creo->getHealthMax();
		addBar(0, healthCreoMax);
	}

	void changeStrengthBar(int32 strength) {
		if (strength == 0) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);

		uint32 updatecount = creo->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		creo->changeStrength(strength);
		uint32 strengthCreo = creo->getStrength();
		addBar(1, strengthCreo);
	}

	void changeMaxStrengthBar(int32 strength) {
		if (strength == 0) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0E);

		uint32 updatecount = creo->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		creo->changeStrengthMax(strength);
		uint32 strengthCreoMax = creo->getStrengthMax();
		addBar(1, strengthCreoMax);
	}

	void changeConstitutionBar(int32 constitution) {
		if (constitution == 0) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);

		uint32 updatecount = creo->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		creo->changeConstitution(constitution);
		uint32 constitutionCreo = creo->getConstitution();
		addBar(2, constitutionCreo);
	}

	void changeMaxConstitutionBar(int32 constitution) {
		if (constitution == 0) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0E);

		uint32 updatecount = creo->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		creo->changeConstitutionMax(constitution);
		uint32 constitutionCreoMax = creo->getConstitutionMax();
		addBar(2, constitutionCreoMax);
	}

	void changeActionBar(int32 action) {
		if (action == 0) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);

		uint32 updatecount = creo->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		creo->changeAction(action);
		uint32 actionCreo = creo->getAction();
		addBar(3, actionCreo);
	}

	void changeMaxActionBar(int32 action) {
		if (action == 0) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0E);

		uint32 updatecount = creo->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		creo->changeActionMax(action);
		uint32 actionCreoMax = creo->getActionMax();
		addBar(3, actionCreoMax);
	}

	void changeQuicknessBar(int32 quickness) {
		if (quickness == 0) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);

		uint32 updatecount = creo->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		creo->changeQuickness(quickness);
		uint32 quicknessCreo = creo->getQuickness();
		addBar(4, quicknessCreo);
	}

	void changeMaxQuicknessBar(int32 quickness) {
		if (quickness == 0) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0E);

		uint32 updatecount = creo->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		creo->changeQuicknessMax(quickness);
		uint32 quicknessCreoMax = creo->getQuicknessMax();
		addBar(4, quicknessCreoMax);
	}

	void changeStaminaBar(int32 stamina) {
		if (stamina == 0) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);

		uint32 updatecount = creo->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		creo->changeStamina(stamina);
		uint32 staminaCreo = creo->getStamina();
		addBar(5, staminaCreo);
	}

	void changeMaxStaminaBar(int32 stamina) {
		if (stamina == 0) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0E);

		uint32 updatecount = creo->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		creo->changeStaminaMax(stamina);
		uint32 staminaCreoMax = creo->getStaminaMax();
		addBar(5, staminaCreoMax);
	}

	void changeMindBar(int32 mind) {
		if (mind == 0) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);

		uint32 updatecount = creo->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		creo->changeMind(mind);
		uint32 mindCreo = creo->getMind();
		addBar(6, mindCreo);
	}

	void changeMaxMindBar(int32 mind) {
		if (mind == 0) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0E);

		uint32 updatecount = creo->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		creo->changeMindMax(mind);
		uint32 mindCreoMax = creo->getMindMax();
		addBar(6, mindCreoMax);
	}

	void changeFocusBar(int32 focus) {
		if (focus == 0) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);

		uint32 updatecount = creo->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		creo->changeFocus(focus);
		uint32 focusCreo = creo->getFocus();
		addBar(7, focusCreo);
	}

	void changeMaxFocusBar(int32 focus) {
		if (focus == 0) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0E);

		uint32 updatecount = creo->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		creo->changeFocusMax(focus);
		uint32 focusCreoMax = creo->getFocusMax();
		addBar(7, focusCreoMax);
	}

	void changeWillpowerBar(int32 willpower) {
		if (willpower == 0) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0D);

		uint32 updatecount = creo->getNewHAMUpdateCounter(1);
		startList(1, updatecount);

		creo->changeWillpower(willpower);
		uint32 willpowerCreo = creo->getWillpower();
		addBar(8, willpowerCreo);
	}

	void changeMaxWillpowerBar(int32 willpower) {
		if (willpower == 0) {
			creo->error("update creo delta6 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x0E);

		uint32 updatecount = creo->getNewHAMMaxUpdateCounter(1);
		startList(1, updatecount);

		creo->changeWillpowerMax(willpower);
		uint32 willpowerCreoMax = creo->getWillpowerMax();
		addBar(8, willpowerCreoMax);
	}

	void addBar(uint16 index, uint32& value, uint32 nvalue) {
		removeListIntElement(index, value = nvalue);
	}

	void addBar(uint16 index, uint32 value) {
		removeListIntElement(index, value);
	}

	void updateMoodID() {
		addByteUpdate(0x0A, creo->getMoodID());
	}

	void updateMoodStr() {
		addAsciiUpdate(0x04, creo->getMood());
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
};

#endif /*CREATUREOBJECTDELTAMESSAGE6_H_*/
