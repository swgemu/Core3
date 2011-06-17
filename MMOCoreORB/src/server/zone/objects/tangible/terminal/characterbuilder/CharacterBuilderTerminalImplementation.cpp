#include "CharacterBuilderTerminal.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/sui/characterbuilderbox/SuiCharacterBuilderBox.h"
#include "server/zone/managers/professions/ProfessionManager.h"
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

	ManagedReference<SuiCharacterBuilderBox*> sui = new SuiCharacterBuilderBox(player, rootNode);
	sui->setUsingObject(_this);

	player->sendMessage(sui->generateMessage());
	player->addSuiBox(sui);
}

bool CharacterBuilderTerminalImplementation::doEnhanceCharacter(uint32 crc, PlayerCreature* player, int amount, int duration, int buffType, uint8 attribute) {
	if (player == NULL)
		return false;

	if (player->hasBuff(crc))
		return false;

	ManagedReference<Buff*> buff = new Buff(player, crc, duration, buffType);
	buff->setAttributeModifier(attribute, amount);
	player->addBuff(buff);

	return true;
}

void CharacterBuilderTerminalImplementation::enhanceCharacter(PlayerCreature* player) {
	if (player == NULL)
		return;

	bool message = true;

	message = message && doEnhanceCharacter(0x98321369, player, medicalBuff, medicalDuration, BuffType::MEDICAL, 0); // medical_enhance_health
	message = message && doEnhanceCharacter(0x815D85C5, player, medicalBuff, medicalDuration, BuffType::MEDICAL, 1); // medical_enhance_strength
	message = message && doEnhanceCharacter(0x7F86D2C6, player, medicalBuff, medicalDuration, BuffType::MEDICAL, 2); // medical_enhance_constitution
	message = message && doEnhanceCharacter(0x4BF616E2, player, medicalBuff, medicalDuration, BuffType::MEDICAL, 3); // medical_enhance_action
	message = message && doEnhanceCharacter(0x71B5C842, player, medicalBuff, medicalDuration, BuffType::MEDICAL, 4); // medical_enhance_quickness
	message = message && doEnhanceCharacter(0xED0040D9, player, medicalBuff, medicalDuration, BuffType::MEDICAL, 5); // medical_enhance_stamina

	message = message && doEnhanceCharacter(0x11C1772E, player, performanceBuff, performanceDuration, BuffType::PERFORMANCE, 6); // performance_enhance_dance_mind
	message = message && doEnhanceCharacter(0x2E77F586, player, performanceBuff, performanceDuration, BuffType::PERFORMANCE, 7); // performance_enhance_music_focus
	message = message && doEnhanceCharacter(0x3EC6FCB6, player, performanceBuff, performanceDuration, BuffType::PERFORMANCE, 8); // performance_enhance_music_willpower

	if (message)
		player->sendSystemMessage("An unknown force strengthens you for battles yet to come.");
}

void CharacterBuilderTerminalImplementation::giveLanguages(PlayerCreature* player) {
	if (player == NULL)
		return;

	ProfessionManager* professionManager = server->getProfessionManager();

	professionManager->awardSkillBox("social_language_basic_speak", player, true, true);
	professionManager->awardSkillBox("social_language_basic_comprehend", player, true, true);
	professionManager->awardSkillBox("social_language_rodian_speak", player, true, true);
	professionManager->awardSkillBox("social_language_rodian_comprehend", player, true, true);
	professionManager->awardSkillBox("social_language_trandoshan_speak", player, true, true);
	professionManager->awardSkillBox("social_language_trandoshan_comprehend", player, true, true);
	professionManager->awardSkillBox("social_language_moncalamari_speak", player, true, true);
	professionManager->awardSkillBox("social_language_moncalamari_comprehend", player, true, true);
	professionManager->awardSkillBox("social_language_wookiee_speak", player, true, true);
	professionManager->awardSkillBox("social_language_wookiee_comprehend", player, true, true);
	professionManager->awardSkillBox("social_language_bothan_speak", player, true, true);
	professionManager->awardSkillBox("social_language_bothan_comprehend", player, true, true);
	professionManager->awardSkillBox("social_language_twilek_speak", player, true, true);
	professionManager->awardSkillBox("social_language_twilek_comprehend", player, true, true);
	professionManager->awardSkillBox("social_language_zabrak_speak", player, true, true);
	professionManager->awardSkillBox("social_language_zabrak_comprehend", player, true, true);
	professionManager->awardSkillBox("social_language_lekku_speak", player, true, true);
	professionManager->awardSkillBox("social_language_lekku_comprehend", player, true, true);
	professionManager->awardSkillBox("social_language_ithorian_speak", player, true, true);
	professionManager->awardSkillBox("social_language_ithorian_comprehend", player, true, true);
	professionManager->awardSkillBox("social_language_sullustan_speak", player, true, true);
	professionManager->awardSkillBox("social_language_sullustan_comprehend", player, true, true);
}
