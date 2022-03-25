/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "engine/engine.h"

#include "server/zone/objects/creature/buffs/Buff.h"
#include "BuffDurationEvent.h"

#include "templates/params/creature/CreatureAttribute.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/Buffs.h"
#include "server/zone/managers/skill/SkillModManager.h"

void BuffImplementation::init() {
	attributeModifiers.setNoDuplicateInsertPlan();
	attributeModifiers.setNullValue(0);
	skillModifiers.setNoDuplicateInsertPlan();
	skillModifiers.setNullValue(0);

	E3_ASSERT(buffDuration >= 0);
}

void BuffImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();

	attributeModifiers.setNullValue(0);
	skillModifiers.setNullValue(0);
}

void BuffImplementation::loadBuffDurationEvent(CreatureObject* creo) {
	if(nextExecutionTime.getTime() - time(0) > buffDuration) {
		error("Buff timer was f'ed in the a!  Serialized Time:" + String::valueOf((int)(nextExecutionTime.getTime() - time(0))) + " Duration: " + String::valueOf(buffDuration));
		nextExecutionTime = Time((uint32)(time(0) + (int)buffDuration));
	}

	if (nextExecutionTime.isPast()) {
		buffEvent = new BuffDurationEvent(creo, _this.getReferenceUnsafeStaticCast());
		buffEvent->execute();
		//info("nextExeutionTime.isPast()", true);
	} else {
		buffEvent = new BuffDurationEvent(creo, _this.getReferenceUnsafeStaticCast());
		buffEvent->schedule(nextExecutionTime);

		//info("scheduling buffEvent with nextExecutionTime difference from now" + String::valueOf(nextExecutionTime.miliDifference()), true);
	}
}

void BuffImplementation::notifyLoadFromDatabase() {
/*
	if (buffEvent != nullptr && buffEvent->isScheduled()) {
		buffEvent->cancel();
		error("Buff had event scheduled before it was loaded!");
	}

	*/

	//info("initializeTransientMembers() nextExecutionTime difference from now" + String::valueOf(nextExecutionTime.miliDifference()), true);
}

void BuffImplementation::renew(float newDuration) {
	if (newDuration > 0)
		buffDuration = newDuration;

	clearBuffEvent();
	scheduleBuffEvent();
}

void BuffImplementation::sendTo(CreatureObject* player) {
	if (buffCRC != 0) {
		AddBuffMessage* abm = new AddBuffMessage(player, buffCRC, getTimeLeft());
		player->sendMessage(abm);
	}
}

void BuffImplementation::setBuffEventNull() {
	buffEvent = nullptr;
}

void BuffImplementation::sendDestroyTo(CreatureObject* player) {
	if (!player->hasBuff(buffCRC)) {
		RemoveBuffMessage* rbm = new RemoveBuffMessage(player, buffCRC);
		player->sendMessage(rbm);
	}
}

Time BuffImplementation::getTimeApplied() const {
	return timeApplied;
}

int BuffImplementation::compareTo(const Buff* buff) const {
	Time rhs = buff->getTimeApplied();

	return timeApplied.compareTo(rhs);
}

void BuffImplementation::activate(bool applyModifiers) {
	debug() << "activating buff with crc " << hex << buffCRC;

	try {
		if (applyModifiers)
			applyAllModifiers();

		scheduleBuffEvent();

		timeApplied.updateToCurrentTime();

		debug() << "nextExecutionTime miliDifference:" << nextExecutionTime.miliDifference();

		ManagedReference<CreatureObject*> creo = creature.get();
		if (creo->isPlayerCreature())
			sendTo(creo);

		if (!startMessage.isEmpty())
			creo->sendSystemMessage(startMessage);

		if (!startFlyFile.isEmpty())
			creo->showFlyText(startFlyFile, startFlyAux, startFlyRed, startFlyGreen, startFlyBlue);

		if (!startSpam.isEmpty()) {
			creo->sendStateCombatSpam(startSpam.getFile(), startSpam.getStringID(), spamColor, 0, broadcastSpam);
		}

	} catch (const Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}
}

void BuffImplementation::applyAllModifiers() {
	if (!modsApplied) {
		applyAttributeModifiers();
		applySkillModifiers();
		applyStates();
		modsApplied = true;
	}
}

void BuffImplementation::removeAllModifiers() {
	if (modsApplied) {
		removeAttributeModifiers();
		removeSkillModifiers();
		removeStates();
		modsApplied = false;
	}
}

void BuffImplementation::deactivate(bool removeModifiers) {
	ManagedReference<CreatureObject*> strongRef = creature.get();

	if (strongRef == nullptr)
		return;

	try {
		if (removeModifiers)
			removeAllModifiers();

		if (strongRef->isPlayerCreature())
			sendDestroyTo(strongRef);

		if (!endMessage.isEmpty())
			strongRef->sendSystemMessage(endMessage);

		if (!endFlyFile.isEmpty())
			strongRef->showFlyText(endFlyFile, endFlyAux, endFlyRed, endFlyGreen, endFlyBlue);

		if (!endSpam.isEmpty()) {
			strongRef->sendStateCombatSpam(endSpam.getFile(), endSpam.getStringID(), spamColor, 0, broadcastSpam);
		}

		clearBuffEvent();

	} catch (const Exception& e) {
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

String BuffImplementation::getAttributeModifierString() const {
	if (attributeModifiers.size() == 0)
		return String("none");

	StringBuffer retString;

	for (int i = 0; i < attributeModifiers.size(); i++) {
		const auto& entry = attributeModifiers.elementAt(i);
		retString << CreatureAttribute::getName(entry.getKey()) << " +"
			<< entry.getValue() << ";";
	}

	return retString.toString();
}

String BuffImplementation::getSkillModifierString() const {
	if (skillModifiers.size() == 0)
		return String("none");

	StringBuffer retString;

	for (int i = 0; i < skillModifiers.size(); i++) {
		const auto& entry = skillModifiers.elementAt(i);
		retString << entry.getKey() << " +" << entry.getValue() << "; ";
	}

	return retString.toString();
}

void BuffImplementation::scheduleBuffEvent() {
	buffEvent = new BuffDurationEvent(creature.get(), _this.getReferenceUnsafeStaticCast());
	buffEvent->schedule((int) (buffDuration * 1000));
	AtomicTime time;
	Core::getTaskManager()->getNextExecutionTime(buffEvent, time);

	nextExecutionTime = time.getTimeObject();
}

float BuffImplementation::getTimeLeft() const {
	if (buffEvent == nullptr || !buffEvent->isScheduled()) {
		//info("buffEvent == nullptr || !buffEvent->isScheduled()", true);
		return 0.0f;
	}

	AtomicTime next;

	Core::getTaskManager()->getNextExecutionTime(buffEvent, next);

	float timeleft = round(Time().miliDifference(next.getTimeObject()) / 1000.0f);

	//info("timeLeft = " + String::valueOf(timeleft), true);

	return Math::max(0.0f, timeleft);
}

void BuffImplementation::applyAttributeModifiers() {
	ManagedReference<CreatureObject*> creo = creature.get();

	if (creo == nullptr)
		return;

	int size = attributeModifiers.size();

	if (size <= 0)
		return;

	for (int i = 0; i < size; ++i) {
		VectorMapEntry<uint8, int>* entry = &attributeModifiers.elementAt(i);

		uint8 attribute = entry->getKey();
		int value = entry->getValue();

		if (value == 0)
			continue;

		try {
			int currentMaxHAM = creo->getMaxHAM(attribute);

			int newMaxHAM = currentMaxHAM + value;
			if (newMaxHAM < 1)
					newMaxHAM = 1;

			int buffAmount = newMaxHAM - currentMaxHAM;
			attributeModifiers.drop(attribute);
			attributeModifiers.put(attribute, buffAmount);

			creo->setMaxHAM(attribute, newMaxHAM);

			if (creo->getHAM(attribute) > newMaxHAM - creo->getWounds(attribute))
				creo->setHAM(attribute, newMaxHAM - creo->getWounds(attribute));

			if (!creo->isDead() && !creo->isIncapacitated()) {
				if (fillAttributesOnBuff) {
					int attributeval = Math::max(newMaxHAM, creo->getHAM(attribute) + value);
					creo->healDamage(creo, attribute, attributeval, true);
				} else if (value >= 0)
					creo->healDamage(creo, attribute, value);
			}

		} catch (Exception& e) {
			error(e.getMessage());
			e.printStackTrace();
		}
	}

}

void BuffImplementation::applySkillModifiers() {
	ManagedReference<CreatureObject*> creo = creature.get();

	if (creo == nullptr)
		return;

	int size = skillModifiers.size();

	for (int i = 0; i < size; ++i) {
		VectorMapEntry<String, int>* entry = &skillModifiers.elementAt(i);

		String key = entry->getKey();
		int value = entry->getValue();

		creo->addSkillMod(SkillModManager::BUFF, key, value, true);
	}

	// if there was a speed or acceleration mod change, this will take care of immediately setting them.
	// the checks for if they haven't changed are in these methods
	creo->updateSpeedAndAccelerationMods();
}

void BuffImplementation::applyStates() {
	ManagedReference<CreatureObject*> creo = creature.get();

	if (creo == nullptr)
		return;

	int size = states.size();

	for (int i = 0; i < size; ++i) {

		creo->setState(states.get(i), true);
	}
}

void BuffImplementation::removeAttributeModifiers() {
	ManagedReference<CreatureObject*> creo = creature.get();

	if (creo == nullptr)
		return;

	int size = attributeModifiers.size();

	if (size <= 0)
		return;

	for (int i = 0; i < size; ++i) {
		VectorMapEntry<uint8, int>* entry = &attributeModifiers.elementAt(i);

		uint8 attribute = entry->getKey();
		int value = entry->getValue();

		if (value == 0)
			continue;

		try {

			int attributemax = creo->getMaxHAM(attribute) - value;

			int currentVal = creo->getHAM(attribute);

			creo->setMaxHAM(attribute, attributemax);

			if (currentVal >= attributemax) {
				//creature.get()->inflictDamage(creature.get(), attribute, currentVal - attributemax, isSpiceBuff());

				if (attribute % 3 == 0) {
					creo->inflictDamage(creo, attribute, currentVal - attributemax, false);
				} // else setMaxHam sets secondaries to max
			}

		} catch (Exception& e) {
			error(e.getMessage());
			e.printStackTrace();
		}


		/*int attributeval = Math::min(attributemax, creature.get()->getHAM(attribute) - value);

		creature.get()->setHAM(attribute, attributeval);*/
	}

}

void BuffImplementation::removeSkillModifiers() {
	ManagedReference<CreatureObject*> creo = creature.get();

	if (creo == nullptr)
		return;

	int size = skillModifiers.size();

	for (int i = 0; i < size; ++i) {
		VectorMapEntry<String, int>* entry = &skillModifiers.elementAt(i);

		String key = entry->getKey();
		int value = entry->getValue();

		creo->addSkillMod(SkillModManager::BUFF, key, -value, true);

	}

	// if there was a speed or acceleration mod change, this will take care of immediately setting them.
	// the checks for if they haven't changed are in these methods
	creo->updateSpeedAndAccelerationMods();
}

void BuffImplementation::removeStates() {
	ManagedReference<CreatureObject*> creo = creature.get();

	if (creo == nullptr)
		return;

	int size = states.size();

	for (int i = 0; i < size; ++i) {
		creo->clearState(states.get(i), true);
	}
}

void BuffImplementation::clearBuffEvent() {
	if (buffEvent != nullptr) {
		if (buffEvent->isScheduled())
			buffEvent->cancel();

		buffEvent->setBuffObject(nullptr);
		buffEvent = nullptr;
		nextExecutionTime.updateToCurrentTime();
	}
}

bool BuffImplementation::isActive() const {
	return (buffEvent != nullptr && buffEvent->isScheduled());
}

void BuffImplementation::setStartMessage(StringIdChatParameter& start) {
	startMessage = start;
}

void BuffImplementation::setEndMessage(StringIdChatParameter& end) {
	endMessage = end;
}

void BuffImplementation::setStartSpam(StringIdChatParameter& start) {
	startSpam = start;
}

void BuffImplementation::setEndSpam(StringIdChatParameter& end) {
	endSpam = end;
}

void BuffImplementation::setSpamColor(uint8 color) {
	spamColor = color;
}

void BuffImplementation::setBroadcastSpam(bool value) {
	broadcastSpam = value;
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
