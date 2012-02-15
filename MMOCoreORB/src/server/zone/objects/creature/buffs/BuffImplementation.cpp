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

#include "Buff.h"
#include "BuffDurationEvent.h"
#include "BuffList.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/Buffs.h"
#include "server/zone/packets/object/ShowFlyText.h"

void BuffImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();

	attributeModifiers.setNullValue(0);
	skillModifiers.setNullValue(0);
}

void BuffImplementation::notifyLoadFromDatabase() {
	if (buffEvent != NULL)
		return;

	//info("initializeTransientMembers() nextExecutionTime difference from now" + String::valueOf(nextExecutionTime.miliDifference()), true);

	if (nextExecutionTime.isPast()) {
		buffEvent = new BuffDurationEvent(creature, _this);
		buffEvent->schedule(1000);
		//info("nextExeutionTime.isPast()", true);
	} else {
		buffEvent = new BuffDurationEvent(creature, _this);
		buffEvent->schedule(nextExecutionTime);

		//info("scheduling buffEvent with nextExecutionTime difference from now" + String::valueOf(nextExecutionTime.miliDifference()), true);
	}
}

void BuffImplementation::sendTo(CreatureObject* player) {
	if (buffCRC != 0) {
		AddBuffMessage* abm = new AddBuffMessage(player, buffCRC, getTimeLeft());
		player->sendMessage(abm);
	}
}

void BuffImplementation::setBuffEventNull() {
	buffEvent = NULL;
}

void BuffImplementation::sendDestroyTo(CreatureObject* player) {
	if (!player->hasBuff(buffCRC)) {
		RemoveBuffMessage* rbm = new RemoveBuffMessage(player, buffCRC);
		player->sendMessage(rbm);
	}
}

void BuffImplementation::activate(bool applyModifiers) {
	//info("activating buff with crc " + String::hexvalueOf((int)buffCRC), true);
	try {
		if (applyModifiers) {
			applyAttributeModifiers();
			applySkillModifiers();
			applyStates();
		}

		buffEvent = new BuffDurationEvent(creature, _this);
		buffEvent->schedule((int) (buffDuration * 1000));
		//nextExecutionTime = buffEvent->getNextExecutionTime();
		Core::getTaskManager()->getNextExecutionTime(buffEvent, nextExecutionTime);

		//info("nextExecutionTime miliDifference:" + String::valueOf(nextExecutionTime.miliDifference()), true);

		if (creature->isPlayerCreature())
			sendTo((cast<CreatureObject*>(creature.get())));

		if (!startMessage.isEmpty())
			creature->sendSystemMessage(startMessage);

		if (!startFlyFile.isEmpty())
			creature->showFlyText(startFlyFile, startFlyAux, startFlyRed, startFlyGreen, startFlyBlue);

	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}
}

void BuffImplementation::deactivate(bool removeModifiers) {
	ManagedReference<CreatureObject*> strongRef = creature.get();

	if (strongRef == NULL)
		return;

	try {
		if (removeModifiers) {
			removeAttributeModifiers();
			removeSkillModifiers();
			removeStates();
		}

		if (creature->isPlayerCreature())
			sendDestroyTo(cast<CreatureObject*>(creature.get()));

		if (!endMessage.isEmpty())
			creature->sendSystemMessage(endMessage);

		if (!endFlyFile.isEmpty())
			creature->showFlyText(endFlyFile, endFlyAux, endFlyRed, endFlyGreen, endFlyBlue);

		clearBuffEvent();

	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}
}

void BuffImplementation::parseAttributeModifierString(const String& modifierstring) {
	StringTokenizer tokenizer(modifierstring);
	tokenizer.setDelimeter(";");

	while (tokenizer.hasMoreTokens()) {
		String token;
		tokenizer.getStringToken(token);

		int tokpos = token.indexOf("=");

		if (tokpos == -1)
			continue;

		uint8 attribute = CreatureAttribute::getAttribute(token.subString(0, tokpos));
		int value = Integer::valueOf(token.subString(tokpos + 1, token.length()));

		attributeModifiers.put(attribute, value);
	}
}

void BuffImplementation::parseSkillModifierString(const String& modifierstring) {
	StringTokenizer tokenizer(modifierstring);
	tokenizer.setDelimeter(";");

	while (tokenizer.hasMoreTokens()) {
		String token;
		tokenizer.getStringToken(token);

		int tokpos = token.indexOf("=");

		if (tokpos == -1)
			continue;

		String modname = token.subString(0, tokpos);
		float value = Float::valueOf(token.subString(tokpos + 1, token.length()));

		skillModifiers.put(modname, (int) value);
	}
}

String BuffImplementation::getAttributeModifierString() {
	return String("");
}

String BuffImplementation::getSkillModifierString() {
	return String("");
}

void BuffImplementation::scheduleBuffEvent() {
	//buffEvent = new BuffDurationEvent(creature, _this);
}

float BuffImplementation::getTimeLeft() {
	if (buffEvent == NULL || !buffEvent->isScheduled()) {
		//info("buffEvent == NULL || !buffEvent->isScheduled()", true);
		return 0.0f;
	}

	Time next;

	Core::getTaskManager()->getNextExecutionTime(buffEvent, next);

	float timeleft = round(Time().miliDifference(next) / 1000.0f);

	//info("timeLeft = " + String::valueOf(timeleft), true);

	return MAX(0.0f, timeleft);
}


void BuffImplementation::applyAttributeModifiers() {
	if (creature == NULL)
		return;

	if (speedMultiplierMod >= 0.f && speedMultiplierMod != creature->getSpeedMultiplierMod()){
		creature->setSpeedMultiplierMod(speedMultiplierMod);
	}

	if (accelerationMultiplierMod >= 0.f &&  accelerationMultiplierMod != creature->getAccelerationMultiplierMod()){
		creature->setAccelerationMultiplierMod(accelerationMultiplierMod);
	}

	int size = attributeModifiers.size();

	if (size <= 0)
		return;

	for (int i = 0; i < size; ++i) {
		VectorMapEntry<uint8, int>* entry = &attributeModifiers.elementAt(i);

		uint8 attribute = entry->getKey();
		int value = entry->getValue();

		if (value == 0)
			continue;

		int attributemax = creature->getMaxHAM(attribute) + value;
		int attributeval = MAX(attributemax, creature->getHAM(attribute) + value);

		creature->setMaxHAM(attribute, attributemax);

		if (fillAttributesOnBuff) {
			//creature->setHAM(attribute, attributeval - creature->getWounds(attribute));
			creature->healDamage(creature, attribute, attributeval, true);
		} else if (value >= 0)
			creature->healDamage(creature, attribute, value);
	}

}

void BuffImplementation::applySkillModifiers() {
	if (creature == NULL)
		return;

	int size = skillModifiers.size();

	for (int i = 0; i < size; ++i) {
		VectorMapEntry<String, int>* entry = &skillModifiers.elementAt(i);

		String key = entry->getKey();
		int value = entry->getValue();

		creature->addSkillMod(key, value, true);
	}
}

void BuffImplementation::applyStates() {
	if (creature == NULL)
		return;

	int size = states.size();

	for (int i = 0; i < size; ++i) {

		creature->setState(states.get(i), true);
	}
}

void BuffImplementation::removeAttributeModifiers() {
	if (creature == NULL)
		return;

	if (speedMultiplierMod >= 0.f &&  speedMultiplierMod == creature->getSpeedMultiplierMod()){
		creature->setSpeedMultiplierMod(1.f);
	}

	if (accelerationMultiplierMod >= 0.f &&  accelerationMultiplierMod == creature->getAccelerationMultiplierMod()){
		creature->setAccelerationMultiplierMod(1.f);
	}

	int size = attributeModifiers.size();

	if (size <= 0)
		return;

	for (int i = 0; i < size; ++i) {
		VectorMapEntry<uint8, int>* entry = &attributeModifiers.elementAt(i);

		uint8 attribute = entry->getKey();
		int value = entry->getValue();

		if (value == 0)
			continue;

		int attributemax = creature->getMaxHAM(attribute) - value;

		int currentVal = creature->getHAM(attribute);

		creature->setMaxHAM(attribute, attributemax);

		if (currentVal >= attributemax) {
			//creature->inflictDamage(creature, attribute, currentVal - attributemax, isSpiceBuff());

			if (attribute % 3 == 0) {
				creature->inflictDamage(creature, attribute, currentVal - attributemax, false);
			} // else setMaxHam sets secondaries to max
		}


		/*int attributeval = MIN(attributemax, creature->getHAM(attribute) - value);

		creature->setHAM(attribute, attributeval);*/
	}

}

void BuffImplementation::removeSkillModifiers() {
	if (creature == NULL)
		return;

	int size = skillModifiers.size();

	for (int i = 0; i < size; ++i) {
		VectorMapEntry<String, int>* entry = &skillModifiers.elementAt(i);

		String key = entry->getKey();
		int value = entry->getValue();

		creature->addSkillMod(key, -value, true);

	}
}

void BuffImplementation::removeStates() {
	if (creature == NULL)
		return;

	int size = states.size();

	for (int i = 0; i < size; ++i) {
		creature->clearState(states.get(i), true);
	}
}

void BuffImplementation::clearBuffEvent() {
	if (buffEvent != NULL) {
		if (buffEvent->isScheduled())
			buffEvent->cancel();

		buffEvent->setBuffObject(NULL);
		buffEvent = NULL;
		nextExecutionTime.updateToCurrentTime();
	}
}

bool BuffImplementation::isActive() {
	return (buffEvent != NULL && buffEvent->isScheduled());
}

void BuffImplementation::setStartMessage(StringIdChatParameter& start) {
	startMessage = start;
}

void BuffImplementation::setEndMessage(StringIdChatParameter& end) {
	endMessage = end;
}

void BuffImplementation::setStartFlyText(const String& file, const String& aux, uint8 red, uint8 green, uint8 blue) {
	startFlyFile = file;
	startFlyAux = aux;
	startFlyRed = red;
	startFlyGreen = green;
	startFlyBlue = blue;
}

void BuffImplementation::setEndFlyText(const String& file, const String& aux, uint8 red, uint8 green, uint8 blue) {
	endFlyFile = file;
	endFlyAux = aux;
	endFlyRed = red;
	endFlyGreen = green;
	endFlyBlue = blue;
}

