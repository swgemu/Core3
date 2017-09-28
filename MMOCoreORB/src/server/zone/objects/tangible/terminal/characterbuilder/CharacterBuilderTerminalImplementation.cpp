#include "server/zone/objects/tangible/terminal/characterbuilder/CharacterBuilderTerminal.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/player/sui/characterbuilderbox/SuiCharacterBuilderBox.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "templates/tangible/CharacterBuilderTerminalTemplate.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/jedi/JediManager.h"
#include "server/zone/managers/director/DirectorManager.h"

void CharacterBuilderTerminalImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	CharacterBuilderTerminalTemplate* terminalData = dynamic_cast<CharacterBuilderTerminalTemplate*>(templateData);

	if (terminalData == NULL)
		return;

	rootNode = terminalData->getItemList();

	//info("loaded " + String::valueOf(itemList.size()));
}

void CharacterBuilderTerminalImplementation::initializeTransientMembers() {
	TerminalImplementation::initializeTransientMembers();

	setLoggingName("CharacterBuilderTerminal");
}

int CharacterBuilderTerminalImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	//info("entering start terminal radial call", true);

	if (selectedID != 20) // not use object
		return 1;

	sendInitialChoices(player);

	return 0;
}

void CharacterBuilderTerminalImplementation::sendInitialChoices(CreatureObject* player) {
	//info("entering sendInitialChoices", true);

	if (rootNode == NULL) {
		player->sendSystemMessage("There was an error initializing the menu for this character builder terminal. Sorry for the inconvenience.");
		return;
	}

	ManagedReference<SuiCharacterBuilderBox*> sui = new SuiCharacterBuilderBox(player, rootNode);
	sui->setUsingObject(_this.getReferenceUnsafeStaticCast());

	player->sendMessage(sui->generateMessage());
	player->getPlayerObject()->addSuiBox(sui);
}

void CharacterBuilderTerminalImplementation::enhanceCharacter(CreatureObject* player) {
	PlayerManager* pm = player->getZoneServer()->getPlayerManager();

	pm->enhanceCharacter(player);

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	for (int i = 0; i < ghost->getActivePetsSize(); i++) {
		ManagedReference<AiAgent*> pet = ghost->getActivePet(i);

		if (pet != NULL) {
			Locker crossLocker(pet, player);

			pm->enhanceCharacter(pet);
		}
	}
}

void CharacterBuilderTerminalImplementation::giveLanguages(CreatureObject* player) {
	SkillManager* skillManager = server->getSkillManager();

	skillManager->awardSkill("social_language_basic_speak", player, true, true, true);
	skillManager->awardSkill("social_language_basic_comprehend", player, true, true, true);
	skillManager->awardSkill("social_language_rodian_speak", player, true, true, true);
	skillManager->awardSkill("social_language_rodian_comprehend", player, true, true, true);
	skillManager->awardSkill("social_language_trandoshan_speak", player, true, true, true);
	skillManager->awardSkill("social_language_trandoshan_comprehend", player, true, true, true);
	skillManager->awardSkill("social_language_moncalamari_speak", player, true, true, true);
	skillManager->awardSkill("social_language_moncalamari_comprehend", player, true, true, true);
	skillManager->awardSkill("social_language_wookiee_speak", player, true, true, true);
	skillManager->awardSkill("social_language_wookiee_comprehend", player, true, true, true);
	skillManager->awardSkill("social_language_bothan_speak", player, true, true, true);
	skillManager->awardSkill("social_language_bothan_comprehend", player, true, true, true);
	skillManager->awardSkill("social_language_twilek_speak", player, true, true, true);
	skillManager->awardSkill("social_language_twilek_comprehend", player, true, true, true);
	skillManager->awardSkill("social_language_zabrak_speak", player, true, true, true);
	skillManager->awardSkill("social_language_zabrak_comprehend", player, true, true, true);
	skillManager->awardSkill("social_language_lekku_speak", player, true, true, true);
	skillManager->awardSkill("social_language_lekku_comprehend", player, true, true, true);
	skillManager->awardSkill("social_language_ithorian_speak", player, true, true, true);
	skillManager->awardSkill("social_language_ithorian_comprehend", player, true, true, true);
	skillManager->awardSkill("social_language_sullustan_speak", player, true, true, true);
	skillManager->awardSkill("social_language_sullustan_comprehend", player, true, true, true);
}

void CharacterBuilderTerminalImplementation::grantGlowyBadges(CreatureObject* player) {
	CharacterBuilderTerminalTemplate* terminalTemplate = dynamic_cast<CharacterBuilderTerminalTemplate*>(templateObject.get());

	if (terminalTemplate == NULL)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	Vector<int> ids = terminalTemplate->getGlowyBadgeIds();

	for (int i = 0; i < ids.size(); i++) {
		ghost->awardBadge(ids.get(i));
	}
}

void CharacterBuilderTerminalImplementation::grantJediInitiate(CreatureObject* player) {
	if (JediManager::instance()->getJediProgressionType() != JediManager::VILLAGEJEDIPROGRESSION)
		return;

	CharacterBuilderTerminalTemplate* terminalTemplate = dynamic_cast<CharacterBuilderTerminalTemplate*>(templateObject.get());

	if (terminalTemplate == NULL)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	SkillManager* skillManager = server->getSkillManager();

	grantGlowyBadges(player);

	Lua* lua = DirectorManager::instance()->getLuaInstance();

	Reference<LuaFunction*> luaVillageGmCmd = lua->createFunction("FsIntro", "completeVillageIntroFrog", 0);
	*luaVillageGmCmd << player;

	luaVillageGmCmd->callFunction();

	Vector<String> branches = terminalTemplate->getVillageBranchUnlocks();

	for (int i = 0; i < branches.size(); i++) {
		String branch = branches.get(i);
		player->setScreenPlayState("VillageUnlockScreenPlay:" + branch, 2);
		skillManager->awardSkill(branch + "_04", player, true, true, true);
	}

	luaVillageGmCmd = lua->createFunction("FsOutro", "completeVillageOutroFrog", 0);
	*luaVillageGmCmd << player;

	luaVillageGmCmd->callFunction();
}
