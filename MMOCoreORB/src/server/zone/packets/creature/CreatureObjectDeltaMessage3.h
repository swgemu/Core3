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

#ifndef CREATUREOBJECTDELTAMESSAGE3_H_
#define CREATUREOBJECTDELTAMESSAGE3_H_

#include "../../packets/DeltaMessage.h"

#include "../../objects/creature/CreatureObject.h"

#include "../../objects/creature/CreatureAttribute.h"

class CreatureObjectDeltaMessage3 : public DeltaMessage {
	CreatureObject* creo;

public:
	CreatureObjectDeltaMessage3(CreatureObject* cr)
			: DeltaMessage(cr->getObjectID(), 0x4352454F, 3) {
		creo = cr;
	}

	/*void updateCharacterAppearance() {
		String appearance;
		creo->getCustomizationString(appearance);
		addAsciiUpdate(4, appearance);
	}*/

	void updateCreatureBitmask(uint32 value) {
		addIntUpdate(0x06, value);
	}

	/*void updateIncapacitationRecoveryTime(uint32 dur) {
		addIntUpdate(0x07, dur);
	}

	void updatePosture() {
		addByteUpdate(0x0B, creo->getPosture());
	}

	void updateFactionRank() {
		addByteUpdate(0x0C, creo->getFactionRank());
	}*/

	void updateState() {
		addLongUpdate(0x10, creo->getStateBitmask());
	}

	/*void updateCreatureBitmask() {
		addIntUpdate(0x06, creo->getOptionsBitmask());
	}

	void updateConditionDamage() {
		addIntUpdate(8, creo->getConditionDamage());
	}

	void updateMaxCondition() {
		addIntUpdate(9, creo->getMaxCondition());
	}

	void updateHeight() {
		addFloatUpdate(14, creo->getHeight());
	}

	void updateShockWounds() {
		addIntUpdate(15, creo->getShockWounds());
	}

	void updateCreatureLinkID() {
		addLongUpdate(0x0D, creo->getCreatureLinkID());
	}

	void updateHAMWoundsBars(int32 healthWounds, int32 actionWounds, int32 mindWounds) {
		startUpdate(0x11);

		uint8 h = 0, a = 0, m = 0;

		if (creo->getHealthWounds() != healthWounds)
			h = 1;

		if (creo->getActionWounds() != actionWounds)
			a = 1;

		if (creo->getMindWounds() != mindWounds)
			m = 1;

		uint32 updatecount = creo->getNewWoundsUpdateCounter(h + a + m);
		startList((h+a+m), updatecount);

		if (h) {
			int32 healthw = creo->getHealthWounds();
			addBar(0, healthw, healthWounds);

			creo->setHealthWounds(healthw);
		}

		if (a) {
			int32 actionw = creo->getActionWounds();
			addBar(3, actionw, actionWounds);

			creo->setActionWounds(actionw);
		}

		if (m) {
			int32 mindw = creo->getMindWounds();
			addBar(6, mindw, mindWounds);

			creo->setMindWounds(mindw);
		}
	}

	void updateWoundsBar(uint8 attribute, int32 value) {
		int32 creoWounds = creo->getWounds(attribute);

		if (value == creoWounds) {
			creo->error("update creo delta3 bar error");
			StackTrace::printStackTrace();
		}

		startUpdate(0x11);

		uint32 updatecount = creo->getNewWoundsUpdateCounter(1);
		startList(1, updatecount);

		addBar(attribute, creoWounds, value);

		creo->setWounds(attribute, creoWounds);
	}

	void updateHealthWoundsBar(int32 value) {
		updateWoundsBar(CreatureAttribute::HEALTH, value);
	}

	void updateStrengthWoundsBar(int32 value) {
		updateWoundsBar(CreatureAttribute::STRENGTH, value);
	}

	void updateConstitutionWoundsBar(int32 value) {
		updateWoundsBar(CreatureAttribute::CONSTITUTION, value);
	}

	void updateActionWoundsBar(int32 value) {
		updateWoundsBar(CreatureAttribute::ACTION, value);
	}

	void updateQuicknessWoundsBar(int32 value) {
		updateWoundsBar(CreatureAttribute::QUICKNESS, value);
	}

	void updateStaminaWoundsBar(int32 value) {
		updateWoundsBar(CreatureAttribute::STAMINA, value);
	}

	void updateMindWoundsBar(int32 value) {
		updateWoundsBar(CreatureAttribute::MIND, value);
	}

	void updateFocusWoundsBar(int32 value) {
		updateWoundsBar(CreatureAttribute::FOCUS, value);
	}

	void updateWillpowerWoundsBar(int32 value) {
		updateWoundsBar(CreatureAttribute::WILLPOWER, value);
	}

	void addBar(uint16 index, int32& value, int32 nvalue) {
		removeListIntElement(index, value = nvalue);
	}*/
};

#endif /*CREATUREOBJECTDELTAMESSAGE3_H_*/
