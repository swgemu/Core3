#include "CharacterBuilderTerminal.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/sui/characterbuilderbox/SuiCharacterBuilderBox.h"

#include "server/zone/templates/tangible/CharacterBuilderTerminalTemplate.h"
#include "CharacterBuilderMenuNode.h"

void CharacterBuilderTerminalImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	CharacterBuilderTerminalTemplate* terminalData = dynamic_cast<CharacterBuilderTerminalTemplate*>(templateData);

	if (terminalData == NULL)
		return;

	rootNode = terminalData->getItemList();

	performanceBuff = terminalData->getPerformanceBuff();
	medicalBuff = terminalData->getMedicalBuff();
	performanceDuration = terminalData->getPerformanceDuration();
	medicalDuration = terminalData->getMedicalDuration();

	//info("loaded " + String::valueOf(itemList.size()));
}

void CharacterBuilderTerminalImplementation::initializeTransientMembers() {
	TerminalImplementation::initializeTransientMembers();

	setLoggingName("CharacterBuilderTerminal");
}

int CharacterBuilderTerminalImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	//info("entering start terminal radial call", true);

	if (selectedID != 20) // not use object
		return 1;

	sendInitialChoices(player);

	return 0;
}

void CharacterBuilderTerminalImplementation::sendInitialChoices(PlayerCreature* player) {
	//info("entering sendInitialChoices", true);

	if (rootNode == NULL) {
		player->sendSystemMessage("There was an error initializing the menu for this character builder terminal. Sorry for the inconvenience.");
		return;
	}

	SuiCharacterBuilderBox* sui = new SuiCharacterBuilderBox(player, rootNode);
	sui->setUsingObject(_this);

	player->sendMessage(sui->generateMessage());
	player->addSuiBox(sui);
}

void CharacterBuilderTerminalImplementation::enhanceCharacter(PlayerCreature* player) {
	if (player == NULL)
		return;

	String buffName;
	uint32 buffCRC;
	ManagedReference<Buff*> buff;

	int duration = 60 * medicalDuration;

	buffName = "medical_enhance_health";
	buffCRC = buffName.hashCode();

	if (!player->hasBuff(buffCRC)) {
		buff = new Buff(player, buffCRC, duration, BuffType::MEDICAL);
		buff->setAttributeModifier(0, medicalBuff);
		player->addBuff(buff);
	}

	buffName = "medical_enhance_strength";
	buffCRC = buffName.hashCode();

	if (!player->hasBuff(buffCRC)) {
		buff = new Buff(player, buffCRC, duration, BuffType::MEDICAL);
		buff->setAttributeModifier(1, medicalBuff);
		player->addBuff(buff);
	}

	buffName = "medical_enhance_constitution";
	buffCRC = buffName.hashCode();

	if (!player->hasBuff(buffCRC)) {
		buff = new Buff(player, buffCRC, duration, BuffType::MEDICAL);
		buff->setAttributeModifier(2, medicalBuff);
		player->addBuff(buff);
	}

	buffName = "medical_enhance_action";
	buffCRC = buffName.hashCode();

	if (!player->hasBuff(buffCRC)) {
		buff = new Buff(player, buffCRC, duration, BuffType::MEDICAL);
		buff->setAttributeModifier(3, medicalBuff);
		player->addBuff(buff);
	}

	buffName = "medical_enhance_quickness";
	buffCRC = buffName.hashCode();

	if (!player->hasBuff(buffCRC)) {
		buff = new Buff(player, buffCRC, duration, BuffType::MEDICAL);
		buff->setAttributeModifier(4, medicalBuff);
		player->addBuff(buff);
	}

	buffName = "medical_enhance_stamina";
	buffCRC = buffName.hashCode();

	if (!player->hasBuff(buffCRC)) {
		buff = new Buff(player, buffCRC, duration, BuffType::MEDICAL);
		buff->setAttributeModifier(5, medicalBuff);
		player->addBuff(buff);
	}

	duration = 60 * performanceDuration;

	buffName = "performance_enhance_dance_mind";
	buffCRC = buffName.hashCode();

	if (!player->hasBuff(buffCRC)) {
		buff = new Buff(player, buffCRC, duration, BuffType::PERFORMANCE);
		buff->setAttributeModifier(6, performanceBuff);
		player->addBuff(buff);
	}

	buffName = "performance_enhance_music_focus";
	buffCRC = buffName.hashCode();

	if (!player->hasBuff(buffCRC)) {
		buff = new Buff(player, buffCRC, duration, BuffType::PERFORMANCE);
		buff->setAttributeModifier(7, performanceBuff);
		player->addBuff(buff);
	}

	buffName = "performance_enhance_music_willpower";
	buffCRC = buffName.hashCode();

	if (!player->hasBuff(buffCRC)) {
		buff = new Buff(player, buffCRC, duration, BuffType::PERFORMANCE);
		buff->setAttributeModifier(8, performanceBuff);
		player->addBuff(buff);
	}

	player->sendSystemMessage("An unknown force strengthens you for battles yet to come.");
}
