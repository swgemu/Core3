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

#ifndef CREATUREOBJECTDELTAMESSAGE1_H_
#define CREATUREOBJECTDELTAMESSAGE1_H_

#include "../../packets/DeltaMessage.h"

#include "../../objects/creature/CreatureObjectImplementation.h"

#include "../../objects/creature/CreatureAttribute.h"

class CreatureObjectDeltaMessage1 : public DeltaMessage {
	CreatureObjectImplementation* creo;

public:
	CreatureObjectDeltaMessage1(CreatureObjectImplementation* cr)
			: DeltaMessage(cr->getObjectID(), 0x4352454F, 1) {
		creo = cr;
	}

	void startSkillBoxListUpdate(int skillBoxesToUpdate) {
		startUpdate(0x03);
		startList(skillBoxesToUpdate, creo->skillBoxesUpdateCounter += skillBoxesToUpdate);
	}

	void addSkillBox(const String& name) {
		insertByte(0x01);
		insertAscii(name.toCharArray());
	}

	void removeSkillBox(const String& name) {
		insertByte(0x00);
		insertAscii(name.toCharArray());
	}

	void updateBankCredits() {
		startUpdate(0x00);
		insertInt(creo->getBankCredits());
	}

	void updateBaseStats()
	{
		startUpdate(0x02);

		uint32 updatecount = creo->getNewHAMBaseUpdateCounter(9);
		startList(9, updatecount);

		int32 healthCreo = creo->getBaseHealth();
		addBar(0, healthCreo);
		int32 strengthCreo = creo->getBaseStrength();
		addBar(1, strengthCreo);
		int32 constCreo = creo->getBaseConstitution();
		addBar(2, constCreo);
		int32 actionCreo = creo->getBaseAction();
		addBar(3, actionCreo);
		int32 quicknessCreo = creo->getBaseQuickness();
		addBar(4, quicknessCreo);
		int32 staminaCreo = creo->getBaseStamina();
		addBar(5, staminaCreo);
		int32 mindCreo = creo->getBaseMind();
		addBar(6, mindCreo);
		int32 focusCreo = creo->getBaseFocus();
		addBar(7, focusCreo);
		int32 willpowerCreo = creo->getBaseWillpower();
		addBar(8, willpowerCreo);

	}

	void updateBaseAttributeBar(uint8 attribute, int32 value) {
		startUpdate(0x02);

		uint32 updatecount = creo->getNewHAMBaseUpdateCounter(1);
		startList(1, updatecount);

		int32 creoBaseAttribute = creo->getBaseAttribute(attribute);
		addBar(attribute, creoBaseAttribute, value);

		creo->setBaseAttribute(attribute, creoBaseAttribute);
	}

	void updateBaseHealthBar(int32 value) {
		updateBaseAttributeBar(CreatureAttribute::HEALTH, value);
	}

	void updateBaseStrengthBar(int32 value) {
		updateBaseAttributeBar(CreatureAttribute::STRENGTH, value);
	}

	void updateBaseConstitutionBar(int32 value) {
		updateBaseAttributeBar(CreatureAttribute::CONSTITUTION, value);
	}

	void updateBaseActionBar(int32 value) {
		updateBaseAttributeBar(CreatureAttribute::ACTION, value);
	}

	void updateBaseQuicknessBar(int32 value) {
		updateBaseAttributeBar(CreatureAttribute::QUICKNESS, value);
	}

	void updateBaseStaminaBar(int32 value) {
		updateBaseAttributeBar(CreatureAttribute::STAMINA, value);
	}

	void updateBaseMindBar(int32 value) {
		updateBaseAttributeBar(CreatureAttribute::MIND, value);
	}

	void updateBaseFocusBar(int32 value) {
		updateBaseAttributeBar(CreatureAttribute::FOCUS, value);
	}

	void updateBaseWillpowerBar(int32 value) {
		updateBaseAttributeBar(CreatureAttribute::WILLPOWER, value);
	}

	void addBar(uint16 index, int32& value, int32 nvalue) {
		removeListIntElement(index, value = nvalue);
	}

	void addBar(uint16 index, int32 value) {
		removeListIntElement(index, value);
	}

	void updateCashCredits() {
		startUpdate(0x01);
		insertInt(creo->getCashCredits());
	}



};

#endif /*CREATUREOBJECTDELTAMESSAGE1_H_*/
